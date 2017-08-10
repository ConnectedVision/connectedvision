/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** HTTPSClientPoco.cpp
**
** written by Michael Rauter
** 
*******************************************************/

#include "HTTPSClientPoco.h"

#include <boost/thread/mutex.hpp>

#include <Poco/Foundation.h>
#include <Poco/Exception.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/PrivateKeyPassphraseHandler.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/Session.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/RejectCertificateHandler.h>
//#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/StreamCopier.h>

using namespace ConnectedVision::HTTP;

using namespace Poco;
using namespace Poco::Net;

class ConnectedVision::HTTP::PimplHTTPSClientPoco
{
public:
	Poco::Net::Context::Ptr pContext;

	class KeyHandler: public Poco::Net::PrivateKeyPassphraseHandler
	{
	private:

		std::string m_key;

	public:

		KeyHandler(std::string key) : PrivateKeyPassphraseHandler(true), m_key(key)
		{
		}

		virtual ~KeyHandler() 
		{
		}

		virtual void onPrivateKeyRequested(const void* pSender, std::string& privateKey) 
		{
			privateKey = m_key;
		}
	};

	class InvalidCertHandler: public Poco::Net::InvalidCertificateHandler
	{

	public:

	  InvalidCertHandler(void) : InvalidCertificateHandler(true)
	  {
	  }

	  virtual void onInvalidCertificate(const void* pSender, Poco::Net::VerificationErrorArgs& errorCert)
	  {
		std::cout << __FUNCTION__ << " called" << std::endl;
	  }

	};
};


HTTPSClientPoco::HTTPSClientPoco(HTTPSClientPoco::Params params)
{
	pImpl = new ConnectedVision::HTTP::PimplHTTPSClientPoco();
	
	//Poco::Path appName = "Connected_Vision";
	Poco::Path dirName = "";

	// Set constants similar to properties file
	Poco::Path caLocation(dirName, params.caLocation);
	Poco::Net::Context::VerificationMode verificationMode = Poco::Net::Context::VERIFY_RELAXED;
	int verificationDepth = 9;
	bool loadDefaultCAs = true;
	std::string cipherList = "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH";
	bool extendedVerification = false;
	bool cacheSessions = true;
	int sessionCacheSize = 100;
	Poco::Net::Context::Usage usage = Poco::Net::Context::CLIENT_USE;

	// Create SSL context 
	pImpl->pContext = new Poco::Net::Context(
		usage,
		caLocation.toString(),
		verificationMode,
		verificationDepth,
		loadDefaultCAs,
		cipherList
	);
			
	Poco::Net::SSLManager::PrivateKeyPassphraseHandlerPtr pKeyHandler = new PimplHTTPSClientPoco::KeyHandler(params.caPassword);

	//Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pInvalidCertHandler = new Poco::Net::AcceptCertificateHandler(false);
	//Poco::Net::SSLManager::InvalidCertificateHandlerPtr pInvalidCertHandler = new PimplHTTPSClientPoco::InvalidCertHandler;
	//SharedPtr<InvalidCertificateHandler> pInvalidCertHandler = new ConsoleCertificateHandler(false);
	SharedPtr<InvalidCertificateHandler> pInvalidCertHandler = new RejectCertificateHandler(false);		 
	Poco::Net::SSLManager::instance().initializeClient(pKeyHandler, pInvalidCertHandler, pImpl->pContext);
}

HTTPSClientPoco::~HTTPSClientPoco()
{
	delete(pImpl);
}

void HTTPSClientPoco::performRequest(const HTTPClientRequest &request, ConnectedVision::HTTP::HTTPResponse &response)
{
	try
	{
		// Initialize session
		Poco::URI uri(request.getUri());
		Poco::Net::HTTPSClientSession client_session(uri.getHost(), uri.getPort(), pImpl->pContext);

		//Poco::Net::SecureStreamSocket socket = client_session.socket();
		//if (socket.havePeerCertificate())
		//{
		//	X509Certificate cert = socket.peerCertificate();
		//	std::cout<<cert.issuerName()<<"\n"; 
		//}
		//else
		//{
		//	std::cout<<"No certificate\n";
		//}

		//bool blocking = client_session.socket().getBlocking();
		//client_session.socket().setBlocking(false);

		//Poco::Net::StreamSocket socket = client_session.socket();
		//bool reuseAddress = client_session.socket().getReuseAddress();
		//bool reusePort = client_session.socket().getReusePort();

		// Prepare and send request
		std::string path(uri.getPathAndQuery());
		Poco::Net::HTTPRequest requestPoco;

		std::string payload = "";

		switch (request.getMethod())
		{
		case ConnectedVision::HTTP::HTTP_Method_GET:
			requestPoco.setMethod(Poco::Net::HTTPRequest::HTTP_GET);
			break;
		case ConnectedVision::HTTP::HTTP_Method_PUT:
			requestPoco.setMethod(Poco::Net::HTTPRequest::HTTP_PUT);
			payload = request.getPayload();
			break;
		case ConnectedVision::HTTP::HTTP_Method_POST:
			//requestPoco.setMethod(Poco::Net::HTTPRequest::HTTP_POST);
			//requestPoco.set("payload", request.getPayload());
			throw HTTPClientException("error in HTTPSClientPoco::performRequest(...): method HTTP POST not implemented");
			break;
		case ConnectedVision::HTTP::HTTP_Method_DELETE:
			requestPoco.setMethod(Poco::Net::HTTPRequest::HTTP_DELETE);
			//requestPoco.set("payload", request.getPayload());
			break;
		case ConnectedVision::HTTP::HTTP_Method_HEAD:
			requestPoco.setMethod(Poco::Net::HTTPRequest::HTTP_HEAD);
			break;
		default:
			throw HTTPClientException("error in HTTPSClientPoco::performRequest(...): unknown HTTP method issued");
			break;
		};
		
		requestPoco.setURI(path);
		requestPoco.setVersion(Poco::Net::HTTPMessage::HTTP_1_1);

		if (!payload.empty())
		{
			requestPoco.setContentLength( payload.length() );
			client_session.sendRequest(requestPoco) << payload;
		}
		else
		{
			client_session.sendRequest(requestPoco);
		}

		// Get response
		Poco::Net::HTTPResponse responsePoco;
		std::istream& is = client_session.receiveResponse(responsePoco);

		std::string responseString;
		Poco::StreamCopier::copyToString(is, responseString);

		response.content.setContent(responseString);
		response.content.setContentType(responsePoco.getContentType());
		response.status = (ConnectedVision::HTTP::EnumHTTPStatus) ( responsePoco.getStatus() );

	} catch (Poco::Exception& e) {
		throw ConnectedVision::runtime_error("Exception in HTTPSClientPoco::performRequest(...): HTTPS request failed, reason: " + std::string(e.what()));		
	}
};
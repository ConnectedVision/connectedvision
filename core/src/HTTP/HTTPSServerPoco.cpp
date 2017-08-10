/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** HTTPSServerPoco.cpp
**
** written by Michael Rauter and Andi Zoufal
** 
*******************************************************/

#include "HTTPSServerPoco.h"

#include <IConnectedVisionModule.h>

#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <Poco/Net/HTMLForm.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <Poco/Net/NetworkInterface.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SecureServerSocket.h>

#include <Poco/Net/SSLManager.h>
#include <Poco/Net/PrivateKeyPassphraseHandler.h>

#include <Poco/Net/RejectCertificateHandler.h>

using namespace ConnectedVision::HTTP;

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;


// =============================================================================

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

// =============================================================================

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

HTTPSServerPoco::HTTPSServerPoco(HTTPSServerPoco::HttpsParams &httpsParams) : HTTPServerPoco()  {
	Poco::Path dirName = "";

    // Set constants similar to properties file
    Poco::Path privateKeyFile(dirName, httpsParams.privateKeyFile);
	Poco::Path certificateFile(dirName, httpsParams.certificateFile);
    Poco::Path caLocation(dirName, httpsParams.caLocation);
    Poco::Net::Context::VerificationMode verificationMode = Poco::Net::Context::VERIFY_RELAXED;
    int verificationDepth = 9;
    bool loadDefaultCAs = true;
    std::string cipherList = "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH";
    bool extendedVerification = false;
    bool cacheSessions = true;
    int sessionCacheSize = 100;
    Poco::Net::Context::Usage usage = Poco::Net::Context::SERVER_USE;

    // Init SSL globally
    Poco::Net::initializeSSL();

    // Create key and ivalid certificate handler instances first
    Poco::Net::SSLManager::PrivateKeyPassphraseHandlerPtr pKeyHandler = new KeyHandler(httpsParams.password);
    //Poco::Net::SSLManager::InvalidCertificateHandlerPtr pInvalidCertHandler = new InvalidCertHandler;
	//SharedPtr<InvalidCertificateHandler> pInvalidCertHandler = new ConsoleCertificateHandler(false);
	SharedPtr<InvalidCertificateHandler> pInvalidCertHandler = new RejectCertificateHandler(false);

    // Create SSL context 
    Poco::Net::Context::Ptr pContext = new Poco::Net::Context(
        usage,
        privateKeyFile.toString(),
        certificateFile.toString(),
        caLocation.toString(),
        verificationMode,
        verificationDepth,
        loadDefaultCAs,
        cipherList
    );
  
    // Extra features for the default context (important!)
    pContext->enableSessionCache(cacheSessions);
    pContext->setSessionCacheSize(sessionCacheSize);
    pContext->enableExtendedCertificateVerification(extendedVerification);

    // Init SSL Server manager default values
    Poco::Net::SSLManager::instance().initializeServer(
        pKeyHandler,
        pInvalidCertHandler,
        pContext
    );

};

HTTPSServerPoco::~HTTPSServerPoco() {
    // un-init SSL globally and return
    Poco::Net::uninitializeSSL();
}

Poco::Net::ServerSocket HTTPSServerPoco::createServerSocket(int port)
{
	Poco::Net::SecureServerSocket socket(port); // set-up a server socket
	return(socket);
}
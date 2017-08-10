/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <Poco/DigestStream.h>
#include <Poco/MD5Engine.h>

#include <rapidjson/document.h>

#include <general.h>
#include <helper.h>
#include "./Class_generic_config.h"

#include <boost/algorithm/string/trim.hpp>

using namespace std;
using namespace ConnectedVision;

static std::string removeWhitespaces(const std::string& src)
{
	string dst;
	bool escaped = false;
	bool string = false;
	dst.reserve( src.size() );
	for (unsigned int i = 0; i < src.size(); i++)
	{
		escaped = false;
		char ch = src[i];

		if ( ch == '\\' && !escaped )
			escaped = true;
		if ( ch == '"' && !escaped )
			string = !string;
		if ( ( ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' )
			|| string || escaped )
			dst += ch;
	}


	return dst;
}

Class_generic_config::Class_generic_config()
{
	clear();
}

Class_generic_config::Class_generic_config(const rapidjson::Value& value)
{
	clear();
	parseJson(value);
}

Class_generic_config::Class_generic_config(const std::string& str) : Stub_generic_config("")
{
	clear();
	parseJson(str);
};

std::string Class_generic_config::toJson() const
{
	return Stub_generic_config::toJson();
}

rapidjson::Value& Class_generic_config::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	Stub_generic_config::toJson(node, allocator);

	if ((node.HasMember("initialParams")) && (node.HasMember("params")))
	{
		if ((this->initialParams) && (this->params) && (*this->initialParams == *this->params))
		{
			if (!this->getconst_configFeatures()->getconst_allowDynamicParameters()) // only remove "initialParams" member for configs that do not allow dynamic parameters
			{
				node.RemoveMember("initialParams");
			}
		}
	}

	return node;
}

void Class_generic_config::parseJson(const char *str)
{
	Stub_generic_config::parseJson(str);
}

void Class_generic_config::parseJson(const rapidjson::Value& value)
{
	// parse config - default processing by base class implementation (from Stub_generic_config class)
	Stub_generic_config::parseJson(value);

	// if no initialParams object was provided
	if ((!value.HasMember("initialParams"))&&(value.HasMember("params")))
	{
		if (!value["params"].IsNull())
		{
			// copy params object into initParams object
			set_initialParams(boost::shared_ptr<std::string>(new std::string( jsonToStr(value["params"]))));
		}
		else
		{
			set_initialParams(boost::shared_ptr<std::string>(new std::string("{}")));
		}
	}
	// if no params object was provided
	else if ((value.HasMember("initialParams"))&&(!value.HasMember("params")))
	{
		if (!value["initialParams"].IsNull())
		{
			// copy initParams object into params object
			set_params(boost::shared_ptr<std::string>(new std::string( jsonToStr(value["initialParams"]))));
		}
		else
		{
			set_params(boost::shared_ptr<std::string>(new std::string("{}")));
		}
	}
	// if both initParams and params object are missing
	else if ((!value.HasMember("initialParams"))&&(!value.HasMember("params")))
	{
		// set empty object both for initParams and params object
		rapidjson::Value emptyObject;
		emptyObject.SetObject();
		set_initialParams(boost::shared_ptr<std::string>(new std::string( jsonToStr(emptyObject))));
		set_params(boost::shared_ptr<std::string>(new std::string( jsonToStr(emptyObject))));
	}
	// if both initParams and params object are provided
	else //else if ((value.HasMember("initialParams"))&&(value.HasMember("params")))
	{
		// create merged params object (params object becomes provided initParams object extended by changed/extra members of provided params object)
		rapidjson::Document doc;
		rapidjson::Value::AllocatorType &allocator = doc.GetAllocator();
		rapidjson::Value extendedObject;
		if ((!value["initialParams"].IsNull())&&(!value["params"].IsNull()))
		{
			rapidjson::Value extendedObject;
			extendJsonObject(value["initialParams"], value["params"], extendedObject, allocator);
			// set extendedObject as params object
			set_params(boost::shared_ptr<std::string>(new std::string( jsonToStr(extendedObject))));
		}
		else // no merging
		{
			// if null value in member "initialParams" -> make empty object
			if (value["initialParams"].IsNull())
			{
				rapidjson::Value emptyObject;
				emptyObject.SetObject();
				set_initialParams(boost::shared_ptr<std::string>(new std::string( jsonToStr(emptyObject))));
			}
			// if null value in member "params" -> make empty object
			if (value["params"].IsNull())
			{
				rapidjson::Value emptyObject;
				emptyObject.SetObject();
				set_params(boost::shared_ptr<std::string>(new std::string( jsonToStr(emptyObject))));
			}
		}
	}
}

ConnectedVision::id_t Class_generic_config::compute_id()
{
	Poco::MD5Engine md5;
	Poco::DigestOutputStream ostr(md5);
	
	string data;

	// moduleID
	data = get_moduleID();
	ostr << data;	

	// moduleURI
	data = *get_moduleURI();
	ostr << data;

	// configFeatures
	data = this->get_configFeatures()->toJson();
	ostr << data;

	// compact(no whitespaces) params JSON
	data = removeWhitespaces( *this->get_initialParams() );
	ostr << data;

	// configChainIDs of all configs in chain 
	const auto& chain = getconst_chain();
	for (auto it = chain->begin(); it != chain->end(); ++it)
	{
		const boost::shared_ptr<Class_generic_config_chain>& chainItem = *it;

		// configID
		rapidjson::Document json;
		if ( json.Parse<0>( chainItem->get_config()->c_str() ).HasParseError() )
			throw ConnectedVision::runtime_error( "parse error of JSON Object: " + *chainItem->get_config());
		data.clear();
		if ( json["id"].IsString() )
			data = json["id"].GetString();
		else
			throw ConnectedVision::runtime_error( "required member is missing: 'id' " + *chainItem->get_config());
		ostr << data;


		// loop through connections
		const auto& connections = chainItem->getconst_connections();
		for (auto connit = connections->begin(); connit != connections->end(); ++connit)
		{
			data = (*connit)->toJson();
			ostr << data;
		}
	}

	// compute MD5
	ostr.flush(); // Ensure everything gets passed to the digest engine
	const Poco::DigestEngine::Digest& digest = md5.digest(); // obtain result
	std::string result = Poco::DigestEngine::digestToHex(digest);

	set_id( strToID(result) );

	return get_id();
}

void Class_generic_config::setDynamicParameter(string name, string value)
{

}

boost::shared_ptr<Class_generic_config_chain> Class_generic_config::getSubConfigConnectionByInputPin( const pinID_t& pinID ) const
{
	const auto& chain = getconst_chain();

	pinID_t pinIdIndexed = getIndexedPinID(pinID);

	// search through config chain
	for (auto itChain = chain->begin(); itChain != chain->end(); ++itChain)
	{
		auto chainItem = *itChain;

		const auto& connections = chainItem->getconst_connections();
		
		// loop through all connections to find the corresponding pin
		for(auto itConnection = connections->begin(); itConnection != connections->end(); ++itConnection)
		{
			const pinID_t& connectionInputPinID = *((*itConnection)->getconst_inputPinID()); // typed (default index = 0) or indexed from connection (user input)
			pinID_t connectionInputPinIdIndexed = getIndexedPinID(connectionInputPinID);
			
			if(connectionInputPinIdIndexed == pinIdIndexed)
			{
				return chainItem;
			}
		}
	}

	return boost::shared_ptr<Class_generic_config_chain>();
}

std::string Class_generic_config::removeCommentsAndResolveReferencesInConfig(const std::string &config)
{
	// first remove comments
	char *stringBuffer = new char[config.size()	+ 1]; // + 1 for terminating 0
	int outputPosInBuffer = 0;
	bool inSingleLineComment = false;
	bool inMultipleLineComment = false;
	bool inString = false;
	for (int i=0; i<config.size(); i++)
	{
		bool inCommentThisIteration = inSingleLineComment | inMultipleLineComment;

		char currentChar = config.at(i);
		char nextChar = 0;
		if (i<config.size()-1)
		{
			nextChar = config.at(i+1);
		}

		if ( (!inCommentThisIteration)&& (currentChar == '"') ) // string opening/closing handling
		{
			inString = !inString;
		}

		if (!inString)
		{
			if ( (!inCommentThisIteration)&& (currentChar == '/') && (nextChar == '/') ) // single line comment start
			{
				inSingleLineComment = true;
				i+=2;
			}
			if ( (!inCommentThisIteration)&& (currentChar == '/') && (nextChar == '*') ) // multiple line comment start
			{
				inMultipleLineComment = true;
				i+=2;
			}

			if (inSingleLineComment) // handling for single line comment end and extension to next line
			{
				if ( (currentChar == 13) && (nextChar == 10) ) // windows handling
				{
					inSingleLineComment = false;					
				}
				else if ( (currentChar == 13) && (nextChar != 10) ) // mac handling
				{
					inSingleLineComment = false;
				}
				else if ( (currentChar == 10) ) // unix handling
				{
					inSingleLineComment = false;
				}

				if (currentChar == '\\') // extension to next line handling 
				{
					char charAfterNextChar = 0;
					if (i<config.size()-2)
					{
						charAfterNextChar = config.at(i+2);
					}

					if ( (nextChar == 13) && (charAfterNextChar == 10) ) // windows handling
					{
						i+=2;			
					}
					else if ( (nextChar == 13) && (charAfterNextChar != 10) ) // mac handling
					{
						i+=2;
					}
					else if ( (nextChar == 10) ) // unix handling
					{
						i++;
					}
				}
			}


			if ( (inMultipleLineComment) && (currentChar == '*') && (nextChar == '/') ) // handling for multiple line comment end
			{				
				inMultipleLineComment = false;
				i++;
			}
		}
		
		// only write to output string buffer if not in comment and not just switched from or to comment mode (which means current position (of this iteration) is a char of the comment control string
		if ( (!inCommentThisIteration) && (inCommentThisIteration == (inSingleLineComment | inMultipleLineComment)) )
		{
			stringBuffer[outputPosInBuffer++] = currentChar;
		}
	}
	stringBuffer[outputPosInBuffer] = 0; // c-string termination 0

	std::string processedConfig(stringBuffer);

	delete[](stringBuffer);


	// then resolve replacement defines

	bool singleLineReplacementFound = true; // make sure main loop starts
	bool multipleLineReplacementFound = true; // make sure main loop starts
	while ((singleLineReplacementFound)||(multipleLineReplacementFound)) // main loop
	{
		singleLineReplacementFound = false;
		multipleLineReplacementFound = false;
		bool inString = false;
		for (int i=0; i<processedConfig.size(); i++)
		{
			char currentChar = processedConfig.at(i);
			if (currentChar == '"')
			{
				inString = !inString;
			}
			else if (currentChar == '#') // a potential #define or #startdef keyword might start here
			{
				if (!singleLineReplacementFound)
				{
					const std::string matchStringDefineStart = "#startdef ";		
					size_t posFound = processedConfig.find(matchStringDefineStart, i);					
					if (posFound == i)
					{
						multipleLineReplacementFound = true; // make sure to search for further multiple line replacements (will signal the main loop to go on)
						size_t posReplacementStart = posFound + matchStringDefineStart.size();
						const std::string matchStringDefineEnd = "#enddef";
						size_t posPotentialReplacementEnd = processedConfig.find(matchStringDefineEnd, posReplacementStart);
						if (posPotentialReplacementEnd != std::string::npos)
						{							
							size_t len = posPotentialReplacementEnd - posReplacementStart + 1;
							std::string replacementString = processedConfig.substr(posReplacementStart, len - 1);

							bool inStringInReplacementString = false;
							for (int j=0; j<replacementString.size(); j++)
							{
								char current = replacementString.at(j);
								if (current == '"')
								{
									inStringInReplacementString = !inStringInReplacementString;
								}
								else if ( (!inStringInReplacementString) && ( (replacementString.find("#startdef ") == j) || (replacementString.find("#define ") == j) ) )
								{
									throw std::runtime_error("error in augmented config - recursive replacement defines are not allowed");
								}
							}

							// remove replacement define from config string
							processedConfig.erase(posFound, matchStringDefineStart.size() + len + matchStringDefineEnd.size());

							size_t posSeparator = replacementString.find_first_of(" \n");
							std::string replacementIdentifier = replacementString.substr(0, posSeparator);
							boost::trim_right(replacementIdentifier); // remove line ending characters or additional spaces
							std::string replacementValue = replacementString.substr(posSeparator+1);
							boost::trim_right(replacementValue); // remove line ending characters or additional spaces

							//replace all occurences of replacement references
							boost::replace_all(processedConfig, "$" + replacementIdentifier + "$", replacementValue);

							break; // important to leave loop over processedConfig.size() since processedConfig changed
						}
					}			
				}
				if (!multipleLineReplacementFound)
				{
					const std::string matchStringDefineStart = "#define ";		
					size_t posFound = processedConfig.find(matchStringDefineStart, i);
					if (posFound == i)
					{
						singleLineReplacementFound = true; // make sure to search for further single line replacements (will signal the main loop to go on)
						size_t posReplacementStart = posFound + matchStringDefineStart.size();
						size_t posPotentialReplacementEnd = processedConfig.find_first_of("\n", posReplacementStart);
						//if (posPotentialReplacementEnd != std::string::npos)
						{							
							size_t len = posPotentialReplacementEnd - posReplacementStart + 1;
							std::string replacementString = processedConfig.substr(posReplacementStart, len - 1);

							bool inStringInReplacementString = false;
							for (int j=0; j<replacementString.size(); j++)
							{
								char current = replacementString.at(j);
								if (current == '"')
								{
									inStringInReplacementString = !inStringInReplacementString;
								}
								else if ( (!inStringInReplacementString) && ( (replacementString.find("#startdef ") == j) || (replacementString.find("#define ") == j) ) )
								{
									throw std::runtime_error("error in augmented config - recursive replacement defines are not allowed");
								}
							}

							// remove replacement define from config string
							processedConfig.erase(posFound, matchStringDefineStart.size() + len);

							size_t posSeparator = replacementString.find_first_of(" ");
							std::string replacementIdentifier = replacementString.substr(0, posSeparator);
							boost::trim_right(replacementIdentifier); // remove line ending characters or additional spaces
							std::string replacementValue = replacementString.substr(posSeparator+1);
							boost::trim_right(replacementValue); // remove line ending characters or additional spaces

							//replace all occurences of replacement references
							boost::replace_all(processedConfig, "$" + replacementIdentifier + "$", replacementValue);

							break; // important to leave loop over processedConfig.size() since processedConfig changed
						}
					}
				}
			}
		}
	}	
	
	while (singleLineReplacementFound) // main loop
	{
		
		bool inString = false;
		for (int i=0; i<processedConfig.size(); i++)
		{
			char currentChar = processedConfig.at(i);
			if (currentChar == '"')
			{
				inString = !inString;
			}
			else if (currentChar == '#') // a potential #define keyword might start here
			{
			}
		}
	}
	
	return( processedConfig );
}

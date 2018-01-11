/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef general_def
#define general_def

#include <stdint.h>
#include <limits.h> // LLONG_MAX define
#include <stdio.h> // sprintf function
#include <stdexcept> // std::runtime_error
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <rapidjson/document.h>		// rapidjson's DOM-style API
#include <rapidjson/writer.h>	// for stringify JSON
#include <rapidjson/stringbuffer.h>

#if (_MSC_VER == 1600) // check for Visual Studio 2010
#define noexcept
#pragma warning( disable : 4290 )
#endif

namespace ConnectedVision
{
typedef std::string id_t;

#define ID_NULL ""
inline id_t strToID( const char *str ) { return std::string(str); };
inline id_t strToID( std::string &str ) { return str; };
//inline id_t strToID( std::string str ) { return str; };
inline const char * IDToChar( const id_t &id ) { return id.c_str(); };
inline std::string IDToStr( const id_t &id ) { return id; };

typedef std::string pinID_t;

typedef int64_t timestamp_t;
const int64_t TIMESTAMP_MAX = LLONG_MAX;

static std::string intToStr(int64_t i)
{
	return boost::lexical_cast<std::string>(i);
}

static std::string doubleToStr(double i)
{
	return boost::lexical_cast<std::string>(i);
}

inline std::string jsonToStr(const rapidjson::Value& node)
{
	if ( node.IsString() )
	{
		return( std::string("\"") + node.GetString() + std::string("\"") );
	}
	else if ( node.IsInt64() )
	{
		return( intToStr( node.GetInt64() ) );
	}
	else if ( node.IsNumber() )
	{
		return( doubleToStr( node.GetDouble() ) );
	}
	else if ( node.IsBool() )
	{
		return( intToStr( node.GetBool() ) );
	}
	else if ( node.IsObject() || node.IsArray() )
	{
		rapidjson::StringBuffer s;
		rapidjson::Writer<rapidjson::StringBuffer> writer(s);
		node.Accept(writer);
		return std::string(s.GetString());
	}

	throw std::runtime_error( "[jsonToStr] unsupported type: " + node.GetType() );
}

} // namespace ConnectedVision

#endif // general_def



/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// original author: Michael Rauter

#include <helper.h>
#include <Module/Control/Class_generic_config.h>

#include <CppUTest/TestHarness.h>

namespace ConnectedVision 
{

namespace Module 
{
	
const std::string jsonReference =
											"{ \"name\": \"ConfigPreprocessor json\","
											"\"description\": \"test json for ConfigPreprocessor\""											
											"}";

const std::string jsonReferenceWithStringWithCommentCharSequences =
											"{ \"name\": \"ConfigPreprocessor json\","
											"\"description\": \"test json for ConfigPreprocessor with // and /* */ in it\""											
											"}";

const std::string jsonReferenceWithUndefinedReference =
											"{ \"name\": \"ConfigPreprocessor $this reference does not exist$ json\","
											"\"description\": \"test json for ConfigPreprocessor\""											
											"}";

const std::string jsonWithSingleLineComments =
											"{"
											"\n// a single line comment\n"
											"\"name\": \"ConfigPreprocessor json\","
											"\n// another single line comment\n"
											"\"description\": \"test json for ConfigPreprocessor\" // and another one starting in the middle of a line\n"											
											"}";

const std::string jsonWithSingleLineCommentExpandedToNextLine =
											"{"
											"\"name\": \"ConfigPreprocessor json\","
											"\n// a single line comment\\expanded to the next line\n"
											"\"description\": \"test json for ConfigPreprocessor\""											
											"}";

const std::string jsonWithSingleLineCommentWithCommentedOutMultipleLineComment =
											"{"
											"\"name\": \"ConfigPreprocessor json\","
											"\n// a single line comment with a commented-out embedded /* char sequence\n"
											"\"description\": \"test json for ConfigPreprocessor\""											
											"}";

const std::string jsonWithSingleLineCommentAtEndOfString =
											"{"
											"\"name\": \"ConfigPreprocessor json\","
											"\"description\": \"test json for ConfigPreprocessor\""											
											"}"
											"\n// a single line comment at end of string";

const std::string jsonWithMultipleLineComments =
											"{"
											"\n/* a multiple\n *\n\n line comment */\n"
											"\"name\": \"ConfigPreprocessor json\","
											"\n/* another multiple\n *\n\n line comment without line end after closing comment syntax */"
											"\"description\": \"test json for ConfigPreprocessor\""											
											"}";

const std::string jsonWithMultipleLineCommentWithCommentedOutSingleLineComment =
											"{"
											"\"name\": \"ConfigPreprocessor json\","
											"\n/* a multiple\n *\n\n line comment with a commented-out embedded // char sequence */"
											"\"description\": \"test json for ConfigPreprocessor\""											
											"}";

const std::string jsonWithMultipleLineCommentAtEndOfString =
											"{"											
											"\"name\": \"ConfigPreprocessor json\","											
											"\"description\": \"test json for ConfigPreprocessor\""											
											"}"
											"/* a multiple\n *\n\n line comment without line end before and after comment at end of string */"
											;

const std::string jsonSingleLineReplacementDefine =
											"{ \"name\": \"ConfigPreprocessor $replacement$\","
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#define replacement json\n";

const std::string jsonSingleLineReplacementDefineAtEndOfString =
											"{ \"name\": \"ConfigPreprocessor $replacement$\","
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#define replacement json";

const std::string jsonSingleLineReplacementDefineButNoReference =
											"{ \"name\": \"ConfigPreprocessor json\","
											"\"description\": \"test json for ConfigPreprocessor\""											
											"}"
											"#define replacement json\n";

const std::string jsonNonExistingReplacementDefineReferenced =
											"{ \"name\": \"ConfigPreprocessor $this reference does not exist$ json\","
											"\"description\": \"test json for ConfigPreprocessor\""											
											"}"
											"#define replacement1 json\n"
											"#startdef replacement2\n test\ntest\n#enddef\n";

const std::string jsonMultipleLineReplacementDefine =
											"{ \"name\": \"ConfigPreprocessor $replacement$\","
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#startdef replacement\njson\n#enddef\n";

const std::string jsonMultipleLineReplacementDefineAlternative =
											"{ \"name\": \"ConfigPreprocessor $replacement$\","
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#startdef replacement json#enddef\n";

const std::string jsonMultipleLineReplacementDefineAtEndOfString =
											"{ \"name\": \"ConfigPreprocessor $replacement$\","
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#startdef replacement\njson\n#enddef";

const std::string jsonSingleLineReplacementDefineInReplacementDefineString =
											"{ \"name\": $nameReplacement$,"
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#define nameReplacement \"ConfigPreprocessor $replacement$\"\n"
											"#define replacement json\n";

const std::string jsonMultipleLineReplacementDefineInReplacementDefineString =
											"{ \"name\": $nameReplacement$,"
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#startdef nameReplacement\n\"ConfigPreprocessor $replacement$\"\n#enddef\n"
											"#startdef replacement json#enddef\n\n";

const std::string jsonRecursiveSingleLineReplacementShouldFail =
											"{ \"name\": $nameReplacement$,"
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#define nameReplacement #define replacement json\n";

const std::string jsonRecursiveMultipleLineReplacementShouldFail =
											"{ \"name\": $nameReplacement$,"
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#startdef nameReplacement #startdef replacement json#enddef #enddef\n";

const std::string jsonRecursiveSingleLineReplacementAlternativeShouldFail =
											"{ \"name\": $nameReplacement$,"
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#define nameReplacement #startdef replacement json#enddef\n";

const std::string jsonRecursiveMultipleLineReplacementAlternativeShouldFail =
											"{ \"name\": $nameReplacement$,"
											"\"description\": \"test $replacement$ for ConfigPreprocessor\""											
											"}"
											"#startdef nameReplacement #define replacement json\n#enddef\n";

TEST_GROUP(ConfigPreprocessor)
{
	void setup()
	{
		// Init stuff
	}

	void teardown()
	{
		// Uninit stuff
	}
};


/////////////////////////////////////////////////////////////// tests for config preprocessor (comments and replacement defines/references) ///////////////////////////////////////////////////////

// comments tests

TEST(ConfigPreprocessor, singleLineComments)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonWithSingleLineComments;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, singleLineCommentExpandedToNextLine)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonWithSingleLineCommentExpandedToNextLine;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, singleLineCommentWithCommentedOutMultipleLineComment)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonWithSingleLineCommentWithCommentedOutMultipleLineComment;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, singleLineCommentAtEndOfString)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonWithSingleLineCommentAtEndOfString;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, multipleLineComments)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonWithMultipleLineComments;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, multipleLineCommentWithCommentedOutSingleLineComment)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonWithMultipleLineCommentWithCommentedOutSingleLineComment;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, multipleLineCommentAtEndOfString)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonWithMultipleLineCommentAtEndOfString;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, stringWithCommentCharSequences)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonReferenceWithStringWithCommentCharSequences;
	std::string reference = jsonReferenceWithStringWithCommentCharSequences;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}


// replacement defines/references tests

TEST(ConfigPreprocessor, singleLineReplacementDefine)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonSingleLineReplacementDefine;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, singleLineReplacementDefineAtEndOfString)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonSingleLineReplacementDefineAtEndOfString;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, singleLineReplacementDefineButNoReference)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonSingleLineReplacementDefineButNoReference;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, nonExistingReplacementDefineReferenced)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonNonExistingReplacementDefineReferenced;
	std::string reference = jsonReferenceWithUndefinedReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, multipleLineReplacementDefine)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonMultipleLineReplacementDefine;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, multipleLineReplacementDefineAlternative)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonMultipleLineReplacementDefineAlternative;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, multipleLineReplacementDefineAtEndOfString)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonMultipleLineReplacementDefineAtEndOfString;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, singleLineReplacementDefineInReplacementDefineString)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonSingleLineReplacementDefineInReplacementDefineString;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, multipleLineReplacementDefineInReplacementDefineString)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonMultipleLineReplacementDefineInReplacementDefineString;
	std::string reference = jsonReference;
	// test
	std::string output = Class_generic_config::removeCommentsAndResolveReferencesInConfig(input);
	CHECK_EQUAL(trimStringAndRemoveSpaces(output), trimStringAndRemoveSpaces(reference));
}

TEST(ConfigPreprocessor, recursiveSingleLineReplacementShouldFail)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonRecursiveSingleLineReplacementShouldFail;
	std::string reference = jsonReference;
	// test
	CHECK_THROWS(std::runtime_error, Class_generic_config::removeCommentsAndResolveReferencesInConfig(input));
}

TEST(ConfigPreprocessor, recursiveMultipleLineReplacementShouldFail)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonRecursiveMultipleLineReplacementShouldFail;
	std::string reference = jsonReference;
	// test
	CHECK_THROWS(std::runtime_error, Class_generic_config::removeCommentsAndResolveReferencesInConfig(input));
}

TEST(ConfigPreprocessor, recursiveSingleLineReplacementAlternativeShouldFail)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonRecursiveSingleLineReplacementAlternativeShouldFail;
	std::string reference = jsonReference;
	// test
	CHECK_THROWS(std::runtime_error, Class_generic_config::removeCommentsAndResolveReferencesInConfig(input));
}

TEST(ConfigPreprocessor, recursiveMultipleLineReplacementAlternativeShouldFail)
{
	//////////////////////////////////////
	// test initialization
	std::string input = jsonRecursiveMultipleLineReplacementAlternativeShouldFail;
	std::string reference = jsonReference;
	// test
	CHECK_THROWS(std::runtime_error, Class_generic_config::removeCommentsAndResolveReferencesInConfig(input));
}


}} // namespace scope

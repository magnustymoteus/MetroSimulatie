#include "parser/Parser.h"
#include "tinyxml/tinyxml.h"
#include <gtest/gtest.h>

class ParserTest: public ::testing::Test {
protected:
    friend class Parser;
    Parser parser_;
    Parser parserHappyDay_ = Parser("tests/unit/Parser/configHappyDayTest.xml");
};

TEST_F(ParserTest, DefaultConstructor) {
    EXPECT_TRUE(parser_.properlyInitialized());
    EXPECT_FALSE(parser_.getSupportedTags().empty());
}
TEST_F(ParserTest, HappyDay) {
   EXPECT_TRUE(parserHappyDay_.properlyInitialized());
    std::map<std::string, std::vector<std::string> > expectedSupportedTags =
        {{"STATION", {"naam", "volgende", "vorige", "spoorNr"}},
        {"TRAM", {"lijnNr", "snelheid", "beginStation"}}};
    EXPECT_EQ(parserHappyDay_.getSupportedTags(), expectedSupportedTags);

    // ... to do
}


#include "parser/Parser.h"
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
   EXPECT_FALSE(parserHappyDay_.getSupportedTags().empty());
   // ... to do
}


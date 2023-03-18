//
// Created by gruzi on 18/03/2023.
//
#include <gtest/gtest.h>
#include "station/Station.h"

class StationDomainTest: public ::testing::Test {
protected:
    Station station_;
};

TEST_F(StationDomainTest, DefaultConstructor) {
    EXPECT_TRUE(station_.properlyInitialized());
    EXPECT_TRUE(station_.getNaam().empty());
    EXPECT_FALSE(station_.getVolgende());
    EXPECT_FALSE(station_.getVorige());
    EXPECT_EQ(station_.getSpoorNr(), 0);
}
TEST_F(StationDomainTest, SettersGetters) {
    EXPECT_TRUE(station_.properlyInitialized());
    const std::string name="naamTest";
    const int spoorNr = 17;
    EXPECT_NO_FATAL_FAILURE(station_.setNaam(name));
    EXPECT_NO_FATAL_FAILURE(station_.setSpoorNr(spoorNr));
    EXPECT_EQ(station_.getNaam(), name);
    EXPECT_EQ(station_.getSpoorNr(), spoorNr);
    EXPECT_FALSE(station_.getVorige());
    EXPECT_FALSE(station_.getVolgende());
}
//
// Created by gruzi on 18/03/2023.
//
#include <gtest/gtest.h>
#include "station/Station.h"

class StationDomainTest: public ::testing::Test {
protected:
};

TEST_F(StationDomainTest, DefaultConstructor) {
    Station station_("test_naam", "test_type", 12);
    EXPECT_TRUE(station_.properlyInitialized());
    EXPECT_EQ(station_.getNaam(), "test_naam");
    EXPECT_FALSE(station_.getVolgende());
    EXPECT_FALSE(station_.getVorige());
    EXPECT_EQ(station_.getSpoorNr(), 12);
    EXPECT_EQ(station_.getType(), "test_type");
}
TEST_F(StationDomainTest, SettersGetters) {
    Station station_("test_naam", "test_type", 11);
    const std::string name="naamTest";
    EXPECT_TRUE(station_.properlyInitialized());
    const int spoorNr = 17;
    EXPECT_NO_FATAL_FAILURE(station_.setNaam(name));
    EXPECT_NO_FATAL_FAILURE(station_.setSpoorNr(spoorNr));
    EXPECT_EQ(station_.getNaam(), name);
    EXPECT_EQ(station_.getSpoorNr(), spoorNr);
    EXPECT_FALSE(station_.getVorige());
    EXPECT_FALSE(station_.getVolgende());
}
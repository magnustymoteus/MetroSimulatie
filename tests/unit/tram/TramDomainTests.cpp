//
// Created by gruzi on 18/03/2023.
//
#include <gtest/gtest.h>
#include "Tram/Tram.h"

class TramDomainTest: public ::testing::Test {
protected:
};

//TEST_F(TramDomainTest, DefaultConstructor) {
//    Tram tram_(1,2,"test");
//    EXPECT_TRUE(tram_.properlyInitialized());
//
//    EXPECT_EQ(tram_.getLijnNr(), 1);
//    EXPECT_EQ(tram_.getSnelheid(), 0);
//    EXPECT_EQ(tram_.getVoertuigNr(), 2);
//    EXPECT_EQ(tram_.getType(), "test");
//
//    EXPECT_FALSE(tram_.getHuidigeStation());
//    EXPECT_FALSE(tram_.getBeginStation());
//}
//TEST_F(TramDomainTest, SettersGetters) {
//    Tram tram_(1,2,"test");
//    EXPECT_TRUE(tram_.properlyInitialized());
//    const int lijnNr=200, snelheid=90;
//    EXPECT_NO_FATAL_FAILURE(tram_.setSnelheid(snelheid));
//    EXPECT_NO_FATAL_FAILURE(tram_.setLijnNr(lijnNr));
//    EXPECT_EQ(tram_.getSnelheid(), snelheid);
//    EXPECT_EQ(tram_.getLijnNr(), lijnNr);
//    EXPECT_FALSE(tram_.getBeginStation());
//    EXPECT_FALSE(tram_.getHuidigeStation());
//}
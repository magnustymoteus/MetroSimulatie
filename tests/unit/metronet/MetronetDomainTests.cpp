//
// Created by gruzi on 17/03/2023.
//

#include <gtest/gtest.h>
#include "Metronet/Metronet.h"
#include "Tram/PCC.h"
#include "Tram/Albatros.h"
#include "Tram/Stadslijner.h"

class MetronetDomainTest: public ::testing::Test {
protected:
    Metronet metronet;
    Metronet metronet2;

    // Stations for metronet
    Station* station1 = new Station("A", "type");
    Station* station2 = new Station("B", "type");
    Station* station3 = new Station("C", "type");
    Station* station4 = new Station("D", "type");
    // Stations for metronet2
    Station* metrostation1 = new Station("M1", "Metrostation");
    Station* metrostation2 = new Station("M2", "Metrostation");
    Station* halte = new Station("H", "Halte");
    // Create Different types for metronet2
    std::vector<std::string > stationTypesVanPCC = {"Metrostation", "Halte"};
    std::vector<std::string > stationTypesVanAlbatros = {"Metrostation"};
    // Create trams for metronet2
    Tram* PCC_tram = new PCC(1, 1, 5, 10);
    Tram* Albatros_tram = new Albatros(1, 2);

    void setSporen(){
        station1->setSpoor(1, std::make_pair(station3, station2));
        station2->setSpoor(1, std::make_pair(station1, station3));
        station3->setSpoor(1, std::make_pair(station2, station1));
    }
    void setStations() {
        metronet.pushStation(station1);
        metronet.pushStation(station2);
        metronet.pushStation(station3);
    }
    Tram* tram1 = new Stadslijner(1,1);
    Tram* tram2 = new Stadslijner(1,2);
    void setTrams(){
        tram1->setBeginStation(station1);
        tram2->setBeginStation(station3);
        tram1->setHuidigeStation(station1);
        tram2->setHuidigeStation(station3);
        std::vector<std::string > bediendeStations;
        bediendeStations.push_back("type");
        metronet.pushTram(tram1);
        metronet.pushTram(tram2);
    }
    void setMetronet2(){
        // Add spoor to all stations
        metrostation1->setSpoor(1, std::make_pair(halte, metrostation2));
        metrostation2->setSpoor(1, std::make_pair(metrostation1, halte));
        halte->setSpoor(1, std::make_pair(metrostation2, metrostation1));
        // Set trams
        PCC_tram->setBeginStation(halte);
        PCC_tram->setHuidigeStation(halte);
        Albatros_tram->setBeginStation(metrostation1);
        Albatros_tram->setHuidigeStation(metrostation1);
        // Push everything to metronet2
        metronet2.pushStation(metrostation1);
        metronet2.pushStation(metrostation2);
        metronet2.pushStation(halte);
        metronet2.pushTram(PCC_tram);
        metronet2.pushTram(Albatros_tram);
    };
};
TEST_F(MetronetDomainTest, SettersGetters) {
    EXPECT_TRUE(metronet.properlyInitialized());
    EXPECT_TRUE(metronet.getStations().empty());
    EXPECT_TRUE(metronet.getTrams().empty());

    EXPECT_NO_THROW(setSporen());
    EXPECT_NO_THROW(setStations());

    EXPECT_EQ(station1->getVolgende(1), station2);
    EXPECT_EQ(station2->getVolgende(1), station3);
    EXPECT_EQ(station3->getVolgende(1), station1);
    EXPECT_EQ(station1->getVorige(1), station3);
    EXPECT_EQ(station3->getVorige(1), station2);
    EXPECT_EQ(station2->getVorige(1), station1);
    EXPECT_TRUE(metronet.properlyInitialized());
}
TEST_F(MetronetDomainTest, Push) {
    EXPECT_NO_THROW(setSporen());
    EXPECT_NO_THROW(setStations());
    EXPECT_EQ(metronet.getStations().size(), 3);
    EXPECT_EQ(station1->getSporen().size(), 1);
    EXPECT_EQ(station2->getSporen().size(), 1);
    EXPECT_EQ(station3->getSporen().size(), 1);

    EXPECT_NO_THROW(metronet.pushStation(station4));

    EXPECT_EQ(metronet.getStations().size(), 4);

    EXPECT_NO_THROW(metronet.pushSpoor("A", 17, std::make_pair(station4, station2)));
    EXPECT_NO_THROW(metronet.pushSpoor("B", 17, std::make_pair(station1, station3)));
    EXPECT_NO_THROW(metronet.pushSpoor("C", 17, std::make_pair(station2, station4)));
    EXPECT_NO_THROW(metronet.pushSpoor("D", 17, std::make_pair(station3, station1)));

    EXPECT_EQ(station1->getSporen().size(), 2);
    EXPECT_EQ(station2->getSporen().size(), 2);
    EXPECT_EQ(station3->getSporen().size(), 2);
    EXPECT_EQ(station4->getSporen().size(), 1);

    EXPECT_NO_THROW(setTrams());
    EXPECT_EQ(metronet.getTrams().size(), 2);
}

//TEST_F(MetronetDomainTest, MoveTrams){
//    EXPECT_NO_THROW(setSporen());
//    EXPECT_NO_THROW(setStations());
//    EXPECT_NO_THROW(setTrams());
//    EXPECT_NO_THROW(metronet.moveTram(tram1, 4));
//    EXPECT_NO_THROW(metronet.moveTram(tram2, 4));
//    EXPECT_EQ(tram1->getHuidigeStation(), station2);
//    EXPECT_EQ(tram2->getHuidigeStation(), station1);
//}
//TEST_F(MetronetDomainTest, AutoSimulatie){
//    EXPECT_NO_THROW(setSporen());
//    EXPECT_NO_THROW(setStations());
//    EXPECT_NO_THROW(setTrams());
//    EXPECT_NO_THROW(metronet.autoSimulate(3));
//}

TEST_F(MetronetDomainTest, RijdenVanTramsMetType){
    EXPECT_NO_THROW(setMetronet2());
}
TEST_F(MetronetDomainTest, RijdenVanTramsMetType2){
    EXPECT_NO_THROW(setMetronet2());
    EXPECT_NO_THROW(metronet2.moveTram(PCC_tram, 1));
    EXPECT_NO_THROW(metronet2.moveTram(Albatros_tram, 1));
}
TEST_F(MetronetDomainTest, RijdenVanTramsMetType3){
    EXPECT_NO_THROW(setMetronet2());
    EXPECT_NO_THROW(metronet2.moveTram(PCC_tram, 3));
    EXPECT_NO_THROW(metronet2.moveTram(Albatros_tram, 3));
}
TEST_F(MetronetDomainTest, RijdenVanTramsMetType4){
    EXPECT_NO_THROW(setMetronet2());
    EXPECT_NO_THROW(metronet2.moveTram(PCC_tram, 3));
    EXPECT_NO_THROW(metronet2.moveTram(Albatros_tram, 3));
    EXPECT_EQ(PCC_tram->getHuidigeStation(), halte);
    EXPECT_EQ(Albatros_tram->getHuidigeStation(), metrostation2);
}
TEST_F(MetronetDomainTest, DefectenEnReparaties){
    EXPECT_NO_THROW(setSporen());
    EXPECT_NO_THROW(setStations());
    EXPECT_NO_THROW(setTrams());
    EXPECT_EQ(tram1->getAantalDefecten(), 0);
    EXPECT_EQ(tram2->getAantalDefecten(), 0);
}
TEST_F(MetronetDomainTest, DefectenEnReparaties2){
    EXPECT_NO_THROW(setSporen());
    EXPECT_NO_THROW(setStations());
    EXPECT_NO_THROW(setTrams());
    EXPECT_EQ(tram1->getReparatieTijd(), 0);
    EXPECT_EQ(tram2->getReparatieTijd(), 0);
}
TEST_F(MetronetDomainTest, DefectenEnReparaties3){
    EXPECT_NO_THROW(setMetronet2());
    EXPECT_NO_THROW(metronet2.autoSimulate(5));
    EXPECT_EQ(PCC_tram->getHuidigeStation(), metrostation2);
}
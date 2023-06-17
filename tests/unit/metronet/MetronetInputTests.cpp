#include "Metronet/MetronetImporter.h"
#include "tinyxml/tinyxml.h"
#include <gtest/gtest.h>
#include <sstream>

const std::string filePath = "tests/unit/metronet/";

class MetronetInputTest: public ::testing::Test {
protected:
    MetronetImporter importer_;
};

TEST_F(MetronetInputTest, DefaultConstructor) {
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_FALSE(importer_.getSupportedTags().empty());
}
TEST_F(MetronetInputTest, ConfigPath) {
    const std::string configPath = filePath+"configs/configConfigPathTest.xml";
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_EQ(importer_.getConfigPath(), "");
    EXPECT_NO_THROW(importer_.setConfigPath(configPath));
    EXPECT_EQ(importer_.getConfigPath(), configPath);
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, HappyDay) {
    const std::string configPath = filePath+"configs/configHappyDayTest.xml";
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.setConfigPath(configPath));
    EXPECT_EQ(importer_.getConfigPath(), configPath);
    std::map<std::string, std::vector<std::string> > expectedSupportedTags =
        {{"STATION", {"naam", "volgende", "vorige", "spoorNr"}},
        {"TRAM", {"lijnNr", "snelheid", "beginStation"}}};
    EXPECT_EQ(importer_.getSupportedTags(), expectedSupportedTags);
    Metronet* Metronet = importer_.parseFile(filePath+"input/happydayTest.xml");
    EXPECT_TRUE(Metronet->spoorExists(12));
    EXPECT_TRUE(Metronet->tramExists(12));

    EXPECT_TRUE(Metronet->retrieveStation("A"));
    EXPECT_TRUE(Metronet->retrieveStation("B"));
    EXPECT_TRUE(Metronet->retrieveStation("C"));
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, IllegalTag) {
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.setConfigPath(filePath+"configs/configIllegalTagTest.xml"));
    EXPECT_TRUE(importer_.properlyInitialized());
    std::map<std::string, std::vector<std::string> > expectedSupportedTags =
            {{"LEGAL_TAG", {"legal_property_1", "legal_property_2"}}};
    EXPECT_EQ(importer_.getSupportedTags(), expectedSupportedTags);
    const std::string illTag = "ILLEGAL_TAG";
    const std::string lTag = "LEGAL_TAG";
    EXPECT_FALSE(importer_.isTagSupported(illTag));
    EXPECT_DEATH(importer_.isPropertySupported(illTag, "some_property"),
                 "Tag name expected to be supported!");

    EXPECT_TRUE(importer_.isTagSupported(lTag));
    EXPECT_FALSE(importer_.isPropertySupported(lTag, "some_property"));
    EXPECT_TRUE(importer_.isPropertySupported(lTag, "legal_property_1"));
    EXPECT_TRUE(importer_.isPropertySupported(lTag, "legal_property_2"));
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, XMLSyntaxErrors) {
    EXPECT_TRUE(importer_.properlyInitialized());
    const std::string configPath = filePath+"configs/configXMLSyntaxErrorsTest.xml";
    EXPECT_DEATH(importer_.parseFile(filePath+"input/XMLSyntaxErrorsTest.xml"),
                 "File expected to be loaded!");
    EXPECT_DEATH(importer_.setConfigPath(configPath), "Config file expected to be loaded!");
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, DifferentTagsOrder) {
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.parseFile(filePath+"input/differentTagsOrderTest.xml"));
    EXPECT_TRUE(importer_.properlyInitialized());
}

TEST_F(MetronetInputTest, ReadTramsAndStationsTypes){
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml"));
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, ReadTramsAndStationsTypes2){
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml"));
    Metronet* metronet = importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml");
    EXPECT_EQ(metronet->getStations().size(), 3);
    EXPECT_EQ(metronet->getTrams().size(), 3);
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, ReadTramsAndStationsTypes3){
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml"));
    Metronet* metronet = importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml");
    EXPECT_TRUE(metronet->getIsConsistent());
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, ReadTramsAndStationsTypes4){
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml"));
    Metronet* metronet = importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml");
    EXPECT_NO_THROW(metronet->autoSimulate(3));
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, ReadTramsAndStationsTypes5){
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml"));
    Metronet* metronet = importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml");
    EXPECT_TRUE(metronet->tramExists(12));
    EXPECT_TRUE(metronet->tramExists(21));
    EXPECT_FALSE(metronet->tramExists(666));
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, TramNr){
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml"));
    Metronet* metronet = importer_.parseFile(filePath+"input/readTramsAndStationsTypesTest.xml");
    EXPECT_TRUE(metronet->getIsConsistent());
    EXPECT_NO_THROW(metronet->getTrams());
    std::multimap<int, Tram *> trams = metronet->getTrams();
    for(std::multimap<int, Tram *>::iterator tramIterator = trams.begin(); tramIterator != trams.end(); tramIterator++){
        EXPECT_TRUE(tramIterator->second->getVoertuigNr() == 1 || tramIterator->second->getVoertuigNr() == 3);
    }
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, MeerdereSporen){
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.parseFile(filePath+"input/MeerdereSporenTest.xml"));
    EXPECT_TRUE(importer_.properlyInitialized());
}
TEST_F(MetronetInputTest, MeerdereSporen2){
    EXPECT_TRUE(importer_.properlyInitialized());
    EXPECT_NO_THROW(importer_.parseFile(filePath+"input/MeerdereSporenTest.xml"));
    Metronet* metronet = importer_.parseFile(filePath+"input/MeerdereSporenTest.xml");
    EXPECT_NO_THROW(metronet->getStations());
    std::map<std::string, Station*> stations = metronet->getStations();
    for(std::map<std::string, Station*>::iterator stationIterator = stations.begin(); stationIterator != stations.end();
                                                                                    stationIterator++){
        EXPECT_EQ(stationIterator->second->getSporen().size(), 2);
    }
    EXPECT_TRUE(importer_.properlyInitialized());
}
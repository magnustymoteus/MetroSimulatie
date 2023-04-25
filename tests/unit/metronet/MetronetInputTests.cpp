#include "metronet/MetronetImporter.h"
#include "tinyxml/tinyxml.h"
#include <gtest/gtest.h>
#include <sstream>

const std::string filePath = "tests/unit/Metronet/";

/*class MetronetInputTest: public ::testing::Test {
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
    EXPECT_EQ(importer_.getConfigPath(), "components/Metronet/config_metronet.xml");
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
    Metronet Metronet = importer_.parseFile(filePath+"input/happydayTest.xml");
    EXPECT_TRUE(Metronet.spoorExists(12));
    EXPECT_TRUE(Metronet.tramExists(12));

    EXPECT_TRUE(Metronet.retrieveStation(12, "A"));
    EXPECT_TRUE(Metronet.retrieveStation(12, "B"));
    EXPECT_TRUE(Metronet.retrieveStation(12, "C"));
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
}*/
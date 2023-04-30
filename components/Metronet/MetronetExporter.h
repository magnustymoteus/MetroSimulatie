//
// Created by gruzi on 17/03/2023.
//

#ifndef PROJECT_SOFTWARE_PRACTICUM2_METRONETEXPORTER_H
#define PROJECT_SOFTWARE_PRACTICUM2_METRONETEXPORTER_H

#include "Metronet/Metronet.h"

/**
 * @brief This serves as an exporter for an instance of Metronet which outputs information to a text file.
 * @author Patryk Pilichowski
 * @author Daria Matviichuk
 * @date 17/03/2023
 * @version 0.1
 */

class MetronetExporter {
private:
    MetronetExporter* _initCheck;
public:
    bool properlyInitialized() const;
    /**
    * @brief Constructor of MetronetExporter
    */
    MetronetExporter();

    /**
    * @brief Outputs information of a Metronet instance to a .txt file.
     * @param metronet The Metronet instance
     * @param pathFile The file path where the text file must be outputted to.
    */
    static void output(const Metronet* const &metronet, const std::string &pathFile);
    /**
    * @brief Outputs information of a Metronet instance in an "advanced" manner to a .txt file.
     * @param metronet The Metronet instance
     * @param pathFile The file path where the text file must be outputted to.
    */
    static void outputAdvanced(const Metronet* const &metronet, const std::string &pathFile);
};


#endif //PROJECT_SOFTWARE_PRACTICUM2_METRONETEXPORTER_H

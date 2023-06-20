//
// Created by dasha on 18.06.2023.
//

#ifndef METROSIMULATIE_UTILS_H
#define METROSIMULATIE_UTILS_H
#include <sstream>
#include <dirent.h>
#include <cstring>


/**
    * @brief Outputs information of the given line
     * @param lijn Line to print
    */
template<typename T>
inline void print(const T& lijn) {
    std::ostringstream oss;
    oss << lijn;
    std::cout << oss.str();
}
inline int getFileCount(const char* folderPath) {
    const char* extension = ".ini";
    DIR* directory = opendir(folderPath);
    if (directory == NULL) {
        std::cerr << "Failed to open directory." << std::endl;
        return -1;
    }

    int fileCount = 0;
    struct dirent* entry;
    while ((entry = readdir(directory)) != NULL) {
        if (entry->d_type == DT_REG) {  // Regular file
            const char* fileExtension = strrchr(entry->d_name, '.');
            if (fileExtension != NULL && strcmp(fileExtension, extension) == 0) {
                fileCount++;
            }
        }
    }

    closedir(directory);

    return fileCount;
}

std::string intToString(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

int getIndex(std::map<std::string,Station*> stations, Station* station){
    int i = 0;
    for(std::map<std::string,Station*>::const_iterator it = stations.begin(); it != stations.end(); ++it){
        if(it->second == station) break;
        i++;
    }
    return i;
}

#endif //METROSIMULATIE_UTILS_H

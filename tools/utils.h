//
// Created by dasha on 18.06.2023.
//

#ifndef METROSIMULATIE_UTILS_H
#define METROSIMULATIE_UTILS_H
#include <sstream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif


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
int getFileCount(const std::string& directoryPath) {
    int fileCount = 0;

#ifdef _WIN32
    WIN32_FIND_DATA findData;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    std::string searchPath = directoryPath + "\\*";

    hFind = FindFirstFile(searchPath.c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                fileCount++;
            }
        } while (FindNextFile(hFind, &findData) != 0);

        FindClose(hFind);
    }
#else
    DIR* dir;
    struct dirent* entry;

    dir = opendir(directoryPath.c_str());

    if (dir != 0) {
        while ((entry = readdir(dir)) != 0) {
            if (entry->d_type == DT_REG) {
                fileCount++;
            }
        }

        closedir(dir);
    }
#endif

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

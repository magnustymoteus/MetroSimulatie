//
// Created by gruzi on 12/03/2023.
//

#include "Metronet.h"

Metronet::Metronet(std::map<int, Station*> &newSporen, std::map<int, Tram*> &newTrams) : fSporen(newSporen),
fTrams(newTrams)
{}
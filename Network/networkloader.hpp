#pragma once

#include <iostream>
#include <fstream>
#include "network.hpp"

//load in a network
Network loadNetwork(std::string path);

//store a network
void storeNetwork(std::string path, Network* network);
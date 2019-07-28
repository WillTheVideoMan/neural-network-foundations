#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "data.hpp"

//loads the MNIST training data
DataSet<NumberData> loadMNISTTraining(bool showProgress, int start, int size);

//load in all the MNIST training data
DataSet<NumberData> loadMNISTTraining(bool showProgress);

//loads the MNIST test data
DataSet<NumberData> loadMNISTTest(bool showProgress, int start, int size);

//load in all the MNIST test data
DataSet<NumberData> loadMNISTTest(bool showProgress);

//this method loads in the data from the MNIST database
DataSet<NumberData> loadMNIST(bool showProgress, std::string path, int start, int size);
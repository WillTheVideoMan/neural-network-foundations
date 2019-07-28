#pragma once

#include "network.hpp"

//// __ Stochastic Gradient Descent using CPU __ ////

//sgd algorithm for training the neural network
void stochasticDescentCPU(Network* net, int epochs, int miniBatchSize, double learnRate, DataSet<NumberData>* trainingData, DataSet<NumberData>* testData);

//applies sgd using backprop to a mini batch
void updateMiniBatch(Network* net, DataSet<NumberData>* miniBatch, double learnRate);

//backpropegation algorithm for calculating the gradient of the cost function
void backpropagation(Network* net, Matrix* dgradw, Vector* dgradb, Vector* image, Vector* result);


//// __ Stochastic Gradient Descent using GPU __ ////

void __host__ stochasticDescentGPU();
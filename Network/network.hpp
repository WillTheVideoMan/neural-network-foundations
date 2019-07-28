#pragma once

#include "matrix.hpp"
#include "costfunctions.hpp"
#include "data.hpp"

class Classifier {
public:
  //has the ability to classify a single image in vector form
  virtual int classify(Vector image) = 0;

  //has the ability to evaluate a set of data
  virtual int evaluate(DataSet<NumberData> testData) = 0;
};

class Network : public Classifier {
protected:
  int layerCount;
  int* layers;

  Matrix* weights;
  Vector* biases;

public:

  //initialise the neural network with random weights and biases
  Network(int* layers, int layerCount);

  //initialise the neural network by loading in weights and biases
  Network(int* layers, int layerCount, Matrix* weights, Vector* biases);

  //method that gets output for input x for current weights and biases
  Vector feedForward(Vector x);

  //return the number of pieces of data in the test data correctly evaluated
  int evaluate(DataSet<NumberData> testData);

  //classify this image with current weights and biases
  int classify(Vector image);

  //getters and setters
  int getLayerCount();

  int* getLayers();

  Matrix* getWeights();

  Vector* getBiases();
};
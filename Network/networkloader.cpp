#include "networkloader.hpp"

Network loadNetwork(std::string path) {
  int* layers = nullptr;
  Vector* biases = nullptr;
  Matrix* weights = nullptr;

  const std::string networksPath = "../data/networks/" + path;
  std::ifstream loader(networksPath, std::ifstream::binary);

  if (!loader.is_open())
    std::cout << "\nError: failed to load network\n";

  char* buffer = new char[8];

  //get layer count
  int layerCount = 0;
  loader.read(buffer, sizeof(int));
  memcpy(&layerCount, buffer, sizeof(int));

  //get layers
  layers = new int[layerCount]();
  for (int i = 0; i < layerCount; i++) {
    loader.read(buffer, sizeof(int));
    memcpy(&layers[i], buffer, sizeof(int));
  }

  //get biases
  biases = new Vector[layerCount - 1];
  for (int i = 0; i < layerCount - 1; i++) {
    biases[i] = Vector(layers[i + 1]);

    for (int j = 0; j < layers[i + 1]; j++) {
      loader.read(buffer, sizeof(double));
      memcpy(&biases[i][j], buffer, sizeof(double));
    }
  }

  //get weights
  weights = new Matrix[layerCount - 1];
  for (int i = 0; i < layerCount - 1; i++) {
    weights[i] = Matrix(layers[i + 1], layers[i]);

    for (int j = 0; j < layers[i + 1]; j++) {
      for (int k = 0; k < layers[i]; k++) {
        loader.read(buffer, sizeof(double));
        memcpy(&weights[i](j, k), buffer, sizeof(double));
      }
    }
  }

  delete[] buffer;
  loader.close();

  return Network(layers, layerCount, weights, biases);
}

void storeNetwork(std::string path, Network* network) {

  const std::string networksPath = "../data/networks/" + path;
  std::ofstream writer(networksPath, std::ofstream::binary);

  if (!writer.is_open())
    std::cout << "\nError: failed to store network\n";

  char* buffer = new char[8];

  int layerCount = network->getLayerCount();

  //write amount of layers first
  memcpy(buffer, (char*)&layerCount, sizeof(int));
  writer.write(buffer, sizeof(int));

  //write in the layers
  for (int i = 0; i < layerCount; i++) {
    memcpy(buffer, (char*)(&network->getLayers()[i]), sizeof(int));
    writer.write(buffer, sizeof(int));
  }

  //write in the biases
  for (int i = 0; i < layerCount - 1; i++) {
    for (int j = 0; j < network->getLayers()[i + 1]; j++) {
      memcpy(buffer, (char*)(&network->getBiases()[i][j]), sizeof(double));
      writer.write(buffer, sizeof(double));
    }
  }

  //write in the weights
  for (int i = 0; i < layerCount - 1; i++) {
    for (int j = 0; j < network->getLayers()[i + 1]; j++) {
      for (int k = 0; k < network->getLayers()[i]; k++) {
        memcpy(buffer, (char*)(&network->getWeights()[i](j,k)), sizeof(double));
        writer.write(buffer, sizeof(double));
      }
    }
  }

  delete[] buffer;

  writer.close();
}
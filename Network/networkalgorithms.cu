#include "networkalgorithms.cuh"

//// __ Stochastic Gradient Descent using CPU __ ////

//sgd algorithm for training the neural network on the CPU
void stochasticDescentCPU(Network* net, int epochs, int miniBatchSize, double learnRate, DataSet<NumberData>* trainingData, DataSet<NumberData>* testData) {

  //run each epoch of training
  for (int i = 0; i < epochs; i++) {
    int batchCount = trainingData->getSize() / miniBatchSize;
    DataSet<NumberData>* miniBatches = trainingData->randomise().split(miniBatchSize);

    //update mini batches
    for (int j = 0; j < batchCount; j++) {
      updateMiniBatch(net, &miniBatches[j], learnRate);
    }

    delete[] miniBatches;

    //test the current weights and biases against the test data
    if (testData != nullptr) {
      std::cout << net->evaluate(*testData) << "/" << testData->getSize() << " numbers correctly classified\n";
    }
    std::cout << "Epoch " << i << " complete\n";
  }
}

//applies sgd using backprop to a mini batch
void updateMiniBatch(Network* net, DataSet<NumberData>* miniBatch, double learnRate) {

  Matrix* gradw = new Matrix[net->getLayerCount() - 1]();
  Vector* gradb = new Vector[net->getLayerCount() - 1]();

  Matrix* dgradw = new Matrix[net->getLayerCount() - 1]();
  Vector* dgradb = new Vector[net->getLayerCount() - 1]();

  for (int j = 0; j < net->getLayerCount() - 1; j++) {
    gradw[j] = Matrix(net->getWeights()[j].rows(), net->getWeights()[j].cols());
    gradb[j] = Vector(net->getBiases()[j].size());
  }

  //for each piece of training data
  for (int i = 0; i < miniBatch->getSize(); i++) {

    for (int j = 0; j < net->getLayerCount() - 1; j++) {
      dgradw[j] = Matrix(net->getWeights()[j].rows(), net->getWeights()[j].cols());
      dgradb[j] = Vector(net->getBiases()[j].size());
    }

    backpropagation(net, dgradw, dgradb, &(*miniBatch)[i].getData(), &(*miniBatch)[i].getResult());

    for (int j = 0; j < net->getLayerCount() - 1; j++) {
      gradw[j] += dgradw[j];
      gradb[j] += dgradb[j];
    }
  }

  for (int j = 0; j < net->getLayerCount() - 1; j++) {
    net->getWeights()[j] += gradw[j] * (-learnRate / (double)miniBatch->getSize());
    net->getBiases()[j] += gradb[j] * (-learnRate / (double)miniBatch->getSize());
  }

  delete[] gradw;
  delete[] gradb;
  delete[] dgradw;
  delete[] dgradb;
}

//backpropegation algorithm for calculating the gradient of the cost function
void backpropagation(Network* net, Matrix* dgradw, Vector* dgradb, Vector* image, Vector* result) {
  int layerCount = net->getLayerCount();

  Vector* As = new Vector[layerCount](); //activations
  Vector* Zs = new Vector[layerCount - 1](); //pre sigmoid activations

  //get activations of layers
  As[0] = *image;

  for (int i = 0; i < layerCount - 1; i++) {
    Zs[i] = net->getWeights()[i] * As[i] + net->getBiases()[i];
    As[i + 1] = Sigmoid::f(Zs[i]);
  }

  //backwards pass
  Vector delta = CrossEntropyCost::finalError(Zs[layerCount - 2], As[layerCount - 1], *result);

  dgradb[layerCount - 2] = delta;
  dgradw[layerCount - 2] = Matrix::toRowMat(delta) * Matrix::toColMat(As[layerCount - 2]);

  for (int i = 2; i < layerCount; i++) {
    delta = (net->getWeights()[layerCount - i].transpose() * delta).schur(Sigmoid::fPrime(Zs[layerCount - i - 1]));
    dgradb[layerCount - i - 1] = delta;
    dgradw[layerCount - i - 1] = Matrix::toRowMat(delta) * Matrix::toColMat(As[layerCount - i - 1]);
  }

  delete[] As;
  delete[] Zs;
}

//// __ Stochastic Gradient Descent using GPU __ ////
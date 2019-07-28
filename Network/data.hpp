#pragma once

#include <vector>
#include "vector.hpp"

class DataElement {
protected:

  //the vectorised data
  Vector data;

public:

  //retrieve the data
  Vector getData();

  //get the ideal output for this data
  virtual Vector getResult() = 0;
};

class NumberData : public DataElement {
protected:

  //the number the data represents
  int number;

public:

  //construct a new numebr data piece
  NumberData(Vector image, int number);
  
  NumberData();

  //get vectorised result
  Vector getResult();

  int getNumber() { return number; }
};

template <typename D>
class DataSet {
private:
  std::vector<D> data;
  int size;

public:
  DataSet(int size);

  DataSet();

  D& operator[](int i);

  DataSet<D> randomise();

  DataSet<D>* split(int newSize);

  int getSize() { return size; };
};

template <typename D>
DataSet<D>::DataSet(int size) {
  this->size = size;
  this->data = std::vector<D>(size);
}

template <typename D>
DataSet<D>::DataSet() {}

template <typename D>
D& DataSet<D>::operator[](int i) {
  return data[i];
}

template <typename D>
DataSet<D> DataSet<D>::randomise() {

  int seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> uniform(0, 10000000);

  int i = size;
  while (1 < i) {
    int j = uniform(generator) % i--;
    D temp = data[i];
    data[i] = data[j];
    data[j] = temp;
  }

  return *this;
}

template <typename D>
DataSet<D>* DataSet<D>::split(int newSize) {
  int batchCount = size / newSize;

  DataSet<D>* batches = new DataSet<D>[batchCount]();

  for (int i = 0; i < batchCount; i++) {
    batches[i] = DataSet<D>(newSize);

    for (int j = 0; j < newSize; j++) {
      int index = i * newSize + j;
      batches[i][j] = data[index];
    }
  }
  return batches;
}
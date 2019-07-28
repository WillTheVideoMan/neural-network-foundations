#include "data.hpp"

Vector DataElement::getData() {
  return data;
}

NumberData::NumberData(Vector image, int number) {
  this->data = image;
  this->number = number;
}

NumberData::NumberData() {}

Vector NumberData::getResult() {
  Vector result = Vector(10);
  result[number] = 1;
  return result;
}
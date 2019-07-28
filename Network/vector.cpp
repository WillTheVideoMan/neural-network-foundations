#include "vector.hpp"

#include <iostream>

//coonstructors
Vector::Vector(std::vector<double> elts) {
  this->elts = elts;
  this->length = elts.size();
}

Vector::Vector(int length) {
  this->elts = std::vector<double>(length);
  this->length = length;
}

Vector::Vector() {}

//get access to elts
double& Vector::operator[](int i) {
  return elts[i];
}

double& Vector::operator()(int i) {
  return elts[i];
}

//standard vector-field ops.
Vector Vector::operator+(Vector v) {
  if (length != v.size()) throw IncompatibleVectorException();
  Vector u = *this;
  for (int i = 0; i < length; i++) u[i] += v[i];
  return u;
}

void Vector::operator+=(Vector v) {
  if (length != v.size()) throw IncompatibleVectorException();
  for (int i = 0; i < length; i++) elts[i] += v[i];
}

Vector Vector::operator-() {
  return *this * -1;
}

Vector Vector::operator-(Vector v) {
  if (length != v.size()) throw IncompatibleVectorException();
  Vector u = *this;
  for (int i = 0; i < length; i++) u[i] -= v[i];
  return u;
}

void Vector::operator-=(Vector v) {
  if (length != v.size()) throw IncompatibleVectorException();
  for (int i = 0; i < length; i++) elts[i] -= v[i];
}

Vector Vector::operator*(double a) {
  Vector u = *this;
  for (int i = 0; i < length; i++) u[i] *= a;
  return u;
}

void Vector::operator*=(double a) {
  for (int i = 0; i < length; i++) elts[i] *= a;
}

//real vector ops.
Vector Vector::normalize() {
  *this *= 1/magnitude();
  return *this;
}

Vector Vector::schur(Vector v) {
  if (length != v.size()) throw IncompatibleVectorException();
  Vector u = *this;
  for (int i = 0; i < length; i++) u[i] *= v[i];
  return u;
}

double Vector::magnitude() {
  double magnitude = 0;
  for (int i = 0; i < length; i++) magnitude += pow(elts[i], 2);
  return sqrt(magnitude);
}

Vector Vector::fillGaussian(double mu, double sigma) {

  //create a seed based on the time and a normal dis. based on the seed
  int seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::normal_distribution<double> gauss(mu, sigma);

  for (int i = 0; i < length; i++) {
    elts[i] = gauss(generator);
  }

  return *this;
}

int Vector::maxIndex() {
  int j = 0;
  for (int i = 1; i < length; i++) {
    if (elts[j] < elts[i]) j = i;
  }
  return j;
}

//to string
std::string Vector::toString() {
  std::ostringstream stream;
  for (int i = 0; i < length - 1; i++) {
    stream << elts[i] << ", ";
  }
  if (length > 0) stream << elts[length - 1];
  return "[" + stream.str() + "]";
}

//setters and getters
std::vector<double> Vector::getElts() { return elts; }

int Vector::size() { return length; }

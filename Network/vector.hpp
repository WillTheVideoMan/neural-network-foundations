#pragma once

#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <random>
#include <sstream>

#include "linear-algebra-exceptions.hpp"

class Matrix;

class Vector {
private:
  std::vector<double> elts;
  int length; //amount of elts

public:

  //constructors
  Vector(std::vector<double> elts);

  Vector(int length);

  Vector();

  //get access to elts
  double& operator[](int i);

  double& operator()(int i);

  //standard vector field ops.
  Vector operator+(Vector v);

  void operator+=(Vector v);

  Vector operator-(Vector v);

  Vector operator-();

  void operator-=(Vector v);

  Vector operator*(double a);

  void operator*=(double a);

  //real vector ops.
  Vector normalize();

  Vector schur(Vector v);

  double magnitude();

  Vector fillGaussian(double mu, double sigma);

  int maxIndex();

  //to string
  std::string toString();

  //setters and getters
  std::vector<double> getElts();

  int size();
};

#pragma once

#include <vector>
#include <string>
#include <cmath>

#include "vector.hpp"
#include "linear-algebra-exceptions.hpp"

class Matrix {
private:
  std::vector<double> elts;
  int m; //rows
  int n; //columns
  int length; //amount of elts

public:

  //constructor
  Matrix(std::vector<double> elts, int m, int n);

  Matrix(int m, int n);

  Matrix();

  //get access to elts
  double& operator[](int i);

  double& operator()(int i, int j);

  //standard vector-field ops.
  Matrix operator+(Matrix v);

  void operator+=(Matrix v);

  Matrix operator-(Matrix v);

  Matrix operator-();

  void operator-=(Matrix v);

  Matrix operator*(double a);

  void operator*=(double a);

  //real matrix ops.
  Vector operator*(Vector v);

  Matrix operator*(Matrix v);

  void operator*=(Matrix v);

  Matrix transpose();

  Matrix fillGaussian(double mu, double sigma);

  static Matrix toRowMat(Vector v);

  static Matrix toColMat(Vector v);

  //to string
  std::string toString();

  //setters and getters
  std::vector<double> getElts();

  int size();

  int rows();

  int cols();
};

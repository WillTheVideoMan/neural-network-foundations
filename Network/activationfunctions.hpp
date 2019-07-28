#pragma once

#include "vector.hpp"

class Sigmoid {
public:

  //sigmoid
  static double f(double x);

  static Vector f(Vector x);

  //derivative of sigmoid
  static double fPrime(double x);

  static Vector fPrime(Vector x);
};
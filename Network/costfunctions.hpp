#pragma once

#include "vector.hpp"
#include "activationfunctions.hpp"

class QuadraticCost {
public:

  //cost of this function for an output a
  static double f(Vector a, Vector y);

  //return error in final layer, more useful than cost derivative since allows
  //for algebraic manipulation
  static Vector finalError(Vector z, Vector a, Vector y);
};

class CrossEntropyCost {
public:

  //cost of this function for an output a
  static double f(Vector a, Vector y);

  //return error in final layer, more useful than cost derivative since allows
  //for algebraic manipulation
  static Vector finalError(Vector z, Vector a, Vector y);
};
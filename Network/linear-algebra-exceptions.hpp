#pragma once

#include <exception>

class IncompatibleVectorException : public std::exception {
  virtual const char* what() const throw() {
    return "vectors have incompatible sizes, operation cannot be performed";
  }
};

class IncompatibleMatrixException : public std::exception {
  virtual const char* what() const throw() {
    return "matrices have incompatible sizes, operation cannot be performed";
  }
};

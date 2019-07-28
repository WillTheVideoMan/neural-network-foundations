#include "matrix.hpp"

//constructors
Matrix::Matrix(std::vector<double> elts, int m, int n) {
  this->m = m;
  this->n = n;
  this->length = m * n;
  this->elts = elts;
}

Matrix::Matrix(int m, int n) {
  this->m = m;
  this->n = n;
  this->length = m*n;
  this->elts = std::vector<double>(m*n);
}

Matrix::Matrix() {}

//get access to elts
double& Matrix::operator[](int i) {
  return elts[i];
}

double& Matrix::operator()(int i, int j) {
  return elts[i + j*m];
}

//standard vector-field ops.
Matrix Matrix::operator+(Matrix v) {
  if (m != v.rows() || n != v.cols()) throw IncompatibleMatrixException();
  Matrix u = *this;
  for (int i = 0; i < length; i++) u[i] += v[i];
  return u;
}

void Matrix::operator+=(Matrix v) {
  if (m != v.rows() || n != v.cols()) throw IncompatibleMatrixException();
  for (int i = 0; i < length; i++) elts[i] += v[i];
}

Matrix Matrix::operator-() {
  return *this * -1;
}

Matrix Matrix::operator-(Matrix v) {
  if (length != v.size()) throw IncompatibleMatrixException();
  Matrix u = *this;
  for (int i = 0; i < length; i++) u[i] -= v[i];
  return u;
}

void Matrix::operator-=(Matrix v) {
  if (length != v.size()) throw IncompatibleMatrixException();
  for (int i = 0; i < length; i++) elts[i] -= v[i];
}

Matrix Matrix::operator*(double a) {
  Matrix u = *this;
  for (int i = 0; i < length; i++) u[i] *= a;
  return u;
}

void Matrix::operator*=(double a) {
  for (int i = 0; i < length; i++) elts[i] *= a;
}

//real matrix ops.
Vector Matrix::operator*(Vector v) {
  if (n != v.size()) throw IncompatibleVectorException();
  Vector u = Vector(m);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      u[i] += v[j] * (*this)(i, j);
    }
  }
  return u;
}

Matrix Matrix::operator*(Matrix v) {
  if (n != v.rows()) throw IncompatibleMatrixException();
  Matrix u = Matrix(m, v.cols());
  for (int i = 0; i < u.rows(); i++) {
    for (int j = 0; j < u.cols(); j++) {
      for (int k = 0; k < n; k++) {
        u(i, j) += (*this)(i, k) * v(k, j);
      }
    }
  }
  return u;
}

void Matrix::operator*=(Matrix v) {
  *this = *this * v;
}

Matrix Matrix::transpose() {
  Matrix M(n, m);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      M(j, i) = (*this)(i, j);
    }
  }
  return M;
}

Matrix Matrix::fillGaussian(double mu, double sigma) {

  //create a seed based on the time and a normal dis. based on the seed
  int seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::normal_distribution<double> gauss(mu, sigma);

  for (int i = 0; i < length; i++) {
    elts[i] = gauss(generator);
  }

  return *this;
}

Matrix Matrix::toRowMat(Vector v) {
  return Matrix(v.getElts(), v.size(), 1);
}

Matrix Matrix::toColMat(Vector v) {
  return Matrix(v.getElts(), 1, v.size());
}

//to string
std::string Matrix::toString() {
  std::string str;
  for (int j = 0; j < m; j++) {
    std::ostringstream stream;
    for (int i = 0; i < n - 1; i++) {
      stream << (*this)(j, i) << ", ";
    }
    if (n > 0) stream << (*this)(j, n - 1);
    str += "[" + stream.str() + "]\n";
  }
  return str;
}

//setters and getters
std::vector<double> Matrix::getElts() { return elts; }

int Matrix::size() { return length; }

int Matrix::rows() { return m; }

int Matrix::cols() { return n; }

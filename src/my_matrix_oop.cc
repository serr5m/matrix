#include "my_matrix_oop.h"

myMatrix::myMatrix() : myMatrix(1, 1) {}

myMatrix::myMatrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::runtime_error("Incorrect Matrix");
  }
  MemoryAllocation();
}

myMatrix::myMatrix(int rows, int cols, const std::vector<double> &array)
    : myMatrix(rows, cols) {
  if ((cols * rows) != (int)array.size()) {
    throw std::runtime_error(
        "The number of cells does not match the number of array elements");
  }
  int k = 0;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      matrix_[i][j] = array[k++];
    }
  }
}

myMatrix::myMatrix(const myMatrix &other)
    : myMatrix(other.rows_, other.cols_) {
  CopyMatrixData(other);
}

myMatrix::myMatrix(myMatrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

myMatrix::~myMatrix() { RemoveMatrix(); }

int myMatrix::get_rows() { return rows_; }

int myMatrix::get_cols() { return cols_; }

void myMatrix::set_rows(int new_rows) {
  if (rows_ != new_rows) {
    myMatrix tmp(new_rows, cols_);
    tmp.CopyMatrixData(*this);
    *this = tmp;
  }
}

void myMatrix::set_cols(int new_cols) {
  if (cols_ != new_cols) {
    myMatrix tmp(rows_, new_cols);
    tmp.CopyMatrixData(*this);
    *this = tmp;
  }
}

myMatrix &myMatrix::operator=(const myMatrix &other) {
  RemoveMatrix();
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  MemoryAllocation();
  CopyMatrixData(other);
  return *this;
}

double &myMatrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::runtime_error("Incorrect index");
  }
  return matrix_[row][col];
}

myMatrix myMatrix::operator+(const myMatrix &o) {
  myMatrix tmp(*this);
  tmp.SumMatrix(o);
  return tmp;
}

myMatrix myMatrix::operator-(const myMatrix &o) {
  myMatrix tmp(*this);
  tmp.SubMatrix(o);
  return tmp;
}

myMatrix myMatrix::operator*(const myMatrix &o) {
  myMatrix tmp(*this);
  tmp.MulMatrix(o);
  return tmp;
}

myMatrix myMatrix::operator*(const double num) {
  myMatrix tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

bool myMatrix::operator==(const myMatrix &o) { return EqMatrix(o); }

myMatrix myMatrix::operator+=(const myMatrix &o) {
  SumMatrix(o);
  return *this;
}

myMatrix myMatrix::operator-=(const myMatrix &o) {
  SubMatrix(o);
  return *this;
}

myMatrix myMatrix::operator*=(const myMatrix &o) {
  MulMatrix(o);
  return *this;
}

myMatrix myMatrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

bool myMatrix::EqMatrix(const myMatrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if ((std::fabs(matrix_[i][j] - other.matrix_[i][j])) > 1e-7) {
        return false;
      }
    }
  }
  return true;
}

void myMatrix::SumMatrix(const myMatrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error("Incorrect Matrix");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void myMatrix::SubMatrix(const myMatrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error("Incorrect Matrix");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void myMatrix::MulMatrix(const myMatrix &other) {
  if (cols_ != other.rows_) {
    throw std::runtime_error(
        "The number of columns in the first matrix does not match the number "
        "of rows in the second");
  }
  myMatrix tmp(rows_, other.cols_);
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = tmp;
}

void myMatrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

myMatrix myMatrix::Transpose() {
  myMatrix transpose(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transpose.matrix_[j][i] = matrix_[i][j];
    }
  }
  return transpose;
}

double myMatrix::Determinant() {
  double deter = 0;
  int degree = 1;
  if (rows_ != cols_) {
    throw std::runtime_error("This Matrix is not a square");
  }
  if (rows_ == 1) {
    deter = matrix_[0][0];
  } else if (rows_ == 2) {
    deter = matrix_[0][0] * matrix_[1][1] - matrix_[1][0] * matrix_[0][1];
  } else {
    for (int i = 0; i < cols_; i++) {
      double tmp_det = 0;
      tmp_det = MinorMatrix(0, i).Determinant();
      deter = deter + (matrix_[0][i] * tmp_det * degree);
      degree = -degree;
    }
  }
  return deter;
}

myMatrix myMatrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::runtime_error("This Matrix is not a square");
  }
  myMatrix result(rows_, cols_);
  if (cols_ == 1) {
    result.matrix_[0][0] = 1;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        double deter = 0;
        deter = MinorMatrix(i, j).Determinant();
        result.matrix_[i][j] = pow(-1, i + j) * deter;
      }
    }
  }
  return result;
}

myMatrix myMatrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::runtime_error("This Matrix is not a square");
  }
  double deter = Determinant();
  if (fabs(deter) < 1e-7) {
    throw std::runtime_error("Determinant is zero");
  }
  return CalcComplements().Transpose() * (1.0 / deter);
}

void myMatrix::MemoryAllocation() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void myMatrix::RemoveMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

void myMatrix::CopyMatrixData(const myMatrix &other) {
  int min_rows = std::min(other.rows_, rows_);
  int min_cols = std::min(other.cols_, cols_);
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < min_cols; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

myMatrix myMatrix::MinorMatrix(int minor_rows, int minor_cols) {
  int flag_row = 0;
  myMatrix tmp(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_ - 1; i++) {
    if (i == minor_rows) {
      flag_row = 1;
    }
    int flag_col = 0;
    for (int j = 0; j < cols_ - 1; j++) {
      if (j == minor_cols) {
        flag_col = 1;
      }
      tmp.matrix_[i][j] = matrix_[flag_row + i][flag_col + j];
    }
  }
  return tmp;
}

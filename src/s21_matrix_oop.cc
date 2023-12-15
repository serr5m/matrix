#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(1, 1) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::runtime_error("Incorrect Matrix");
  }
  MemoryAllocation();
}

S21Matrix::S21Matrix(int rows, int cols, const std::vector<double> &array)
    : S21Matrix(rows, cols) {
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

S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {
  CopyMatrixData(other);
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

int S21Matrix::get_rows() { return rows_; }

int S21Matrix::get_cols() { return cols_; }

void S21Matrix::set_rows(int new_rows) {
  if (rows_ != new_rows) {
    S21Matrix tmp(new_rows, cols_);
    tmp.CopyMatrixData(*this);
    *this = tmp;
  }
}

void S21Matrix::set_cols(int new_cols) {
  if (cols_ != new_cols) {
    S21Matrix tmp(rows_, new_cols);
    tmp.CopyMatrixData(*this);
    *this = tmp;
  }
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  RemoveMatrix();
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  MemoryAllocation();
  CopyMatrixData(other);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::runtime_error("Incorrect index");
  }
  return matrix_[row][col];
}

S21Matrix S21Matrix::operator+(const S21Matrix &o) {
  S21Matrix tmp(*this);
  tmp.SumMatrix(o);
  return tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &o) {
  S21Matrix tmp(*this);
  tmp.SubMatrix(o);
  return tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &o) {
  S21Matrix tmp(*this);
  tmp.MulMatrix(o);
  return tmp;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

bool S21Matrix::operator==(const S21Matrix &o) { return EqMatrix(o); }

S21Matrix S21Matrix::operator+=(const S21Matrix &o) {
  SumMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &o) {
  SubMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &o) {
  MulMatrix(o);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
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

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error("Incorrect Matrix");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::runtime_error("Incorrect Matrix");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::runtime_error(
        "The number of columns in the first matrix does not match the number "
        "of rows in the second");
  }
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < tmp.rows_; i++) {
    for (int j = 0; j < tmp.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = tmp;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix transpose(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      transpose.matrix_[j][i] = matrix_[i][j];
    }
  }
  return transpose;
}

double S21Matrix::Determinant() {
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

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::runtime_error("This Matrix is not a square");
  }
  S21Matrix result(rows_, cols_);
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

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::runtime_error("This Matrix is not a square");
  }
  double deter = Determinant();
  if (fabs(deter) < 1e-7) {
    throw std::runtime_error("Determinant is zero");
  }
  return CalcComplements().Transpose() * (1.0 / deter);
}

void S21Matrix::MemoryAllocation() {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::RemoveMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

void S21Matrix::CopyMatrixData(const S21Matrix &other) {
  int min_rows = std::min(other.rows_, rows_);
  int min_cols = std::min(other.cols_, cols_);
  for (int i = 0; i < min_rows; i++) {
    for (int j = 0; j < min_cols; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix S21Matrix::MinorMatrix(int minor_rows, int minor_cols) {
  int flag_row = 0;
  S21Matrix tmp(rows_ - 1, cols_ - 1);
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

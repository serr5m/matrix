#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <vector>

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(int rows, int cols, const std::vector<double>& array);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();
  int get_rows();
  int get_cols();
  void set_rows(int rows);
  void set_cols(int cols);
  S21Matrix& operator=(const S21Matrix& other);
  double& operator()(int row, int col);
  S21Matrix operator+(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o);
  S21Matrix operator*(const S21Matrix& o);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& o);
  S21Matrix operator+=(const S21Matrix& o);
  S21Matrix operator-=(const S21Matrix& o);
  S21Matrix operator*=(const S21Matrix& o);
  S21Matrix operator*=(const double num);
  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

 private:
  int rows_ = 0;
  int cols_ = 0;
  double** matrix_ = nullptr;

  void MemoryAllocation();
  void RemoveMatrix();
  void CopyMatrixData(const S21Matrix& other);
  S21Matrix MinorMatrix(int minor_rows, int minor_cols);
};

#endif  // SRC_S21_MATRIX_OOP_H_

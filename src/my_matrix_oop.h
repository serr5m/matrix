#ifndef SRC_my_MATRIX_OOP_H_
#define SRC_my_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <vector>

class myMatrix {
 public:
  myMatrix();
  myMatrix(int rows, int cols);
  myMatrix(int rows, int cols, const std::vector<double>& array);
  myMatrix(const myMatrix& other);
  myMatrix(myMatrix&& other);
  ~myMatrix();
  int get_rows();
  int get_cols();
  void set_rows(int rows);
  void set_cols(int cols);
  myMatrix& operator=(const myMatrix& other);
  double& operator()(int row, int col);
  myMatrix operator+(const myMatrix& o);
  myMatrix operator-(const myMatrix& o);
  myMatrix operator*(const myMatrix& o);
  myMatrix operator*(const double num);
  bool operator==(const myMatrix& o);
  myMatrix operator+=(const myMatrix& o);
  myMatrix operator-=(const myMatrix& o);
  myMatrix operator*=(const myMatrix& o);
  myMatrix operator*=(const double num);
  bool EqMatrix(const myMatrix& other) const;
  void SumMatrix(const myMatrix& other);
  void SubMatrix(const myMatrix& other);
  void MulMatrix(const myMatrix& other);
  void MulNumber(const double num);
  myMatrix Transpose();
  double Determinant();
  myMatrix CalcComplements();
  myMatrix InverseMatrix();

 private:
  int rows_ = 0;
  int cols_ = 0;
  double** matrix_ = nullptr;

  void MemoryAllocation();
  void RemoveMatrix();
  void CopyMatrixData(const myMatrix& other);
  myMatrix MinorMatrix(int minor_rows, int minor_cols);
};

#endif  // SRC_my_MATRIX_OOP_H_

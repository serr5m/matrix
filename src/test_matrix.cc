#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(TestDefaultConstr, Test0) {
  S21Matrix a;
  ASSERT_EQ(a.get_rows(), 1);
}
TEST(TestDefaultConstr, Test1) {
  S21Matrix a;
  ASSERT_EQ(a.get_cols(), 1);
}
TEST(TestConstrWithParametrs, Test0) {
  S21Matrix a(4, 4);
  ASSERT_EQ(a.get_rows(), 4);
  ASSERT_EQ(a.get_cols(), 4);
}
TEST(TestConstrWithParametrs, Test1) {
  S21Matrix a(4, 2);
  ASSERT_EQ(a.get_rows(), 4);
  ASSERT_EQ(a.get_cols(), 2);
}
TEST(TestConstructorWithVector, Test0) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  ASSERT_EQ(a.get_rows(), 2);
  ASSERT_EQ(a.get_cols(), 2);
  ASSERT_EQ(a(0, 0), 1);
  int k = 1;
  for (int i = 0; i < a.get_rows(); i++)
    for (int j = 0; j < a.get_cols(); j++) ASSERT_DOUBLE_EQ(a(i, j), k++);
}
TEST(TestCopyConstructor, Test0) {
  std::vector<double> arr = {1, 2, 3, 4};
  S21Matrix m1(2, 2, arr);
  S21Matrix m2(m1);
  ASSERT_DOUBLE_EQ(m2.get_rows(), m1.get_rows());
  ASSERT_DOUBLE_EQ(m2.get_cols(), m1.get_cols());
  for (int i = 0; i < m2.get_rows(); i++)
    for (int j = 0; j < m2.get_cols(); j++)
      ASSERT_DOUBLE_EQ(m1(i, j), m2(i, j));
}
TEST(TestCopyConstructor, Test1) {
  std::vector<double> arr = {3, 2, 5, 7};
  S21Matrix m1(2, 2, arr);
  S21Matrix m2(m1);

  ASSERT_DOUBLE_EQ(m2.get_rows(), m1.get_rows());
  ASSERT_DOUBLE_EQ(m2.get_cols(), m1.get_cols());
  for (int i = 0; i < m2.get_rows(); i++)
    for (int j = 0; j < m2.get_cols(); j++)
      ASSERT_DOUBLE_EQ(m1(i, j), m2(i, j));
}
TEST(TestMoveConstructor, Test0) {
  S21Matrix a(2, 2, {2, 3.34, 4, 5});
  S21Matrix b(std::move(a));
  ASSERT_EQ(a.get_rows(), 0);
  ASSERT_EQ(a.get_cols(), 0);
  ASSERT_DOUBLE_EQ(b(0, 0), 2);
  ASSERT_DOUBLE_EQ(b(0, 1), 3.34);
  ASSERT_DOUBLE_EQ(b(1, 0), 4);
  ASSERT_DOUBLE_EQ(b(1, 1), 5);
}
TEST(TestGetters, Test0) {
  S21Matrix a(2, 2);
  ASSERT_EQ(a.get_rows(), 2);
  ASSERT_EQ(a.get_cols(), 2);
}
TEST(TestGetters, Test1) {
  S21Matrix a;
  ASSERT_EQ(a.get_rows(), 1);
  ASSERT_EQ(a.get_cols(), 1);
}
TEST(TestSetters, Test0) {
  S21Matrix a(2, 2);
  ASSERT_EQ(a.get_rows(), 2);
  a.set_rows(4);
  ASSERT_EQ(a.get_rows(), 4);
}
TEST(TestSetters, Test1) {
  S21Matrix a(2, 2);
  ASSERT_EQ(a.get_cols(), 2);
  a.set_cols(5);
  ASSERT_EQ(a.get_cols(), 5);
}

TEST(TestEqMatrix, Test0) {
  std::vector<double> array1 = {5, 9, 4, 8};
  S21Matrix a(2, 2, array1);
  S21Matrix b(2, 2, array1);
  ASSERT_TRUE(a.EqMatrix(b));
}

TEST(TestEqMatrix, Test1) {
  std::vector<double> array1 = {5, 9, 4, 8};
  S21Matrix a(2, 2, array1);
  S21Matrix b(2, 2);
  ASSERT_FALSE(a.EqMatrix(b));
}

TEST(TestEqMatrix, Test2) {
  std::vector<double> array1 = {5, 9, 4, 8, 3, 4};
  std::vector<double> array2 = {5, 0, 4, 8, 3, 4};

  S21Matrix a(2, 3, array1);
  S21Matrix b(2, 3, array2);
  ASSERT_FALSE(a.EqMatrix(b));
}
TEST(TestOperatorEqual, Test0) {
  S21Matrix a(3, 2, {1, 2, 3, 4, 5, 6});
  S21Matrix b;
  b = a;
  ASSERT_TRUE(a.EqMatrix(b));
}
TEST(TestOperatorEqualEqual, Test0) {
  //
  S21Matrix a(3, 2, {1, 2, 3, 4, 5, 6});
  S21Matrix b(3, 2, {1, 2, 3, 4, 5, 6});
  ASSERT_TRUE(a == b);
}
TEST(TestSumMatrix, Test0) {
  std::vector<double> array1 = {5, 9, 4, 8, 3, 0};
  std::vector<double> res_array = {10, 18, 8, 16, 6, 0};
  S21Matrix a(2, 3, array1);
  S21Matrix b(2, 3, array1);
  S21Matrix res(2, 3, res_array);
  a.SumMatrix(b);
  for (int i = 0; i < res.get_rows(); i++) {
    for (int j = 0; j < res.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(a(i, j), res(i, j));
    }
  }
}

TEST(TestSumMatrix, Test1) {
  std::vector<double> array1 = {3.23, 9.12, -4, 0.008, 3.01, 44};
  std::vector<double> res_array = {6.46, 18.24, -8, 0.016, 6.02, 88};

  S21Matrix a(2, 3, array1);
  S21Matrix b(2, 3, array1);
  S21Matrix res(2, 3, res_array);
  a.SumMatrix(b);
  for (int i = 0; i < res.get_rows(); i++) {
    for (int j = 0; j < res.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(a(i, j), res(i, j));
    }
  }
}
TEST(TestOperatorPlus, Test0) {
  S21Matrix a(2, 2, {0, 1, 2, 3});
  S21Matrix b(2, 2, {1, 2, 3, 4});
  S21Matrix c = a + b;
  ASSERT_DOUBLE_EQ(c(0, 0), 1);
  ASSERT_DOUBLE_EQ(c(0, 1), 3);
  ASSERT_DOUBLE_EQ(c(1, 0), 5);
  ASSERT_DOUBLE_EQ(c(1, 1), 7);
}

TEST(TestOperatorPlus, Test1) {
  S21Matrix a(2, 2, {0, 1, 2, 3});
  S21Matrix b(2, 2, {-1, -2, -3, -4});
  S21Matrix c = a + b;
  ASSERT_DOUBLE_EQ(c(0, 0), -1);
  ASSERT_DOUBLE_EQ(c(0, 1), -1);
  ASSERT_DOUBLE_EQ(c(1, 0), -1);
  ASSERT_DOUBLE_EQ(c(1, 1), -1);
}

TEST(TestOperatorPlusEqual, Test0) {
  S21Matrix a(2, 2, {0, 1, 2, 3});
  S21Matrix b(2, 2, {-1, -2, -3, -4});
  a += b;
  ASSERT_DOUBLE_EQ(a(0, 0), -1);
  ASSERT_DOUBLE_EQ(a(0, 1), -1);
  ASSERT_DOUBLE_EQ(a(1, 0), -1);
  ASSERT_DOUBLE_EQ(a(1, 1), -1);
}
TEST(TestSubMatrix, Test0) {
  std::vector<double> array = {1, 2, 3, 4, 1, 2, 3, 4, 0};
  S21Matrix a(3, 3, array);
  S21Matrix b(3, 3, array);

  a.SubMatrix(b);
  for (int i = 0; i < a.get_rows(); i++) {
    for (int j = 0; j < a.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(a(i, j), 0);
    }
  }
}
TEST(TestSubMatrix, Test1) {
  std::vector<double> array1 = {3.23, 9.12, -4, 0.008, 3.01, 44};
  std::vector<double> array2 = {6.46, 18.24, -8, 0.016, 6.02, 88};
  std::vector<double> res_array = {-3.23, -9.12, 4, -0.008, -3.01, -44};

  S21Matrix a(2, 3, array1);
  S21Matrix b(2, 3, array2);
  S21Matrix res(2, 3, res_array);
  a.SubMatrix(b);
  for (int i = 0; i < res.get_rows(); i++) {
    for (int j = 0; j < res.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(a(i, j), res(i, j));
    }
  }
}
TEST(TestOperatorSub, Test0) {
  S21Matrix a(2, 2, {0, 1, 2, 3});
  S21Matrix b(2, 2, {-1, -2, -3, -4});
  S21Matrix c = a - b;
  ASSERT_DOUBLE_EQ(c(0, 0), 1);
  ASSERT_DOUBLE_EQ(c(0, 1), 3);
  ASSERT_DOUBLE_EQ(c(1, 0), 5);
  ASSERT_DOUBLE_EQ(c(1, 1), 7);
}
TEST(TestOperatorSubEqual, Test0) {
  S21Matrix a(2, 2, {0, 1, 2, 3});
  S21Matrix b(2, 2, {-1, -2, -3, -4});
  a -= b;
  ASSERT_DOUBLE_EQ(a(0, 0), 1);
  ASSERT_DOUBLE_EQ(a(0, 1), 3);
  ASSERT_DOUBLE_EQ(a(1, 0), 5);
  ASSERT_DOUBLE_EQ(a(1, 1), 7);
}
TEST(TestMulMatrix, Test0) {
  //
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b(2, 2, {2, 3, 4, 5});
  a.MulMatrix(b);
  std::cout << std::endl;
  std::cout << a(0, 0) << std::endl;
  std::cout << std::endl;
  ASSERT_DOUBLE_EQ(a(0, 0), 10);
  ASSERT_DOUBLE_EQ(a(0, 1), 13);
  ASSERT_DOUBLE_EQ(a(1, 0), 22);
  ASSERT_DOUBLE_EQ(a(1, 1), 29);
}
TEST(TestOperatorMul, Test0) {
  S21Matrix a(2, 2, {0, 1, 2, 3});
  S21Matrix b(2, 2, {-1, -2, -3, -4});
  S21Matrix c = a * b;
  ASSERT_DOUBLE_EQ(c(0, 0), -3);
  ASSERT_DOUBLE_EQ(c(0, 1), -4);
  ASSERT_DOUBLE_EQ(c(1, 0), -11);
  ASSERT_DOUBLE_EQ(c(1, 1), -16);
}
TEST(TestOperatorMulEqual, Test0) {
  S21Matrix a(2, 2, {0, 1, 2, 3});
  S21Matrix b(2, 2, {-1, -2, -3, -4});
  a *= b;
  ASSERT_DOUBLE_EQ(a(0, 0), -3);
  ASSERT_DOUBLE_EQ(a(0, 1), -4);
  ASSERT_DOUBLE_EQ(a(1, 0), -11);
  ASSERT_DOUBLE_EQ(a(1, 1), -16);
}
TEST(TestOperatorMulNumber, Test0) {
  S21Matrix a(2, 3, {3.23, 9.12, -4, 0.008, 3.01, 44});
  double b = 0.5;
  a *= b;
  ASSERT_DOUBLE_EQ(a(0, 0), 1.615);
  ASSERT_DOUBLE_EQ(a(0, 1), 4.56);
  ASSERT_DOUBLE_EQ(a(0, 2), -2);
  ASSERT_DOUBLE_EQ(a(1, 0), 0.004);
  ASSERT_DOUBLE_EQ(a(1, 1), 1.505);
  ASSERT_DOUBLE_EQ(a(1, 2), 22);
}

TEST(TestMulNumber, Test1) {
  std::vector<double> array1 = {3.23, 9.12, -4, 0.008, 3.01, 44};
  double b = 0.5;
  std::vector<double> res_array = {1.615, 4.56, -2, 0.004, 1.505, 22};

  S21Matrix a(2, 3, array1);
  S21Matrix res(2, 3, res_array);
  a.MulNumber(b);
  for (int i = 0; i < res.get_rows(); i++) {
    for (int j = 0; j < res.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(a(i, j), res(i, j));
    }
  }
}
TEST(TestMulNumber, Test2) {
  std::vector<double> array1 = {3.23, 9.12, -4, 0.008, 3.01, 44};
  double b = 2;
  std::vector<double> res_array = {6.46, 18.24, -8, 0.016, 6.02, 88};

  S21Matrix a(2, 3, array1);
  S21Matrix res(2, 3, res_array);
  a.MulNumber(b);
  for (int i = 0; i < res.get_rows(); i++) {
    for (int j = 0; j < res.get_cols(); j++) {
      ASSERT_DOUBLE_EQ(a(i, j), res(i, j));
    }
  }
}
TEST(TestTranspose, Test0) {
  S21Matrix a(2, 3, {1, 2, 3, 4, 5, 6});
  S21Matrix b(3, 2, {1, 4, 2, 5, 3, 6});
  ASSERT_TRUE(a.Transpose().EqMatrix(b));
}
TEST(TestTranspose, Test1) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b(2, 2, {1, 3, 2, 4});
  ASSERT_TRUE(a.Transpose().EqMatrix(b));
}

TEST(TestDeterminant, Test0) {
  S21Matrix a(2, 2, {0, 1, 2, 3});
  double deter = a.Determinant();
  ASSERT_DOUBLE_EQ(deter, -2);
}
TEST(TestDeterminant, Test1) {
  S21Matrix a(2, 2, {5.789, 1, 2, 3.4});
  double deter = a.Determinant();
  ASSERT_DOUBLE_EQ(deter, 17.6826);
}
TEST(TestCalcComplements, Test0) {
  S21Matrix a(2, 2, {1, 2, 3, 4});
  S21Matrix b = a.CalcComplements();
  ASSERT_DOUBLE_EQ(b(0, 0), 4);
  ASSERT_DOUBLE_EQ(b(0, 1), -3);
  ASSERT_DOUBLE_EQ(b(1, 0), -2);
  ASSERT_DOUBLE_EQ(b(1, 1), 1);
}
TEST(TestCalcComplements, Test1) {
  S21Matrix a(2, 2, {1, -2, 0.35, 4});
  S21Matrix b = a.CalcComplements();
  ASSERT_DOUBLE_EQ(b(0, 0), 4);
  ASSERT_DOUBLE_EQ(b(0, 1), -0.35);
  ASSERT_DOUBLE_EQ(b(1, 0), 2);
  ASSERT_DOUBLE_EQ(b(1, 1), 1);
}
TEST(TestInverseMatrix, Test0) {
  S21Matrix a(2, 2, {9, 8, 7, 6});
  S21Matrix b = a.InverseMatrix();
  ASSERT_DOUBLE_EQ(b(0, 0), -3);
  ASSERT_DOUBLE_EQ(b(0, 1), 4);
  ASSERT_DOUBLE_EQ(b(1, 0), 3.5);
  ASSERT_DOUBLE_EQ(b(1, 1), -4.5);
}

TEST(TestInverseMatrix, Test1) {
  S21Matrix a(2, 2, {0.5, -4, 7, 4});
  S21Matrix b = a.InverseMatrix();
  ASSERT_NEAR(b(0, 0), 0.13333333333, 1e-7);
  ASSERT_NEAR(b(0, 1), 0.133333333, 1e-7);
  ASSERT_NEAR(b(1, 0), -0.233333333, 1e-7);
  ASSERT_NEAR(b(1, 1), 0.016666667, 1e-7);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

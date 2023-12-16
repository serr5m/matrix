# Matrix Operations Library

This C++ library provides a set of matrix operations implemented in the `Matrix` class. The library includes basic matrix operations, constructors, destructors, and overloaded operators for convenient usage.

## Matrix Operations

Here are the matrix operations that have been implemented in the library:

| Operation                  | Description                                          | Exceptional Situations                           |
| -------------------------- | ---------------------------------------------------- | ------------------------------------------------- |
| `bool EqMatrix(const Matrix& other)` | Checks matrices for equality with each other | - |
| `void SumMatrix(const Matrix& other)` | Adds the second matrix to the current one | Different matrix dimensions |
| `void SubMatrix(const Matrix& other)` | Subtracts another matrix from the current one | Different matrix dimensions |
| `void MulNumber(const double num)` | Multiplies the current matrix by a number | - |
| `void MulMatrix(const Matrix& other)` | Multiplies the current matrix by the second matrix | Columns of the first matrix not equal to rows of the second matrix |
| `Matrix Transpose()` | Creates a new transposed matrix from the current one and returns it | - |
| `Matrix CalcComplements()` | Calculates the algebraic addition matrix of the current one and returns it | Matrix is not square |
| `double Determinant()` | Calculates and returns the determinant of the current matrix | Matrix is not square |
| `Matrix InverseMatrix()` | Calculates and returns the inverse matrix | Matrix determinant is 0 |

## Constructors and Destructors

The following constructors and destructors are available:

- `Matrix()`: Basic constructor that initializes a matrix of some predefined dimension.
- `Matrix(int rows, int cols)`: Parametrized constructor with the number of rows and columns.
- `Matrix(const Matrix& other)`: Copy constructor.
- `Matrix(Matrix&& other)`: Move constructor.
- `~Matrix()`: Destructor.

## Overloaded Operators

The following operators have been overloaded, partly corresponding to the operations described above:

- `+`: Addition of two matrices (Exception: Different matrix dimensions).
- `-`: Subtraction of one matrix from another (Exception: Different matrix dimensions).
- `*`: Matrix multiplication and matrix multiplication by a number (Exception: Columns of the first matrix do not equal the number of rows of the second matrix).
- `==`: Checks for matrices equality (`EqMatrix`).
- `=`: Assignment of values from one matrix to another one.
- `+=`: Addition assignment (`SumMatrix`, Exception: Different matrix dimensions).
- `-=`: Difference assignment (`SubMatrix`, Exception: Different matrix dimensions).
- `*=`: Multiplication assignment (`MulMatrix`/`MulNumber`, Exception: Columns of the first matrix do not equal the number of rows of the second matrix).
- `(int i, int j)`: Indexation by matrix elements (row, column, Exception: Index is outside the matrix).

Feel free to use and contribute to this matrix operations library!

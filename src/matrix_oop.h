#ifndef SRC__MATRIX_OOP_H_
#define SRC__MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void InitializationMatrix();
  void RemoveMatrix();
  bool IsEqDoubles(double value1, double value2);

 public:
  //  Constructors matrix
  Matrix();
  Matrix(int rows, int cols);
  Matrix(const Matrix& other);
  Matrix(Matrix&& other);
  // Destructor matrix
  ~Matrix() { RemoveMatrix(); }
  // Operations with matrix
  bool EqMatrix(const Matrix& other);
  void SumMatrix(const Matrix& other);
  void SubMatrix(const Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix& other);
  Matrix Transpose();
  Matrix CalcComplements();
  double Determinant();
  Matrix InverseMatrix();
  bool EqRowsAndCols(const Matrix& other);
  void SetRows(int rows);
  void SetCols(int cols);
  void SetValue(int row, int column, double value);
  Matrix DeleteRowAndCols(int rows, int column);

  // Overload operators for matrix
  Matrix operator+(const Matrix& other) const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  friend Matrix operator*(const Matrix& matrix, const double num);
  friend Matrix operator*(const double num, const Matrix& matrix);
  friend std::ostream& operator<<(std::ostream& stream, Matrix& matrix);
  friend std::istream& operator>>(std::istream& stream, Matrix& matrix);
  Matrix operator=(const Matrix& other);
  Matrix operator+=(const Matrix& other);
  Matrix operator-=(const Matrix& other);
  Matrix operator*=(const double num);
  double operator()(const int i, int j) { return GetValue(i, j); }
  bool operator==(const Matrix& other) { return EqMatrix(other); }
  // Gets attribute from matrix
  int GetRows() { return rows_; }
  int GetCols() { return cols_; }
  double GetValue(int row, int column) { return matrix_[row][column]; }
};

#endif  //  SRC__MATRIX_OOP_H_

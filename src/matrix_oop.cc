#include "matrix_oop.h"

// Initialization memory for matrix
void Matrix::InitializationMatrix() {
  matrix_ = new double *[rows_];
  for (int row = 0; row < rows_; row++) {
    matrix_[row] = new double[cols_]{};
  }
}

//  remove matrix memory
void Matrix::RemoveMatrix() {
  if (matrix_) {
    for (int row = 0; row < rows_; row++) {
      delete[] matrix_[row];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

void Matrix::SetRows(int rows) {
  if (rows > 0 && rows != rows_) {
    Matrix temp(rows, cols_);
    int allow_row = rows;
    if (rows > rows_) allow_row = rows_;
    for (int row = 0; row < allow_row; row++) {
      for (int column = 0; column < cols_; column++) {
        temp.matrix_[row][column] = matrix_[row][column];
      }
    }
    RemoveMatrix();
    rows_ = rows;
    cols_ = temp.cols_;
    InitializationMatrix();
    for (int row = 0; row < rows_; row++) {
      for (int column = 0; column < cols_; column++) {
        matrix_[row][column] = temp.matrix_[row][column];
      }
    }
    temp.RemoveMatrix();
  }
}

void Matrix::SetCols(int cols) {
  if (cols != cols_ && cols > 0) {
    Matrix temp(rows_, cols);
    int allow_cols = cols;
    if (cols > rows_) allow_cols = cols_;
    for (int row = 0; row < rows_; ++row) {
      for (int column = 0; column < allow_cols; ++column) {
        temp.matrix_[row][column] = matrix_[row][column];
      }
    }
    RemoveMatrix();
    rows_ = temp.rows_;
    cols_ = cols;
    InitializationMatrix();
    for (int row = 0; row < rows_; ++row) {
      for (int column = 0; column < cols_; ++column) {
        matrix_[row][column] = temp.matrix_[row][column];
      }
    }
  }
}

void Matrix::SetValue(int row, int column, double value) {
  if (row <= rows_ && column <= cols_ && row >= 0 && column >= 0) {
    matrix_[row][column] = value;
  } else {
    throw std::invalid_argument("rows or cols can't be <= 0");
  }
}

//  Constructors for matrix
Matrix::Matrix() : Matrix(1, 1) {}

Matrix::Matrix(int rows, int cols) : matrix_{nullptr} {
  if (rows > 0 && cols > 0) {
    rows_ = rows;
    cols_ = cols;
    InitializationMatrix();
  } else {
    throw std::invalid_argument("rows or cols can't be <= 0");
  }
}

// Move constructor
Matrix::Matrix(Matrix &&other) : rows_{0}, cols_{0}, matrix_{nullptr} {
  if (this != &other) {
    std::swap(this->matrix_, other.matrix_);
    std::swap(rows_, other.rows_);
    std::swap(cols_, other.cols_);
  }
}

// Copy constructor
Matrix::Matrix(const Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  InitializationMatrix();
  for (int row = 0; row < rows_; row++) {
    for (int column = 0; column < cols_; column++) {
      matrix_[row][column] = other.matrix_[row][column];
    }
  }
}

// methods for matrix
bool Matrix::EqMatrix(const Matrix &other) {
  bool isEquals = EqRowsAndCols(other);
  for (int row = 0; row < rows_ && isEquals; row++) {
    for (int column = 0; column < cols_ && isEquals; column++) {
      isEquals = IsEqDoubles(matrix_[row][column], other.matrix_[row][column]);
    }
  }
  return isEquals;
}

void Matrix::SumMatrix(const Matrix &other) {
  if (EqRowsAndCols(other)) {
    for (int row = 0; row < rows_; ++row) {
      for (int column = 0; column < cols_; ++column) {
        matrix_[row][column] += other.matrix_[row][column];
      }
    }
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  if (EqRowsAndCols(other)) {
    for (int row = 0; row < rows_; ++row) {
      for (int column = 0; column < cols_; ++column) {
        matrix_[row][column] -= other.matrix_[row][column];
      }
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ == other.rows_) {
    Matrix old_matrix = std::move(*this);
    rows_ = old_matrix.GetRows();
    cols_ = old_matrix.GetCols();
    InitializationMatrix();
    for (int row = 0; row < rows_; ++row) {
      for (int column = 0; column < other.cols_; column++) {
        for (int row_or_cols = 0; row_or_cols < cols_; row_or_cols++) {
          matrix_[row][column] += old_matrix.matrix_[row][row_or_cols] *
                                  other.matrix_[row_or_cols][column];
        }
      }
    }
  }
}

void Matrix::MulNumber(const double num) {
  for (int row = 0; row < rows_; ++row) {
    for (int column = 0; column < cols_; ++column) {
      matrix_[row][column] *= num;
    }
  }
}

Matrix Matrix::Transpose() {
  Matrix result_matrix(cols_, rows_);
  for (int row = 0; row < rows_; row++) {
    for (int column = 0; column < cols_; column++) {
      result_matrix.matrix_[column][row] = matrix_[row][column];
    }
  }
  return result_matrix;
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) throw std::invalid_argument("The matrix is not square");
  Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    for (int row = 0; row < rows_; row++) {
      for (int column = 0; column < cols_; column++) {
        Matrix minor_matrix = DeleteRowAndCols(row, column);
        result.matrix_[row][column] =
            pow(-1.0, row + column) * minor_matrix.Determinant();
        minor_matrix.RemoveMatrix();
      }
    }
  }
  return result;
}

double Matrix::Determinant() {
  if (rows_ != cols_) throw std::invalid_argument("The matrix is not square");
  double result = 0.0;
  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int column = 0; column < cols_; column++) {
      Matrix minor_matrix = DeleteRowAndCols(0, column);
      result +=
          pow(-1, column) * matrix_[0][column] * minor_matrix.Determinant();
      minor_matrix.RemoveMatrix();
    }
  }
  return result;
}

Matrix Matrix::DeleteRowAndCols(int rows, int column) {
  Matrix result(rows_ - 1, cols_ - 1);
  int row, col;
  for (int i = 0; i < result.rows_; i++) {
    for (int j = 0; j < result.cols_; j++) {
      if (i < rows) {
        row = i;
      } else {
        row = i + 1;
      }
      if (j < column) {
        col = j;
      } else {
        col = j + 1;
      }
      result.matrix_[i][j] = matrix_[row][col];
    }
  }
  return result;
}

Matrix Matrix::InverseMatrix() {
  if (rows_ != cols_) throw std::invalid_argument("The matrix is not square");
  double determinant = Determinant();
  if (IsEqDoubles(determinant, 0.0))
    throw std::invalid_argument("determinant is zero");
  Matrix result = CalcComplements().Transpose();
  result.MulNumber(1.0 / determinant);
  return result;
}

bool Matrix::EqRowsAndCols(const Matrix &other) {
  return (rows_ == other.rows_) && (cols_ == other.cols_);
}

//  Overload operators for matrix
Matrix Matrix::operator+(const Matrix &other) const {
  Matrix matrix(*this);
  matrix.SumMatrix(other);
  return matrix;
}

Matrix Matrix::operator-(const Matrix &other) const {
  Matrix matrix(*this);
  matrix.SubMatrix(other);
  return matrix;
}

Matrix operator*(const double num, const Matrix &matrix) {
  Matrix temp_matrix(matrix);
  temp_matrix.MulNumber(num);
  return temp_matrix;
}

Matrix operator*(const Matrix &matrix, const double num) {
  Matrix temp_matrix(matrix);
  temp_matrix.MulNumber(num);
  return temp_matrix;
}

Matrix Matrix::operator*(const Matrix &other) const {
  Matrix matrix(*this);
  matrix.MulMatrix(other);
  return matrix;
}

Matrix Matrix::operator=(const Matrix &other) {
  Matrix result(other);
  return result;
}

Matrix Matrix::operator+=(const Matrix &other) {
  SumMatrix(other);
  return *this;
}

Matrix Matrix::operator-=(const Matrix &other) {
  SubMatrix(other);
  return *this;
}

Matrix Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

std::ostream &operator<<(std::ostream &stream, Matrix &matrix) {
  for (int row = 0; row < matrix.GetRows(); row++) {
    for (int column = 0; column < matrix.GetCols(); column++) {
      stream << matrix.GetValue(row, column) << " ";
    }
    stream << "\n";
  }
  return stream;
}

std::istream &operator>>(std::istream &stream, Matrix &matrix) {
  for (int row = 0; row < matrix.GetRows(); row++) {
    for (int column = 0; column < matrix.GetCols(); column++) {
      double value;
      stream >> value;
      matrix.SetValue(row, column, value);
    }
  }
  return stream;
}

bool Matrix::IsEqDoubles(double value1, double value2) {
  static constexpr auto epsilon = 1.0e-06f;
  bool status = false;
  if (abs(value1 - value2) <= epsilon) {
    status = true;
  } else {
    status =
        (abs(value1 - value2) <= epsilon * std::max(abs(value1), abs(value2)));
  }
  return status;
}

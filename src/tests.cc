#include "tests.h"

TEST_F(MatrixTest, constructors) {
  Matrix test1;
  EXPECT_EQ(test1.GetRows(), 1);
  EXPECT_EQ(test1.GetCols(), 1);
  EXPECT_EQ(matrix1.GetRows(), 2);
  EXPECT_EQ(matrix1.GetCols(), 6);
  EXPECT_EQ(matrix2_1.GetRows(), 5);
  EXPECT_EQ(matrix2_1.GetCols(), 5);
  Matrix src(std::move(matrix3_1));
  EXPECT_EQ(src.GetRows(), 7);
  EXPECT_EQ(src.GetCols(), 8);
  Matrix second(src);
  EXPECT_TRUE(src == second);
}

TEST_F(MatrixTest, EqMatrixTest) {
  EXPECT_FALSE(matrix1.EqMatrix(matrix4_1));
  EXPECT_TRUE(matrix2_1.EqMatrix(matrix2_2));
}

TEST_F(MatrixTest, SumMatrix) {
  matrix2_1.SumMatrix(matrix2_2);
  EXPECT_TRUE(matrix2_1.EqMatrix(resultSum_1));
  matrix3_1.SumMatrix(matrix3_2);
  EXPECT_TRUE(matrix3_1.EqMatrix(resultSum_2));
  matrix4_1.SumMatrix(matrix4_2);
  EXPECT_TRUE(matrix4_1.EqMatrix(resultSum_3));
}

TEST_F(MatrixTest, SubMatrixTest) {
  matrix2_1.SubMatrix(matrix2_2);
  EXPECT_TRUE(matrix2_1.EqMatrix(resultSub_1));
  matrix3_1.SubMatrix(matrix3_2);
  EXPECT_TRUE(matrix3_1.EqMatrix(resultSub_2));
  matrix4_1.SubMatrix(matrix4_2);
  EXPECT_TRUE(matrix4_1.EqMatrix(resultSub_3));
}

TEST_F(MatrixTest, MulNumberTest) {
  matrix2_1.MulNumber(1.0);
  EXPECT_TRUE(matrix2_1.EqMatrix(matrix2_2));
  matrix3_1.MulNumber(9.54);
  EXPECT_TRUE(matrix3_1.EqMatrix(resultMulNum_1));
  matrix4_1.MulNumber(-0.023);
  EXPECT_TRUE(matrix4_1.EqMatrix(resultMulNum_2));
}

TEST_F(MatrixTest, MulMatrixTest) {
  matrix2_1.MulMatrix(matrix2_2);
  EXPECT_TRUE(matrix2_1.EqMatrix(resultMul_1));
  matrix3_1.MulMatrix(matrix3_2);
  EXPECT_TRUE(matrix3_1.EqMatrix(resultMul_2));
}

TEST_F(MatrixTest, TransposeTest) {
  EXPECT_TRUE(matrix2_1.Transpose().EqMatrix(resultTranspose_1));
  EXPECT_TRUE(matrix3_1.Transpose().EqMatrix(resultTranspose_2));
  EXPECT_TRUE(matrix4_1.Transpose().EqMatrix(resultTranspose_3));
}

TEST_F(MatrixTest, CalcComplementsTest) {
  EXPECT_TRUE(matrix2_1.CalcComplements().EqMatrix(resultCalcComplements));
  EXPECT_ANY_THROW(matrix3_1.CalcComplements());
  EXPECT_ANY_THROW(matrix4_1.CalcComplements());
}

TEST_F(MatrixTest, DeterminantTest) {
  EXPECT_DOUBLE_EQ(matrix2_1.Determinant(), -1.9491984839158434);
  EXPECT_ANY_THROW(matrix3_1.Determinant());
  EXPECT_ANY_THROW(matrix4_1.Determinant());
}

TEST_F(MatrixTest, InverseMatrixTest) {
  EXPECT_TRUE(matrix2_1.InverseMatrix().EqMatrix(resultInverse));
  EXPECT_ANY_THROW(matrix3_1.InverseMatrix());
  EXPECT_ANY_THROW(matrix4_1.InverseMatrix());
}

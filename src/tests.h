#ifndef SRC_TESTS_H
#define SRC_TESTS_H

#include <gtest/gtest.h>

#include <fstream>
#include <iostream>

#include "matrix_oop.h"

using namespace std;

class MatrixTest : public ::testing::Test {
 protected:
  void SetUp() override {
    ifstream file;
    file.open("data.txt");
    file >> matrix1 >> matrix2_1 >> matrix2_2 >> matrix3_1;
    file >> matrix3_2 >> matrix4_1 >> matrix4_2;
    file.close();
    file.open("result.txt");
    file >> resultSum_1 >> resultSum_2 >> resultSum_3;
    file >> resultSub_1 >> resultSub_2 >> resultSub_3;
    file >> resultMulNum_1 >> resultMulNum_2 >> resultMul_1;
    file >> resultMul_2 >> resultTranspose_1 >> resultTranspose_2;
    file >> resultTranspose_3 >> resultCalcComplements >> resultInverse;
    file.close();
  }
  Matrix matrix1 = Matrix(2, 6);
  Matrix matrix2_1 = Matrix(5, 5);
  Matrix matrix2_2 = Matrix(5, 5);
  Matrix matrix3_1 = Matrix(7, 8);
  Matrix matrix3_2 = Matrix(7, 8);
  Matrix matrix4_1 = Matrix(3, 4);
  Matrix matrix4_2 = Matrix(3, 4);
  Matrix resultSum_1 = Matrix(5, 5);
  Matrix resultSum_2 = Matrix(7, 8);
  Matrix resultSum_3 = Matrix(3, 4);
  Matrix resultSub_1 = Matrix(5, 5);
  Matrix resultSub_2 = Matrix(7, 8);
  Matrix resultSub_3 = Matrix(3, 4);
  Matrix resultMul_1 = Matrix(5, 5);
  Matrix resultMul_2 = Matrix(7, 8);
  Matrix resultMulNum_1 = Matrix(7, 8);
  Matrix resultMulNum_2 = Matrix(3, 4);
  Matrix resultTranspose_1 = Matrix(5, 5);
  Matrix resultTranspose_2 = Matrix(8, 7);
  Matrix resultTranspose_3 = Matrix(4, 3);
  Matrix resultCalcComplements = Matrix(5, 5);
  Matrix resultInverse = Matrix(5, 5);
};

#endif  //  SRC_TESTS_H

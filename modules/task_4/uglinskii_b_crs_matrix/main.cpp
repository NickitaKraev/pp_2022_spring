// Copyright 2022 Uglinskii Bogdan
#include <gtest/gtest.h>
#include <time.h>

#include <iostream>
#include <vector>

#include "./crs_multiplication.h"


TEST(Multiplication_seq, crs_50x50_30) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(50, 50, 30);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(50, 50, 30);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  std::vector<std::vector<double>> C;

  NormalMulty(ExpandMatrix(matrix_A), ExpandMatrix(matrix_B), &C);
  MatrixCRS crs_C;
  ConvertToCRS(C, &crs_C);
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, crs_C));
}

TEST(Multiplication_parallel, 3x3_4) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(3, 3, 4);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(3, 3, 4);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  MatrixCRS C_std;
  CRSMultiplySTD(matrix_A, matrix_B, &C_std);
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_std));
}

TEST(Multiplication_parallel, 10x10_10) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(10, 10, 10);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(10, 10, 10);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  MatrixCRS C_std;
  CRSMultiplySTD(matrix_A, matrix_B, &C_std);
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_std));
}

TEST(Multiplication_parallel, 25x25_35) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(25, 25, 35);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(25, 25, 35);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  MatrixCRS C_std;
  CRSMultiplySTD(matrix_A, matrix_B, &C_std);
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_std));
}

TEST(Multiplication_parallel, 30x30_40) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(30, 30, 40);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(30, 30, 40);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  MatrixCRS C_std;
  CRSMultiplySTD(matrix_A, matrix_B, &C_std);
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_std));
}

TEST(Multiplication_parallel, 50x50_65) {
  MatrixCRS matrix_A = GenerateRandomMatrixCRS(50, 50, 65);
  MatrixCRS matrix_B = GenerateRandomMatrixCRS(50, 50, 65);

  MatrixCRS matrix_C;
  CRSMultiply(matrix_A, matrix_B, &matrix_C);

  MatrixCRS C_std;
  CRSMultiplySTD(matrix_A, matrix_B, &C_std);
  ASSERT_TRUE(CompareMatrixCRS(matrix_C, C_std));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

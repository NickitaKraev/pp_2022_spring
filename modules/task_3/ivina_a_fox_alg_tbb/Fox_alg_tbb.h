// Copyright 2022 Ivina Anastasiya
#ifndef MODULES_TASK_3_IVINA_A_FOX_ALG_TBB_FOX_ALG_TBB_H_
#define MODULES_TASK_3_IVINA_A_FOX_ALG_TBB_FOX_ALG_TBB_H_

#include <vector>
#include <cstddef>

struct Cij {
  size_t i;
  size_t j;
};
using Matrix = std::vector<std::vector<double>>;
using MatrixRow = std::vector<double>;
using TasksForProcess = std::vector<Cij>;
using TasksForManyProcesses = std::vector<TasksForProcess>;

Matrix FillMatrixRandom(const Matrix &matrix);
void PrintMatrix(const Matrix &Matrix);
Matrix DenseMatrixMultiplication(const Matrix &a, const Matrix &b);
Matrix BlockMatrixMultiplication(const Matrix &a, const Matrix &b);
Matrix Fox(const Matrix &a, const Matrix &b);

#endif  // MODULES_TASK_3_IVINA_A_FOX_ALG_TBB_FOX_ALG_TBB_H_

// Copyright 2022 Javier Galindo


#ifndef MODULES_TASK_4_GALINDO_FOX_ALGORITHM_THREAD_GALINDO_FOX_ALGORITHM_THREAD_H_
#define MODULES_TASK_4_GALINDO_FOX_ALGORITHM_THREAD_GALINDO_FOX_ALGORITHM_THREAD_H_
#include <vector>
#include <iostream>
#include <ctime>
#include <random>
#include <cmath>
#include <limits>

typedef std::vector<double> Matrix;

bool isEqual(double x, double y);
bool isEqualMatrix(const Matrix& A, const Matrix& B);
bool isSizeCorrect(size_t size, size_t t_count);

Matrix createRandomMatrix(size_t size);
Matrix sequentialMatrixMultiplication(const std::vector<double>& A,
    const std::vector<double>& B, size_t BlockSize);
Matrix sequentialBlockMatrixMultiplication(const std::vector<double>& A,
    const std::vector<double>& B, size_t Size);
Matrix parallelBlockMatrixMultiplication(const std::vector<double>& A,
    const std::vector<double>& B, size_t Size, int threads_count);


#endif  // MODULES_TASK_4_GALINDO_FOX_ALGORITHM_THREAD_GALINDO_FOX_ALGORITHM_THREAD_H_

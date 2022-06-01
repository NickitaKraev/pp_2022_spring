// Copyright 2022 Schyotkin Artyom
#include "../../../modules/task_1/schyotkin_a_fox_mult/fox_mult.h"

#include <iostream>

std::vector<std::vector<double>> getRandom(int n) {
  std::random_device dev;
  static std::mt19937 gen(dev());

  std::vector<std::vector<double>> C(n, std::vector<double>(n, 0));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++) C[i][j] = gen() % 100;

  return C;
}

void multiply(std::vector<std::vector<double>>* C,
              const std::vector<std::vector<double>>& A,
              const std::vector<std::vector<double>>& B) {
  int n = A.size();
  (*C) = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 0; k < n; k++) (*C)[i][j] += A[i][k] * B[k][j];
}

void foxMultiplication(std::vector<std::vector<double>>* C,
                       const std::vector<std::vector<double>>& A,
                       const std::vector<std::vector<double>>& B,
                       int block_size) {
  if (A.size() != B[0].size()) {
    std::cout << "Error: different size\n";
    return;
  }

  int n = A.size();

  if (block_size > n) {
    std::cout << "Error: invalid block size\n";
    return;
  }

  (*C) = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));
  int endA, endB;

  for (int a = 0; a < n; a += block_size) {
    endA = std::min(a + block_size, n);
    for (int b = 0; b < n; b += block_size) {
      endB = std::min(b + block_size, n);
      for (int i = 0; i < n; i++) {
        for (int j = a; j < endA; j++) {
          for (int k = b; k < endB; k++) {
            (*C)[i][j] += A[i][k] * B[k][j];
          }
        }
      }
    }
  }
}

// Copyright 2022 Schyotkin Artyom
#include "../../../modules/task_2/schyotkin_a_fox_mult/fox_mult.h"

#include <omp.h>

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

void foxMultiplicationParallel(std::vector<std::vector<double>>* C,
                               const std::vector<std::vector<double>>& A,
                               const std::vector<std::vector<double>>& B) {
  if (A.size() != B[0].size()) {
    std::cout << "Error: different size\n";
    return;
  }

  int n = A.size();

  (*C) = std::vector<std::vector<double>>(n, std::vector<double>(n, 0));

  int q = std::sqrt(omp_get_max_threads());
  int block_size = n / q;

#pragma omp parallel num_threads(q* q)
  {
    int i_thread = omp_get_thread_num() / q;
    int j_thread = omp_get_thread_num() % q;
    int h1 = i_thread * block_size;
    int h2 = j_thread * block_size;
    std::vector<std::vector<double>> blockA(block_size), blockB(block_size);
    std::vector<std::vector<double>> blockC(block_size,
                                            std::vector<double>(block_size, 0));

    for (int z = 0; z < q; ++z) {
      int s = ((i_thread + z) % q) * block_size;
      for (int k = 0; k < block_size; ++k) {
        blockA[k] = std::vector<double>(A[h1 + k].begin() + s,
                                        A[h1 + k].begin() + s + block_size);
        blockB[k] = std::vector<double>(B[s + k].begin() + h2,
                                        B[s + k].begin() + (h2 + block_size));
      }
      for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < block_size; j++) {
          for (int t = 0; t < block_size; t++)
            blockC[i][j] += blockA[i][t] * blockB[t][j];
        }
      }
    }

    for (int i = 0; i < block_size; i++) {
      for (int j = 0; j < block_size; j++) {
        (*C)[i + h1][j + h2] = blockC[i][j];
      }
    }
  }
}

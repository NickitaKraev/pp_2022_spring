// Copyright 2022 Utyugov Denis
#include "../../../modules/task_4/utyugov_d_cannons_alg_std/cannons_alg.h"

#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "../../../3rdparty/unapproved/unapproved.h"

std::vector<double> getRandomVector(int size) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<double> vec(size);
  for (int i = 0; i < size; i++) {
    vec[i] = gen() % size;
  }
  return vec;
}

std::vector<std::vector<double>> getRndMatrix(int size) {
  std::vector<std::vector<double>> A(size, std::vector<double>(size));
  for (int i = 0; i < size; i++) {
    A[i] = getRandomVector(size);
  }
  return A;
}

std::vector<std::vector<double>> Multiplicate(
    std::vector<std::vector<double>> A, std::vector<std::vector<double>> B,
    int size) {
  std::vector<std::vector<double>> C(size, std::vector<double>(size));
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      for (int k = 0; k < size; k++) C[i][j] += A[i][k] * B[k][j];
  return C;
}

std::vector<std::vector<double>> BlockMultiplicate(
    std::vector<std::vector<double>> A, std::vector<std::vector<double>> B,
    int BlSize) {
  int size = A.size();
  std::vector<std::vector<double>> C(size, std::vector<double>(size, 0));
  int Minj, Mink = 0;

  for (int Globj = 0; Globj < size; Globj += BlSize) {
    Minj = std::min<int>(Globj + BlSize, size);
    for (int Globk = 0; Globk < size; Globk += BlSize) {
      Mink = std::min<int>(Globk + BlSize, size);

      for (int i = 0; i < size; i++)
        for (int j = Globj; j < Minj; j++)
          for (int k = Globk; k < Mink; k++) {
            C[i][j] += A[i][k] * B[k][j];
          }
    }
  }
  return C;
}

std::vector<std::vector<double>> CannonsAlg(std::vector<std::vector<double>> A,
                                            std::vector<std::vector<double>> B,
                                            int num_threads) {
  std::thread* threads = new std::thread[num_threads];
  int size = A.size();
  int q = std::sqrt(num_threads);

  int newSize = size;
  while (newSize % q != 0) {
    A.push_back(std::vector<double>(size, 0));
    B.push_back(std::vector<double>(size, 0));
    newSize++;
  }

  std::vector<std::vector<double>> C(newSize, std::vector<double>(newSize, 0));
  int BlSize = newSize / q;

  for (int i = 0; i < newSize; i++)
    for (int j = 0; j < newSize - size; j++) {
      A[i].push_back(0);
      B[i].push_back(0);
    }

  auto func = [&](int i_thread, int j_thread) {
    int place_i = i_thread;
    int place_j = j_thread;
    int Ai = 0, Aj = 0, Bi = 0, Bj = 0;

    std::vector<std::vector<double>> Aij(BlSize), Bij(BlSize),
        Cij(BlSize, std::vector<double>(BlSize, 0));

    // first iterration
    for (int n = 0; n < BlSize; n++) {
      Ai = place_i * BlSize + n;
      Aj = ((place_i + place_j) % q) * BlSize;
      Bi = Aj + n;
      Bj = place_j * BlSize;
      Aij[n] =
          std::vector<double>(A[Ai].begin() + Aj, A[Ai].begin() + Aj + BlSize);
      Bij[n] =
          std::vector<double>(B[Bi].begin() + Bj, B[Bi].begin() + Bj + BlSize);
    }

    // main construction
    int nextAi, nextAj, nextBi, nextBj = 0;
    for (int iter = 0; iter < q; iter++) {
      for (int i = 0; i < BlSize; i++)
        for (int j = 0; j < BlSize; j++)
          for (int k = 0; k < BlSize; k++) Cij[i][j] += Aij[i][k] * Bij[k][j];

      if (iter == q - 1) break;

      for (int n = 0; n < BlSize; n++) {
        nextAi = place_i * BlSize + n;
        nextAj = ((Aj / BlSize + iter + 1) % q) * BlSize;
        nextBi = ((Bi / BlSize + iter + 1) % q) * BlSize + n;
        nextBj = place_j * BlSize;
        Aij[n] = std::vector<double>(A[nextAi].begin() + nextAj,
                                     A[nextAi].begin() + nextAj + BlSize);
        Bij[n] = std::vector<double>(B[nextBi].begin() + nextBj,
                                     B[nextBi].begin() + nextBj + BlSize);
      }
    }
    for (int i = 0; i < BlSize; i++)
      for (int j = 0; j < BlSize; j++)
        C[place_i * BlSize + i][place_j * BlSize + j] = Cij[i][j];
  };

  int count = 0;
  for (int i = 0; i < q; ++i) {
    for (int j = 0; j < q; ++j) {
      threads[count] = std::thread(func, i, j);
      count++;
    }
  }

  for (int i = 0; i < num_threads; ++i) threads[i].join();

  // parallel resize
  auto resize = [&](int start, int temp_n) {
    for (auto i = start; i < temp_n; ++i) {
      C[i].resize(size);
    }
  };

  if (size != newSize) {
    std::thread* threads1 = new std::thread[BlSize];
    for (int i = 0; i < BlSize; ++i) {
      threads1[i] = std::thread(resize, i * q, i * q + q);
    }
    for (int j = 0; j < BlSize; ++j) {
      threads1[j].join();
    }
    delete[] threads1;
  }
  C.resize(size);
  delete[] threads;
  return C;

  return C;
}

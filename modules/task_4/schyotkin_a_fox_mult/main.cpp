// Copyright 2022 Schyotkin Artyom
#include <gtest/gtest.h>

#include "../../../3rdparty/unapproved/unapproved.h"
#include "./fox_mult.h"

TEST(FOX_MULT, TEST_1) {
  int size = 8;
  std::vector<std::vector<double>> A = getRandom(size);
  std::vector<std::vector<double>> B = getRandom(size);
  std::vector<std::vector<double>> C1;
  std::vector<std::vector<double>> C2;
  std::vector<std::vector<double>> C3;

  multiply(&C1, A, B);

  int block_size = 2;
  foxMultiplication(&C2, A, B, block_size);
  foxMultiplicationParallel(&C3, A, B);

  for (int i = 0; i < size; i++) {
    ASSERT_EQ(C1[i], C2[i]);
    ASSERT_EQ(C1[i], C3[i]);
  }
}

TEST(FOX_MULT, TEST_2) {
  int size = 16;
  std::vector<std::vector<double>> A = getRandom(size);
  std::vector<std::vector<double>> B = getRandom(size);
  std::vector<std::vector<double>> C1;
  std::vector<std::vector<double>> C2;

  multiply(&C1, A, B);
  foxMultiplicationParallel(&C2, A, B);

  for (int i = 0; i < size; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(FOX_MULT, TEST_3) {
  int size = 32;
  std::vector<std::vector<double>> A = getRandom(size);
  std::vector<std::vector<double>> B = getRandom(size);
  std::vector<std::vector<double>> C1;
  std::vector<std::vector<double>> C2;

  multiply(&C1, A, B);
  foxMultiplicationParallel(&C2, A, B);

  for (int i = 0; i < size; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(FOX_MULT, TEST_4) {
  int size = 8;
  std::vector<std::vector<double>> A = getRandom(size);
  std::vector<std::vector<double>> B = getRandom(size);
  std::vector<std::vector<double>> C1;
  std::vector<std::vector<double>> C2;

  multiply(&C1, A, B);
  foxMultiplicationParallel(&C2, A, B);

  for (int i = 0; i < size; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(FOX_MULT, TEST_5) {
  int size = 8;
  std::vector<std::vector<double>> A = getRandom(size);
  std::vector<std::vector<double>> B = getRandom(size);
  std::vector<std::vector<double>> C1;
  std::vector<std::vector<double>> C2;
  std::vector<std::vector<double>> C3;

  int block_size = 2;

  auto time1 = clock();
  foxMultiplication(&C2, A, B, block_size);
  auto time2 = clock();
  double time_seq = (static_cast<double>(time2 - time1) / CLOCKS_PER_SEC);

  time1 = clock();
  foxMultiplicationParallel(&C3, A, B);
  time2 = clock();
  double time_par = (static_cast<double>(time2 - time1) / CLOCKS_PER_SEC);

  std::cout << "Fox mult seq: " << time_seq << "\n";
  std::cout << "Fox mult par: " << time_par << "\n";
  std::cout << "Eff: " << time_seq / time_par << "\n";
}

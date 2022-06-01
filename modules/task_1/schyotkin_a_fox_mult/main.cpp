// Copyright 2022 Schyotkin Artyom
#include <gtest/gtest.h>

#include "./fox_mult.h"

TEST(FOX_MULT, TEST_1) {
  int size = 8;
  std::vector<std::vector<double>> A = getRandom(size);
  std::vector<std::vector<double>> B = getRandom(size);
  std::vector<std::vector<double>> C1;
  std::vector<std::vector<double>> C2;

  multiply(&C1, A, B);

  int block_size = 2;
  foxMultiplication(&C2, A, B, block_size);

  for (int i = 0; i < size; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(FOX_MULT, TEST_2) {
  int size = 16;
  std::vector<std::vector<double>> A = getRandom(size);
  std::vector<std::vector<double>> B = getRandom(size);
  std::vector<std::vector<double>> C1;
  std::vector<std::vector<double>> C2;

  multiply(&C1, A, B);

  int block_size = 4;
  foxMultiplication(&C2, A, B, block_size);

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

  int block_size = 8;
  foxMultiplication(&C2, A, B, block_size);

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

  int block_size = 8;
  foxMultiplication(&C2, A, B, block_size);

  for (int i = 0; i < size; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

TEST(FOX_MULT, TEST_5) {
  int size = 4;
  std::vector<std::vector<double>> A = getRandom(size);
  std::vector<std::vector<double>> B = getRandom(size);
  std::vector<std::vector<double>> C1;
  std::vector<std::vector<double>> C2;

  multiply(&C1, A, B);

  int block_size = 1;
  foxMultiplication(&C2, A, B, block_size);

  for (int i = 0; i < size; i++) {
    ASSERT_EQ(C1[i], C2[i]);
  }
}

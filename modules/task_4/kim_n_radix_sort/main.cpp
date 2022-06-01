// Copyright 2022 Kim Nikita
#include <gtest/gtest.h>
// #include <omp.h>
#include <vector>
#include <iostream>
#include "./radix_sort.h"

TEST(STD_THREAD, Vector_One_Size) {
  int size = 1;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(STD_THREAD, Vector_Two_Size) {
  int size = 2;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(STD_THREAD, Vector_Odd_Size) {
  int size = 21;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(STD_THREAD, Vector_Even_Size) {
  int size = 20;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(STD_THREAD, Vector_Odd_Large_Size) {
  int size = 121;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(STD_THREAD, Vector_Even_Large_Size) {
  int size = 120;
  std::vector<int> input_vec = getRandomVector(size);

  std::vector<int> exp_res = radixSort(input_vec, size);

  std::vector<int> res = radixSortParallel(input_vec, size);

  ASSERT_EQ(exp_res, res);
}

TEST(STD_THREAD, Vector_Mega_Large_Size) {
  int size = 1000003;
  // double t1, t2;
  std::vector<int> input_vec = getRandomVector(size);

  // t1 = omp_get_wtime();
  std::vector<int> exp_res = radixSort(input_vec, size);
  // t1 = omp_get_wtime() - t1;

  // t2 = omp_get_wtime();
  std::vector<int> res = radixSortParallel(input_vec, size);
  // t2 = omp_get_wtime() - t2;

  ASSERT_EQ(exp_res, res);
  // std::cout << "Sequential: " << t1 << " Parallel: " << t2 << "\n" << "Boost: " << t1/t2 << "\n";
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

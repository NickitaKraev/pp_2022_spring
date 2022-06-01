// Copyright 2022 Tulkina Olga

#include <gtest/gtest.h>

#include "../../modules/task_3/tulkina_o_labeling/labeling.h"

TEST(TBB, Test_1x1) {
  std::vector<std::vector<int>> binary_image = {{0}};

  binary_image = labeling(binary_image);

  std::vector<std::vector<int>> expected = {{0}};
  int a = binary_image.size();
  for (int i = 0; i < a; i++) EXPECT_EQ(expected[i], binary_image[i]);
}

TEST(TBB, Test_1x5) {
  std::vector<std::vector<int>> binary_image = {{0, 1, 1, 0, 1}};

  binary_image = labeling(binary_image);

  std::vector<std::vector<int>> expected = {{0, 2, 2, 0, 5}};
  int a = binary_image.size();
  for (int i = 0; i < a; i++) EXPECT_EQ(expected[i], binary_image[i]);
}

TEST(TBB, Test_5x1) {
  std::vector<std::vector<int>> binary_image = {{0}, {1}, {1}, {1}, {1}};

  binary_image = labeling(binary_image);

  std::vector<std::vector<int>> expected = {{0}, {2}, {2}, {2}, {2}};
  int a = binary_image.size();
  for (int i = 0; i < a; i++) EXPECT_EQ(expected[i], binary_image[i]);
}

TEST(TBB, Test_10x10) {
  std::vector<std::vector<int>> binary_image = {
      {0, 1, 1, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0, 0, 0, 1, 0},
      {1, 0, 1, 1, 1, 1, 1, 1, 0, 0}, {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
      {1, 0, 0, 0, 0, 0, 0, 1, 0, 1}, {1, 0, 0, 1, 0, 1, 0, 1, 0, 0},
      {1, 0, 1, 0, 1, 1, 1, 0, 0, 1}, {1, 0, 0, 1, 1, 1, 0, 0, 1, 1},
      {1, 0, 0, 0, 1, 0, 0, 0, 1, 1}, {1, 0, 0, 0, 0, 0, 1, 1, 1, 1}};

  binary_image = labeling(binary_image);

  std::vector<std::vector<int>> expected = {
      {0, 2, 2, 0, 2, 0, 0, 0, 0, 0},    {0, 0, 2, 2, 0, 0, 0, 0, 2, 0},
      {21, 0, 2, 2, 2, 2, 2, 2, 0, 0},   {21, 0, 0, 0, 0, 2, 2, 0, 2, 0},
      {21, 0, 0, 0, 0, 0, 0, 2, 0, 2},   {21, 0, 0, 2, 0, 2, 0, 2, 0, 0},
      {21, 0, 2, 0, 2, 2, 2, 0, 0, 70},  {21, 0, 0, 2, 2, 2, 0, 0, 70, 70},
      {21, 0, 0, 0, 2, 0, 0, 0, 70, 70}, {21, 0, 0, 0, 0, 0, 70, 70, 70, 70}};
  int a = binary_image.size();
  for (int i = 0; i < a; i++) EXPECT_EQ(expected[i], binary_image[i]);
}

TEST(TBB, Test_10x10_version2) {
  int width = 10;
  int height = 10;
  std::vector<std::vector<int>> binary_image = {
      {0, 1, 1, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 1, 1, 0, 0, 0, 0, 1, 0},
      {1, 0, 1, 1, 1, 1, 1, 1, 0, 0}, {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
      {1, 0, 0, 0, 0, 0, 0, 1, 0, 1}, {1, 0, 0, 1, 0, 1, 0, 1, 0, 0},
      {1, 0, 1, 0, 1, 1, 1, 0, 0, 1}, {1, 0, 0, 1, 1, 1, 0, 0, 1, 1},
      {1, 0, 0, 0, 1, 0, 0, 0, 1, 1}, {1, 0, 0, 0, 0, 0, 1, 1, 1, 1}};

  std::vector<std::vector<int>> binary_image_tbb(height,
                                                 std::vector<int>(width));
  binary_image_tbb = labeling_tbb(binary_image);

  std::vector<std::vector<int>> expected = {
      {0, 2, 2, 0, 2, 0, 0, 0, 0, 0},    {0, 0, 2, 2, 0, 0, 0, 0, 2, 0},
      {21, 0, 2, 2, 2, 2, 2, 2, 0, 0},   {21, 0, 0, 0, 0, 2, 2, 0, 2, 0},
      {21, 0, 0, 0, 0, 0, 0, 2, 0, 2},   {21, 0, 0, 2, 0, 2, 0, 2, 0, 0},
      {21, 0, 2, 0, 2, 2, 2, 0, 0, 70},  {21, 0, 0, 2, 2, 2, 0, 0, 70, 70},
      {21, 0, 0, 0, 2, 0, 0, 0, 70, 70}, {21, 0, 0, 0, 0, 0, 70, 70, 70, 70}};
  int a = binary_image.size();
  for (int i = 0; i < a; i++) EXPECT_EQ(binary_image_tbb[i], expected[i]);
}

TEST(TBB, Test_3000x3000) {
  int width = 3000;
  int height = 3000;

  std::random_device dev;
  std::mt19937 gen(dev());
  std::uniform_real_distribution<> urd(0, 2);
  std::vector<std::vector<int>> binary_image(height, std::vector<int>(width));
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < height; x++) {
      binary_image[y][x] = urd(gen);
    }
  }

  std::vector<std::vector<int>> binary_image_seq(height,
                                                 std::vector<int>(width));
  double t1 = omp_get_wtime();
  binary_image_seq = labeling(binary_image);
  double t2 = omp_get_wtime();

  std::vector<std::vector<int>> binary_image_tbb(height,
                                                 std::vector<int>(width));
  double t3 = omp_get_wtime();
  binary_image_tbb = labeling_tbb(binary_image);

  double t4 = omp_get_wtime();
  int a = binary_image.size();
  for (int i = 0; i < a; i++)
    EXPECT_EQ(binary_image_tbb[i], binary_image_seq[i]);
  printf("seq labeling: %lf\n", t2 - t1);
  printf("parallel labeling: %lf\n", t4 - t3);
  printf("labeling: %lf\n", (t2 - t1) / (t4 - t3));
}

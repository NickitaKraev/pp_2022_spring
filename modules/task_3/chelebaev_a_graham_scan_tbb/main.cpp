// Copyright 2022 Chelebaev Artem
#include "../../../modules/task_3/chelebaev_a_graham_scan_tbb/graham_scan_tbb.h"
#include "gtest/gtest.h"
#define THREAD_NUM 4

TEST(graham_scan_tbb, fixed_set_1) {
  std::vector<std::pair<double, double>> result(16);
  result[0] = std::make_pair(0, 0);
  result[1] = std::make_pair(1, -3);
  result[2] = std::make_pair(3, -2);
  result[3] = std::make_pair(6, -4);
  result[4] = std::make_pair(7, -2);
  result[5] = std::make_pair(5, 1);
  result[6] = std::make_pair(8, 3);
  result[7] = std::make_pair(2, 6);
  result[8] = std::make_pair(1, 3);
  result[9] = std::make_pair(2, 1);
  result[10] = std::make_pair(3, 3);
  result[11] = std::make_pair(5, 5);
  result[12] = std::make_pair(4, -1);
  result[13] = std::make_pair(5, -2);
  result[14] = std::make_pair(7, 1);
  result[15] = std::make_pair(5, 3);

  auto res = tbb_graham_conv_hull(result.begin(), result.end(), 4);

  std::vector<std::pair<double, double>> check(res.size());
  check[6] = std::make_pair(2, 6);
  check[5] = std::make_pair(5, 5);
  check[4] = std::make_pair(8, 3);
  check[3] = std::make_pair(7, -2);
  check[2] = std::make_pair(6, -4);
  check[1] = std::make_pair(1, -3);
  check[0] = std::make_pair(0, 0);

  ASSERT_EQ(res, check);
}

TEST(graham_scan_tbb, fixed_set_2) {
  std::vector<std::pair<double, double>> result(22);
  result[0] = std::make_pair(0, 1);
  result[1] = std::make_pair(0, -5);
  result[2] = std::make_pair(0, -6);
  result[3] = std::make_pair(4, -6);
  result[4] = std::make_pair(2, -4);
  result[5] = std::make_pair(4, -2);
  result[6] = std::make_pair(7, -2);
  result[7] = std::make_pair(5, -1);
  result[8] = std::make_pair(5, 2);
  result[9] = std::make_pair(2, 1);
  result[10] = std::make_pair(3, 3);
  result[11] = std::make_pair(7, 2);
  result[12] = std::make_pair(9, 2);
  result[13] = std::make_pair(9, -4);
  result[14] = std::make_pair(8, 5);
  result[15] = std::make_pair(6, 4);
  result[16] = std::make_pair(3, 4);
  result[17] = std::make_pair(2, 5);
  result[18] = std::make_pair(1, 3);
  result[19] = std::make_pair(0, 2);
  result[20] = std::make_pair(0, 0);
  result[21] = std::make_pair(-1, 0);

  auto res = tbb_graham_conv_hull(result.begin(), result.end(), 4);

  std::vector<std::pair<double, double>> check(res.size());
  check[7] = std::make_pair(0, 2);
  check[6] = std::make_pair(2, 5);
  check[5] = std::make_pair(8, 5);
  check[4] = std::make_pair(9, 2);
  check[3] = std::make_pair(9, -4);
  check[2] = std::make_pair(4, -6);
  check[1] = std::make_pair(0, -6);
  check[0] = std::make_pair(-1, 0);

  ASSERT_EQ(res, check);
}

TEST(graham_scan_tbb, random_points) {
  int size = 1000;
  auto area = gen_random_points(size);
  std::vector<std::pair<double, double>> check(size);

  auto res_tbb = tbb_graham_conv_hull(area.begin(), area.end(), 4);
  auto res_std = graham_conv_hull(area.begin(), area.end());

  ASSERT_EQ(res_tbb, res_std);
}

TEST(graham_scan_tbb, random_points_seq) {
  int size = 10000;
  auto area = gen_random_points(size);
  std::vector<std::pair<double, double>> check(size);

  auto res_std = graham_conv_hull(area.begin(), area.end());

  ASSERT_EQ(res_std, res_std);
}

TEST(graham_scan_tbb, random_points_tbb) {
  int size = 10000;
  auto area = gen_random_points(size);
  std::vector<std::pair<double, double>> check(size);

  auto res_tbb = tbb_graham_conv_hull(area.begin(), area.end(), 4);

  ASSERT_EQ(res_tbb, res_tbb);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

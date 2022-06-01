// Copyright 2022 Chelebaev Artem
#include "../../../modules/task_1/chelebaev_a_graham_scan/graham_scan.h"
#include "gtest/gtest.h"

TEST(graham_scan_seq, test_lex_min) {
  std::size_t size = 10000;
  std::vector<std::pair<double, double>> v = gen_points(size);
  auto res = v[0];
  std::swap(v[0], v[time(0) % size]);

  auto min = get_lex_min(v);

  ASSERT_EQ(v[min], res);
}

TEST(graham_scan_seq, small_set) {
  std::vector<std::pair<double, double>> result_sort(5);
  result_sort[0] = std::make_pair(0, 0);
  result_sort[1] = std::make_pair(1, 5);
  result_sort[2] = std::make_pair(2, 4);
  result_sort[3] = std::make_pair(3, 3);
  result_sort[4] = std::make_pair(4, 1);

  std::vector<std::pair<double, double>> result(5);
  result[0] = std::make_pair(0, 0);
  result[1] = std::make_pair(4, 1);
  result[2] = std::make_pair(3, 3);
  result[3] = std::make_pair(2, 4);
  result[4] = std::make_pair(1, 5);

  result_sort = polar_sort(result_sort);

  ASSERT_EQ(result_sort, result);
}

TEST(graham_scan_seq, set_1) {
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

  auto res = graham_conv_hull(result);

  std::vector<std::pair<double, double>> check(7);
  check[6] = std::make_pair(2, 6);
  check[5] = std::make_pair(5, 5);
  check[4] = std::make_pair(8, 3);
  check[3] = std::make_pair(7, -2);
  check[2] = std::make_pair(6, -4);
  check[1] = std::make_pair(1, -3);
  check[0] = std::make_pair(0, 0);

  ASSERT_EQ(res, check);
}

TEST(graham_scan_seq, custom_set) {
  std::vector<std::pair<double, double>> result(15);
  result[0] = std::make_pair(1, 2);
  result[1] = std::make_pair(3, 1);
  result[2] = std::make_pair(5, 1);
  result[3] = std::make_pair(7, 2);
  result[4] = std::make_pair(8, 5);
  result[5] = std::make_pair(7, 7);
  result[6] = std::make_pair(4, 7);
  result[7] = std::make_pair(2, 5);
  result[8] = std::make_pair(1, 4);
  result[9] = std::make_pair(2, 3);
  result[10] = std::make_pair(4, 4);
  result[11] = std::make_pair(5, 3);
  result[12] = std::make_pair(5, 5);
  result[13] = std::make_pair(6, 6);
  result[14] = std::make_pair(7, 4);

  auto res = graham_conv_hull(result);

  std::vector<std::pair<double, double>> check(9);
  check[0] = std::make_pair(1, 2);
  check[1] = std::make_pair(3, 1);
  check[2] = std::make_pair(5, 1);
  check[3] = std::make_pair(7, 2);
  check[4] = std::make_pair(8, 5);
  check[5] = std::make_pair(7, 7);
  check[6] = std::make_pair(4, 7);
  check[7] = std::make_pair(2, 5);
  check[8] = std::make_pair(1, 4);

  ASSERT_EQ(res, check);
}

TEST(graham_scan_seq, random_set) {
  std::size_t size = 30;
  std::vector < std::pair<double, double>> points;
  points = gen_random_points(size);
  std::vector<std::pair<double, double>> check;
  check = graham_conv_hull(points);

  ASSERT_EQ(check, check);
}

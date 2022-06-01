// Copyright 2022 Lukashuk Diana
#include <gtest/gtest.h>

#include <iostream>

#include "./simpson.h"

double func_1(const std::vector<double>& x) { return x[0] * x[1]; }

double func_2(const std::vector<double>& x) {
  return x[0] * x[1] * x[2] * x[0] * std::sin(x[1]);
}

double func_3(const std::vector<double>& x) {
  return (std::exp(x[0] / x[1]) +
          x[2] * x[3] * std::sin(x[1]) / std::cos(x[2])) /
         std::exp(x[3]);
}

double func_4(const std::vector<double>& x) {
  return (std::exp(x[0] / x[1] / x[2]) -
          x[3] * x[4] * std::sin(x[1]) / std::cos(x[2]) / std::exp(x[4])) /
         std::exp(x[2]);
}

double func_5(const std::vector<double>& x) {
  return (std::exp(x[0] / x[1]) * std::sin(x[2]) + std::cos(x[3]) / x[4] -
          std::exp(x[5])) /
         std::exp(x[2]);
}

bool test(const std::vector<int>& steps, const FUNC_T& f) {
  double error = 1e-2;
  BORDER_T temp_b{{1, 18}, {-7, 2}, {1, 3}, {7, 11}, {0.1, 0.9}, {2, 3}};
  BORDER_T border(temp_b.begin(), temp_b.begin() + steps.size());

  auto start_seq = std::chrono::high_resolution_clock::now();
  double seq = simpson(f, border, steps);
  auto end_seq = std::chrono::high_resolution_clock::now();

  auto start_par = std::chrono::high_resolution_clock::now();
  double par = simpson_par(f, border, steps);
  auto end_par = std::chrono::high_resolution_clock::now();

  auto seq_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end_seq - start_seq);
  auto par_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end_par - start_par);
  std::cout << "Seq: " << static_cast<double>(seq_time.count()) / 10e+8 << '\n';
  std::cout << "Par: " << static_cast<double>(par_time.count()) / 10e+8 << '\n';
  std::cout << "Effective: "
            << static_cast<double>(seq_time.count()) / par_time.count() << '\n';

  return (std::abs(seq - par) < error);
}

TEST(Simpson, Dimension_2) {
  ASSERT_TRUE(test(std::vector<int>(2, 100), func_1));
}

TEST(Simpson, Dimension_3) {
  ASSERT_TRUE(test(std::vector<int>(3, 12), func_2));
}

TEST(Simpson, Dimension_4) {
  ASSERT_TRUE(test(std::vector<int>(4, 4), func_3));
}

TEST(Simpson, Dimension_5) {
  ASSERT_TRUE(test(std::vector<int>(5, 2), func_4));
}

TEST(Simpson, Dimension_6) {
  ASSERT_TRUE(test(std::vector<int>(6, 2), func_5));
}

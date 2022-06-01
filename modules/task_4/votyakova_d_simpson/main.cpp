// Copyright 2022 Votyakova Daria
#include <gtest/gtest.h>

#include <cmath>

#include "../../../3rdparty/unapproved/unapproved.h"
#include "./simpson.h"

TEST(SIMPSON_METHOD_STD, TEST_FUNCTION_1) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        return x * x - 2 * y;
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}});
  std::vector<int> n({5, 5});

  double result = getSTDSimpson(f, limits, n);
  double ref = 293.99;

  double error = 100;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_STD, TEST_FUNCTION_2) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return log10(2 * x * x) + sqrt(z) + 5 * y;
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {2, 5}});
  std::vector<int> n({2, 2, 2});

  double result = getSTDSimpson(f, limits, n);
  double ref = 203.74;

  double error = 100;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_STD, TEST_FUNCTION_3) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return x * y * z;
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {4, 5}});
  std::vector<int> n({2, 2, 2});

  double result = getSTDSimpson(f, limits, n);
  double ref = 283.50;

  double error = 100;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_STD, TEST_FUNCTION_4) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return x - sqrt(10) * 5 * y + z;
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {0, 5}});
  std::vector<int> n({3, 2, 2});

  double result = getSTDSimpson(f, limits, n);
  double ref = -426.512;

  double error = 100;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_STD, TEST_FUNCTION_5) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        double t = vec[3];
        return cos(5 * x) + exp(y) + 2.9 * sin(z) - t * t;
      };

  std::vector<std::pair<double, double>> limits(
      {{4, 10}, {1, 2}, {1, 5}, {6, 10}});
  std::vector<int> n({2, 2, 1, 1});

  auto seq_1 = clock();
  getSeqSimpson(f, limits, n);
  auto seq_2 = clock();

  auto par_1 = clock();
  getSTDSimpson(f, limits, n);
  auto par_2 = clock();

  auto speed = (static_cast<float>(seq_2 - seq_1) / CLOCKS_PER_SEC) /
               (static_cast<float>(par_2 - par_1) / CLOCKS_PER_SEC);

  std::cout << static_cast<float>(seq_2 - seq_1) / CLOCKS_PER_SEC << std::endl;
  std::cout << static_cast<float>(par_2 - par_1) / CLOCKS_PER_SEC << std::endl;
  std::cout << speed << std::endl;
}

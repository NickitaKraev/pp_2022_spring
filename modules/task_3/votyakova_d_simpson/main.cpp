// Copyright 2022 Votyakova Daria
#include <gtest/gtest.h>
#include <omp.h>

#include <cmath>

#include "./simpson.h"

TEST(SIMPSON_METHOD_TBB, TEST_FUNCTION_1) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        return x * x - 2 * y;
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}});
  std::vector<int> n({3, 3});

  double result = getTBBSimpson(f, limits, n);
  double ref = 293.99;

  double error = 10;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_TBB, TEST_FUNCTION_2) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return log10(2 * x * x) + sqrt(z) + 5 * y;
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {2, 5}});
  std::vector<int> n({2, 2, 2});

  double result = getTBBSimpson(f, limits, n);
  double ref = 203.74;

  double error = 10;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_TBB, TEST_FUNCTION_3) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return x * y * z;
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {4, 5}});
  std::vector<int> n({2, 2, 2});

  double result = getTBBSimpson(f, limits, n);
  double ref = 283.50;

  double error = 10;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_TBB, TEST_FUNCTION_4) {
  const std::function<double(std::vector<double>)> f =
      [](std::vector<double> vec) {
        double x = vec[0];
        double y = vec[1];
        double z = vec[2];
        return y + cos(-2 * x * z);
      };

  std::vector<std::pair<double, double>> limits({{4, 10}, {1, 2}, {0, 5}});
  std::vector<int> n({2, 2, 2});

  double result = getTBBSimpson(f, limits, n);
  double ref = 44.45;

  double error = 10;
  ASSERT_NEAR(result, ref, error);
}

TEST(SIMPSON_METHOD_TBB, TEST_FUNCTION_5) {
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
  std::vector<int> n({2, 2, 2, 2});

  double t1 = omp_get_wtime();
  double seq_result = getSeqSimpson(f, limits, n);
  double t2 = omp_get_wtime();
  double seq_time = t2 - t1;

  t1 = omp_get_wtime();
  double parallel_result = getTBBSimpson(f, limits, n);
  t2 = omp_get_wtime();
  double parallel_time = t2 - t1;

  std::cout << "Seq. time     " << seq_time << std::endl;
  std::cout << "Parallel time " << parallel_time << std::endl;
  std::cout << "Speed         " << seq_time / parallel_time << std::endl;

  double ref = -5832.64;

  double error = 100;
  ASSERT_NEAR(parallel_result, ref, error);
  ASSERT_NEAR(seq_result, ref, error);
}

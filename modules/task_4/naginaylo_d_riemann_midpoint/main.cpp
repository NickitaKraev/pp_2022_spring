// Copyright 2022 Naginaylo Dmitriy
#include <gtest/gtest.h>

#include <chrono>  // NOLINT
#include <cmath>

#include "./riemann_midpoint.h"

const double error = 200;

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;

void time_test(const int dim, const int subdiv, const vector_pair& limits,
               const function& func, double* result, double* parallel_result) {
  // seq
  auto time_start = high_resolution_clock::now();
  *result = riemannMidpoint(dim, subdiv, limits, func);
  auto time_end = high_resolution_clock::now();
  double time_seq =
      duration_cast<microseconds>(time_end - time_start).count() / 1000.0;

  // parallel
  time_start = high_resolution_clock::now();
  *parallel_result = riemannMidpointParallel(dim, subdiv, limits, func);
  time_end = high_resolution_clock::now();
  double time_parallel =
      duration_cast<microseconds>(time_end - time_start).count() / 1000.0;

  double speed = time_seq / time_parallel;
  std::cout << "Sequential time | " << time_seq << " seconds\n";
  std::cout << "Parallel time   | " << time_parallel << " seconds\n";
  std::cout << "Speed-up        | " << speed << " times\n";
}

TEST(RIEMANN_MIDPOINT_TBB, TEST_FUNC_1) {
  const int dim = 1;
  const int subdiv = 10;
  const vector_pair limits = {{0, 4}};
  const function func = [](vector_double vec) {
    const double x = vec[0];
    return 2 * sin(x);
  };

  const double reference = 3.307;
  double result, parallel_result;

  time_test(dim, subdiv, limits, func, &result, &parallel_result);

  ASSERT_NEAR(result, reference, error);
  ASSERT_NEAR(parallel_result, reference, error);
}

TEST(RIEMANN_MIDPOINT_TBB, TEST_FUNC_2) {
  const int dim = 2;
  const int subdiv = 10;
  const vector_pair limits = {{1, 2}, {-5, 8}};
  const function func = [](vector_double vec) {
    const double x = vec[0];
    const double y = vec[1];
    return 2 * sin(x) + y * y;
  };

  const double reference = 237.196;
  double result, parallel_result;

  time_test(dim, subdiv, limits, func, &result, &parallel_result);

  ASSERT_NEAR(result, reference, error);
  ASSERT_NEAR(parallel_result, reference, error);
}

TEST(RIEMANN_MIDPOINT_TBB, TEST_FUNC_3) {
  const int dim = 2;
  const int subdiv = 10;
  const vector_pair limits = {{1, 2}, {-5, 8}};
  const function func = [](vector_double vec) {
    const double x = vec[0];
    const double y = vec[1];
    return 2 * cos(y) + x * x;
  };

  const double reference = 30.394;
  double result, parallel_result;

  time_test(dim, subdiv, limits, func, &result, &parallel_result);

  ASSERT_NEAR(result, reference, error);
  ASSERT_NEAR(parallel_result, reference, error);
}

TEST(RIEMANN_MIDPOINT_TBB, TEST_FUNC_4) {
  const int dim = 3;
  const int subdiv = 5;
  const vector_pair limits = {{1, 2}, {-5, 8}, {10, 14}};
  const function func = [](vector_double vec) {
    const double x = vec[0];
    const double y = vec[1];
    const double z = vec[2];
    return 4 * tan(x) + sin(y) * y - z;
  };

  const double reference = -303.872;
  double result, parallel_result;

  time_test(dim, subdiv, limits, func, &result, &parallel_result);

  ASSERT_NEAR(result, reference, error);
  ASSERT_NEAR(parallel_result, reference, error);
}

TEST(RIEMANN_MIDPOINT_TBB, TEST_FUNC_5) {
  const int dim = 3;
  const int subdiv = 5;
  const vector_pair limits = {{4, 6}, {-2, 7}, {-1, 11}};
  const function func = [](vector_double vec) {
    const double x = vec[0];
    const double y = vec[1];
    const double z = vec[2];
    return (x + y + z) / (sin(x));
  };

  const double reference = -4226.674;
  double result, parallel_result;

  time_test(dim, subdiv, limits, func, &result, &parallel_result);

  ASSERT_NEAR(result, reference, error);
  ASSERT_NEAR(parallel_result, reference, error);
}

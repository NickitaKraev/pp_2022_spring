// Copyright 2022 Naginaylo Dmitriy
#include <gtest/gtest.h>

#include <cmath>

#include "./riemann_midpoint.h"

const double error = 200;

TEST(RIEMANN_MIDPOINT_SEQ, TEST_FUNC_1) {
  const int dim = 1;
  const int subdiv = 10;
  const vector_pair limits = {{0, 4}};
  const function func = [](vector_double vec) {
    const double x = vec[0];
    return 2 * sin(x);
  };

  const double reference = 3.307;
  double result = riemannMidpoint(dim, subdiv, limits, func);

  ASSERT_NEAR(result, reference, error);
}

TEST(RIEMANN_MIDPOINT_SEQ, TEST_FUNC_2) {
  const int dim = 2;
  const int subdiv = 10;
  const vector_pair limits = {{1, 2}, {-5, 8}};
  const function func = [](vector_double vec) {
    const double x = vec[0];
    const double y = vec[1];
    return 2 * sin(x) + y * y;
  };

  const double reference = 237.196;
  double result = riemannMidpoint(dim, subdiv, limits, func);

  ASSERT_NEAR(result, reference, error);
}

TEST(RIEMANN_MIDPOINT_SEQ, TEST_FUNC_3) {
  const int dim = 2;
  const int subdiv = 10;
  const vector_pair limits = {{1, 2}, {-5, 8}};
  const function func = [](vector_double vec) {
    const double x = vec[0];
    const double y = vec[1];
    return 2 * cos(y) + x * x;
  };

  const double reference = 30.394;
  double result = riemannMidpoint(dim, subdiv, limits, func);

  ASSERT_NEAR(result, reference, error);
}

TEST(RIEMANN_MIDPOINT_SEQ, TEST_FUNC_4) {
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
  double result = riemannMidpoint(dim, subdiv, limits, func);

  ASSERT_NEAR(result, reference, error);
}

TEST(RIEMANN_MIDPOINT_SEQ, TEST_FUNC_5) {
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
  double result = riemannMidpoint(dim, subdiv, limits, func);

  ASSERT_NEAR(result, reference, error);
}

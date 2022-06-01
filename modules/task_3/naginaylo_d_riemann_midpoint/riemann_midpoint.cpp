// Copyright 2022 Naginaylo Dmitriy
#include "../../../modules/task_3/naginaylo_d_riemann_midpoint/riemann_midpoint.h"

// Helper funcs
///////////////////////////////////////////////////////////////////////////////

vector_double find_deltas(const int dim, const int subdiv,
                          const vector_pair& limits) {
  vector_double delta(dim);
  for (int i = 0; i < dim; i++) {
    delta[i] = (limits[i].second - limits[i].first) / subdiv;
  }
  return delta;
}

///////////////////////////////////////////////////////////////////////////////

int find_iter_num(const int dim, const int subdiv) {
  int iter_num = 1;
  for (int i = 0; i < dim; i++) {
    iter_num = iter_num * subdiv;
  }
  return iter_num;
}

///////////////////////////////////////////////////////////////////////////////

vector_double find_midpoint(const int dim, const int subdiv,
                            const vector_pair& limits,
                            const vector_double& delta, const int iter) {
  vector_double point(dim);
  for (int i = 0; i < dim; i++) {
    point[i] = limits[i].first + (iter % subdiv) * delta[i] + delta[i] * 0.5;
  }

  return point;
}

///////////////////////////////////////////////////////////////////////////////

// Seq
double main_loop(const int dim, const int subdiv, const vector_pair& limits,
                 const function& func, const int iter_num,
                 const vector_double& delta) {
  double result = 0.0;
  for (int iter = 0; iter < iter_num; iter++) {
    vector_double point = find_midpoint(dim, subdiv, limits, delta, iter);
    result += func(point);
  }

  return result;
}

// Parallel
double main_loop_parallel(const int dim, const int subdiv,
                          const vector_pair& limits, const function& func,
                          const int iter_num, const vector_double& delta) {
  double result = tbb::parallel_reduce(
      tbb::blocked_range<int>(0, iter_num), 0.0,
      [&](tbb::blocked_range<int> r, double local_result) {
        for (int iter = r.begin(); iter < r.end(); ++iter) {
          vector_double point = find_midpoint(dim, subdiv, limits, delta, iter);
          local_result += func(point);
        }
        return local_result;
      },
      std::plus<double>());

  return result;
}

///////////////////////////////////////////////////////////////////////////////

double find_area(const int dim, const vector_double& delta,
                 const double result) {
  double final_result = result;
  for (int i = 0; i < dim; i++) {
    final_result *= delta[i];
  }
  return final_result;
}

///////////////////////////////////////////////////////////////////////////////

// Main func
///////////////////////////////////////////////////////////////////////////////

// Seq
double riemannMidpoint(const int dim, const int subdiv,
                       const vector_pair& limits, const function& func) {
  int iter_num = find_iter_num(dim, subdiv);
  vector_double delta = find_deltas(dim, subdiv, limits);

  double result = main_loop(dim, subdiv, limits, func, iter_num, delta);
  result = find_area(dim, delta, result);

  return result;
}

// Parallel OMP
double riemannMidpointParallel(const int dim, const int subdiv,
                               const vector_pair& limits,
                               const function& func) {
  int iter_num = find_iter_num(dim, subdiv);
  vector_double delta = find_deltas(dim, subdiv, limits);

  double result =
      main_loop_parallel(dim, subdiv, limits, func, iter_num, delta);
  result = find_area(dim, delta, result);

  return result;
}

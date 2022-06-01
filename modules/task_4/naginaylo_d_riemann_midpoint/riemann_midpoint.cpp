// Copyright 2022 Naginaylo Dmitriy
#include "../../../modules/task_4/naginaylo_d_riemann_midpoint/riemann_midpoint.h"

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
  double result = 0.0;
  std::vector<double> local_result(THREADS, 0.0);

  auto work_lambda = [&dim, &subdiv, &limits, &delta, &func, &local_result](
                         int begin, int end, int index) {
    for (int iter = begin; iter < end; iter++) {
      vector_double point = find_midpoint(dim, subdiv, limits, delta, iter);
      local_result[index] += func(point);
    }
  };

  std::vector<std::thread> threads(THREADS);
  const int grainsize = iter_num / THREADS;

  for (int index = 0; index < THREADS - 1; ++index) {
    int start = grainsize * index;
    int end = grainsize * (index + 1);

    threads[index] =
        std::thread(work_lambda, start, end, index);
  }
  threads.back() = std::thread(work_lambda, grainsize * (THREADS - 1), iter_num,
                               THREADS - 1);

  for (auto&& i : threads) {
    i.join();
  }

  for (auto val : local_result) {
    result += val;
  }

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

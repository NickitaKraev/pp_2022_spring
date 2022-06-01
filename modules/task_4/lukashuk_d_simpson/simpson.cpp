// Copyright 2022 Lukashuk Diana
#include "../../../modules/task_4/lukashuk_d_simpson/simpson.h"

typedef std::vector<double> VEC_T;
int PROC_SIZE = 4;

double simpson(const FUNC_T& f, const BORDER_T& borders,
               const std::vector<int>& steps) {
  int iter = 1;
  int dimen = static_cast<int>(steps.size());
  double integral = 0;
  int pow_6 = static_cast<int>(std::pow(6, dimen));
  VEC_T h(dimen);
  std::vector<VEC_T> param(dimen, VEC_T(6));
  VEC_T args(dimen);
  for (int i = 0; i < dimen; i++) {
    h[i] = (borders[i].second - borders[i].first) / steps[i];
    iter *= steps[i];
  }
  for (int i = 0, x = i; i < iter; i++, x = i) {
    for (int d = 0; d < dimen; d++) {
      param[d][0] = borders[d].first + (x % steps[d]) * h[d];
      param[d][1] = param[d][0] + h[d] / 2;
      param[d][4] = param[d][3] = param[d][2] = param[d][1];
      param[d][5] = param[d][0] + h[d];
      x /= steps[d];
    }
    for (int j = 0, x = j; j < pow_6; j++, x = j) {
      for (int d = 0; d < dimen; d++) {
        args[d] = param[d][x % 6];
        x /= 6;
      }
      integral += f(args);
    }
  }
  for (int i = 0; i < dimen; i++) {
    integral *= h[i] / 6.0;
  }
  return integral;
}

void parallel(const FUNC_T& f, const BORDER_T& borders,
              const std::vector<int>& steps, const VEC_T& h, int begin, int end,
              int dimen, double* integral) {
  std::vector<VEC_T> param(dimen, VEC_T(6));
  std::vector<double> args(dimen);
  int pow_6 = static_cast<int>(std::pow(6, dimen));
  for (int i = begin, x = i; i < end; i++, x = i) {
    for (int d = 0; d < dimen; d++) {
      param[d][0] = borders[d].first + (x % steps[d]) * h[d];
      param[d][1] = param[d][0] + h[d] / 2;
      param[d][4] = param[d][3] = param[d][2] = param[d][1];
      param[d][5] = param[d][0] + h[d];
      x /= steps[d];
    }
    for (int j = 0, x = j; j < pow_6; j++, x = j) {
      for (int d = 0; d < dimen; d++) {
        args[d] = param[d][x % 6];
        x /= 6;
      }
      *integral += f(args);
    }
  }
}

double simpson_par(const FUNC_T& f, const BORDER_T& borders,
                   const std::vector<int>& steps) {
  int iter = 1;
  int dimen = static_cast<int>(steps.size());
  double integral = 0;
  VEC_T h(dimen);
  for (int i = 0; i < dimen; i++) {
    h[i] = (borders[i].second - borders[i].first) / steps[i];
    iter *= steps[i];
  }
  std::vector<std::thread> t(PROC_SIZE);
  std::vector<double> proc_res(PROC_SIZE, 0.0);
  int temp = iter % PROC_SIZE;
  int delta = iter / PROC_SIZE;
  for (int rank = 0; rank < PROC_SIZE; rank++) {
    int begin = rank * delta;
    int end = begin + delta + (rank < temp ? 1 : 0);
    t[rank] = std::thread(parallel, f, borders, steps, h, begin, end, dimen,
                          &proc_res[rank]);
  }
  for (int rank = 0; rank < PROC_SIZE; rank++) {
    // if (t[rank].joinable())
    t[rank].join();
    integral += proc_res[rank];
  }
  for (int i = 0; i < dimen; i++) {
    integral *= h[i] / 6.0;
  }
  return integral;
}

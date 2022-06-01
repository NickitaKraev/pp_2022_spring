// Copyright 2022 Votyakova Daria
#include "../../../modules/task_4/votyakova_d_simpson/simpson.h"

#include <cmath>

#include "../../../3rdparty/unapproved/unapproved.h"

double getSTDSimpson(const std::function<double(std::vector<double>)>& f,
                     const std::vector<std::pair<double, double>>& limits,
                     const std::vector<int>& n) {
  int dim = n.size();
  std::vector<double> h(dim);
  int64_t counter = 1;
  for (int i = 0; i < dim; ++i) {
    h[i] = (limits[i].second - limits[i].first) / n[i];
    counter *= n[i];
  }
  double result = 0.0;

  const int thread_num = std::thread::hardware_concurrency();
  std::vector<double> local_sum(thread_num, 0.0);

  auto thread_func = [dim, limits, n, &local_sum, f, h](int begin, int end,
                                                        int index) {
    for (int i = begin; i < end; ++i) {
      std::vector<std::vector<double>> params(dim);
      int temp = i;
      for (int j = 0; j < dim; ++j) {
        params[j].push_back(limits[j].first + temp % n[j] * h[j]);
        params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
        params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
        params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
        params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
        params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j]);
        temp /= n[j];
      }
      std::vector<double> point;
      for (int i = 0; i < pow(6, dim); ++i) {
        int temp = i;
        for (int j = 0; j < dim; ++j) {
          point.push_back(params[j][temp % 6]);
          temp /= 6;
        }
        local_sum[index] += f(point);
        point.clear();
      }
      params.clear();
    }
  };

  std::vector<std::thread> threads(thread_num);
  int delta = counter / thread_num;

  for (int index = 0; index < thread_num; ++index) {
    int begin = delta * index;
    int end = delta * (index + 1);

    if (index != thread_num - 1) {
      threads[index] = std::thread(thread_func, begin, end, index);
    } else {
      threads[index] = std::thread(thread_func, delta * (thread_num - 1),
                                   counter, thread_num - 1);
    }
  }

  for (auto&& i : threads) {
    i.join();
  }

  for (auto val : local_sum) {
    result += val;
  }

  for (int i = 0; i < dim; ++i) {
    result *= h[i] / 6.0;
  }
  return result;
}

double getSeqSimpson(const std::function<double(std::vector<double>)>& f,
                     const std::vector<std::pair<double, double>>& limits,
                     const std::vector<int>& n) {
  int dim = n.size();
  std::vector<double> h(dim);
  int64_t counter = 1;
  for (int i = 0; i < dim; ++i) {
    h[i] = (limits[i].second - limits[i].first) / n[i];
    counter *= n[i];
  }
  double result = 0.0;
  for (int i = 0; i < counter; ++i) {
    std::vector<std::vector<double>> params(dim);
    int temp = i;
    for (int j = 0; j < dim; ++j) {
      params[j].push_back(limits[j].first + temp % n[j] * h[j]);
      params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
      params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
      params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
      params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j] / 2);
      params[j].push_back(limits[j].first + temp % n[j] * h[j] + h[j]);
      temp /= n[j];
    }
    std::vector<double> point;
    for (int i = 0; i < pow(6, dim); ++i) {
      int temp = i;
      for (int j = 0; j < dim; ++j) {
        point.push_back(params[j][temp % 6]);
        temp /= 6;
      }
      result += f(point);
      point.clear();
    }
    params.clear();
  }
  for (int i = 0; i < dim; ++i) {
    result *= h[i] / 6.0;
  }
  return result;
}

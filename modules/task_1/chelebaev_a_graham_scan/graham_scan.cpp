// Copyright 2022 Chelebaev Artem
#include "../../../modules/task_1/chelebaev_a_graham_scan/graham_scan.h"

#include <algorithm>
#include <cmath>
#include <stack>

std::vector<std::pair<double, double>> gen_points(std::size_t size) {
  std::vector<std::pair<double, double>> result(size);
  result[0] = std::make_pair(0, 0);
  for (std::size_t i = 1; i < size; ++i) {
    result[i] = std::make_pair(i, 10);
  }
  return result;
}

std::vector<std::pair<double, double>> gen_random_points(std::size_t size) {
  std::mt19937 rand_r(time(0));
  std::vector<std::pair<double, double>> vec(size);
  for (std::size_t i = 0; i < size; ++i) {
    vec[i].first = rand_r() % 100;
    vec[i].second = rand_r() % 100;
  }
  return vec;
}

double get_polar_radius(const std::pair<double, double>& point) {
  return std::sqrt(point.first * point.first + point.second * point.second);
}

double get_polar_grad(const std::pair<double, double>& point) {
  return std::atan(point.second / point.first);
}

double calc_det(const std::pair<double, double>& x,
                const std::pair<double, double>& y,
                const std::pair<double, double>& z) {
  return (y.first - x.first) * (z.second - x.second) -
         (z.first - x.first) * (y.second - x.second);
}

std::size_t get_lex_min(std::vector<std::pair<double, double>> v) {
  std::size_t min_idx = 0;
  for (std::size_t i = 1; i < v.size(); ++i) {
    if (v[i] < v[min_idx]) {
      min_idx = i;
    }
  }
  return min_idx;
}

std::vector<std::pair<double, double>> polar_sort(
    std::vector<std::pair<double, double>> v) {
  std::sort(v.begin() + 1, v.end(),
            [&](const std::pair<double, double>& a,
                const std::pair<double, double>& b) {
              double grad_a = get_polar_grad(a);
              double grad_b = get_polar_grad(b);

              if (grad_a < grad_b) {
                return true;
              } else if ((std::abs(grad_a - grad_b) <= 1e-8) &&
                         (get_polar_radius(a) < get_polar_radius(b))) {
                return true;
              } else {
                return false;
              }
            });
  return v;
}

std::vector<std::pair<double, double>> graham_conv_hull(
    std::vector<std::pair<double, double>> points) {
  std::size_t min_idx = get_lex_min(points);
  std::swap(points[0], points[min_idx]);
  auto lex_min = points[0];

  for (std::size_t i = 0; i < points.size(); ++i) {
    points[i].first -= lex_min.first;
    points[i].second -= lex_min.second;
  }

  auto sorted_points = polar_sort(points);

  std::stack<std::pair<double, double>> res;
  std::size_t stack_size = res.size();
  res.push(sorted_points[0]);
  res.push(sorted_points[1]);

  std::pair<double, double> x, y, z;
  for (std::size_t i = 2; i < sorted_points.size(); ++i) {
    stack_size = res.size();
    y = res.top();
    res.pop();
    x = res.top();
    z = sorted_points[i];
    double det = calc_det(x, y, z);

    if ((det > 0) || (det == 0)) {
      res.push(y);
      res.push(sorted_points[i]);
    } else if (stack_size < 3) {
      res.push(sorted_points[i]);
    } else {
      --i;
    }
  }

  std::vector<std::pair<double, double>> res_vec(res.size());
  std::size_t i = res.size() - 1;
  while (!res.empty()) {
    res_vec[i] = res.top();
    res_vec[i].first += lex_min.first;
    res_vec[i].second += lex_min.second;
    res.pop();
    --i;
  }

  return res_vec;
}

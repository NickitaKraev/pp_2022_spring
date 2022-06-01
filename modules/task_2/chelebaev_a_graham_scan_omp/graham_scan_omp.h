// Copyright 2022 Chelebaev Artem
#ifndef MODULES_TASK_2_CHELEBAEV_A_GRAHAM_SCAN_OMP_GRAHAM_SCAN_OMP_H_
#define MODULES_TASK_2_CHELEBAEV_A_GRAHAM_SCAN_OMP_GRAHAM_SCAN_OMP_H_

#include <ctime>
#include <random>
#include <utility>
#include <vector>

std::vector<std::pair<double, double>> gen_random_points(std::size_t size);

bool is_less(const std::pair<double, double>& a,
             const std::pair<double, double>& b);

double get_polar_radius(const std::pair<double, double>& point);
double get_polar_grad(const std::pair<double, double>& point);
double calc_det(const std::pair<double, double>& x,
                const std::pair<double, double>& y,
                const std::pair<double, double>& z);
std::size_t get_lex_min(std::vector<std::pair<double, double>> v);

std::vector<std::pair<double, double>> graham_conv_hull(
    std::vector<std::pair<double, double>>::iterator begin,
    std::vector<std::pair<double, double>>::iterator end);
std::vector<std::pair<double, double>> omp_graham_conv_hull(
    std::vector<std::pair<double, double>>::iterator begin,
    std::vector<std::pair<double, double>>::iterator end,
    std::size_t n_threads = 2);

#endif  // MODULES_TASK_2_CHELEBAEV_A_GRAHAM_SCAN_OMP_GRAHAM_SCAN_OMP_H_

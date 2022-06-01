// Copyright 2022 Chelebaev Artem
#ifndef MODULES_TASK_1_CHELEBAEV_A_GRAHAM_SCAN_GRAHAM_SCAN_H_
#define MODULES_TASK_1_CHELEBAEV_A_GRAHAM_SCAN_GRAHAM_SCAN_H_

#include <utility>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

std::vector<std::pair<double, double>> gen_points(std::size_t size);
std::vector<std::pair<double, double>> gen_random_points(std::size_t size);

double get_polar_radius(const std::pair<double, double>& point);
double get_polar_grad(const std::pair<double, double>& point);
double calc_det(const std::pair<double, double>& x,
                const std::pair<double, double>& y,
                const std::pair<double, double>& z);

std::size_t get_lex_min(std::vector<std::pair<double, double>> v);
std::vector<std::pair<double, double>> polar_sort(
    std::vector<std::pair<double, double>> v);

std::vector<std::pair<double, double>> graham_conv_hull(
    std::vector<std::pair<double, double>> points);

#endif  // MODULES_TASK_1_CHELEBAEV_A_GRAHAM_SCAN_GRAHAM_SCAN_H_

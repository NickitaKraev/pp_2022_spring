// Copyright 2022 Chelebaev Artem
#pragma once
#ifndef MODULES_TASK_4_CHELEBAEV_A_GRAHAM_SCAN_STD_GRAHAM_SCAN_STD_H_
#define MODULES_TASK_4_CHELEBAEV_A_GRAHAM_SCAN_STD_GRAHAM_SCAN_STD_H_
#include <omp.h>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <random>
#include <utility>

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
std::vector<std::pair<double, double>> std_graham_conv_hull(
    std::vector<std::pair<double, double>>::iterator begin,
    std::vector<std::pair<double, double>>::iterator end,
    std::size_t n_threads = 4);

#endif  // MODULES_TASK_4_CHELEBAEV_A_GRAHAM_SCAN_STD_GRAHAM_SCAN_STD_H_

//  Copyright 2022 Butescu Vladimir
#ifndef MODULES_TASK_4_BUTESCU_V_GAUSS_VERT_THREAD_VERT_GAUSS_H_
#define MODULES_TASK_4_BUTESCU_V_GAUSS_VERT_THREAD_VERT_GAUSS_H_

#include <vector>
#include <random>
#include <ctime>


int clamp(int value, int max, int min);
std::vector<double> createRandomMatrix(int rows, int cols);
std::vector<double> gauss_filter_sequence(const std::vector<double>& matrix,
    int rows, int cols);
std::vector<double> gauss_filter_parralel_thread(const std::vector<double>& matrix,
    int rows, int cols);

#endif  // MODULES_TASK_4_BUTESCU_V_GAUSS_VERT_THREAD_VERT_GAUSS_H_

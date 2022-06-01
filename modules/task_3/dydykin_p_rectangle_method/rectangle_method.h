// Copyright 2022 Dydykin Pavel
#ifndef MODULES_TASK_3_DYDYKIN_P_RECTANGLE_METHOD_RECTANGLE_METHOD_H_
#define MODULES_TASK_3_DYDYKIN_P_RECTANGLE_METHOD_RECTANGLE_METHOD_H_

#include <math.h>
#include <tbb/tbb.h>
#include <omp.h>
#include <iostream>
#include <vector>
#include "gtest/gtest.h"


double Rectangle_Method_Seq(std::vector <int> start_integ,
    std::vector <int> end_integ, const int count,
    std::function<double(std::vector<double>)> function);
double Rectangle_Method_Parallel(std::vector <int> start_integ,
    std::vector <int> end_integ, const int count,
    std::function<double(std::vector<double>)> function);

#endif  // MODULES_TASK_3_DYDYKIN_P_RECTANGLE_METHOD_RECTANGLE_METHOD_H_

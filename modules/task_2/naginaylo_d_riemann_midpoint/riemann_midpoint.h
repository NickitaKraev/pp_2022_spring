// Copyright 2022 Naginaylo Dmitriy
#ifndef MODULES_TASK_2_NAGINAYLO_D_RIEMANN_MIDPOINT_RIEMANN_MIDPOINT_H_
#define MODULES_TASK_2_NAGINAYLO_D_RIEMANN_MIDPOINT_RIEMANN_MIDPOINT_H_

#include <omp.h>

#include <functional>
#include <utility>
#include <vector>

using vector_double = std::vector<double>;
using vector_pair = std::vector<std::pair<double, double>>;
using function = std::function<double(std::vector<double>)>;

double riemannMidpoint(const int dim, const int subdiv,
                       const vector_pair& limits, const function& func);
double riemannMidpointParallel(const int dim, const int subdiv,
                               const vector_pair& limits, const function& func);

#endif  // MODULES_TASK_2_NAGINAYLO_D_RIEMANN_MIDPOINT_RIEMANN_MIDPOINT_H_

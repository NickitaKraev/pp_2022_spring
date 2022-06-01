// Copyright 2022 Mishina Nadezhda
#ifndef MODULES_TASK_3_MISHINA_N_CONJ_GRADIENTS_MISHINA_N_CONJ_GRADIENTS_H_
#define MODULES_TASK_3_MISHINA_N_CONJ_GRADIENTS_MISHINA_N_CONJ_GRADIENTS_H_


#include <iostream>
#include <vector>
#include "tbb/tbb.h"
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"

double VecMultVec(const std::vector<double>& v1,
 const std::vector<double>& v2);
std::vector<double> MatrMultVec(const std::vector<std::vector<double>>& M,
 const std::vector<double>& v);
std::vector<double> VecMultNum(const std::vector<double>& v, double d);
std::vector<double> VecSum(const std::vector<double>& v1,
 const std::vector<double>& v2);
std::vector<double> VecOtr(const std::vector<double>& v);
std::vector<double> ConjGrad(const std::vector<std::vector<double>>& M,
 const std::vector<double>& b);
std::vector<double> MatrMultVecPar(const std::vector<std::vector<double>>& M,
 const std::vector<double>& v, int n);
std::vector<double> ConjGradPar(const std::vector<std::vector<double>>& M,
 const std::vector<double>& b, int n);
std::vector<double> RandVec(int count);
std::vector<std::vector<double>> RandMatr(int count);

#endif  // MODULES_TASK_3_MISHINA_N_CONJ_GRADIENTS_MISHINA_N_CONJ_GRADIENTS_H_

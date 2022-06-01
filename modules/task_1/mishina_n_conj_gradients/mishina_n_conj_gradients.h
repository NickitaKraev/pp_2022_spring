// Copyright 2022 Mishina Nadezhda
#ifndef MODULES_TASK_1_MISHINA_N_CONJ_GRADIENTS_MISHINA_N_CONJ_GRADIENTS_H_
#define MODULES_TASK_1_MISHINA_N_CONJ_GRADIENTS_MISHINA_N_CONJ_GRADIENTS_H_

#include <iostream>
#include <vector>

double VecMultVec(const std::vector<double>& v1, const std::vector<double>& v2);
std::vector<double> MatrMultVec(const std::vector<std::vector<double>>& M,
  const std::vector<double>& v);
std::vector<double> VecMultNum(const std::vector<double>& v, double d);
std::vector<double> VecSum(const std::vector<double>& v1,
  const std::vector<double>& v2);
std::vector<double> VecOtr(const std::vector<double>& v);
std::vector<double> ConjGrad(const std::vector<std::vector<double>>& M,
  const std::vector<double>& b);

#endif  // MODULES_TASK_1_MISHINA_N_CONJ_GRADIENTS_MISHINA_N_CONJ_GRADIENTS_H_

// Copyright 2022 Utyugov Denis

#ifndef MODULES_TASK_3_UTYUGOV_D_CANNONS_ALG_TBB_CANNONS_ALG_H_
#define MODULES_TASK_3_UTYUGOV_D_CANNONS_ALG_TBB_CANNONS_ALG_H_
#include <string>
#include <vector>

std::vector<double> getRandomVector(int size);
std::vector<std::vector<double>> getRndMatrix(int size);
std::vector<std::vector<double>> Multiplicate(
    std::vector<std::vector<double>> A, std::vector<std::vector<double>> B,
    int size);
std::vector<std::vector<double>> BlockMultiplicate(
    std::vector<std::vector<double>> A, std::vector<std::vector<double>> B,
    int BlSize);
std::vector<std::vector<double>> CannonsAlg(std::vector<std::vector<double>> A,
                                            std::vector<std::vector<double>> B,
                                            int num_threads);
#endif  // MODULES_TASK_3_UTYUGOV_D_CANNONS_ALG_TBB_CANNONS_ALG_H_

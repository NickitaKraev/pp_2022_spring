// Copyright 2022 Kim Nikita
#ifndef MODULES_TASK_4_KIM_N_RADIX_SORT_RADIX_SORT_H_
#define MODULES_TASK_4_KIM_N_RADIX_SORT_RADIX_SORT_H_

#include <vector>
#include <deque>


std::vector<int> getRandomVector(int size);

int getMax(std::vector<int> input_vec, int size);

void getMergedVector(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>* res);

void doWork(const int* start, const int size, std::vector<int>* res, int max_value);

std::vector<int> countSort(const std::vector<int>& input_vec, int size, int place);

std::vector<int> radixSort(const std::vector<int>& input_vec, int size);

std::vector<int> radixSortParallel(const std::vector<int>& input_vec, int size);

#endif  // MODULES_TASK_4_KIM_N_RADIX_SORT_RADIX_SORT_H_

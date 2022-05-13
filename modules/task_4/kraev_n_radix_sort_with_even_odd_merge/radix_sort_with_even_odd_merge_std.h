// Copyright 2022 Kraev Nikita
#ifndef MODULES_TASK_4_KRAEV_N_RADIX_SORT_WITH_EVEN_ODD_MERGE_RADIX_SORT_WITH_EVEN_ODD_MERGE_STD_H_
#define MODULES_TASK_4_KRAEV_N_RADIX_SORT_WITH_EVEN_ODD_MERGE_RADIX_SORT_WITH_EVEN_ODD_MERGE_STD_H_

#include <omp.h>
#include <vector>
#include <random>

std::vector<double> getRandomVector(int size);
void radixSort(std::vector<double>* vec);
std::vector<double> parallelRadixSort(std::vector<double>* vec,
    int number_threads, int size);
void evenOrOddSplitter(std::vector<double>* vec_1, std::vector<double>* vec_2,
    bool check);
std::vector<double> simpleComparator(std::vector<double>* vec_1,
    std::vector<double>* vec_2);
std::vector<double> batcherMerge(std::vector<double>* vec_1,
    std::vector<double>* vec_2);
std::vector<double> parallelRadixSort(std::vector<double>* vec, int size);

#endif  // MODULES_TASK_4_KRAEV_N_RADIX_SORT_WITH_EVEN_ODD_MERGE_RADIX_SORT_WITH_EVEN_ODD_MERGE_STD_H_

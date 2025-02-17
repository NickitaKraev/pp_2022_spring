// Copyright 2022 Trevogin Kirill
#ifndef MODULES_TASK_2_TREVOGIN_K_HOAR_HOAR_H_
#define MODULES_TASK_2_TREVOGIN_K_HOAR_HOAR_H_
#include <vector>

void quickSort(int left, int right, std::vector<double>* arr);
std::vector<double> getRandomVector(int size);
bool checkCorrectnessOfSort(std::vector<double>* vec);
void quickSortParallel(std::vector<double>* arr, int th = 8);
void EvenSplitter(int start, size_t size1, size_t size2,
    std::vector<double>* arr);
void OddSplitter(int start, size_t size1, size_t size2,
    std::vector<double>* arr);
#endif  // MODULES_TASK_2_TREVOGIN_K_HOAR_HOAR_H_

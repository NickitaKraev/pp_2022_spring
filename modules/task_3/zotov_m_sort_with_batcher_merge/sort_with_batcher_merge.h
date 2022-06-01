// Copyright 2022 Zotov Maxim
#ifndef MODULES_TASK_3_ZOTOV_M_SORT_WITH_BATCHER_MERGE_SORT_WITH_BATCHER_MERGE_H_
#define MODULES_TASK_3_ZOTOV_M_SORT_WITH_BATCHER_MERGE_SORT_WITH_BATCHER_MERGE_H_

#include <vector>
#include <string>

int getMaxDigit(std::vector<int> data);
std::vector<int> getRandomVector(int size);
void radixSort(std::vector<int>* main_data, int size, int offset);
void parallelRadixSort(std::vector<int>* data, int size, int ThreadNum);

#endif  // MODULES_TASK_3_ZOTOV_M_SORT_WITH_BATCHER_MERGE_SORT_WITH_BATCHER_MERGE_H_

// Copyright 2022 Krivosheev Miron
#ifndef MODULES_TASK_3_KRIVOSHEEV_M_RADIX_SORT_W_BATCHER_BATCHER_H_
#define MODULES_TASK_3_KRIVOSHEEV_M_RADIX_SORT_W_BATCHER_BATCHER_H_
#include <vector>

bool checkSort(std::vector<int> arr);
void radixSort(std::vector<int> *vec);
void countSort(std::vector<int> *vec, int exp);
void radixSortSeq(std::vector<int>* vec);
void countSortSeq(std::vector<int>* vec, int exp);
int getMax(std::vector<int> *vec);
std::vector<int> EvenOddBatch(std::vector<int> vec1, std::vector<int> vec2);
std::vector<int> evenBatch(std::vector<int> vec1, std::vector<int> vec2);
std::vector<int> oddBatch(std::vector<int> vec1, std::vector<int> vec2);
std::vector<int> EvenOddBatch_seq(std::vector<int> vec1, std::vector<int> vec2);
std::vector<int> evenBatch_seq(std::vector<int> vec1, std::vector<int> vec2);
std::vector<int> oddBatch_seq(std::vector<int> vec1, std::vector<int> vec2);
std::vector<int> GetRandVector(int size);

#endif  // MODULES_TASK_3_KRIVOSHEEV_M_RADIX_SORT_W_BATCHER_BATCHER_H_

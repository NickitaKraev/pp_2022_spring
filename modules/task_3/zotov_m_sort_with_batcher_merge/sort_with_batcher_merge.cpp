// Copyright 2022 Zotov Maxim
#include <tbb/tbb.h>
#include <vector>
#include <random>
#include <iostream>
#include "../../../modules/task_3/zotov_m_sort_with_batcher_merge/sort_with_batcher_merge.h"

const int MAX = 30000;

std::vector<int> getRandomVector(int size) {
    std::mt19937 generate;
    generate.seed(time(0));
    std::uniform_real_distribution<> uid(-MAX, MAX);
    std::vector<int> tmp;
    for (int i = 0; i < size; i++) {
        tmp.push_back(uid(generate));
    }
    return tmp;
}

int getMaxDigit(std::vector<int> data) {
    int max_digit = 0;
    int size = data.size();
    while (size > 0) {
        max_digit++;
        for (size_t i = 0; i < data.size(); i++) {
            int div = data[i] / powf(10, max_digit);
            if (div == 0)
                size--;
        }
    }

    return max_digit;
}

void  radixSort(std::vector<int>* main_data, int size, int offset) {
    std::vector<int> sorted_data[19];
    int koef = 0;
    int max_digit = getMaxDigit(*main_data);
    while (koef < max_digit) {
        for (int i = offset; i < offset + size; i++) {
            int digit = (*main_data)[i] / pow(10, koef);
            digit = digit % 10;
            sorted_data[digit + 9].push_back((*main_data)[i]);
        }

        int iter = 0;
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < static_cast<int>(sorted_data[i].size()); j++) {
                (*main_data)[offset + iter] = sorted_data[i][j];
                iter++;
            }
            sorted_data[i].clear();
        }
        koef++;
    }
}

int getNumberOfIterations(int tN) {
    int k = 1;
    while (tN > std::pow(2, k)) {
        k++;
    }
    return k;
}

void splitData(std::vector<int>* data, std::vector<int>* first, int f, int f_displ, int s, int s_displ) {
    while (f < f_displ && s < s_displ) {
        if ((*data)[f] < (*data)[s]) {
            first->push_back((*data)[f]);
            f += 2;
        } else {
            first->push_back((*data)[s]);
            s += 2;
        }
    }

    if (f >= f_displ) {
        for (int j = s; j < s_displ; j += 2) {
            first->push_back((*data)[j]);
        }
    } else if (s >= s_displ) {
        for (int j = f; j < f_displ; j += 2) {
            first->push_back((*data)[j]);
        }
    }
}

void mergeData(std::vector<int>* data, std::vector<int>* first, int f, int f_displ, int s, int s_displ) {
    int i = 0;

    while (f < f_displ) {
        (*data)[f] = (*first)[i];
        f += 2;
        i++;
    }

    while (s < s_displ) {
        (*data)[s] = (*first)[i];
        s += 2;
        i++;
    }
}


void oddMerge(std::vector<int>* data, int f_size, int f_offset, int s_size, int s_offset) {
    int f = f_offset + 1, s = s_offset + 1;
    int f_displ = f_size + f_offset, s_displ = s_size + s_offset;
    std::vector<int> first;

    splitData(data, &first, f, f_displ, s, s_displ);
    mergeData(data, &first, f, f_displ, s, s_displ);
}

void evenMerge(std::vector<int>* data, int f_size, int f_offset, int s_size, int s_offset) {
    int f = f_offset, s = s_offset;
    int f_displ = f_size + f_offset, s_displ = s_size + s_offset;
    std::vector<int> first;

    splitData(data, &first, f, f_displ, s, s_displ);
    mergeData(data, &first, f, f_displ, s, s_displ);
}

void compare(std::vector<int>* data, int size, int offset) {
    for (int i = offset; i < size + offset; i++) {
        if ((*data)[i] > (*data)[i + 1]) std::swap((*data)[i], (*data)[i + 1]);
    }
}

class Data {
 private:
    std::vector<int>* mainData;
    std::vector<int>* localData;
    std::vector<int>* localSize;
 public:
    Data(std::vector<int>* mainData_, std::vector<int>* localData_, std::vector<int>* localSize_):
        mainData(mainData_), localData(localData_), localSize(localSize_) {}
    void operator()(const tbb::blocked_range<int>& range)const {
        for (int i = range.begin(); i != range.end(); i++) {
            radixSort(mainData, (*localData)[i], (*localSize)[i]);
        }
    }
};

void parallelRadixSort(std::vector<int>* data, int size, int number_threads) {
    int local_size = size / number_threads;
    int remain = size % number_threads;
    std::vector<int> sendCount(number_threads);
    std::vector<int> displ;
    int iterator;
    int sum = 0;
    for (int i = 0; i < number_threads; i++) {
        sendCount[i] = local_size;
        if (remain > 0) {
            sendCount[i]++;
            remain--;
        }
        displ.push_back(sum);
        sum += sendCount[i];
    }
    iterator = getNumberOfIterations(number_threads);
    tbb::task_scheduler_init init(number_threads);
    tbb::parallel_for(tbb::blocked_range<int>(0, number_threads, 1),
        Data(data, &sendCount, &displ),
        tbb::auto_partitioner());
    init.terminate();
    for (int j = 0; j < iterator; j++) {
        for (int i = 0; i < number_threads; i += 2) {
            if (i + 1 < number_threads) {
                evenMerge(data, sendCount[i], displ[i], sendCount[i + 1], displ[i + 1]);
                oddMerge(data, sendCount[i], displ[i], sendCount[i + 1], displ[i + 1]);
                compare(data, sendCount[i], displ[i]);
                compare(data, sendCount[i + 1] - 1, displ[i + 1]);
            }
        }

        for (int j = 0; j < number_threads - 1; j += 2) {
            sendCount[j / 2] = sendCount[j] + sendCount[j + 1];
            displ[j / 2] = displ[j];
        }
        if (number_threads % 2 == 1) {
            sendCount[(number_threads - 1) / 2] = sendCount[number_threads - 1];
            displ[(number_threads - 1) / 2] = displ[number_threads - 1];
            number_threads = number_threads / 2 + 1;
        } else {
            number_threads /= 2;
        }
    }
}

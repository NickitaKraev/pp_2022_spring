// Copyright 2022 Tulkina Olga

#ifndef MODULES_TASK_3_TULKINA_O_LABELING_LABELING_H_
#define MODULES_TASK_3_TULKINA_O_LABELING_LABELING_H_

#include <omp.h>
#include <tbb/tbb.h>

#include <cmath>
#include <random>
#include <vector>

class Union {
  std::vector<int> label_image;

 public:
  explicit Union(int N) {
    label_image.resize(N);
    for (int i = 0; i < N; i++) {
      label_image[i] = i;
    }
  }

  int get_label(int index) {
    int root = index;
    while (root != label_image[root]) root = label_image[root];
    while (label_image[index] != root) {
      int new_index = label_image[index];
      label_image[index] = root;
      index = new_index;
    }
    return root;
  }

  void set_label(int my_index, int neighbor_index) {
    int my_label = get_label(my_index);
    int neighbor_label = get_label(neighbor_index);
    if (my_label == neighbor_label) return;

    (neighbor_label < my_label) ? label_image[my_label] = neighbor_label
                                : label_image[neighbor_label] = my_label;
  }
};

std::vector<std::vector<int>> labeling(
    const std::vector<std::vector<int>>& binary_image);
std::vector<std::vector<int>> labeling_tbb(
    const std::vector<std::vector<int>>& binary_image);
#endif  // MODULES_TASK_3_TULKINA_O_LABELING_LABELING_H_

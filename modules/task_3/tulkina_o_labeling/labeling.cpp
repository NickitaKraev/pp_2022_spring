// Copyright 2022 Tulkina Olga

#include "../../modules/task_3/tulkina_o_labeling/labeling.h"

const int THREADS = 12;
std::vector<std::vector<int>> labeling(
    const std::vector<std::vector<int>>& binary_image) {
  int width = binary_image[0].size(), height = binary_image.size();

  Union un(height * width + 1);

  std::vector<std::vector<int>> res(height, std::vector<int>(width));

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (binary_image[y][x] > 0) {
        int index = y * width + x + 1;

        if (x > 0 && binary_image[y][x - 1]) {
          un.set_label(index, y * width + x - 1 + 1);
        }
        if (y > 0 && binary_image[y - 1][x]) {
          un.set_label(index, (y - 1) * width + x + 1);
        }
        if ((y > 0 && x > 0) && binary_image[y - 1][x - 1]) {
          un.set_label(index, (y - 1) * width + (x - 1) + 1);
        }
        if ((y > 0 && x < width - 1) && binary_image[y - 1][x + 1]) {
          un.set_label(index, (y - 1) * width + (x + 1) + 1);
        }
      }
    }
  }

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      if (binary_image[y][x] > 0) res[y][x] = un.get_label(y * width + x + 1);
    }
  }
  return res;
}

std::vector<std::vector<int>> labeling_tbb(
    const std::vector<std::vector<int>>& binary_image) {
  int width = binary_image[0].size(), height = binary_image.size();

  Union un(height * width + 1);
  std::vector<std::vector<int>> res(height, std::vector<int>(width));
  tbb::task_scheduler_init init(THREADS);
  tbb::task_group gruppe;
  int step = height / THREADS;

  for (int i = 0; i < THREADS; i++) {
    gruppe.run([&binary_image, i, width, &un, step, height]() {
      int start, finish;
      if (i < THREADS - 1) {
        start = step * i;
        finish = step * (i + 1);
      } else {
        start = step * (THREADS - 1);
        finish = height;
      }
      for (int y = start; y < finish; y++) {
        for (int x = 0; x < width; x++) {
          if (binary_image[y][x] > 0) {
            int index = y * width + x + 1;

            if (x > 0 && binary_image[y][x - 1]) {
              un.set_label(index, y * width + x - 1 + 1);
            }
            if (y > 0 && binary_image[y - 1][x]) {
              un.set_label(index, (y - 1) * width + x + 1);
            }
            if ((y > 0 && x > 0) && binary_image[y - 1][x - 1]) {
              un.set_label(index, (y - 1) * width + (x - 1) + 1);
            }
            if ((y > 0 && x < width - 1) && binary_image[y - 1][x + 1]) {
              un.set_label(index, (y - 1) * width + (x + 1) + 1);
            }
          }
        }
      }
    });
  }
  gruppe.wait();

  for (int i = 0; i < THREADS; i++) {
    gruppe.run([&binary_image, i, width, &un, step, height, &res]() {
      int start, finish;
      if (i < THREADS - 1) {
        start = step * i;
        finish = step * (i + 1);
      } else {
        start = step * (THREADS - 1);
        finish = height;
      }
      for (int y = start; y < finish; y++) {
        for (int x = 0; x < width; x++) {
          if (binary_image[y][x] > 0)
            res[y][x] = un.get_label(y * width + x + 1);
        }
      }
    });
  }
  gruppe.wait();

  return res;
}

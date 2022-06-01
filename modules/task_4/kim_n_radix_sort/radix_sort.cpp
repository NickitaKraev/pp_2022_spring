// Copyright 2022 Kim Nikita

#include <vector>
#include <deque>
#include <random>
#include "../../../3rdparty/unapproved/unapproved.h"
#include "../../../modules/task_4/kim_n_radix_sort/radix_sort.h"


std::vector<int> getRandomVector(int size) {
  std::random_device dev;
  std::mt19937 gen(dev());
  std::vector<int> res(size);
  int sign;
  for (int i = 0; i < size; i++) {
    sign = 1 + gen() % 2 * -2;
    res[i] = gen() % 10000 * sign;
  }
  return res;
}

int getMax(std::vector<int> input_vec, int size) {
  int max = abs(input_vec[0]);
  for (int i = 1; i < size; i++)
    if (abs(input_vec[i]) > max)
      max = abs(input_vec[i]);
  return max;
}

void getMergedVector(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>* res) {
  int a_size = a.size();
  int b_size = b.size();

  int i = 0, j = 0;
  while (i < a_size && j < b_size) {
    if (a[i] <= b[j]) {
      res->push_back(a[i]);
      i++;
    } else {
      res->push_back(b[j]);
      j++;
    }
  }

  for (; i < a_size; i++)
    res->push_back(a[i]);
  for (; j < b_size; j++)
    res->push_back(b[j]);
}

void doWork(const int* start, const int size, std::vector<int>* res, int max_value) {
  for (int i = 0; i < size; i++) {
    res->push_back(start[i]);
  }
  for (int place = 1; max_value / place > 0; place *= 10) {
    *res = countSort(*res, size, place);
  }
}

std::vector<int> countSort(const std::vector<int>& input_vec, int size, int place) {
  int dig, sign;
  std::vector<int> ans(size);

  // digits of 19 since range is -9 to 9
  std::vector<int> digits(19);
  for (int i = 0; i < size; i++) {
    // add digits to the correct index
    // -9 + 9 -> 0
    // 9 + 9 -> 18
    sign = input_vec[i] < 0 ? -1 : 1;
    dig = (((input_vec[i] * sign) / place) % 10) * sign + 9;
    digits[dig]++;
  }

  for (int i = 1; i < 19; i++)
    digits[i] += digits[i - 1];

  for (int i = size - 1; i >= 0; i--) {
    sign = input_vec[i] < 0 ? -1 : 1;
    dig = (((input_vec[i] * sign) / place) % 10) * sign + 9;
    ans[digits[dig] - 1] = input_vec[i];
    digits[dig]--;
  }
  return ans;
}

std::vector<int> radixSort(const std::vector<int>& input_vec, int size) {
  int max_value = getMax(input_vec, size);
  std::vector<int> res(input_vec);

  for (int place = 1; max_value / place > 0; place *= 10)
    res = countSort(res, size, place);
  return res;
}

std::vector<int> radixSortParallel(const std::vector<int>& input_vec, int size) {
  int proc = std::thread::hardware_concurrency();
  // int proc = 2;
  int chunk = size / proc;
  int i = 0;
  int max_value = getMax(input_vec, size);
  std::deque<std::vector<int>> res;
  for (int i = 0; i < proc; i++) {
    res.emplace_back();
  }

  std::vector<std::thread> threads;
  for (; i < proc-1; i++) {
    threads.emplace_back(doWork, &input_vec[i * chunk], chunk, &res[i], max_value);
  }
  doWork(&input_vec[i * chunk], size - i * chunk, &res[i], max_value);

  for (std::thread & t : threads) {
      t.join();
  }
  threads.clear();

  for (int i = 0; i < proc - 1; i++) {
    res.emplace_back();
    getMergedVector(res[0], res[1], &res.back());
    res.pop_front();
    res.pop_front();
  }
  return res[0];
}

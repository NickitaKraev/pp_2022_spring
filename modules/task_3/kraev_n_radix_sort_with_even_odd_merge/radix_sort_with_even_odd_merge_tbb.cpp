// Copyright 2022 Kraev Nikita
#include "../../../modules/task_3/kraev_n_radix_sort_with_even_odd_merge/radix_sort_with_even_odd_merge_tbb.h"

std::vector<double> getRandomVector(int size) {
  std::vector<double> random_vec(size);

  std::random_device rd;
  std::default_random_engine generator(rd());
  double a = -5000.0, b = 5000.0;
  std::uniform_real_distribution<double> dis(a, b);

  for (int i = 0; i < size; ++i) {
    random_vec[i] = dis(generator);
  }

  return random_vec;
}

void radixSort(std::vector<double>* vec) {
  size_t size = vec->size();
  size_t local_size;
  int tmp;
  int j = 0;
  std::vector<std::vector<double>> counters(256);
  for (int index = 0; index < 7; index++) {
    for (size_t i = 0; i < size; i++) {
      tmp = static_cast<int>(*((unsigned char*)&(*vec)[i] + index));
      counters[tmp].push_back((*vec)[i]);
    }

    for (int i = 0; i < 256; i++) {
      if (!counters[i].empty()) {
        local_size = counters[i].size();
        for (size_t k = 0; k < local_size; k++) {
          (*vec)[j] = counters[i][k];
          ++j;
        }
        counters[i].clear();
      }
    }
    j = 0;
  }

  for (size_t i = 0; i < size; i++) {
    tmp = static_cast<int>(*((unsigned char*)&(*vec)[i] + 7));
    counters[tmp].push_back((*vec)[i]);
  }

  for (int i = 255; i >= 128; i--) {
    if (!counters[i].empty()) {
      local_size = counters[i].size();
      for (size_t k = local_size - 1; k >= 1; k--) {
        (*vec)[j] = counters[i][k];
        j++;
      }
      (*vec)[j] = counters[i][0];
      j++;
    }
  }

  for (int i = 0; i < 128; i++) {
    if (!counters[i].empty()) {
      local_size = counters[i].size();
      for (size_t k = 0; k < local_size; k++) {
        (*vec)[j] = counters[i][k];
        j++;
      }
    }
  }
}

void evenOrOddSplitter(std::vector<double>* vec_1, std::vector<double>* vec_2,
                       bool check) {
  size_t a, b;
  size_t size_1 = vec_1->size(), size_2 = vec_2->size();
  if (check)
    a = 0, b = 0;
  else
    a = 1, b = 1;

  std::vector<double> tmp;

  while (a < size_1 && b < size_2) {
    if ((*vec_1)[a] < (*vec_2)[b]) {
      tmp.push_back((*vec_1)[a]);
      a += 2;
    } else {
      tmp.push_back((*vec_2)[b]);
      b += 2;
    }
  }

  if (a >= size_1) {
    for (size_t j = b; j < size_2; j += 2) {
      tmp.push_back((*vec_2)[j]);
    }
  } else {
    for (size_t j = a; j < size_1; j += 2) {
      tmp.push_back((*vec_1)[j]);
    }
  }

  if (check)
    a = 0, b = 0;
  else
    a = 1, b = 1;

  size_t i = 0;

  while (a < size_1) {
    (*vec_1)[a] = tmp[i];
    a += 2;
    i++;
  }

  while (b < size_2) {
    (*vec_2)[b] = tmp[i];
    b += 2;
    i++;
  }
}

std::vector<double> simpleComparator(std::vector<double>* vec_1,
                                     std::vector<double>* vec_2) {
  size_t size_1 = vec_1->size(), size_2 = vec_2->size();
  std::vector<double> result(size_1 + size_2);
  size_t j = 0;
  for (size_t i = 0; i < size_1 - 1; i++) {
    if ((*vec_1)[i] > (*vec_1)[i + 1]) {
      std::swap((*vec_1)[i], (*vec_1)[i + 1]);
    }
    result[j++] = (*vec_1)[i];
  }
  result[j++] = (*vec_1)[size_1 - 1];

  if ((*vec_1)[size_1 - 1] > (*vec_2)[0]) {
    result[j - 1] = (*vec_2)[0];
    (*vec_2)[0] = (*vec_1)[size_1 - 1];
  }
  for (size_t i = 0; i < size_2 - 1; i++) {
    if ((*vec_2)[i] > (*vec_2)[i + 1]) {
      std::swap((*vec_2)[i], (*vec_2)[i + 1]);
    }
    result[j++] = (*vec_2)[i];
  }
  result[j] = (*vec_2)[size_2 - 1];

  return result;
}

std::vector<double> batcherMerge(std::vector<double>* vec_1,
                                 std::vector<double>* vec_2) {
  evenOrOddSplitter(vec_1, vec_2, true);
  evenOrOddSplitter(vec_1, vec_2, false);
  return simpleComparator(vec_1, vec_2);
}

std::vector<double> parallelRadixSort(std::vector<double>* vec,
                                      int number_threads, int size) {
  int local_size = size / number_threads;
  int remainder = size % number_threads;
  std::vector<std::vector<double>> data(number_threads);
  data[0] = {vec->begin(), vec->begin() + local_size + remainder};
  for (int i = 1; i < number_threads; i++) {
    data[i] = {vec->begin() + local_size * i + remainder,
               vec->begin() + local_size * (i + 1) + remainder};
  }

  tbb::task_scheduler_init init(number_threads);
  tbb::parallel_for(tbb::blocked_range<size_t>(0, data.size(), 1),
                    [&data](const tbb::blocked_range<size_t>& range) {
                      size_t begin = range.begin(), end = range.end();
                      for (size_t i = begin; i != end; ++i) radixSort(&data[i]);
                    },
                    tbb::auto_partitioner());
  init.terminate();

  for (int i = 1; i < number_threads; i++) {
    data[0] = batcherMerge(&data[0], &data[i]);
  }

  return data[0];
}

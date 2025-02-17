// Copyright 2022 Kamenev Ilya

#include <math.h>

#include <stdexcept>
#include <string>

#include "../../modules/task_2/kamenev_i_strassen_matrix_multiply_omp/strassen_matrix_multiply_omp.h"

void naive_mult(double* a, double* b, double* c, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      c[i * size + j] = 0;
      for (int k = 0; k < size; k++) {
        c[i * size + j] += a[i * size + k] * b[k * size + j];
      }
    }
  }
}

void get_p1(double* a11, double* a22, double* b11, double* b22, double* slice,
        int size) {
  double* res1 = new double[size * size * 2];
  double* res2 = res1 + size * size;
  for (int i = 0; i < size * size; i++) {
    res1[i] = a11[i] + a22[i];
    res2[i] = b11[i] + b22[i];
  }
  strassen_omp(res1, res2, slice, size);
  delete[] res1;
}
void get_p2(double* a21, double* a22, double* b11, double* slice, int size) {
  double* res1 = new double[size * size];
  for (int i = 0; i < size * size; i++) {
    res1[i] = a21[i] + a22[i];
  }
  strassen_omp(res1, b11, slice, size);
  delete[] res1;
}
void get_p3(double* a11, double* b12, double* b22, double* slice, int size) {
  double* res1 = new double[size * size];
  for (int i = 0; i < size * size; i++) {
    res1[i] = b12[i] - b22[i];
  }
  strassen_omp(a11, res1, slice, size);
  delete[] res1;
}
void get_p4(double* a22, double* b21, double* b11, double* slice, int size) {
  double* res1 = new double[size * size];
  for (int i = 0; i < size * size; i++) {
    res1[i] = b21[i] - b11[i];
  }
  strassen_omp(a22, res1, slice, size);
  delete[] res1;
}
void get_p5(double* a11, double* a12, double* b22, double* slice, int size) {
  double* res1 = new double[size * size];
  for (int i = 0; i < size * size; i++) {
    res1[i] = a11[i] + a12[i];
  }
  strassen_omp(res1, b22, slice, size);
  delete[] res1;
}
void get_p6(double* a21, double* a11, double* b11, double* b12, double* slice,
        int size) {
  double* res1 = new double[size * size * 2];
  double* res2 = res1 + size * size;
  for (int i = 0; i < size * size; i++) {
    res1[i] = a21[i] - a11[i];
    res2[i] = b11[i] + b12[i];
  }
  strassen_omp(res1, res2, slice, size);
  delete[] res1;
}
void get_p7(double* a12, double* a22, double* b21, double* b22, double* slice,
        int size) {
  double* res1 = new double[size * size * 2];
  double* res2 = res1 + size * size;
  for (int i = 0; i < size * size; i++) {
    res1[i] = a12[i] - a22[i];
    res2[i] = b21[i] + b22[i];
  }
  strassen_omp(res1, res2, slice, size);
  delete[] res1;
}

bool is_exp_of_2(int n) { return (n & (n - 1)) == 0; }

void strassen_omp(double* a, double* b, double* c, int size) {
  if (!is_exp_of_2(size)) {
    throw std::invalid_argument("no power 2");
  }

  if (size <= 32) {
    naive_mult(a, b, c, size);
    return;
  }

  int part_size = static_cast<int>(size * size / 4);

  double* a11 = new double[size * size * 2];
  double* a12 = a11 + part_size;
  double* a21 = a12 + part_size;
  double* a22 = a21 + part_size;

  double* b11 = a22 + part_size;
  double* b12 = b11 + part_size;
  double* b21 = b12 + part_size;
  double* b22 = b21 + part_size;

  double* c11 = new double[size * size + part_size * 9];
  double* c12 = c11 + part_size;
  double* c21 = c12 + part_size;
  double* c22 = c21 + part_size;

  double* slice1 = c22 + part_size;
  double* slice2 = slice1 + part_size;
  double* slice3 = slice2 + part_size;
  double* slice4 = slice3 + part_size;
  double* slice5 = slice4 + part_size;
  double* slice6 = slice5 + part_size;
  double* slice7 = slice6 + part_size;

  int half_split = static_cast<int>(size / 2);
  for (int i = 0; i < half_split; i++) {
    for (int j = 0; j < half_split; j++) {
      a11[i * half_split + j] = a[i * size + j];
      a12[i * half_split + j] = a[i * size + half_split + j];
      a21[i * half_split + j] = a[(half_split + i) * size + j];
      a22[i * half_split + j] = a[(half_split + i) * size + half_split + j];

      b11[i * half_split + j] = b[i * size + j];
      b12[i * half_split + j] = b[i * size + half_split + j];
      b21[i * half_split + j] = b[(half_split + i) * size + j];
      b22[i * half_split + j] = b[(half_split + i) * size + half_split + j];
    }
  }

#pragma omp parallel sections shared(a11, a12, a21, a22, b11, b12, b21, b22)
  {
#pragma omp section
    { get_p1(a11, a22, b11, b22, slice1, size / 2); }
#pragma omp section
    { get_p2(a21, a22, b11, slice2, size / 2); }
#pragma omp section
    { get_p3(a11, b12, b22, slice3, size / 2); }
#pragma omp section
    { get_p4(a22, b21, b11, slice4, size / 2); }
#pragma omp section
    { get_p5(a11, a12, b22, slice5, size / 2); }
#pragma omp section
    { get_p6(a21, a11, b11, b12, slice6, size / 2); }
#pragma omp section
    { get_p7(a12, a22, b21, b22, slice7, size / 2); }
  }
  for (int i = 0; i < (size / 2) * (size / 2); i++) {
    c11[i] = slice1[i] + slice4[i] - slice5[i] + slice7[i];
    c12[i] = slice3[i] + slice5[i];
    c21[i] = slice2[i] + slice4[i];
    c22[i] = slice1[i] - slice2[i] + slice3[i] + slice6[i];
  }

  for (int i = 0; i < half_split; i++) {
    for (int j = 0; j < half_split; j++) {
      c[i * size + j] = c11[i * half_split + j];
      c[i * size + half_split + j] = c12[i * half_split + j];
      c[(half_split + i) * size + j] = c21[i * half_split + j];
      c[(half_split + i) * size + half_split + j] = c22[i * half_split + j];
    }
  }

  delete[] a11;
  delete[] c11;
}

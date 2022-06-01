// Copyright 2022 Kolosova Alena

#ifndef MODULES_TASK_1_KOLOSOVA_A_MULT_COMPLEX_CCS_MATRIX_CCS_COMPLEX_MULT_H_
#define MODULES_TASK_1_KOLOSOVA_A_MULT_COMPLEX_CCS_MATRIX_CCS_COMPLEX_MULT_H_

#include <vector>
#include <complex>
#include <iostream>

struct CCS_matrix {
    int row_n;
    int col_n;
    std::vector<std::complex<double>> val;
    std::vector<int> rows;
    std::vector<int> column_pointer;

    friend std::ostream& operator<<(std::ostream& stream, const CCS_matrix& m) {
        stream << "matrix rows = " << m.row_n << " cols = " << m.col_n << std::endl << "values: ";
        for (auto elem : m.val)
            stream << elem << ' ';
        stream << std::endl << "rows: ";
        for (auto elem : m.rows)
            stream << elem << ' ';
        stream << std::endl << "column pointer: ";
        for (auto elem : m.column_pointer)
            stream << elem << ' ';
        stream << std::endl;
        return stream;
    }

    bool operator==(const CCS_matrix& m) const {
        if (m.row_n == row_n && m.col_n == col_n && m.val == val &&
            m.rows == rows && m.column_pointer == column_pointer) return true;
        return false;
    }

    explicit CCS_matrix(int r = 0, int c = 0) {
        row_n = r;
        col_n = c;
    }

    explicit CCS_matrix(std::vector<std::vector<std::complex<double>>> m);
};

std::vector<std::vector<std::complex<double>>> generate_matrix(int r, int c,
    double density = 0.5);
std::vector<std::vector<std::complex<double>>> multiply_v(
    const std::vector<std::vector<std::complex<double>>>& A,
    const std::vector<std::vector<std::complex<double>>>& B);

CCS_matrix transpose(const CCS_matrix& A);
CCS_matrix multiply(const CCS_matrix& A, const CCS_matrix& B);

std::complex<double> scalar_mult(const std::vector<std::complex<double>>& v1,
    const std::vector<int>& pos1, int start1, int end1,
    const std::vector<std::complex<double>>& v2, const std::vector<int>& pos2,
    int start2, int end2);

#endif  // MODULES_TASK_1_KOLOSOVA_A_MULT_COMPLEX_CCS_MATRIX_CCS_COMPLEX_MULT_H_

// Copyright 2022 Kolosova Alena

#include <vector>
#include <random>
#include <iostream>

#include "../../../modules/task_1/kolosova_a_mult_complex_ccs_matrix/ccs_complex_mult.h"

std::vector<std::vector<std::complex<double>>> generate_matrix(int r, int c,
    double density) {
    if (r <= 0 || c <= 0) {
        throw("Incorrect matrix size for generation");
    }
    if (density < 0 || density>1) density = 0.5;

    std::random_device dev;
    std::mt19937 rgen(dev());
    std::uniform_real_distribution<double> prob{ 0.0, 1.0 };
    std::uniform_real_distribution<double> val{ 0.0, 100.0 };
    std::vector<std::vector<std::complex<double>>> matrix(r);

    for (int i = 0; i < r; ++i) {
        matrix[i].resize(c);
        for (int j = 0; j < c; ++j) {
            if (prob(rgen) <= density) {
                matrix[i][j] = val(rgen);
            }
        }
    }
    return matrix;
}

std::vector<std::vector<std::complex<double>>> multiply_v(
    const std::vector<std::vector<std::complex<double>>>& A,
    const std::vector<std::vector<std::complex<double>>>& B) {
    if (A.size() == 0 || B.size() == 0)
        throw("Empty matrices, cannot multiply");
    if (A[0].size() != B.size())
        throw("Incompatible matrices size for multiplication");

    std::vector<std::vector<std::complex<double>>> C(B.size());
    for (int i = 0; i < static_cast<int>(C.size()); i++) {
        C[i] = std::vector<std::complex<double>>(A[0].size(), {0.0, 0.0});
    }

    for (int i = 0; i < static_cast<int>(A.size()); i++)
        for (int j = 0; j < static_cast<int>(B[0].size()); j++)
            for (int k = 0; k < static_cast<int>(B.size()); k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

CCS_matrix::CCS_matrix(std::vector<std::vector<std::complex<double>>> m) {
    row_n = m.size();
    col_n = (row_n) ? m[0].size() : 0;
    int ptr = 0;
    for (int j = 0; j < static_cast<int>(m[0].size()); j++) {
        column_pointer.push_back(ptr);
        for (int i = 0; i < static_cast<int>(m.size()); i++) {
            if (m[i][j].real() || m[i][j].imag()) {
                val.push_back(m[i][j]);
                rows.push_back(i);
                ptr++;
            }
        }
    }
    column_pointer.push_back(ptr);
}

CCS_matrix transpose(const CCS_matrix& A) {
    CCS_matrix res(A.col_n, A.row_n);
    std::vector<std::vector<std::complex<double>>> tmpVals(res.col_n);  // vector of new values by columns
    std::vector<std::vector<int>> tmpRows(res.col_n);  // vector of new row indexes
    int tmpCol = 0;  // column of current element (in old matrix)

    for (int i = 0; i < static_cast<int>(A.val.size()); i++) {
        while (i >= A.column_pointer[tmpCol + 1]) tmpCol++;
        tmpVals[A.rows[i]].push_back(A.val[i]);
        tmpRows[A.rows[i]].push_back(tmpCol);
    }

    tmpCol = 0;
    for (int i = 0; i < static_cast<int>(tmpVals.size()); i++) {
        res.column_pointer.push_back(tmpCol);
        res.val.insert(res.val.end(), tmpVals[i].begin(), tmpVals[i].end());
        res.rows.insert(res.rows.end(), tmpRows[i].begin(), tmpRows[i].end());
        tmpCol += tmpVals[i].size();
    }
    res.column_pointer.push_back(tmpCol);
    return res;
}

CCS_matrix multiply(const CCS_matrix& A, const CCS_matrix& B) {
    if (A.col_n != B.row_n)
        throw("Incompatible matrices size for multiplication");
    CCS_matrix At = transpose(A);

    std::vector<std::vector<std::complex<double>>> tmpVals(B.col_n);
    std::vector<std::vector<int>> tmpRows(B.col_n);

    for (int j = 0; j < B.col_n; j++) {
        if (B.column_pointer[j] == B.column_pointer[j + 1]) continue;
        for (int i = 0; i < A.row_n; i++) {
            if (At.column_pointer[i] == At.column_pointer[i + 1]) continue;
            std::complex<double> v = scalar_mult(At.val, At.rows, At.column_pointer[i],
                At.column_pointer[i + 1],
                B.val, B.rows, B.column_pointer[j], B.column_pointer[j + 1]);
            if (v != 0.0) {
                tmpVals[j].push_back(v);
                tmpRows[j].push_back(i);
            }
        }
    }

    CCS_matrix res(A.row_n, B.col_n);
    int tmpCol = 0;
    for (int i = 0; i < res.col_n; i++) {
        res.column_pointer.push_back(tmpCol);
        res.val.insert(res.val.end(), tmpVals[i].begin(), tmpVals[i].end());
        res.rows.insert(res.rows.end(), tmpRows[i].begin(), tmpRows[i].end());
        tmpCol += tmpVals[i].size();
    }
    res.column_pointer.push_back(tmpCol);
    return res;
}

std::complex<double> scalar_mult(const std::vector<std::complex<double>>& v1,
    const std::vector<int>& pos1, int start1, int end1,
    const std::vector<std::complex<double>>& v2, const std::vector<int>& pos2,
    int start2, int end2) {
    std::complex<double> res = {0, 0};
    for (int i = start1, j = start2; i < end1 && j < end2;) {
        if (pos1[i] == pos2[j]) {
            res += v1[i] * v2[j];
            i++;
            j++;
        } else {
            if (pos1[i] < pos2[j]) i++;
            else
                j++;
        }
    }
    return res;
}

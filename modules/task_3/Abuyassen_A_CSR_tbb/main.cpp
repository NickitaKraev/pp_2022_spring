// Copyright 2022 Abuyassen Albara

#include <gtest/gtest.h>
#include <tbb/tick_count.h>
#include <vector>
#include <complex>
#include "./CSR_tbb.h"

TEST(CSR_tbb, multiplication_100_100) {
    int width = 100, height = 100;
    std::vector<std::complex<int>> A = randomSparseMatrix(height, width);
    std::vector<std::complex<int>> B = randomSparseMatrix(height, width);
    CSR A_ = sparesify(A, height, width);
    CSR B_ = sparesify(B, height, width);
    tbb::tick_count t0, t1;
    t0 = tbb::tick_count::now();
    std::vector<std::complex<int>> SEQ = A_ * B_;
    t1 = tbb::tick_count::now();
    printf("Sequential time : %g s\n", (t1-t0).seconds());
    t0 = tbb::tick_count::now();
    std::vector<std::complex<int>> PAR = tbb_multiply(A_, B_);
    t1 = tbb::tick_count::now();
    printf("Parallel time : %g s\n", (t1-t0).seconds());
    ASSERT_TRUE(SEQ == PAR);
}

TEST(CSR_tbb, multiplication_250_300) {
    int width = 300, height = 250;
    std::vector<std::complex<int>> A = randomSparseMatrix(height, width);
    std::vector<std::complex<int>> B = randomSparseMatrix(width, height);
    CSR A_ = sparesify(A, height, width);
    CSR B_ = sparesify(B, width, height);
    tbb::tick_count t0, t1;
    t0 = tbb::tick_count::now();
    std::vector<std::complex<int>> SEQ = A_ * B_;
    t1 = tbb::tick_count::now();
    printf("Sequential time : %g s\n", (t1-t0).seconds());
    t0 = tbb::tick_count::now();
    std::vector<std::complex<int>> PAR = tbb_multiply(A_, B_);
    t1 = tbb::tick_count::now();
    printf("Parallel time : %g s\n", (t1-t0).seconds());
    ASSERT_TRUE(SEQ == PAR);
}

TEST(CSR_tbb, multiplication_1000_1000) {
    int width = 1000, height = 1000;
    std::vector<std::complex<int>> A = randomSparseMatrix(height, width);
    std::vector<std::complex<int>> B = randomSparseMatrix(width, height);
    CSR A_ = sparesify(A, height, width);
    CSR B_ = sparesify(B, width, height);
    tbb::tick_count t0, t1;
    t0 = tbb::tick_count::now();
    std::vector<std::complex<int>> SEQ = A_ * B_;
    t1 = tbb::tick_count::now();
    printf("Sequential time : %g s\n", (t1-t0).seconds());
    t0 = tbb::tick_count::now();
    std::vector<std::complex<int>> PAR = tbb_multiply(A_, B_);
    t1 = tbb::tick_count::now();
    printf("Parallel time : %g s\n", (t1-t0).seconds());
    ASSERT_TRUE(SEQ == PAR);
}

TEST(CSR_tbb, multiplication_250_160) {
    int width = 160, height = 250;
    std::vector<std::complex<int>> A = randomSparseMatrix(height, width);
    std::vector<std::complex<int>> B = randomSparseMatrix(width, height);
    CSR A_ = sparesify(A, height, width);
    CSR B_ = sparesify(B, width, height);
    tbb::tick_count t0, t1;
    t0 = tbb::tick_count::now();
    std::vector<std::complex<int>> SEQ = A_ * B_;
    t1 = tbb::tick_count::now();
    printf("Sequential time : %g s\n", (t1-t0).seconds());
    t0 = tbb::tick_count::now();
    std::vector<std::complex<int>> PAR = tbb_multiply(A_, B_);
    t1 = tbb::tick_count::now();
    printf("Parallel time : %g s\n", (t1-t0).seconds());
    ASSERT_TRUE(SEQ == PAR);
}

TEST(CSR_tbb, multiplication_20_10) {
    int width = 20, height = 10;
    std::vector<std::complex<int>> A = randomSparseMatrix(height, width);
    std::vector<std::complex<int>> B = randomSparseMatrix(width, height);
    CSR A_ = sparesify(A, height, width);
    CSR B_ = sparesify(B, width, height);
    tbb::tick_count t0, t1;
    t0 = tbb::tick_count::now();
    std::vector<std::complex<int>> SEQ = A_ * B_;
    t1 = tbb::tick_count::now();
    printf("Sequential time : %g s\n", (t1-t0).seconds());
    t0 = tbb::tick_count::now();
    std::vector<std::complex<int>> PAR = tbb_multiply(A_, B_);
    t1 = tbb::tick_count::now();
    printf("Parallel time : %g s\n", (t1-t0).seconds());
    ASSERT_TRUE(SEQ == PAR);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Copyright 2022 Kurguzikov Kirill
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "./labeling.h"

TEST(Labeling_TBB, Test_234x243) {
    int rows = 234;
    int cols = 243;
    std::vector<std::vector<int>> arr = myrand(rows, cols, 28000);
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> expected;
    int n_size_seq = 0;
    int n_size_par = 0;
    tbb::tick_count t1, t2, t3, t4;
    t1 = tbb::tick_count::now();
    res = ParLabeling(arr, rows, cols);
    t2 = tbb::tick_count::now();
    n_size_par = check_for_par(res, rows, cols);

    t3 = tbb::tick_count::now();
    expected = SeqLabeling(arr, rows, cols);
    t4 = tbb::tick_count::now();
    n_size_seq = check_for_seq(expected, rows, cols);

    printf("\tparallel time %f\n", (t2 - t1).seconds());
    printf("\tsequential time %f\n", (t4 - t3).seconds());
    bool check_passed = false;
    if ((n_size_par == n_size_seq) && (n_size_par != 0)) {
        check_passed = true;
    }

    ASSERT_TRUE(check_passed);
}

TEST(Labeling_TBB, Test_160x160) {
    int rows = 160;
    int cols = 160;
    std::vector<std::vector<int>> arr = myrand(rows, cols, 11000);
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> expected;
    int n_size_seq = 0;
    int n_size_par = 0;
    tbb::tick_count t1 = tbb::tick_count::now();
    res = ParLabeling(arr, rows, cols);
    tbb::tick_count t2 = tbb::tick_count::now();
    n_size_par = check_for_par(res, rows, cols);

    tbb::tick_count t3 = tbb::tick_count::now();
    expected = SeqLabeling(arr, rows, cols);
    tbb::tick_count t4 = tbb::tick_count::now();
    n_size_seq = check_for_seq(expected, rows, cols);
    printf("\tparallel time %f\n", (t2 - t1).seconds());
    printf("\tsequential time %f\n", (t4 - t3).seconds());
    bool check_passed = false;
    if ((n_size_par == n_size_seq) && (n_size_par != 0)) {
        check_passed = true;
    }

    ASSERT_TRUE(check_passed);
}

TEST(Labeling_TBB, Test_200x70) {
    int rows = 200;
    int cols = 70;
    std::vector<std::vector<int>> arr = myrand(rows, cols, 5000);
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> expected;
    int n_size_seq = 0;
    int n_size_par = 0;
    tbb::tick_count t1 = tbb::tick_count::now();
    res = ParLabeling(arr, rows, cols);
    tbb::tick_count t2 = tbb::tick_count::now();
    n_size_par = check_for_par(res, rows, cols);

    tbb::tick_count t3 = tbb::tick_count::now();
    expected = SeqLabeling(arr, rows, cols);
    tbb::tick_count t4 = tbb::tick_count::now();
    n_size_seq = check_for_seq(expected, rows, cols);
    printf("\tparallel time %f\n", (t2 - t1).seconds());
    printf("\tsequential time %f\n", (t4 - t3).seconds());
    bool check_passed = false;
    if ((n_size_par == n_size_seq) && (n_size_par != 0)) {
        check_passed = true;
    }

    ASSERT_TRUE(check_passed);
}

TEST(Labeling_TBB, Test_300x300) {
    int rows = 300;
    int cols = 300;
    std::vector<std::vector<int>> arr = myrand(rows, cols, 45000);
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> expected;
    int n_size_seq = 0;
    int n_size_par = 0;
    tbb::tick_count t1 = tbb::tick_count::now();
    res = ParLabeling(arr, rows, cols);
    tbb::tick_count t2 = tbb::tick_count::now();
    n_size_par = check_for_par(res, rows, cols);

    tbb::tick_count t3 = tbb::tick_count::now();
    expected = SeqLabeling(arr, rows, cols);
    tbb::tick_count t4 = tbb::tick_count::now();
    n_size_seq = check_for_seq(expected, rows, cols);
    printf("\tparallel time %f\n", (t2 - t1).seconds());
    printf("\tsequential time %f\n", (t4 - t3).seconds());
    bool check_passed = false;
    if ((n_size_par == n_size_seq) && (n_size_par != 0)) {
        check_passed = true;
    }

    ASSERT_TRUE(check_passed);
}
TEST(Labeling_TBB, Test_55x85) {
    int rows = 55;
    int cols = 85;
    std::vector<std::vector<int>> arr = myrand(rows, cols, 2200);
    std::vector<std::vector<int>> res;
    std::vector<std::vector<int>> expected;
    int n_size_seq = 0;
    int n_size_par = 0;
    tbb::tick_count t1 = tbb::tick_count::now();
    res = ParLabeling(arr, rows, cols);
    tbb::tick_count t2 = tbb::tick_count::now();
    n_size_par = check_for_par(res, rows, cols);

    tbb::tick_count t3 = tbb::tick_count::now();
    expected = SeqLabeling(arr, rows, cols);
    tbb::tick_count t4 = tbb::tick_count::now();
    n_size_seq = check_for_seq(expected, rows, cols);
    printf("\tparallel time %f\n", (t2 - t1).seconds());
    printf("\tsequential time %f\n", (t4 - t3).seconds());
    bool check_passed = false;
    if ((n_size_par == n_size_seq) && (n_size_par != 0)) {
        check_passed = true;
    }

    ASSERT_TRUE(check_passed);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

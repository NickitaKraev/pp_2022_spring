// Copyright 2022 Kraev Nikita
#include <gtest/gtest.h>
#include "./radix_sort_with_even_odd_merge_tbb.h"

TEST(Parallel_Sort, Test_Radix_Sort_1) {
    std::vector<double> vec = { 1.0, -6.2, 7.45, -22.3457, 0.0, 45.69876, -0.03 };
    std::vector<double> sort_vec = { -22.3457, -6.2, -0.03, 0.0, 1.0, 7.45, 45.69876 };
    int number_threads = 2;
    int size = 7;
    vec = parallelRadixSort(&vec, number_threads, size);
    ASSERT_EQ(sort_vec, vec);
}

TEST(Parallel_Sort, Test_Radix_Sort_2) {
    int size = 100;
    std::vector<double> vec = getRandomVector(size);
    std::vector<double> std_sort_vec = vec;
    int number_threads = 2;
    std::sort(std_sort_vec.begin(), std_sort_vec.end());
    vec = parallelRadixSort(&vec, number_threads, size);
    ASSERT_EQ(std_sort_vec, vec);
}

TEST(Parallel_Sort, Test_Radix_Sort_3) {
    int size = 100;
    std::vector<double> vec = getRandomVector(size);
    std::vector<double> seq_vec = vec;
    int number_threads = 2;
    radixSort(&seq_vec);
    vec = parallelRadixSort(&vec, number_threads, size);
    ASSERT_EQ(seq_vec, vec);
}

TEST(Parallel_Sort, Test_Radix_Sort_4) {
    int size = 500;
    std::vector<double> vec = getRandomVector(size);
    std::vector<double> seq_vec = vec;
    int number_threads = 3;
    radixSort(&seq_vec);
    vec = parallelRadixSort(&vec, number_threads, size);
    ASSERT_EQ(seq_vec, vec);
}

TEST(Parallel_Sort, Test_Radix_Sort_5) {
    int size = 1000;
    std::vector<double> vec = getRandomVector(size);
    std::vector<double> seq_vec = vec;
    int number_threads = 4;
    radixSort(&seq_vec);
    vec = parallelRadixSort(&vec, number_threads, size);
    ASSERT_EQ(seq_vec, vec);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

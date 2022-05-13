// Copyright 2022 Kraev Nikita
#include <gtest/gtest.h>
#include "../../../3rdparty/unapproved/unapproved.h"
#include "./radix_sort_with_even_odd_merge_std.h"

TEST(Parallel_Sort, Test_Radix_Sort_1) {
    std::vector<double> vec = { 1.0, -6.2, 7.45, -22.3457, 0.0, 45.69876, -0.03, 0.1 };
    std::vector<double> sort_vec = { -22.3457, -6.2, -0.03, 0.0, 0.1, 1.0, 7.45, 45.69876 };
    int size = 8;
    vec = parallelRadixSort(&vec, size);
    ASSERT_EQ(sort_vec, vec);
}

TEST(Parallel_Sort, Test_Radix_Sort_2) {
    int size = 100;
    std::vector<double> vec = getRandomVector(size);
    std::vector<double> std_sort_vec = vec;
    std::sort(std_sort_vec.begin(), std_sort_vec.end());
    vec = parallelRadixSort(&vec, size);
    ASSERT_EQ(std_sort_vec, vec);
}

TEST(Parallel_Sort, Test_Radix_Sort_3) {
    int size = 300;
    std::vector<double> vec = getRandomVector(size);
    std::vector<double> seq_vec = vec;
    radixSort(&seq_vec);
    vec = parallelRadixSort(&vec, size);
    ASSERT_EQ(seq_vec, vec);
}

TEST(Parallel_Sort, Test_Radix_Sort_4) {
    int size = 500;
    std::vector<double> vec = getRandomVector(size);
    std::vector<double> seq_vec = vec;
    radixSort(&seq_vec);
    vec = parallelRadixSort(&vec, size);
    ASSERT_EQ(seq_vec, vec);
}

TEST(Parallel_Sort, Test_Radix_Sort_5) {
    int size = 1000;
    std::vector<double> vec = getRandomVector(size);
    std::vector<double> seq_vec = vec;
    radixSort(&seq_vec);
    vec = parallelRadixSort(&vec, size);
    ASSERT_EQ(seq_vec, vec);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

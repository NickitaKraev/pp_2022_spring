// Copyright 2022 Kolosova Alena
#include <gtest/gtest.h>

#include "./ccs_complex_mult.h"

TEST(CCSComplexMatrix, can_generate_matrix_with_default_density) {
    ASSERT_NO_THROW(generate_matrix(10, 10));
}

TEST(CCSComplexMatrix, can_generate_matrix_with_set_density) {
    ASSERT_NO_THROW(generate_matrix(10, 10, 0.3));
}

TEST(CCSComplexMatrix, can_convert_matrix_to_CCS) {
    std::vector<std::complex<double>> v1{ {0.0, 0.0}, {3.0, 0.0}, {0.0, 0.0}, {0.0, 7.0} };
    std::vector<std::complex<double>> v2{ {0.0, 0.0}, {0.0, 0.0}, {8.0, 0.0}, {0.0, 0.0} };
    std::vector<std::complex<double>> v3{ {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };
    std::vector<std::complex<double>> v4{ {9.0, 0.0}, {0.0, 0.0}, {0.0, 15.0}, {0.0, 17.0} };
    std::vector<std::vector<std::complex<double>>> vControl{ v1, v2, v3, v4 };

    CCS_matrix vTest(4, 4);
    vTest.val = { {9.0, 0.0}, {3.0, 0.0}, {8.0, 0.0}, {0.0, 15.0}, {0.0, 7.0}, {0.0, 17.0} };
    vTest.rows = { 3, 0, 1, 3, 0, 3 };
    vTest.column_pointer = { 0, 1, 2, 4, 6 };

    CCS_matrix m(vControl);
    EXPECT_EQ(m, vTest);
}

TEST(CCSComplexMatrix, can_transpose_matrix) {
    CCS_matrix m1(4, 5);
    m1.val = { {9.0, 0.0}, {3.0, 0.0}, {8.0, 0.0}, {0.0, 15.0}, {0.0, 7.0}, {0.0, 17.0}, {0.0, 5.0} };
    m1.rows = { 3, 0, 1, 3, 0, 3 , 3};
    m1.column_pointer = { 0, 1, 2, 4, 6, 7 };

    CCS_matrix m2(5, 4);
    m2.val = { {3.0, 0.0}, {0.0, 7.0}, {8.0, 0.0}, {9.0, 0.0}, {0.0, 15.0}, {0.0, 17.0}, {0.0, 5.0} };
    m2.rows = { 1, 3, 2, 0, 2, 3, 4};
    m2.column_pointer = { 0, 2, 3, 3, 7 };

    CCS_matrix m2t = transpose(m2);
    EXPECT_EQ(m1, m2t);
}

TEST(CCSComplexMatrix, throws_when_multiplies_empty_matrix_as_vector) {
    std::vector<std::vector<std::complex<double>>> v;
    EXPECT_ANY_THROW(multiply_v(v, v));
}

TEST(CCSComplexMatrix, throws_when_matrices_are_of_incompatible_size) {
    std::vector<std::vector<std::complex<double>>> v1(10);
    for (auto row : v1) row = std::vector<std::complex<double>>(3, { 1.0, 0.0 });

    std::vector<std::vector<std::complex<double>>> v2(10);
    for (auto row : v2) row = std::vector<std::complex<double>>(3, { 1.0, 0.0 });

    EXPECT_ANY_THROW(multiply_v(v1, v2));
}

TEST(CCSComplexMatrix, throws_when_CCS_matrices_are_of_incompatible_size) {
    CCS_matrix m1(2, 3), m2(4, 5);
    EXPECT_ANY_THROW(multiply(m1, m2));
}

TEST(CCSComplexMatrix, can_multiply_matrices_as_vectors) {
    std::vector<std::complex<double>> v1{ {2, 0}, {5, 0}, {7, 0} };
    std::vector<std::complex<double>> v2{ {6, 0}, {3, 0}, {4, 0} };
    std::vector<std::complex<double>> v3{ {5, 0}, {-2, 0}, {-3, 0} };
    std::vector<std::vector<std::complex<double>>> m1{ v1, v2, v3 };

    std::vector<std::complex<double>> v21{ {1, 0}, {-1, 0}, {1, 0} };
    std::vector<std::complex<double>> v22{ {-38, 0}, {41, 0}, {-34, 0} };
    std::vector<std::complex<double>> v23{ {27, 0}, {-29, 0}, {24, 0} };
    std::vector<std::vector<std::complex<double>>> m2{ v21, v22, v23 };

    std::vector<std::complex<double>> v31{ {1, 0}, {0, 0}, {0, 0} };
    std::vector<std::complex<double>> v32{ {0, 0}, {1, 0}, {0, 0} };
    std::vector<std::complex<double>> v33{ {0, 0}, {0, 0}, {1, 0} };
    std::vector<std::vector<std::complex<double>>> m3{ v31, v32, v33 };

    EXPECT_EQ(m3, multiply_v(m1, m2));
}

TEST(CCSComplexMatrix, can_multiply_small_CCS_matrices) {
    std::vector<std::vector<std::complex<double>>> mTest1 = generate_matrix(10, 10, 0.1),
        mTest2 = generate_matrix(10, 10, 0.1);
    CCS_matrix m1(mTest1), m2(mTest2);
    EXPECT_EQ(CCS_matrix(multiply_v(mTest1, mTest2)), multiply(m1, m2));
}

TEST(CCSComplexMatrix, can_multiply_larger_CCS_matrices) {
    std::vector<std::vector<std::complex<double>>> mTest1 = generate_matrix(100, 100, 0.1),
        mTest2 = generate_matrix(100, 100, 0.1);
    CCS_matrix m1(mTest1), m2(mTest2);
    EXPECT_EQ(CCS_matrix(multiply_v(mTest1, mTest2)), multiply(m1, m2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

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
    std::vector<std::complex<double>> v1{ {0.0, 0.0}, {3.0, 0.0}, {0.0, 0.0}, {0.0, 7.0}, {0.0, 0.0} };
    std::vector<std::complex<double>> v2{ {0.0, 0.0}, {0.0, 0.0}, {8.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };
    std::vector<std::complex<double>> v3{ {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0} };
    std::vector<std::complex<double>> v4{ {9.0, 0.0}, {0.0, 0.0}, {0.0, 15.0}, {0.0, 17.0}, {0.0, 5.0} };
    std::vector<std::vector<std::complex<double>>> m01{ v1, v2, v3, v4 };
    CCS_matrix m1(m01);

    std::vector<std::complex<double>> v11{ {0, 0}, {0, 0}, {0, 0}, {9, 0} };
    std::vector<std::complex<double>> v12{ {3, 0}, {0, 0}, {0, 0}, {0, 0} };
    std::vector<std::complex<double>> v13{ {0, 0}, {8, 0}, {0, 0}, {0, 15} };
    std::vector<std::complex<double>> v14{ {0, 7}, {0, 0}, {0, 0}, {0, 17} };
    std::vector<std::complex<double>> v15{ {0, 0}, {0, 0}, {0, 0}, {0, 5} };
    std::vector<std::vector<std::complex<double>>> m02{ v11, v12, v13, v14, v15 };
    CCS_matrix m2(m02);

    CCS_matrix m2t = transpose(m2);

    EXPECT_EQ(m1, m2t);
}

TEST(CCSComplexMatrix, can_transpose_matrix_tbb) {
    CCS_matrix m1(4, 5);
    m1.val = { {9.0, 0.0}, {3.0, 0.0}, {8.0, 0.0}, {0.0, 15.0}, {0.0, 7.0}, {0.0, 17.0}, {0.0, 5.0} };
    m1.rows = { 3, 0, 1, 3, 0, 3 , 3 };
    m1.column_pointer = { 0, 1, 2, 4, 6, 7 };

    CCS_matrix m2(5, 4);
    m2.val = { {3.0, 0.0}, {0.0, 7.0}, {8.0, 0.0}, {9.0, 0.0}, {0.0, 15.0}, {0.0, 17.0}, {0.0, 5.0} };
    m2.rows = { 1, 3, 2, 0, 2, 3, 4 };
    m2.column_pointer = { 0, 2, 3, 3, 7 };

    CCS_matrix m2t = transpose_tbb(m2);

    EXPECT_EQ(m1, m2t);
}

TEST(CCSComplexMatrix, throws_when_CCS_matrices_are_of_incompatible_size) {
    CCS_matrix m1(2, 3), m2(4, 5);
    EXPECT_ANY_THROW(multiply(m1, m2));
}

TEST(CCSComplexMatrix, throws_when_CCS_matrices_are_of_incompatible_size_tbb) {
    CCS_matrix m1(2, 3), m2(4, 5);
    EXPECT_ANY_THROW(multiply_tbb(m1, m2));
}

TEST(CCSComplexMatrix, can_multiply_small_CCS_matrices) {
    std::vector<std::vector<std::complex<double>>> tmp1 = generate_matrix(10, 10, 0.1),
        tmp2 = generate_matrix(10, 10, 0.1);
    CCS_matrix m1(tmp1), m2(tmp2);

    tbb::tick_count start1 = tbb::tick_count::now();
    CCS_matrix res1 = multiply(m1, m2);
    tbb::tick_count end1 = tbb::tick_count::now();
    double dt1 = (end1 - start1).seconds();
    std::cerr << "Sequential: " << dt1 << std::endl;

    tbb::tick_count start2 = tbb::tick_count::now();
    CCS_matrix res2 = multiply_tbb(m1, m2);
    tbb::tick_count end2 = tbb::tick_count::now();
    double dt2 = (end2 - start2).seconds();
    std::cerr << "Parallel: " << dt2 << std::endl;

    EXPECT_EQ(res1, res2);
}

TEST(CCSComplexMatrix, can_multiply_medium_CCS_matrices) {
    std::vector<std::vector<std::complex<double>>> tmp1 = generate_matrix(100, 100, 0.1),
        tmp2 = generate_matrix(100, 100, 0.1);
    CCS_matrix m1(tmp1), m2(tmp2);

    tbb::tick_count start1 = tbb::tick_count::now();
    CCS_matrix res1 = multiply(m1, m2);
    tbb::tick_count end1 = tbb::tick_count::now();
    double dt1 = (end1 - start1).seconds();
    std::cerr << "Sequential: " << dt1 << std::endl;

    tbb::tick_count start2 = tbb::tick_count::now();
    CCS_matrix res2 = multiply_tbb(m1, m2);
    tbb::tick_count end2 = tbb::tick_count::now();
    double dt2 = (end2 - start2).seconds();
    std::cerr << "Parallel: " << dt2 << std::endl;

    EXPECT_EQ(res1, res2);
}

TEST(CCSComplexMatrix, can_multiply_large_CCS_matrices) {
    std::vector<std::vector<std::complex<double>>> tmp1 = generate_matrix(1000, 1000, 0.1),
        tmp2 = generate_matrix(1000, 1000, 0.1);
    CCS_matrix m1(tmp1), m2(tmp2);

    tbb::tick_count start1 = tbb::tick_count::now();
    CCS_matrix res1 = multiply(m1, m2);
    tbb::tick_count end1 = tbb::tick_count::now();
    double dt1 = (end1 - start1).seconds();
    std::cerr << "Sequential: " << dt1 << std::endl;

    tbb::tick_count start2 = tbb::tick_count::now();
    CCS_matrix res2 = multiply_tbb(m1, m2);
    tbb::tick_count end2 = tbb::tick_count::now();
    double dt2 = (end2 - start2).seconds();
    std::cerr << "Parallel: " << dt2 << std::endl;

    EXPECT_EQ(res1, res2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

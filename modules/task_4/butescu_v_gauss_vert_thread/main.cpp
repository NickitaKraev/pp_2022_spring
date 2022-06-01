  // Copyright 2022 Butescu Vladimir
#include <gtest/gtest.h>
#include <vector>
#include "../../../modules/task_4/butescu_v_gauss_vert_thread/vert_gauss.h"

TEST(Gaussian_Filter_Thread, Zero_Rows_Cols) {
    int rows = 0;
    int cols = 0;
    std::vector<double> matrix(rows * cols);

    ASSERT_ANY_THROW(matrix = gauss_filter_parralel_thread(matrix, rows, cols));
}

TEST(Gaussian_Filter_Thread, Zero_Matrix) {
    int rows = 3;
    int cols = 3;
    std::vector<double> matrix(0);

    ASSERT_ANY_THROW(matrix = gauss_filter_parralel_thread(matrix, rows, cols));
}

TEST(Gaussian_Filter_Thread, Test_Random_Matrix_Size_25x25) {
    int rows = 25;
    int cols = 25;
    std::vector<double> matrix = createRandomMatrix(rows, cols);

    auto start_seq = clock();
    std::vector <double> sq = gauss_filter_sequence(matrix, cols, rows);
    auto end_seq = clock();
    double seq_time = static_cast<double>(end_seq - start_seq) / CLOCKS_PER_SEC;

    auto start_thread = clock();
    std::vector <double> pp = gauss_filter_parralel_thread(matrix, cols, rows);
    auto end_thread = clock();
    double thread_time = static_cast<double>(start_thread - end_thread) / CLOCKS_PER_SEC;

    std::cout << "SQ TIME: " << seq_time << std::endl;
    std::cout << "PP TIME: " << thread_time << std::endl;

    ASSERT_EQ(sq, pp);
}

TEST(Gaussian_Filter_Thread, Test_Random_Matrix_Size_100x100) {
    int rows = 100;
    int cols = 100;
    std::vector<double> matrix = createRandomMatrix(rows, cols);

    auto start_seq = clock();
    std::vector <double> sq = gauss_filter_sequence(matrix, cols, rows);
    auto end_seq = clock();
    double seq_time = static_cast<double>(end_seq - start_seq) / CLOCKS_PER_SEC;

    auto start_thread = clock();
    std::vector <double> pp = gauss_filter_parralel_thread(matrix, cols, rows);
    auto end_thread = clock();
    double thread_time = static_cast<double>(start_thread - end_thread) / CLOCKS_PER_SEC;

    std::cout << "SQ TIME: " << seq_time << std::endl;
    std::cout << "PP TIME: " << thread_time << std::endl;

    ASSERT_EQ(sq, pp);
}

TEST(Gaussian_Filter_Thread, Test_Random_Matrix_Size_250x250) {
    int rows = 250;
    int cols = 250;
    std::vector<double> matrix = createRandomMatrix(rows, cols);

    auto start_seq = clock();
    std::vector <double> sq = gauss_filter_sequence(matrix, cols, rows);
    auto end_seq = clock();
    double seq_time = static_cast<double>(end_seq - start_seq) / CLOCKS_PER_SEC;

    auto start_thread = clock();
    std::vector <double> pp = gauss_filter_parralel_thread(matrix, cols, rows);
    auto end_thread = clock();
    double thread_time = static_cast<double>(start_thread - end_thread) / CLOCKS_PER_SEC;

    std::cout << "SQ TIME: " << seq_time << std::endl;
    std::cout << "PP TIME: " << thread_time << std::endl;

    ASSERT_EQ(sq, pp);
}

TEST(Gaussian_Filter_Thread, Test_Random_Matrix_Size_500x500) {
    int rows = 500;
    int cols = 500;
    std::vector<double> matrix = createRandomMatrix(rows, cols);

    auto start_seq = clock();
    std::vector <double> sq = gauss_filter_sequence(matrix, cols, rows);
    auto end_seq = clock();
    double seq_time = static_cast<double>(end_seq - start_seq) / CLOCKS_PER_SEC;

    auto start_thread = clock();
    std::vector <double> pp = gauss_filter_parralel_thread(matrix, cols, rows);
    auto end_thread = clock();
    double thread_time = static_cast<double>(start_thread - end_thread) / CLOCKS_PER_SEC;

    std::cout << "SQ TIME: " << seq_time << std::endl;
    std::cout << "PP TIME: " << thread_time << std::endl;

    ASSERT_EQ(sq, pp);
}

TEST(Gaussian_Filter_Thread, Test_Random_Matrix_Size_1000x1000) {
    int rows = 1000;
    int cols = 1000;
    std::vector<double> matrix = createRandomMatrix(rows, cols);

    auto start_seq = clock();
    std::vector <double> sq = gauss_filter_sequence(matrix, cols, rows);
    auto end_seq = clock();
    double seq_time = static_cast<double>(end_seq - start_seq) / CLOCKS_PER_SEC;

    auto start_thread = clock();
    std::vector <double> pp = gauss_filter_parralel_thread(matrix, cols, rows);
    auto end_thread = clock();
    double thread_time = static_cast<double>(start_thread - end_thread) / CLOCKS_PER_SEC;

    std::cout << "SQ TIME: " << seq_time << std::endl;
    std::cout << "PP TIME: " << thread_time << std::endl;

    ASSERT_EQ(sq, pp);
}

TEST(Gaussian_Filter_Thread, Test_Random_Matrix_Size_5000x5000) {
    int rows = 1000;
    int cols = 1000;
    std::vector<double> matrix = createRandomMatrix(rows, cols);

    auto start_seq = clock();
    std::vector <double> sq = gauss_filter_sequence(matrix, cols, rows);
    auto end_seq = clock();
    double seq_time = static_cast<double>(end_seq - start_seq) / CLOCKS_PER_SEC;

    auto start_thread = clock();
    std::vector <double> pp = gauss_filter_parralel_thread(matrix, cols, rows);
    auto end_thread = clock();
    double thread_time = static_cast<double>(start_thread - end_thread) / CLOCKS_PER_SEC;

    std::cout << "SQ TIME: " << seq_time << std::endl;
    std::cout << "PP TIME: " << thread_time << std::endl;

    ASSERT_EQ(sq, pp);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

  // Copyright 2022 Mishina Nadezhda
#include <gtest/gtest.h>
#include "./mishina_n_conj_gradients.h"

TEST(Conjugate_gradient, TEST_2x2) {
    int n = 2;
    std::vector<std::vector<double>> A = { { 5, 6}, {6, 9} };
    std::vector<double> b = { 2, 7 };
    std::vector<double> sol = ConjGradPar(A, b, n);
    std::vector<double> res = { -2.67, 2.56 };
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NEAR(sol[i], res[i], 0.5);
    }
}
TEST(Conjugate_gradient, TEST_5x5) {
    int n = 5;
    std::vector<std::vector<double>> A = { {2, 1, 1, 3, 1},
                                           {1, 3, 2, 2, 4},
                                           {1, 2, 7, 4, 5},
                                           {3, 2, 4, 9, 6},
                                           {1, 4, 5, 6, 13}, };
    std::vector<double> b = { 5, 4, 8, 7, 3};
    std::vector<double> x = ConjGradPar(A, b, n);
    std::vector<double> res = { 2.545, 0.4838, 1.149, -0.4597, -0.3436};
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NEAR(x[i], res[i], 0.5);
    }
}
TEST(Conjugate_gradient, TEST_100x100) {
    int n = 16;
    std::vector<std::vector<double>> A = RandMatr(100);
    std::vector<double> b = RandVec(100);
    clock_t start2 = clock();
    std::vector<double> ResPar = ConjGradPar(A, b, n);
    clock_t finish2 = clock();
    clock_t start1 = clock();
    std::vector<double> ResSec = ConjGrad(A, b);
    clock_t finish1 = clock();
    double TimeSec = static_cast<double>(finish1 - start1) / CLOCKS_PER_SEC;
    std::cout << "Sequental Time:" << TimeSec << std::endl;
    double TimePar = static_cast<double>(finish2 - start2) / CLOCKS_PER_SEC;
    std::cout << "Parallel Time:" << TimePar << std::endl;
    for (int i = 0; i < 100; i++) {
        ASSERT_NEAR(ResSec[i], ResPar[i], 0.5);
    }
}
TEST(Conjugate_gradient, TEST_500x500) {
    int n = 16;
    std::vector<std::vector<double>> A = RandMatr(500);
    std::vector<double> b = RandVec(500);
    clock_t start2 = clock();
    std::vector<double> ResPar = ConjGradPar(A, b, n);
    clock_t finish2 = clock();
    clock_t start1 = clock();
    std::vector<double> ResSec = ConjGrad(A, b);
    clock_t finish1 = clock();
    double TimeSec = static_cast<double>(finish1 - start1) / CLOCKS_PER_SEC;
    std::cout << "Sequental Time:" << TimeSec << std::endl;
    double TimePar = static_cast<double>(finish2 - start2) / CLOCKS_PER_SEC;
    std::cout << "Parallel Time:" << TimePar << std::endl;
    for (int i = 0; i < 500; i++) {
        ASSERT_NEAR(ResSec[i], ResPar[i], 0.5);
    }
}
TEST(Conjugate_gradient, TEST_1000x1000) {
    int n = 16;
    std::vector<std::vector<double>> A = RandMatr(1000);
    std::vector<double> b = RandVec(1000);
    clock_t start2 = clock();
    std::vector<double> ResPar = ConjGradPar(A, b, n);
    clock_t finish2 = clock();
    clock_t start1 = clock();
    std::vector<double> ResSec = ConjGrad(A, b);
    clock_t finish1 = clock();
    double TimeSec = static_cast<double>(finish1 - start1) / CLOCKS_PER_SEC;
    std::cout << "Sequental Time:" << TimeSec << std::endl;
    double TimePar = static_cast<double>(finish2 - start2) / CLOCKS_PER_SEC;
    std::cout << "Parallel Time:" << TimePar << std::endl;
    for (int i = 0; i < 1000; i++) {
        ASSERT_NEAR(ResSec[i], ResPar[i], 0.5);
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

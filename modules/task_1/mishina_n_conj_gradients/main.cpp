  // Copyright 2022 Mishina Nadezhda
#include <gtest/gtest.h>
#include "./mishina_n_conj_gradients.h"

TEST(Conjugate_gradient, TEST_VecMultVec) {
    std::vector<double> a = { 4, 5 };
    std::vector<double> b = { 2, 11 };
    double sol = VecMultVec(a, b);
    double res = 63;
    ASSERT_EQ(sol, res);
}
TEST(Conjugate_gradient, TEST_VecMultNum) {
    std::vector<double> a = { 4, 5 };
    double n = 3;
    std::vector<double> sol = VecMultNum(a, n);
    std::vector<double> res = { 12, 15 };
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_EQ(sol[i], res[i]);
    }
}
TEST(Conjugate_gradient, TEST_VecSum) {
    std::vector<double> a = { 4, 5 };
    std::vector<double> b = { 2, 11 };
    std::vector<double> sol = VecSum(a, b);
    std::vector<double> res = { 6, 16 };
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_EQ(sol[i], res[i]);
    }
}
TEST(Conjugate_gradient, TEST_VecOtr) {
    std::vector<double> a = { 4, 5 };
    std::vector<double> sol = VecOtr(a);
    std::vector<double> res = { -4, -5 };
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_EQ(sol[i], res[i]);
    }
}
TEST(Conjugate_gradient, TEST_MatrMultVec) {
    std::vector<std::vector<double>> A = { { 1, 3}, {3, 8} };
    std::vector<double> b = { 4, 5 };

    std::vector<double> sol = MatrMultVec(A, b);
    std::vector<double> res = { 19, 52 };
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_EQ(sol[i], res[i]);
    }
}
TEST(Conjugate_gradient, TEST_2x2) {
    std::vector<std::vector<double>> A = { { 1, 3}, {3, 8} };
    std::vector<double> b = { 4, 5 };

    std::vector<double> sol = ConjGrad(A, b);
    std::vector<double> res = { -17, 7 };
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NEAR(sol[i], res[i], 0.5);
    }
}
TEST(Conjugate_gradient, TEST_5x5) {
    std::vector<std::vector<double>> A = { {7, 6, 2, 5, 8},
                                           {6, 8, 3, 7, 9},
                                           {2, 3, 2, 3, 3},
                                           {5, 7, 3, 7, 8},
                                           {8, 9, 3, 8, 12}, };
    std::vector<double> b = { 4, 7, 2, 11, 3};

    std::vector<double> x = ConjGrad(A, b);
    std::vector<double> res = { 3.33, -0.33, -7.33, 10.66, -7};
    for (size_t i = 0; i < res.size(); ++i) {
        ASSERT_NEAR(x[i], res[i], 0.5);
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Copyright 2022 Dydykin Pavel
#include "gtest/gtest.h"
#include "../../task_3/dydykin_p_rectangle_method/rectangle_method.h"

double func1(std::vector<double> args) {
    return 2 * args[0] * args[0];
}

double func2(std::vector<double> args) {
    return 8 + 2 * args[0] - args[0] * args[0];
}

double func3(std::vector<double> args) {
    return args[0] + args[1];
}

double func4(std::vector<double> args) {
    return args[0] + args[1] * args[1];
}

double func5(std::vector<double> args) {
    return args[0] * args[0] + args[1] * args[1] + args[2] * args[2];
}

TEST(Dydykin_Rectangle_Method, Test_Exception_1) {
    std::vector<int> start = { 1 };
    std::vector<int> end = { 2, 1 };
    int count = 40;
    ASSERT_ANY_THROW(Rectangle_Method_Parallel(start, end, count, func1));
}

TEST(Dydykin_Rectangle_Method, Test_Exception_2) {
    std::vector<int> start = { 1 };
    std::vector<int> end = { 2 };
    int count = -5;
    ASSERT_ANY_THROW(Rectangle_Method_Parallel(start, end, count, func1));
}

TEST(Dydykin_Rectangle_Method, Test_Exception_3) {
    std::vector<int> start = { 2 };
    std::vector<int> end = { 1 };
    int count = 40;
    ASSERT_ANY_THROW(Rectangle_Method_Parallel(start, end, count, func1));
}

TEST(Dydykin_Rectangle_Method, Test_One_Integral_Func1) {
    std::vector<int> start = { 1 };
    std::vector<int> end = { 2 };
    int count = 40;
    double result = Rectangle_Method_Seq(start, end, count, func1);
    double exp = 4.6;
    EXPECT_NEAR(result, exp, 0.5);
}

TEST(Dydykin_Rectangle_Method, Test_One_Integral_Func2) {
    std::vector<int> start = { -2 };
    std::vector<int> end = { 4 };
    int count = 40;
    double result = Rectangle_Method_Seq(start, end, count, func2);
    double exp = 36;
    EXPECT_NEAR(result, exp, 0.5);
}

TEST(Dydykin_Rectangle_Method, Test_Two_Integral_Func3) {
    std::vector<int> start = { 2, 5 };
    std::vector<int> end = { 3, 7 };
    int count = 40;
    double result = Rectangle_Method_Seq(start, end, count, func3);
    double exp = 50.7;
    EXPECT_NEAR(result, exp, 0.5);
}

TEST(Dydykin_Rectangle_Method, Test_Two_Integral_Func4) {
    std::vector<int> start = { 2, 1 };
    std::vector<int> end = { 3, 2 };
    int count = 40;
    double result = Rectangle_Method_Seq(start, end, count, func4);
    double exp = 19.3;
    EXPECT_NEAR(result, exp, 0.5);
}

// TEST(Dydykin_Rectangle_Method, Test_Three_Integral_Func) {
//    std::vector<int> start = { 0, 0, 0 };
//    std::vector<int> end = { 1, 1, 1 };
//    int count = 1000000;
//    tbb::tick_count t1 = tbb::tick_count::now();
//    double result = Rectangle_Method_Seq(start, end, count, func5);
//    tbb::tick_count t2 = tbb::tick_count::now();
//    tbb::tick_count p1 = tbb::tick_count::now();
//    double result1 = Rectangle_Method_Parallel(start, end, count, func5);
//    tbb::tick_count p2 = tbb::tick_count::now();
//    std::cout << "Sequential time: " << t2 - t1 << std::endl;
//    std::cout << "Parallel time: " << p2 - p1 << std::endl;
//    std::cout << "Efficiency: " << (t2 - t1) / (p2 - p1) << std::endl;
//    EXPECT_NEAR(result, result1, 0.5);
// }

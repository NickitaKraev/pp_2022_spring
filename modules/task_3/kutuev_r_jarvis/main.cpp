// Copyright 2022 Kutuev Roman
#include <gtest/gtest.h>

#include "../../../modules/task_3/kutuev_r_jarvis/jarvis.h"
TEST(Jarvis, test_1) {
    std::vector<Point> quick = convex_hull(set_points(2));
    EXPECT_DOUBLE_EQ(quick.size(), 0);
}

TEST(Jarvis, test_2) {
    std::vector<Point> polygon{ {1, 1}, {2, 2}, {2, 1}, {1, 2} };
    std::vector<Point> quick = convex_hull(polygon);

    EXPECT_DOUBLE_EQ(quick[0].x, polygon[0].x);
    EXPECT_DOUBLE_EQ(quick[0].y, polygon[0].y);
    EXPECT_DOUBLE_EQ(quick[1].x, polygon[2].x);
    EXPECT_DOUBLE_EQ(quick[1].y, polygon[2].y);
    EXPECT_DOUBLE_EQ(quick[2].x, polygon[1].x);
    EXPECT_DOUBLE_EQ(quick[2].y, polygon[1].y);
    EXPECT_DOUBLE_EQ(quick[3].x, polygon[3].x);
    EXPECT_DOUBLE_EQ(quick[3].y, polygon[3].y);
}
TEST(Jarvis, test_3) {
    std::vector<Point> polygon{ {1, 1}, {3, 1}, {3, 2}, {3, 3}, {2, 3}, {1, 3} };
    std::vector<Point> quick = convex_hull(polygon);
    EXPECT_DOUBLE_EQ(quick[0].x, polygon[0].x);
    EXPECT_DOUBLE_EQ(quick[0].y, polygon[0].y);
    EXPECT_DOUBLE_EQ(quick[1].x, polygon[1].x);
    EXPECT_DOUBLE_EQ(quick[1].y, polygon[1].y);
    EXPECT_DOUBLE_EQ(quick[2].x, polygon[3].x);
    EXPECT_DOUBLE_EQ(quick[2].y, polygon[3].x);
    EXPECT_DOUBLE_EQ(quick[3].x, polygon[5].x);
    EXPECT_DOUBLE_EQ(quick[3].y, polygon[5].y);
}
TEST(Jarvis, test_4) {
    std::vector<Point> polygon{ {249, 106}, {419, 341}, {168, 227}, {176, 145},
                               {228, 309}, {449, 247}, {260, 98},  {264, 368},
                               {208, 286}, {365, 0} };
    std::vector<Point> quick = convex_hull(polygon);
    EXPECT_DOUBLE_EQ(quick[0].x, polygon[2].x);
    EXPECT_DOUBLE_EQ(quick[0].y, polygon[2].y);
    EXPECT_DOUBLE_EQ(quick[1].x, polygon[3].x);
    EXPECT_DOUBLE_EQ(quick[1].y, polygon[3].y);
    EXPECT_DOUBLE_EQ(quick[2].x, polygon[9].x);
    EXPECT_DOUBLE_EQ(quick[2].y, polygon[9].y);
    EXPECT_DOUBLE_EQ(quick[3].x, polygon[5].x);
    EXPECT_DOUBLE_EQ(quick[3].y, polygon[5].y);
    EXPECT_DOUBLE_EQ(quick[4].x, polygon[1].x);
    EXPECT_DOUBLE_EQ(quick[4].y, polygon[1].y);
    EXPECT_DOUBLE_EQ(quick[5].x, polygon[7].x);
    EXPECT_DOUBLE_EQ(quick[5].y, polygon[7].y);
    EXPECT_DOUBLE_EQ(quick[6].x, polygon[8].x);
    EXPECT_DOUBLE_EQ(quick[6].y, polygon[8].y);
}

TEST(Jarvis, test_5) {
    std::vector<Point> polygon = set_points(1);
    auto time1 = clock();
    std::vector<Point> quick = convex_hull(polygon);
    auto time2 = clock();
    auto time3 = clock();
    std::vector<Point> quick_omp = convex_hull_tbb(polygon);
    auto time4 = clock();
    printf("seq time : %f\n\n", static_cast<float>(time2 - time1) / CLOCKS_PER_SEC);
    printf("parallel time : %f\n\n", static_cast<float>(time4 - time3) / CLOCKS_PER_SEC);
    printf("time : %f\n\n", static_cast<float>(time2 - time1) / (time4 - time3));
    int size = quick.size();
    for (int i = 0; i < size; i++) {
        EXPECT_DOUBLE_EQ(quick[i].x, quick_omp[i].x);
        EXPECT_DOUBLE_EQ(quick[i].y, quick_omp[i].y);
    }
}

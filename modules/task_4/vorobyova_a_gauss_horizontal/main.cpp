// Copyright 2022 Vorobyova Anya
#include <gtest/gtest.h>

#include "../../../3rdparty/unapproved/unapproved.h"
#include "./gauss_horizontal.h"

TEST(GAUSS_HORIZONTAL_STD, TEST_1) {
  const int width = 5, height = 5;
  img image = getRandomImage(width, height);

  img new_image = getGauss(image, width, height);
  img new_image_std = getGaussSTD(image, width, height);

  for (int i = 0; i < static_cast<int>(new_image.size()); i++) {
    ASSERT_EQ(new_image[i], new_image_std[i]);
  }
}

TEST(GAUSS_HORIZONTAL_STD, TEST_2) {
  const int width = 16, height = 24;
  img image = getRandomImage(width, height);

  img new_image = getGauss(image, width, height);
  img new_image_std = getGaussSTD(image, width, height);

  for (int i = 0; i < static_cast<int>(new_image.size()); i++) {
    ASSERT_EQ(new_image[i], new_image_std[i]);
  }
}

TEST(GAUSS_HORIZONTAL_STD, TEST_3) {
  const int width = 12, height = 12;
  img image = getRandomImage(width, height);

  img new_image = getGauss(image, width, height);
  img new_image_std = getGaussSTD(image, width, height);

  for (int i = 0; i < static_cast<int>(new_image.size()); i++) {
    ASSERT_EQ(new_image[i], new_image_std[i]);
  }
}

TEST(GAUSS_HORIZONTAL_STD, TEST_4) {
  const int width = 11, height = 11;
  img image = getRandomImage(width, height);

  img new_image = getGauss(image, width, height);
  img new_image_std = getGaussSTD(image, width, height);

  for (int i = 0; i < static_cast<int>(new_image.size()); i++) {
    ASSERT_EQ(new_image[i], new_image_std[i]);
  }
}

TEST(GAUSS_HORIZONTAL_STD, TEST_SEQ_TIME) {
  const int width = 2000, height = 1000;
  img image = getRandomImage(width, height);

  auto time_1 = clock();
  getGauss(image, width, height);
  auto time_2 = clock();

  auto time_3 = clock();
  getGaussSTD(image, width, height);
  auto time_4 = clock();

  double seq = static_cast<double>(time_2 - time_1) / CLOCKS_PER_SEC;
  double par = static_cast<double>(time_4 - time_3) / CLOCKS_PER_SEC;
  double speed = (static_cast<double>(time_2 - time_1) / CLOCKS_PER_SEC) /
                 (static_cast<double>(time_4 - time_3) / CLOCKS_PER_SEC);

  std::cout << "Seq " << seq << std::endl;
  std::cout << "Par " << par << std::endl;
  std::cout << speed << std::endl;
}

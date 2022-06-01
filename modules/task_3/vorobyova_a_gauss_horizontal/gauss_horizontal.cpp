// Copyright 2022 Vorobyova Anya

#include "../../../modules/task_3/vorobyova_a_gauss_horizontal/gauss_horizontal.h"

#include <random>

img getRandomImage(int width, int height) {
  std::random_device dev;
  static std::mt19937 gen(dev());
  std::uniform_int_distribution<> uid(0, 255);

  img image = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j] = uid(gen);
    }
  }

  return image;
}

float calcNewPixelColor(const img& image, int x, int y) {
  float returnC = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int idx = (i + 1) * kernel.size + j + 1;
      int pixel = image[y + i][x + j];
      returnC += pixel * kernel.data[idx];
    }
  }
  return returnC;
}

img getGauss(const img& image, int width, int height) {
  img new_image =
      std::vector<std::vector<int>>(height - 2, std::vector<int>(width - 2, 0));

  for (int i = 1; i < height - 1; i++) {
    for (int j = 1; j < width - 1; j++) {
      new_image[i - 1][j - 1] = calcNewPixelColor(image, j, i);
    }
  }
  return new_image;
}

img getGaussTBB(const img& image, int width, int height) {
  img new_image =
      std::vector<std::vector<int>>(height - 2, std::vector<int>(width - 2, 0));

  tbb::parallel_for(
      tbb::blocked_range<int>(1, height - 1), [&](tbb::blocked_range<int> r) {
        for (int i = r.begin(); i < r.end(); ++i) {
          for (int j = 1; j < width - 1; j++) {
            new_image[i - 1][j - 1] = calcNewPixelColor(image, j, i);
          }
        }
      });

  return new_image;
}

// Copyright 2022 Butescu Vladimir
#include "../../../3rdparty/unapproved/unapproved.h"
#include "../../../modules/task_4/butescu_v_gauss_vert_thread/vert_gauss.h"

int clamp(int value, int max, int min) {
    if (value < min)
        return min;
    if (value > max)
        return max;
    return value;
}
std::vector<double> createRandomMatrix(int rows, int cols) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<double> result(rows * cols);
    for (int i = 0; i < rows * cols; i++)
        result[i] = gen() % 256;
    return result;
}
std::vector<double> gauss_filter_sequence(const std::vector<double>& matrix,
    int rows, int cols) {
    if (rows <= 0 || cols <= 0 || matrix.size() == 0) {
        throw - 1;
    }
    const int size = 3;
    const double sigma = 1.0;
    const int radius = 1;
    double norm = 0;

    std::vector<double> result(rows * cols);
    std::vector<double> kernel(size * size);


    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius) * size + j + radius;
            kernel[idx] = exp(-(i * i + j * j) / (sigma * sigma));
            norm += kernel[idx];
        }
    }

    for (int i = 0; i < size * size; i++)
        kernel[i] /= norm;

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            double res = 0;
            for (int i = -radius; i <= radius; i++) {
                for (int j = -radius; j <= radius; j++) {
                    int idx = (i + radius) * size + j + radius;

                    int x_ = clamp(x + j, rows - 1, 0);
                    int y_ = clamp(y + i, cols - 1, 0);

                    double value = matrix[x_ * cols + y_];

                    res += value * kernel[idx];
                }
            }
            res = clamp(res, 255, 0);
            result[x * cols + y] = res;
        }
    }
    return result;
}
std::vector<double> gauss_filter_parralel_thread(const std::vector<double>& matrix, int rows, int cols) {
    if (rows <= 0 || cols <= 0 || matrix.size() == 0) {
        throw - 1;
    }
    const int size = 3;
    const double sigma = 1.0;
    const int radius = 1;
    double norm = 0;

    std::vector<double> kernel(size * size);


    for (int i = -radius; i <= radius; i++) {
        for (int j = -radius; j <= radius; j++) {
            int idx = (i + radius) * size + j + radius;
            kernel[idx] = exp(-(i * i + j * j) / (sigma * sigma));
            norm += kernel[idx];
        }
    }

    for (int i = 0; i < size * size; i++)
        kernel[i] /= norm;

    const int number =
        std::thread::hardware_concurrency();
    std::thread* threads =
        new std::thread[number];

    const int delta = cols / number;
    int residue = cols % number;

    int begin, end = 0;
    std::vector<double> result(matrix.size());
    for (int k = 0; k < number; k++) {
        begin = end;
        end += delta;
        if (residue > 0) {
            end++;
            residue--;
        }
        threads[k] = std::thread(
            [&](int begin, int end) {
                for (int x = begin; x < end; x++) {
                    for (int y = 0; y < cols; y++) {
                        double res = 0;
                        for (int i = -radius; i <= radius; i++) {
                            for (int j = -radius; j <= radius; j++) {
                                int idx = (i + radius) * size + j + radius;

                                int x_ = clamp(x + j, rows - 1, 0);
                                int y_ = clamp(y + i, cols - 1, 0);

                                double value = matrix[x_ * cols + y_];

                                res += value * kernel[idx];
                            }
                        }
                        res = clamp(res, 255, 0);
                        result[x * cols + y] = res;
                    }
                }
            },
            begin, end);
    }

    for (int i = 0; i < number; ++i) {
        threads[i].join();
    }

    delete[] threads;
    return result;
}

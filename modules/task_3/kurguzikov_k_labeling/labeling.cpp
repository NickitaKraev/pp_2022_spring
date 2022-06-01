  //  Copyright 2022 Kurguzikov Kirill

#define NOMINMAX
#include <tbb/tbb.h>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <cmath>
#include "../../../modules/task_3/kurguzikov_k_labeling/labeling.h"


int check_for_par(std::vector<std::vector<int>> lab, int rows, int cols) {
    bool equality = true;
    for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        if (lab[i][j] != 0) {
            if (j != 0) {
                if (lab[i][j] != lab[i][j - 1]) {
                    if (lab[i][j - 1] != 0) {
                        equality = false;
                    }
                }
            }
            if (i != 0) {
                if (lab[i][j] != lab[i - 1][j]) {
                    if (lab[i - 1][j] != 0) {
                        equality = false;
                    }
                }
            }
        }
    }
    }
    if (equality) {
        std::vector<int> nums;
        for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (lab[i][j] != 0) {
                if (nums.empty()) {
                    nums.push_back(lab[i][j]);
                } else {
                    bool clicker = true;
                    for (size_t k = 0; k < nums.size(); k++) {
                        if (lab[i][j] == nums[k]) {
                            clicker = false;
                        }
                    }
                    if (clicker) {
                        nums.push_back(lab[i][j]);
                    }
                }
            }
        }
        }
        return nums.size();
    } else {
        return 0;
    }
}

int check_for_seq(std::vector<std::vector<int>> lab, int rows, int cols) {
    std::vector<int> nums;
    for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
        if (lab[i][j] != 0) {
            if (nums.empty()) {
                nums.push_back(lab[i][j]);
            } else {
                bool clicker = true;
                for (size_t k = 0; k < nums.size(); k++) {
                    if (lab[i][j] == nums[k]) {
                        clicker = false;
                    }
                }
                if (clicker) {
                    nums.push_back(lab[i][j]);
                }
            }
        }
    }
    }
    return nums.size();
}

std::vector<std::vector<int>> myrand(int rows, int cols, int bl_pix_quant) {
    std::vector<int> vec;
    std::vector<std::vector<int>> pic;
    pic.resize(rows);
    for (int i = 0; i < rows; i++) {
        pic[i].resize(cols);
    }
    std::vector<int> tmp;
    std::vector<int> num;
    for (int i = 0; i < rows * cols; i++) {
        tmp.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(tmp.begin(), tmp.end(), g);
    for (int i = 0; i < bl_pix_quant; i++) {
        num.push_back(tmp[i]);
    }
    for (int i = 0; i < rows * cols; i++) {
        int pix = 0;
        for (int j = 0; j < bl_pix_quant; j++) {
            if (i == num[j]) {
                pix = 1;
            }
        }
        if (pix == 0) {
            vec.push_back(0);
        } else {
            vec.push_back(1);
        }
    }
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            pic[i][j] = vec[k];
            k++;
        }
    }
    return pic;
}

std::vector<std::vector<int>> SeqLabeling(std::vector<std::vector<int>> arr,
int rows, int cols) {
    std::vector<std::vector<int>> lab;
    lab.resize(rows);
    for (int i = 0; i < rows; i++) {
        lab[i].resize(cols);
    }
    int label = 0;
    if (arr[0][0] == 1) {
        label = 1;
        if ((arr[1][0] == 1) && (arr[0][1] == 1)) {
            lab[0][0] = lab[1][0] = lab[0][1] = 1;
        } else if ((arr[1][0] == 1) || (arr[0][1] == 1)) {
            if (arr[1][0] != 1) {
                lab[0][0] = lab[0][1] = 1;
            } else {
                lab[0][0] = lab[1][0] = 1;
            }
        } else if ((arr[1][0] == 0) || (arr[0][1] == 0)) {
            lab[0][0] = 1;
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] != 0) {
                if (i == 0) {
                    if (j != 0) {
                        if (lab[i][j - 1] != 0) {
                            lab[i][j] = lab[i][j - 1];
                        } else {
                            label++;
                            lab[i][j] = label;
                        }
                    }
                } else if (j == 0) {
                    if (i != 0) {
                        if (lab[i - 1][j] != 0) {
                            lab[i][j] = lab[i - 1][j];
                        } else {
                            label++;
                            lab[i][j] = label;
                        }
                    }
                } else if ((lab[i][j - 1] == 0) && (lab[i - 1][j] == 0)) {
                    label++;
                    lab[i][j] = label;
                } else if ((lab[i][j - 1] != 0) ^ (lab[i - 1][j] != 0)) {
                    if (lab[i][j - 1] != 0) {
                        lab[i][j] = lab[i][j - 1];
                    } else {
                        lab[i][j] = lab[i - 1][j];
                    }
                } else if ((lab[i][j - 1] != 0) && (lab[i - 1][j] != 0)) {
                    if (lab[i][j - 1] == lab[i - 1][j]) {
                        lab[i][j] = lab[i][j - 1];
                    } else {
                        int minim = std::min(lab[i][j - 1], lab[i - 1][j]);
                        lab[i][j] = lab[i - 1][j] = lab[i][j - 1] = minim;
                    }
                }
            }
        }
    }
    bool rep = true;
    while (rep) {
        for (int i = rows - 1; i >= 0; i--) {
            for (int j = cols - 1; j >= 0; j--) {
                if (arr[i][j] != 0) {
                if ((i == 0) && (j != 0)) {
                if (lab[i][j] != lab[i][j - 1]) {
                if (lab[i][j - 1] != 0) {
                int minim = std::min(lab[i][j], lab[i][j - 1]);
                lab[i][j] = lab[i][j - 1] = minim;
                }
                }
                } else if ((i != 0) && (j == 0)) {
                if (lab[i][j] != lab[i - 1][j]) {
                if (lab[i - 1][j] != 0) {
                int minim = std::min(lab[i][j], lab[i - 1][j]);
                lab[i][j] = lab[i - 1][j] = minim;
                }
                }
                } else if ((i != 0) && (j != 0)) {
                if ((arr[i - 1][j] == 1) && (arr[i][j - 1] == 1)) {
                int min1 = std::min(lab[i][j - 1], lab[i - 1][j]);
                int min2 = std::min(min1, lab[i][j]);
                lab[i][j] = lab[i][j - 1] = lab[i - 1][j] = min2;
                } else if ((arr[i][j - 1] != 0) ^ (arr[i - 1][j] != 0)) {
                if (arr[i][j - 1] != 0) {
                int minim = std::min(lab[i][j - 1], lab[i][j]);
                lab[i][j - 1] = lab[i][j] = minim;
                } else if (arr[i - 1][j] != 0) {
                int minim = std::min(lab[i - 1][j], lab[i][j]);
                lab[i - 1][j] = lab[i][j] = minim;
                            }
                        }
                    }
                }
            }
        }
        rep = false;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (arr[i][j] != 0) {
                    if (j != 0) {
                        if (lab[i][j] != lab[i][j - 1]) {
                            if (lab[i][j - 1] != 0) {
                                rep = true;
                            }
                        }
                    }
                    if (i != 0) {
                        if (lab[i][j] != lab[i - 1][j]) {
                            if (lab[i - 1][j] != 0) {
                                rep = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return lab;
}

std::vector<std::vector<int>> ParLabeling(std::vector<std::vector<int>> arr,
int rows, int cols) {
    std::vector<std::vector<int>> lab;
    lab.resize(rows);
    for (int i = 0; i < rows; i++) {
        lab[i].resize(cols);
    }
    int label = 0;
    if (arr[0][0] == 1) {
        label = 1;
        if ((arr[1][0] == 1) && (arr[0][1] == 1)) {
            lab[0][0] = lab[1][0] = lab[0][1] = 1;
        } else if ((arr[1][0] == 1) ^ (arr[0][1] == 1)) {
            if (arr[1][0] != 1) {
                lab[0][0] = lab[0][1] = 1;
            } else {
                lab[0][0] = lab[1][0] = 1;
            }
        } else if ((arr[1][0] == 0) || (arr[0][1] == 0)) {
            lab[0][0] = 1;
        }
    }
    tbb::spin_mutex mtx;
    tbb::parallel_for(tbb::blocked_range<int>(0, rows, rows / 4),
    [&](const tbb::blocked_range<int>& Range) {
        for (int i = Range.begin(); i < Range.end(); i++) {
            for (int j = 0; j < cols; j++) {
                if ((i % 2 == 0) || (i == 0)) {
                    if (arr[i][j] != 0) {
                        if (i == 0) {
                            if (j != 0) {
                                if (lab[i][j - 1] != 0) {
                                    lab[i][j] = lab[i][j - 1];
                                } else {
                                    tbb::spin_mutex::scoped_lock lock;
                                    lock.acquire(mtx);
                                    label++;
                                    lab[i][j] = label;
                                    lock.release();
                                }
                            }
                        } else if (j == 0) {
                            if (i != 0) {
                                if (lab[i - 1][j] != 0) {
                                    lab[i][j] = lab[i - 1][j];
                                } else {
                                    tbb::spin_mutex::scoped_lock lock;
                                    lock.acquire(mtx);
                                    label++;
                                    lab[i][j] = label;
                                    lock.release();
                                }
                            }
                        } else if ((lab[i][j - 1] == 0) &&
                        (lab[i - 1][j] == 0)) {
                            tbb::spin_mutex::scoped_lock lock;
                            lock.acquire(mtx);
                            label++;
                            lab[i][j] = label;
                            lock.release();
                        } else if ((lab[i][j - 1] != 0) ^
                        (lab[i - 1][j] != 0)) {
                            if (lab[i][j - 1] != 0) {
                                lab[i][j] = lab[i][j - 1];
                            } else {
                                lab[i][j] = lab[i - 1][j];
                            }
                        } else if ((lab[i][j - 1] != 0) &&
                        (lab[i - 1][j] != 0)) {
                            if (lab[i][j - 1] == lab[i - 1][j]) {
                                lab[i][j] = lab[i][j - 1];
                            } else {
                                int minim = std::min(lab[i][j - 1],
                                lab[i - 1][j]);
                                lab[i][j] = lab[i - 1][j] =
                                lab[i][j - 1] = minim;
                            }
                        }
                    }
                }
            }
        }
    });
    tbb::parallel_for(tbb::blocked_range<int>(1, rows, (rows - 1) / 4),
    [&](const tbb::blocked_range<int>& Range) {
        for (int i = Range.begin(); i < Range.end(); i++) {
            for (int j = 0; j < cols; j++) {
                if (i % 2 != 0) {
                    if (arr[i][j] != 0) {
                        if (j == 0) {
                            if (lab[i - 1][j] != 0) {
                                lab[i][j] = lab[i - 1][j];
                            } else {
                                tbb::spin_mutex::scoped_lock lock;
                                lock.acquire(mtx);
                                label++;
                                lab[i][j] = label;
                                lock.release();
                            }
                        } else if ((lab[i][j - 1] == 0) &&
                        (lab[i - 1][j] == 0)) {
                            tbb::spin_mutex::scoped_lock lock;
                            lock.acquire(mtx);
                            label++;
                            lab[i][j] = label;
                            lock.release();
                        } else if ((lab[i][j - 1] != 0) ^
                        (lab[i - 1][j] != 0)) {
                            if (lab[i][j - 1] != 0) {
                                lab[i][j] = lab[i][j - 1];
                            } else {
                                lab[i][j] = lab[i - 1][j];
                            }
                        } else if ((lab[i][j - 1] != 0) &&
                        (lab[i - 1][j] != 0)) {
                            if (lab[i][j - 1] == lab[i - 1][j]) {
                                lab[i][j] = lab[i][j - 1];
                            } else {
                                int minim = std::min(lab[i][j - 1],
                                lab[i - 1][j]);
                                lab[i][j] = lab[i - 1][j] =
                                lab[i][j - 1] = minim;
                            }
                        }
                    }
                }
            }
        }
    });
    bool rep = true;
    while (rep) {
        tbb::parallel_for(tbb::blocked_range<int>(0, rows - 1, (rows - 1) / 4),
        [&](const tbb::blocked_range<int>& Range) {
            for (int i = Range.end(); i >= Range.begin(); i--) {
                for (int j = cols - 1; j >= 0; j--) {
                    if ((i % 2 == 0) || (i == 0)) {
                        if (arr[i][j] != 0) {
                            if ((i == 0) && (j != 0)) {
                                if (lab[i][j] != lab[i][j - 1]) {
                                    if (lab[i][j - 1] != 0) {
                                        int minim = std::min(lab[i][j],
                                        lab[i][j - 1]);
                                        lab[i][j] = lab[i][j - 1] = minim;
                                    }
                                }
                            } else if ((i != 0) && (j == 0)) {
                                if (lab[i][j] != lab[i - 1][j]) {
                                    if (lab[i - 1][j] != 0) {
                                        int minim = std::min(lab[i][j],
                                        lab[i - 1][j]);
                                        lab[i][j] = lab[i - 1][j] = minim;
                                    }
                                }
                            } else if ((i != 0) && (j != 0)) {
                                if ((arr[i - 1][j] == 1) &&
                                (arr[i][j - 1] == 1)) {
                                    int min1 = std::min(lab[i][j - 1],
                                    lab[i - 1][j]);
                                    int min2 = std::min(min1, lab[i][j]);
                                    lab[i][j] = lab[i][j - 1] =
                                    lab[i - 1][j] = min2;
                                } else if ((arr[i][j - 1] != 0) ^
                                (arr[i - 1][j] != 0)) {
                                    if (arr[i][j - 1] != 0) {
                                        int minim = std::min(lab[i][j - 1],
                                        lab[i][j]);
                                        lab[i][j - 1] = lab[i][j] = minim;
                                    } else if (arr[i - 1][j] != 0) {
                                        int minim = std::min(lab[i - 1][j],
                                        lab[i][j]);
                                        lab[i - 1][j] = lab[i][j] = minim;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        });
        tbb::parallel_for(tbb::blocked_range<int>(0, rows - 1, (rows - 1) / 4),
        [&](const tbb::blocked_range<int>& Range) {
            for (int i = Range.end(); i >= Range.begin(); i--) {
                for (int j = cols - 1; j >= 0; j--) {
                    if (i % 2 != 0) {
                        if (arr[i][j] != 0) {
                            if ((i == 0) && (j != 0)) {
                                if (lab[i][j] != lab[i][j - 1]) {
                                    if (lab[i][j - 1] != 0) {
                                        int minim = std::min(lab[i][j],
                                        lab[i][j - 1]);
                                        lab[i][j] = lab[i][j - 1] = minim;
                                    }
                                }
                            } else if ((i != 0) && (j == 0)) {
                                if (lab[i][j] != lab[i - 1][j]) {
                                    if (lab[i - 1][j] != 0) {
                                        int minim = std::min(lab[i][j],
                                        lab[i - 1][j]);
                                        lab[i][j] = lab[i - 1][j] = minim;
                                    }
                                }
                            } else if ((i != 0) && (j != 0)) {
                                if ((arr[i - 1][j] == 1) &&
                                (arr[i][j - 1] == 1)) {
                                    int min1 = std::min(lab[i][j - 1],
                                    lab[i - 1][j]);
                                    int min2 = std::min(min1, lab[i][j]);
                                    lab[i][j] = lab[i][j - 1] =
                                    lab[i - 1][j] = min2;
                                } else if ((arr[i][j - 1] != 0) ^
                                (arr[i - 1][j] != 0)) {
                                    if (arr[i][j - 1] != 0) {
                                        int minim = std::min(lab[i][j - 1],
                                        lab[i][j]);
                                        lab[i][j - 1] = lab[i][j] = minim;
                                    } else if (arr[i - 1][j] != 0) {
                                        int minim = std::min(lab[i - 1][j],
                                        lab[i][j]);
                                        lab[i - 1][j] = lab[i][j] = minim;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        });
        rep = false;
        tbb::parallel_for(tbb::blocked_range<int>(0, rows, rows / 4),
        [&](const tbb::blocked_range<int>& Range) {
            for (int i = Range.begin(); i < Range.end(); i++) {
                for (int j = 0; j < cols; j++) {
                    if (arr[i][j] != 0) {
                        if (j != 0) {
                            if (lab[i][j] != lab[i][j - 1]) {
                                if (lab[i][j - 1] != 0) {
                                    rep = true;
                                }
                            }
                        }
                        if (i != 0) {
                            if (lab[i][j] != lab[i - 1][j]) {
                                if (lab[i - 1][j] != 0) {
                                    rep = true;
                                }
                            }
                        }
                    }
                }
            }
        });
    }
    return lab;
}

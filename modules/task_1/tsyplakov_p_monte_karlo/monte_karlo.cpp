// Copyright 2022 Tsyplakov Pavel
#include "../../../modules/task_1/tsyplakov_p_monte_karlo/monte_karlo.h"
#include <functional>
#include <random>
#include <vector>

using std::exception;
using std::function;
using std::vector;

double getSequentialMonteKarlo(
    function<double(vector<double>)> const& integrableFunction,
    const vector<double>& upperLimit,
    const vector<double>& lowerLimit,
    const int amountOfPoint) {
    if (upperLimit.size() == 0 || lowerLimit.size() == 0 ||
        upperLimit.size() != lowerLimit.size()) {
        throw "Wrong limit!";
    }

    double result = 0.0;
    auto integrableDimensions = upperLimit.size();

    vector<std::uniform_real_distribution<double>> distributions(
        integrableDimensions);
    for (unsigned int counter = 0; counter < integrableDimensions; ++counter) {
        distributions[counter] = std::uniform_real_distribution<double>(
            lowerLimit[counter], upperLimit[counter]);
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    vector<double> randomPoints(integrableDimensions);
    for (int counter = 0; counter < amountOfPoint; ++counter) {
        for (unsigned int i = 0; i < integrableDimensions; ++i) {
            randomPoints[i] = distributions[i](gen);
        }

        result += integrableFunction(randomPoints);
    }

    double partialResult = 1.0;
    for (unsigned int counter = 0; counter < integrableDimensions; ++counter) {
        partialResult *= upperLimit[counter] - lowerLimit[counter];
    }

    result *= (partialResult / amountOfPoint);
    return result;
}

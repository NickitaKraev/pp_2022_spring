// Copyright 2022 Tsyplakov Pavel
#include "../../../modules/task_3/tsyplakov_p_monte_karlo/monte_karlo.h"
#include <tbb/tbb.h>
#include <functional>
#include <random>
#include <vector>

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

double getParallelMonteKarlo(
    std::function<double(std::vector<double>)> const& integrableFunction,
    const std::vector<double>& upperLimit,
    const std::vector<double>& lowerLimit,
    const int amountOfPoint) {
  if (upperLimit.size() == 0 || lowerLimit.size() == 0 ||
      upperLimit.size() != lowerLimit.size()) {
    throw "Wrong limit!";
  }

  double reductionResult = 0.0;
  auto integrableDimensions = upperLimit.size();

  vector<std::uniform_real_distribution<double>> distributions(
      integrableDimensions);
  for (unsigned int counter = 0; counter < integrableDimensions; ++counter) {
    distributions[counter] = std::uniform_real_distribution<double>(
        lowerLimit[counter], upperLimit[counter]);
  }

  std::random_device rd;
  std::mt19937 gen(rd());

  reductionResult = tbb::parallel_reduce(
      tbb::blocked_range<int>(0, amountOfPoint), 0.0,
      [&](tbb::blocked_range<int> r, double runningResult) {
        vector<double> randomPoints(integrableDimensions);

        for (int counter = r.begin(); counter < r.end(); ++counter) {
          for (unsigned int i = 0; i < integrableDimensions; ++i) {
            randomPoints[i] = distributions[i](gen);
          }
          runningResult += integrableFunction(randomPoints);
        }

        return runningResult;
      },
      std::plus<double>());

  double partialResult = 1.0;
  for (unsigned int counter = 0; counter < integrableDimensions; ++counter) {
    partialResult *= upperLimit[counter] - lowerLimit[counter];
  }

  reductionResult *= (partialResult / amountOfPoint);
  return reductionResult;
}

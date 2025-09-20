#ifdef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include <vector>
#include <map>
#include <random>
#include <numeric>
#include <stdexcept>

class RandomNumberGenerator{
public:
RandomNumberGenerator(const std::vector<int>& numbers, const std::vector<int>& frequencies);
int operator()();

int getTotalFrequency() const { return totalFrequency; }

private:
std::vector<int> numbers;
std::vector<int> cumulativeFrequencies;
int totalFrequency = 0;

std::mt19937 rng;
};

#endif// RANDOM_NUMBER_GENERATOR_H

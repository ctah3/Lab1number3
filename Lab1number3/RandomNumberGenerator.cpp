#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator(const std::vector<int>& numbers, const std::vector<int>& frequencies):

	: numbers(numbers) {
	if (numbers.size() != frequencies.size()) {
		throw std::invalid_argument("Vectors of numbers and frequencies must have the same size.");
	}
	if (numbers.empty()) {
		throw std::invalid_argument("Input vectors cannot be empty.");
	}

	cumulativeFrequencies.reserve(frequencies.size());
	int currentCumulativeFrequency = 0;

	for (size_t i = 0; i < frequencies.size(); ++i) {
		if (frequencies[i] <0) {
			throw std::invalid_argument("Frequencies cannot be negative.");
		}
		currentCumulativeFrequency += frequencies[i];
		cumulativeFrequencies.push_back(currentCumulativeFrequency);
	}

	totalFrequency = currentCumulativeFrequency;

	if (totalFrequency == 0) {
		throw std::invalid_argument("Sum of frequencies cannot be zero.");
	}

	std::random_device rd;
	rng.seed(rd());
}

int RandomNumberGenerator::operator()() {
	
	std::uniform_int_distribution<int> dist(1, totalFrequency);
	int randomValue = dist(rng);

	for (size_t i = 0; i < cumulativeFrequencies.size(); ++i) {
		if (randomValue <= cumulativeFrequencies[i]) {
			return numbers[i];
		}
	}
	throw std::logic_error("Internal logic error: Random value could not be mapped to a number.");
}

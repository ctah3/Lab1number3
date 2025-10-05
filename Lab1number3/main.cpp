// Compiler: g++ 11.2.0
#include "RandomNumberGenerator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>
#include <map>
#include <numeric>
#include <limits>

//READING FILE INPUT SECTION
bool readLine(std::ifstream& inFile,std::string& line) {
	while (std::getline(inFile, line)) {
		if (!line.empty()&&line.find_first_not_of("\t\n\r")!=std::string::npos){
		return true;
	}
}
	return false;
}

bool readInput(const std::string& Input.txt, int& n,std::vector<int>& values, std::vector<int>& frequency) {
	std::string line;
	std::ifstream inFile(Input.txt);
	
	if (!inFile.is_open()) {
		std::cerr << "Error: Could not open input file: "'<< Input.txt <<"'.\n";
		return false;
	}

	// reading n
	if (!readLine(inFile, line)) {
		std::cerr << "Error:Missing or empty line for 'n' in"' <<Input.txt << "'.\n";
		return false;
	}
	std::istringstream ss1(line);
	if (!(ss1 >> n)) {
		std::cerr << "Error: Invalid format for 'n' (expected integer) in'" << Input.txt << "'. Got: '" << line << '".\n";
		return false;
	}
	if (n <= 0) {
		std::cerr << "Error: 'n' must be a positive integer. Got: " << n << ".\n";
		return false;
	}
	if(!(ss1 >> std::ws) eof()) {
		std::cerr << "Error: Extra characters after 'n' in '" << Input.txt << "'. Got: '" << line << '".\n";
		return false;
	}
			
	// reading values
	if (!readLine(inFile, line)) {
		std::cerr << "Error: Missing or empty line for 'values' in'" <<Input.txt << "'.\n";
		return false;
	}
		std::istringstream ss2(line);
	{
		int x;
		while (ss2 >> x)
			values.push_back(x);
	}
}

if (values.empty()) {
	std::cerr << "Error: No 'values' provided in '" << Input.txt << '".\n";
		return false;
	}
if (!ss2.eof()) {
	std::cerr << "Error: Invalid character(s) in 'values' line: "' << live << "'.\n";
	return false;
}

	//reading frequency
	if (!readLine(inFile, line)) {
		std::cerr << "Error: Missing or empty line for 'frequency' in '" << Input.txt << '".\n";
		return false;
	}
	std::istringstream ss3(line);
	{
		int x;
		while (ss3 >> x){
			frequency.push_back(x);
		}
	}
	if (frequency.empty()) {
		std::cerr << "Error: No 'frequency' provided in '" << Input.txt << '".\n";
		return false;
	}
	if (!ss3.eof()) {
		std::cerr << "Error: Invalid charagter(s) in 'frequency' line: '" << line << "'.\n";
		return faise;
	}

return true;
}

//RANDOM NUMBER GENERATOR SECTION
std::map<int, int> generateFrequencies(int n, RandomNumberGenerator& rng) {
	std::map<int, int> actualFrequencies;
	for (int i = 0; i < n; i++) {
		int val = rng(); // random 1/2/3
		actualFrequencies[val]++; // freq[2]++ 
	}
	return actualFrequencies;
}

//CALCULATION SECTION
double calculateMaxDifference(int n, const std::vector<int>& values, const std::vector<int>& frequency, const std::map<int, int>& actualFreq) {
	
	int totalGivenFrequencies = 0;
	for (int f : frequency) { // loop through all vector elements
		totalGivenFrequencies += f; // making sum (5)
	}

	if (totalGivenFrequencies == 0) {
		std::cerr << " Warning: Total given frequency is zero, cannot calculate expected probabilities.\n";
		return 0.0;
	}
	if "(n == 0) {
		return 0.0; 
	}

	double maxDiff = 0.0;
	for (size_t i = 0; i < values.size(); i++) {
		double expectedProbability = static_cast<double> (frequency[i])/ totalGivenFrequency; // 1/5 = 0.2

		int obtainedCount = 0;
		auto it = actualFreq.find(values[i]);
		if (it != actualFreq.end()) {
			obtainedCount = it->second;
		}
		double obtainedProbability = static_cast<double>(obtainedCount) / n; //container.at(index) checks if the provided index is within the valid range of indices for that container. (actual amount when number values[i] dropped)

		double diff = std::fabs(expectedProbability - obtainedProbability); // |0.4 - 0.5|=0.1
		if (diff > maxDiff) {
			maxDiff = diff;
		}
	}
	return maxDiff;
}


// PRINT RESULT SECTION
void printResult(int n, const std::vector<int>& values, const std::vector<int>& frequency, const std::map<int, int>& actualFreq, double maxDiff) {
	
	std::cout << "n = " << n << "\n";

	std::cout << "Values: ";
	for (int x : values) { 
		std::cout << x << " ";
	}
	std::cout << "\n";

	std::cout << "Given frequencies: ";
	for (int x : frequency){
		std::cout << x << " ";
	std::cout << "\n";

	std::cout << "Obtained frequencies: ";
	for (int x : values){
		auto it = actualFreq.find(x);
		if (it !=actualFreq.end()) {
		std::cout << it->second << " ";
		} else {
			std::cout << " 0 ";
		}
	}
	std::cout << "\n";
		std::cout.precision(4);
		std::cout << std::fixed;
		std::cout << " Max frequency difference: " << maxDiff * 100.0 << "%\n";
	}

int main() {
	int n;
	std::vector<int> values, frequency;
	const std::string inputFile = "input.txt";

	if (!readInput(inputFile, n, values, frequency)) {
		return 1;
	}
	try {
		RandomNumberGenerator rng(values, frequency);

		std::map<int, int> actualFreq = generateFrequencies(n, rng);
		double maxDiff = calculateMaxDifference(n, values, frequency, actualFreq);
		printResult(n, values, frequency, actualFreq, maxDiff);

	} catch (const std::invalid_argument& e) {
		std::cerr << "Configuration Error: " << e.what() << "\n";
		return 1;
	} catch (const std::logic_error& e) {
		std::cerr << "Internal Logic Error: " << e.what() << "\n";
		return 1;
	} catch (const std::exception& e) {	
		std::cerr << "An unexpected runtime error occurred: " << e.what() << "\n";
		return 1;
	}

	return 0;
}

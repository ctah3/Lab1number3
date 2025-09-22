// Compiler: g++ 11.2.0
#include "RandomNumberGenerator.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

//READING FILE INPUT SECTION
bool readLine(ifstream& inFile, string& line) {
	while (getline(inFile, line)) {
		if (!line.empty())
		return true;
	}
	return false;
}
bool readInput(const string& File, int& n, vector<int>& values, vector<int>& frequency) {
	string line;
	ifstream inFile(File);
	if (!inFile.is_open()) {
		cerr << "Error with file opening\n";
		return false;

	}

	// reading n
	if (!readLine(inFile, line))
		cerr << "Missing n";
	istringstream ss1(line);
	if (!(ss1 >> n) || n <= 0 || !(ss1 >> ws).eof()) {
	cerr << "Invalid n";
	return false;
}
	// reading values
	if (!readLine(inFile, line))
		cerr << "Missing values";
	istringstream ss2(line);
	{
		int x;
		while (ss2 >> x)values.push_back(x);
	}
	if (values.empty()) {
		cerr << "No values";
		return false;
	}
	//reading frequency
	if (!readLine(inFile, line))
		cerr << "Missing frequency";
	istringstream ss3(line);
	{
		int x;
		while (ss3 >> x)frequency.push_back(x);
	}
	if (frequency.empty()) {
		cerr << "No frequency";
		return false;
	}

	return true;
}

//RANDOM NUMBER GENERATOR SECTION
map<int, int> generateFrequencies(int n, RandomNumberGenerator& rng) {
	map<int, int> freq;
	for (int i = 0; i < n; i++) {
		int val = rng(); // random 1/2/3
		freq[val]++; // freq[2]++ 
	}
	return freq;
}

//CALCULATION SECTION
double calculateMaxDifference(int n, const vector<int>& values, const vector<int>& frequency, const map<int, int>& actualFreq) {
	
	int totalFreq = 0;
	for (int f : frequency){ // loop through all vector elements
		totalFreq += f; // making sum (5)
}

	double maxDiff = 0.0;
	for (size_t i = 0; i < values.size(); i++) {
		double expected = (double)frequency[i] / totalFreq; // 1/5 = 0.2
		double obtained = (double)actualFreq.at(values[i]) / n; //container.at(index) checks if the provided index is within the valid range of indices for that container. (actual amount when number values[i] dropped)
		double diff = fabs(expected - obtained); // |0.4 - 0.5|=0.1
		if (diff > maxDiff) {
			maxDiff = diff; 
		}
	}
	return maxDiff;
}

// PRINT RESULT SECTION
void printResult(int n, const vector<int>& values, const vector<int>& frequency, const map<int, int>& actualFreq, double maxDiff) {
	
	cout << "n = " << n << endl;

	cout << "Values: ";
	for (auto x : values) cout << x << " ";
	cout << endl;

	cout << "Given frequencies: ";
	for (auto x : frequency) cout << x << " ";
	cout << endl;

	cout << "Obtained frequencies: ";
	for (auto x : values) cout << actualFreq.at(x) << " ";
	cout << endl;

	cout << "Max frequency difference: " << maxDiff * 100 << "%";
}

int main() {
	int n;
	vector<int> values, frequency;

	if (!readInput("input.txt", n, values, frequency)) {
		cerr<<"Error: Can't get information";
	}

	RandomNumberGenerator rng(values, frequency);
	auto actualFreq = generateFrequencies(n, rng);
	double maxDiff = calculateMaxDifference(n, values, frequency, actualFreq);
	printResult(n, values, frequency, actualFreq, maxDiff);

	return 0;
}

// Compiler: g++ 11.2.0
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <sstream>

using namespace std;

//READING FILE INPUT SECTION
bool readLine(ifstream& inFile, string& outFile) {
	string line;
	while (getline(inFile, line)) {
		if (line.empty()) continue;
		outFile = line;
		return true;
	}
	return false;
}
void readInput(const string& File, const string& Fileout) {
	string line;
	
	ifstream inFile(File);
	ofstream outFile(Fileout);

	if (!inFile.is_open() || !outFile.is_open()) {
		cerr << "error with file opening\n";
		return;

	}
	// reading n
	if (!readLine(inFile, line))
		cerr << "Missing n";
	istringstream ss1(line);//sstream
	int n;
	if (!(ss1 >> n) || n <= 0 || !(ss1 >> ws).eof()) // ws - skipping space and tab; .eof - checking for the end of stream and "true" if nothing else is still in the line
		cerr << "Invalid n";

	// reading values
	if (!readLine(inFile, line))
		cerr << "Missing values";
	istringstream ss2(line);
	vector <int> values;
	{
		int x;
		while (ss2 >> x)values.push_back(x);
	}
	if (values.empty())
		cerr << "no values";

	//reading frequency
	if (!readLine(inFile, line))
		cerr << "Missing frequency";
	istringstream ss3(line);
	vector <int> frequency;
	{
		int x;
		while (ss3 >> x)frequency.push_back(x);
	}
	if (frequency.empty())
		cerr << "no frequency";

	cout << "n = " << n << "\n";
	cout << "values: ";
	for (auto x : values) cout << x << " ";
	cout << "\n";
	cout << "frequency: ";
	for (auto x : frequency) cout << x << " ";
	cout << "\n";

// Change cerr on another error types; | stdexcept
}


// FORMULS SECTION

// RANDOM GENERATOR DECTION

int main() {
	readInput("File.txt", "Fileout.txt");

}

#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <sstream>

using namespace std;

void openFile(const string& File, const string& Fileout) {
	ifstream inFile(File);
	ofstream outFile(Fileout);

	if (!inFile.is_open() || !outFile.is_open()) {
		cerr << "error with file opening\n";
		return;

	}
}


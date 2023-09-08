#pragma once

#include <fstream>

#include "Signal_Modulator.h"

using namespace std;

class IOProvider {
public:

	void Save(float* mass, int length, string path) {
		ofstream bitfile(path, ios::binary | ios::out); // save no noise 
		bitfile.write((char*)mass, (length) * sizeof(float));
		bitfile.close();
	}

};


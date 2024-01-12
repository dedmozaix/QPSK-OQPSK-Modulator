#pragma once

#include <fstream>

using namespace std;

class IOProvider
{
public:

	void Save(float* mass, int length, bool noise)
	{
		if (noise)
		{
			ofstream bitfile("C://liquid_test/liquid_test/bin/Modulated.bin", ios::binary | ios::out); // save no noise 
			bitfile.write((char*)mass, (length) * sizeof(float));
			bitfile.close();
		}
		else
		{
			ofstream bitfile("C://liquid_test/liquid_test/bin/Modulated_noNoise.bin", ios::binary | ios::out); // save no noise 
			bitfile.write((char*)mass, (length) * sizeof(float));
			bitfile.close();
		}


	}

};


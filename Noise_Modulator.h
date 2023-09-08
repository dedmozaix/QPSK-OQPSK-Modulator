#pragma once
#include<iterator>
#include <random>
#include <time.h>
#include <iostream>
#include <map>
#include <iostream>
#include<fstream>

#include <math.h>
#include <cmath>

#include <chrono>

#include "Math_Definer.h"
#include "IOProvider.h"

using namespace std;
using namespace chrono;

class NoiseModulator {

private:
	float _Signal_amp_squad;

public:

	NoiseModulator() {
		_Signal_amp_squad = 0;
	}

	void SetSignalPower(float data) {
		_Signal_amp_squad = data;
	}

	float GetValue() {
		return _Signal_amp_squad;
	}

	void Increase_Signal_amp_squad(float val) {
		_Signal_amp_squad += val;
	}	

	void MakeGaussNoiseMain(float* QPSK, int length, int DBlevel, int k) {

		//unsigned seed = system_clock::now().time_since_epoch().count();
		//default_random_engine generator(seed);

		default_random_engine generator;


		float NoisePower = ConvertDBtoTimes(DBlevel);

		float SignalPower = GetSignalPower(length / 2, _Signal_amp_squad);
		SignalPower = 1;


		printf("noise: %f %f formula = %f \n", SignalPower, NoisePower, sqrt(SignalPower / (NoisePower * k))/2 ); 
		normal_distribution<float> dist(0.0, sqrt(SignalPower / (NoisePower * k))/2 ); 
		
		for (int i = 0; i < length; i+=2) {

			QPSK[i] += dist(generator);
			QPSK[i + 1] += dist(generator);
		}
		

		IOProvider provider;
		provider.Save(QPSK, length, path_Mod_Noise);

	}

};
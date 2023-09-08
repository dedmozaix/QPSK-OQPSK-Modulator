#pragma once

#include <cmath>
#include <iostream>

using namespace std;

#define _USE_MATH_DEFINES
const float PSK_CONST = 0.7071707;
const float PI = 3.1415926535;

const char* path_Mod_Noise = "C://liquid_test/liquid_test/bin/Modulated.bin";
const char* path_Mod_noNoise = "C://liquid_test/liquid_test/bin/Modulated_noNoise.bin";


	float Calculate_MomentPhase(double phase) {
		//cout << "sin = " << sin(phase) << "cos = " << cos(phase) << endl;
		return atan(sin(phase) / cos(phase));
	}

	float Calculate_MomentFreq(double phase) {
		return atan2(sin(phase), cos(phase));
	}

	float QuantValue(double val) {
		if (val >= 0)
			return PSK_CONST;
		return -PSK_CONST;
	}

	float PskQuantValue(double val) {
		if (val == 1)
			return PSK_CONST;
		return -PSK_CONST;
	}

	float ConvertDBtoTimes(float DBlevel) {
		return pow(10, (DBlevel / 10)); //1.26 * DBlevel; 
	}

	float GetSignalPower(int length, float amplitude) {
		cout << "amplitude = " << amplitude << endl;
		return amplitude / length;
	}

	float GetDisp(float power) {
		return 10 * log(power);
	}



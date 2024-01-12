#pragma once

//#include "Math_Definer.h"
#include "../src/IOProvider.h"

#include<iterator>
#include <random>
#include <time.h>
#include <iostream>
#include <chrono>

class Noise_Modulator 
{
public:
	void setSignalPower(float power);
	void makeGaussNoiseMain(float* QPSK, int length, int DBlevel, int k);

private:
	float _signal_power;
};


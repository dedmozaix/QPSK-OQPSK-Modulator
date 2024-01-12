#pragma once

#include "../src/Noise_Modulator.h"

#include<iterator>
#include <random>
#include <time.h>
#include <iostream>
#include <chrono>

void Noise_Modulator::setSignalPower(float power)
{
	_signal_power = power;
}


void Noise_Modulator::makeGaussNoiseMain(float* QPSK, int length, int DBlevel, int k)
{
	//unsigned seed = system_clock::now().time_since_epoch().count();
	//default_random_engine generator(seed);

	std::default_random_engine generator;

	float NoisePower = pow(10, (DBlevel / 10)); //1.26 * DBlevel; 

	float SignalPower = (length / 2) / length;
	//SignalPower = 1;
	this->setSignalPower(SignalPower);


	printf("noise: %f %f formula = %f \n", SignalPower, NoisePower, sqrt(SignalPower / (NoisePower * k)));
	std::normal_distribution<float> dist(0.0, sqrt(SignalPower / (NoisePower * k)));

	for (int i = 0; i < length; i += 2)
	{

		QPSK[i] += dist(generator);
		QPSK[i + 1] += dist(generator);

	}

	IOProvider provider;
	provider.Save(QPSK, length, true);

}
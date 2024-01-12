#pragma once

#include "IOProvider.h"
//#include "Math_Definer.h"
#include "Doppler_Modulator.h"

#include<iterator>
#include <iostream>
#include<fstream>
#include <time.h>

class QPSK_Modulator
{

public:

	QPSK_Modulator(long int length, int k, int Fd, int freq_start, int speed_f)
	{ //Doppler doppler
		_length = length;
		_k = k;
		_Fd = Fd;
		_freq_start = freq_start;
		_freq_speed_inc = speed_f;

		_signal_power = 0;
	}

	QPSK_Modulator()
	{ //Doppler doppler
		_length = 1000;
		_k = 4;
		_Fd = 500;
		_freq_start = 100;
		_freq_speed_inc = 10;

		_signal_power = 0;
	}

	~QPSK_Modulator()
	{
		delete[] _QPSK;
		delete[] _QPSK_noNoise;
	}

	void setSignal(float* mass);
	void setSignalNoNoise(float* mass);

	float* getSignal();
	float* getSignalNoNoise();
	float getSignalPower();
	int getLength();
	int getCountsPerSymbol();

	float getPhaseLinearAcceleration(int val);
	float getIncreasePhaseLinearAcceleration(int val);
	void modulateSinusoidally();
	void modulateArtifically();

	void makeShift(float* mass_for_shift, bool noise);

private:

	long int _length;
	int _k;
	int _Fd;
	int _freq_start;
	int _freq_speed_inc;
	float _signal_power;

	float* _QPSK;				//сигнал
	float* _QPSK_noNoise;		//сигнал для сравнения и оценки правильности демодулятора


};



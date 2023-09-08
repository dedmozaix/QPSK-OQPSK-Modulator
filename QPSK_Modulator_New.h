#pragma once

#include<iterator>
#include <iostream>
#include<fstream>

#include <math.h>
#include <cmath>
#include <time.h>

#include "Signal_Modulator.h"
#include "IOProvider.h"
#include "Math_Definer.h"
#include "Doppler_Modulator_New.h"

using namespace std;


class QPSK_Modulator_New : Signal_Modulator {
private:

	long int _length;
	int _k;
	int _Fd;
	int _freq_start;
	int _freq_speed_inc;

	float _signal_power;

	float* _QPSK;				//сигнал
	float* _QPSK_noNoise;		//сигнал для сравнения и оценки правильности демодулятора


public:

	QPSK_Modulator_New(long int length, int k, int Fd, int freq_start, int speed_f) { //Doppler doppler
		_length = length;
		_k = k;
		_Fd = Fd;
		_freq_start = freq_start;
		_freq_speed_inc = speed_f;

		_signal_power = 0;
	}

	QPSK_Modulator_New() { //Doppler doppler
		_length = 1000;
		_k = 4;
		_Fd = 500;
		_freq_start = 100;
		_freq_speed_inc = 10;

		_signal_power = 0;
	}

	~QPSK_Modulator_New() {
		delete[] _QPSK;
		delete[] _QPSK_noNoise;
	}

	float* GetSignal() {
		return _QPSK;
	}

	float* GetSignal_noNoise() {
		return _QPSK_noNoise;
	}

	float GetSignalPower() {
		return _signal_power;
	}

	int GetLength() {
		return _length * 2 * _k;
	}

	int GetCounts_PerSymbol() {
		return _k;
	}

	float GetPhaseLinearAcceleration(int val) {

		float t = val / (float)_Fd;														//t = отсчет / сек  * отсет = сек 
		float inc_freq = _freq_speed_inc / (float)_Fd * val;							//inc_freq = Гц/cек * сек/отсчет * отсчет = Гц

		float phase = 2 * PI  * (_freq_start + inc_freq) * t; 

		return phase;
	}

	void Modulate_Sinusoidally() override {
		_QPSK = new float[_length];							//cигнал
		_QPSK_noNoise = new float[_length];					//сигнал для сравнения для демодулятора

		Doppler_New doppler_obj(0.2, 0.0, _freq_start);

		float tmp_QuantValueR = -1, tmp_QuantValueI = -1;
		double phase = 0, g_phase = 0;

		float tmp_cos = 0.0, tmp_sin = 0.0;

		for (int i = 0; i < _length; i += 2) {

			if (i % (_k * 2) == 0) {
				phase = GetPhaseLinearAcceleration(i);		//получаем фазу синусойды

				tmp_cos = QuantValue(cos(phase));
				tmp_sin = QuantValue(sin(phase));
			}

			float moment_phase = Calculate_MomentPhase(phase);	//высчитываем моментальную фазу
			float moment_freq = Calculate_MomentFreq(phase);	//высчитываем моментальную частоту	

			_signal_power += 2 * pow(0.707107, 2);				//увеличиваем мощность сигнала

			tmp_QuantValueR = tmp_cos;
			tmp_QuantValueI = tmp_sin;

			_QPSK[i] = tmp_cos;
			_QPSK[i + 1] = tmp_sin;	// doppler_obj.Make_Doppler_Movement_MoveI(tmp_cos, tmp_sin, moment_phase);

			_QPSK_noNoise[i] = tmp_QuantValueR;
			_QPSK_noNoise[i + 1] = tmp_QuantValueI;


			//cout << endl << endl;
		}
		

		IOProvider provider;
		provider.Save(_QPSK, _length, path_Mod_Noise);
		provider.Save(_QPSK_noNoise, _length, path_Mod_noNoise);

		//return _QPSK;
	}

	void Modulate_Artifically() override {
		_QPSK = new float[_length];				//сигнал
		_QPSK_noNoise = new float[_length];		//сигнал для сверки для демодулятора

		Doppler_New doppler_obj(0.2, 0.0, _freq_start);

		srand(time(0));

		float tmp_R = 0, tmp_I = 0;

		for (int i = 0; i < _length; i += 2) {

			if (i % (_k * 2) == 0) {								//формируем случайно квадратуры сигнала
				tmp_R = PskQuantValue(rand() % 2);
				tmp_I = PskQuantValue(rand() % 2);
			}

			float moment_phase = atan(sin(tmp_I) / cos(tmp_R));		//подсчет моментальной фазы
			_signal_power += 2 * pow(0.707107, 2);					//увеличиваем мощность сигнала


			doppler_obj.Make_Doppler_Movement_MoveI(tmp_R, tmp_I, moment_phase);		//добавляем сдвиг допплера

			_QPSK[i] = tmp_R;
			_QPSK[i + 1] = tmp_I;

			_QPSK_noNoise[i] = tmp_R;
			_QPSK_noNoise[i + 1] = tmp_I;
		}

		IOProvider provider;
		provider.Save(_QPSK, _length, path_Mod_Noise);
		provider.Save(_QPSK_noNoise, _length, path_Mod_noNoise);
	}


	template <typename T>
	void Make_Shift(T* mass_for_shift) {

		float* _OQPSK_shifted = new float[_length + _k];		//создаем увеоиченный на k массив

		for (int i = 0; i < _length + _k; i += 2)
		{
			if (i < _k) {
				_OQPSK_shifted[i] = PSK_CONST;					//добавляем фиктивное значение с начала при сдвиге
				_OQPSK_shifted[i + 1] = mass_for_shift[i + 1];


			}
			else if (i >= _length) {
				_OQPSK_shifted[i] = mass_for_shift[i - _k];
				_OQPSK_shifted[i + 1] = PSK_CONST;				//добавляем фиктивное значение в конце при сдвиге
			}
			else {
				_OQPSK_shifted[i] = mass_for_shift[i - _k];
				_OQPSK_shifted[i + 1] = mass_for_shift[i + 1];
			}

		}

		IOProvider provider;
		provider.Save(_OQPSK_shifted, _length + _k, path_Mod_Noise);
	}


};



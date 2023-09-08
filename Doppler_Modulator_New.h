#pragma once


#pragma once
#include <iostream>
#include<math.h>
#include <cmath>

using namespace std;

class Doppler_New {
private:
	float _DopplerConstShift;
	float _prev_phase;
	float _prev_freq;

public:

	Doppler_New(float DopplerConstShift, float prev_phase, float prev_freq) {
		_DopplerConstShift = DopplerConstShift;
		_prev_phase = prev_phase;
		_prev_freq = prev_freq;
	}

	Doppler_New() {
		_DopplerConstShift = 0.2;
		_prev_phase = -1;
		_prev_freq = -1;
	}

	float Get__Prev_Moment_Phase() {
		return _prev_phase;
	}

	void Make_Doppler_Movement_MoveRI(float& real, float& imag, float current_phase) {

		float tmp = real, delta_phase = _prev_phase - current_phase;

		real = tmp * cos(delta_phase) - imag * sin(delta_phase);
		imag = tmp * sin(delta_phase) + imag * cos(delta_phase);

		_prev_phase = current_phase;

	}

	float Make_Doppler_Movement_MoveI(float real, float imag, float current_phase) {

		float delta_phase = _prev_phase - current_phase;
		imag = real * sin(delta_phase) + imag * cos(delta_phase);

		_prev_phase = current_phase;
		return imag;

	}

	void Make_Doppler_Movement_onFreq(float& real, float& imag, float current_freq) {

		float delta_phase = _prev_phase - current_freq;
		imag = real * sin(current_freq) + imag * cos(current_freq);

		_prev_phase = current_freq;

	}



};

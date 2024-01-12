#pragma once

#include<math.h>
#include <cmath>

class Doppler {

public:

	Doppler(float dopplerConstShift, float prev_phase, float prev_freq) {
		_dopplerConstShift = dopplerConstShift;
		_prev_phase = prev_phase;
		_prev_freq = prev_freq;
	}

	Doppler() {
		_dopplerConstShift = 0.2;
		_prev_phase = -1;
		_prev_freq = -1;
	}

	float getPrevMomentPhase();
	void makeDopplerMovementMoveRI(float& real, float& imag, float current_phase);
	float makeDopplerMovementMoveI(float real, float imag, float current_phase, float speed);
	float makeDopplerMovementOnDelta(float real, float imag, float delta_phase);

private:
	float _dopplerConstShift;
	float _prev_phase;
	float _prev_freq;

};

#include "../src/Doppler_Modulator.h"

float Doppler::getPrevMomentPhase() {
	return _prev_phase;
}

void Doppler::makeDopplerMovementMoveRI(float& real, float& imag, float current_phase) {

	float tmp = real, delta_phase = _prev_phase - current_phase;

	real = tmp * cos(delta_phase) - imag * sin(delta_phase);
	imag = tmp * sin(delta_phase) + imag * cos(delta_phase);

	_prev_phase = current_phase;

}

float Doppler::makeDopplerMovementMoveI(float real, float imag, float current_phase, float speed) {

	float delta_phase = (_prev_phase - current_phase) * speed / 10;
	imag = real * sin(delta_phase) + imag * cos(delta_phase);

	_prev_phase = current_phase;
	return imag;

}

float Doppler::makeDopplerMovementOnDelta(float real, float imag, float delta_phase) {

	imag = real * sin(delta_phase) + imag * cos(delta_phase);
	return imag;

}
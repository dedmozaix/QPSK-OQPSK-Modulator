#include "../src/QPSK_Modulator.h"

float quantValue(double val)
{
	if (val >= 0)
		return 0.7071707;
	return -0.7071707;
}

float quantValuePsk(double val)
{
	if (val == 1)
		return 0.7071707;
	return -0.7071707;
}

float* QPSK_Modulator::getSignal()
{
	return _QPSK;
}

void QPSK_Modulator::setSignal(float* mass)
{
	_QPSK = mass;
}

float* QPSK_Modulator::getSignalNoNoise()
{
	return _QPSK_noNoise;
}

void QPSK_Modulator::setSignalNoNoise(float* mass)
{
	_QPSK_noNoise = mass;
}

float QPSK_Modulator::getSignalPower()
{
	return _signal_power;
}

int QPSK_Modulator::getLength()
{
	return _length * 2 * _k;
}

int QPSK_Modulator::getCountsPerSymbol()
{
	return _k;
}

float QPSK_Modulator::getPhaseLinearAcceleration(int val)
{

	float t = val / (float)_Fd;														//t = отсчет / сек  * отсет = сек 
	float inc_freq = _freq_speed_inc / (float)_Fd * val;							//inc_freq = √ц/cек * сек/отсчет * отсчет = √ц

	float phase = 2 * 3.1415926535 * (_freq_start + inc_freq) * t;

	return phase;
}

float QPSK_Modulator::getIncreasePhaseLinearAcceleration(int val)
{
	float t = val / (float)_Fd;														//t = отсчет / сек  * отсет = сек 
	float inc_freq = _freq_speed_inc / (float)_Fd * val;							//inc_freq = √ц/cек * сек/отсчет * отсчет = √ц

	return inc_freq;
}

void QPSK_Modulator::modulateSinusoidally()
{
	_QPSK = new float[_length];							//cигнал
	_QPSK_noNoise = new float[_length];					//сигнал дл€ сравнени€ дл€ демодул€тора

	Doppler doppler_obj(0.2, 0.0, _freq_start);

	float tmp_QuantValueR = -1, tmp_QuantValueI = -1;
	double phase = 0, g_phase = 0;

	float tmp_cos = 0.0, tmp_sin = 0.0;

	for (int i = 0; i < _length; i += 2)
	{

		if (i % (_k * 2) == 0)
		{
			phase = getPhaseLinearAcceleration(i);		//получаем фазу синусойды

			tmp_cos = quantValue(cos(phase));
			tmp_sin = quantValue(sin(phase));
		}

		float moment_phase = atan(sin(phase) / cos(phase));	//высчитываем моментальную фазу
		float moment_freq = atan2(sin(phase), cos(phase));	//высчитываем моментальную частоту	

		_signal_power += 2 * pow(0.707107, 2);				//увеличиваем мощность сигнала

		tmp_QuantValueR = tmp_cos;
		tmp_QuantValueI = tmp_sin;

		_QPSK[i] = tmp_cos;
		_QPSK[i + 1] = tmp_sin;
		// doppler_obj.Make_Doppler_Movement_MoveI(tmp_cos, tmp_sin, moment_phase);

		_QPSK_noNoise[i] = tmp_QuantValueR;
		_QPSK_noNoise[i + 1] = tmp_QuantValueI;


	}


	IOProvider provider;
	provider.Save(_QPSK, _length, true);
	provider.Save(_QPSK_noNoise, _length, false);

}

void QPSK_Modulator::modulateArtifically()
{
	_QPSK = new float[_length];				//сигнал
	_QPSK_noNoise = new float[_length];		//сигнал дл€ сверки дл€ демодул€тора

	Doppler doppler_obj(0.2, 0.0, _freq_start);

	srand(time(0));

	float tmp_R = 0, tmp_I = 0;

	for (int i = 0; i < _length; i += 2)
	{

		float inc_phase = getIncreasePhaseLinearAcceleration(i);		//получаем фазу синусойды
		//printf("inc_phase = %f \n", inc_phase);
		float phase = getPhaseLinearAcceleration(i);		//получаем фазу синусойды


		if (i % (_k * 2) == 0)
		{//формируем случайно квадратуры сигнала
			tmp_R = quantValuePsk(rand() % 2);
			tmp_I = quantValuePsk(rand() % 2);
		}

		float moment_phase = atan(sin(tmp_I) / cos(tmp_R));		//подсчет моментальной фазы
		_signal_power += 2 * pow(0.707107, 2);					//увеличиваем мощность сигнала
		//printf("moment_phase = %f \n", moment_phase);




		//tmp_I = doppler_obj.Make_Doppler_Movement_On_Delta(tmp_R, tmp_I, moment_phase, _freq_speed_inc);		//добавл€ем сдвиг допплера
		tmp_I = doppler_obj.makeDopplerMovementMoveI(tmp_R, tmp_I, moment_phase, _freq_speed_inc);		//добавл€ем сдвиг допплера

		_QPSK[i] = tmp_R;
		_QPSK[i + 1] = tmp_I;

		_QPSK_noNoise[i] = tmp_R;
		_QPSK_noNoise[i + 1] = tmp_I;
	}

	IOProvider provider;
	provider.Save(_QPSK, _length, true);
	provider.Save(_QPSK_noNoise, _length, false);
}

void QPSK_Modulator::makeShift(float* mass_for_shift, bool noise)
{


	for (int i = 0; i < _length; i += 2)
	{
		if (i < _length - _k)
			mass_for_shift[i] = mass_for_shift[i + _k];


		//if (i > _length - 40)
			//printf("signal %d %f %f \n", i, mass_for_shift[i], mass_for_shift[i+1]);

	}
	//printf("signal %f %f \n", mass_for_shift[_length - 4], mass_for_shift[_length - 3]);
	//printf("signal %f %f \n", mass_for_shift[_length - 2], mass_for_shift[_length-1]);

	cout << endl;

	IOProvider provider;
	provider.Save(mass_for_shift, _length + _k, noise); //mass_for_shift

	//return _OQPSK_shifted;
}
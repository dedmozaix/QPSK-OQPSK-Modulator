#include <iostream>
#include <string>

#include "Noise_Modulator.h"

#include "QPSK_Modulator_New.h"

using namespace std;

int main(int argc, char* argv[]) {


	int k = 4, Fd = 10000, f_start = 100, speed_f = 500;
	int noiseLevelDB = 18;
	float speef_percent = 0;

	if (argc > 1) {		//считывем bat файл
		cout << "Get some parameters" << endl;
		for (int i = 1; i < argc; i++) {
			
			
			if (i == 1) {
				speef_percent = (float)stoi(argv[i]) / 100;
				cout << "set speed = " << speef_percent << endl;
				speed_f = Fd * speef_percent;
			}
			if (i == 2) {
				noiseLevelDB = stoi(argv[i]);
				cout << "set noise = " << noiseLevelDB << endl;
			}
			
		}
		cout << endl;
	}
	else if (argc > 3) {
		cout << "Input data error";
	}
	
	long int length = 100000000;		//100000000   50000000
	if (length % (k * Fd) != 0)			//проверяем на полноценность последнего символа
		cout << "Not full symbol "<< length % (k * Fd) << endl;

	cout << "Modulating signal" << endl;
	QPSK_Modulator_New modulator_new(length, k, Fd, f_start, speed_f);	

	modulator_new.Modulate_Sinusoidally();	//моделируем сигнал
	//modulator_new.Modulate_Artifically();
	
	//cout << "making shift" << endl;
	//modulator_new.Make_Shift(modulator_new.GetSignal());
	//modulator_new.Make_Shift(modulator_new.GetSignal_noNoise());


	NoiseModulator noise_obj;
	noise_obj.SetSignalPower(modulator_new.GetSignalPower());
	noise_obj.MakeGaussNoiseMain(modulator_new.GetSignal(), length, noiseLevelDB, k);		//добавляем шум



}
#include "src/QPSK_Modulator.h"
#include "src/Noise_Modulator.h"

#include <iostream>
#include <string>

//using namespace std;

int main(int argc, char* argv[])
{
	int k = 4, Fd = 10000, f_start = 100, speed_f = 1;
	int noiseLevelDB = 8;
	float speef_percent = 0;

	if (argc > 1)
	{		//считывем bat файл
		cout << "Get some parameters" << endl;
		for (int i = 1; i < argc; i++)
		{

			switch (i)
			{
			case 1:
				speef_percent = (float)stoi(argv[i]) / 100;
				cout << "set speed = " << speef_percent << endl;
				speed_f = Fd * speef_percent;
				break;
			case 2:
				noiseLevelDB = stoi(argv[i]);
				cout << "set noise = " << noiseLevelDB << endl;
				break;
			}

		}
		cout << endl;
	}
	else if (argc > 3)
	{
		cout << "Input data error";
	}

	long int length = 10000000;		//100000000   50000000
	if (length % (k * Fd) != 0)			//проверяем на полноценность последнего символа
		cout << "Not full symbol " << length % (k * Fd) << endl;

	cout << "Modulating signal" << endl;
	bool makeShift = true;
	QPSK_Modulator modulator_new(length, k, Fd, f_start, speed_f);

	//modulator_new.Modulate_Sinusoidally();	//моделируем сигнал
	modulator_new.modulateArtifically();

	cout << "making shift" << endl;

	modulator_new.makeShift(modulator_new.getSignal(), true);
	modulator_new.makeShift(modulator_new.getSignalNoNoise(), false);
	
	Noise_Modulator noise_obj;
	noise_obj.makeGaussNoiseMain(modulator_new.getSignal(), length, noiseLevelDB, k);
}
@echo off
echo Start %time%

::C:\Users\nik11\source\repos\Work_QPSK_OPQSK\Debug\
::Work_QPSK_OQSK.exe 1 0
::cd C:\liquid_test\liquid_test\bin\
::liquid_test.exe -i Modulated.bin -o out.bin -T f -p Modulated_noNoise.bin

OQPSK_Modulator.exe 1 0
liquid_test.exe -i Modulated.bin -o out.bin -T f -p Modulated_noNoise.bin

OQPSK_Modulator.exe 1 1
liquid_test.exe -i Modulated.bin -o out.bin -T f -p Modulated_noNoise.bin

OQPSK_Modulator.exe 1 2
liquid_test.exe -i Modulated.bin -o out.bin -T f -p Modulated_noNoise.bin

OQPSK_Modulator.exe 1 3
liquid_test.exe -i Modulated.bin -o out.bin -T f -p Modulated_noNoise.bin


echo Stop %time%
pause
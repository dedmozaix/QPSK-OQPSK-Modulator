@echo off
echo Start %time%

OQPSK_Modulator.exe 1 0

::запуск ликвида
::liquid_test.exe -i Modulated.bin -o out.bin -T f -p Modulated_noNoise.bin



echo Stop %time%
pause

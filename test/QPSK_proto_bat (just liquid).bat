@echo off
echo Start %time%

cd C:\liquid_test\liquid_test\bin\
liquid_test.exe -i Modulated.bin -o out.bin -T f -p Modulated_noNoise.bin

echo Stop %time%
pause
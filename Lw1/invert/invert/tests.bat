@echo off
SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please cpecify path to program
	exit /B 1
)

REM "$(ProjectDir)tests.bat" "$(TargetPath)"

REM If input file is not specified, program must be fail
%MyProgram% && goto err
echo Test 1 passed

REM Is determinante of matrix is 0
%MyProgram% input_zero_det.txt > output.txt || goto err
fc output.txt message_zero_det.txt > nul || goto err
echo Test 2 passed

REM If input file is empty, program must be fail
%MyProgram% empty.txt > output.txt && goto err
echo Test 3 passed

REM Test input1.txt, determinante must be 0 
%MyProgram% input1.txt > output.txt || goto err
fc output.txt message_zero_det.txt > nul || goto err
echo Test 4 passed

REM Test input2.txt 
%MyProgram% input3.txt > output.txt || goto err
fc output.txt output3.txt > nul || goto err
echo Test 5 passed

echo All test passed succesfuly
exit /B 0

:err
echo Test failed
exit /B 1
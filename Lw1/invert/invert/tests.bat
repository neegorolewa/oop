@echo off
SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please cpecify path to program
	exit /B 1
)

REM If input file is not specified, program must be fail
%MyProgram% && goto err
echo Test 1 passed

echo All test passed succesfuly
exit /B 0

:err
echo Test failed
exit /B 1
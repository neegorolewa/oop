@echo off
SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please cpecify path to program
	exit /B 1
)

REM If input and output file and search with replace string is not specified, program must be fail
%MyProgram% && goto err
echo Test 1 passed

REM If replace string is not specified, program must be fail
%MyProgram% input.txt output.txt search && goto err
echo Test 2 passed

REM If replace string with search is not specified, program must be fail
%MyProgram% input.txt output.txt && goto err
echo Test 3 passed

REM If input is empty, output is empty
%MyProgram% Empty.txt output.txt search replace || goto err 
fc Empty.txt output.txt > nul || goto err
echo Test 4 passed

REM Replace substring "1231234" in "12312312345"
%MyProgram% input1.txt output.txt 12312345 # || goto err
fc output.txt  > nul || goto err
echo Test 5 passed

echo All test passed succesfuly
exit /B 0

:err
echo Test failed
exit /B 1
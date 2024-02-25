@echo off
SET MyProgram="%~1"

if %MyProgram%=="" (
	echo Please cpecify path to program
	exit /B 1
)

REM If input stream include file, program must be fail
%MyProgram% input.txt && goto err
echo Test 1 passed

REM If empty stream than ouptut message is ERROR
%MyProgram% < empty.txt > output.txt || goto err
fc output.txt error.txt > nul || goto err
echo Test 2 passed

REM If input stream contains a negative value than ouptut message is ERROR
%MyProgram% < negative_value.txt > output.txt || goto err
fc output.txt error.txt > nul || goto err
echo Test 3 passed

REM If input stream contains a real value with comma than ouptut message is ERROR
%MyProgram% < real_comma_value.txt > output.txt || goto err
fc output.txt error.txt > nul || goto err
echo Test 4 passed

REM If input stream contains a real value with dot than ouptut message is ERROR
%MyProgram% < real_dot_value.txt > output.txt || goto err
fc output.txt error.txt > nul || goto err
echo Test 5 passed

REM If input stream contains a non-valid value than ouptut message is ERROR
%MyProgram% < non_valid_value.txt > output.txt || goto err
fc output.txt error.txt > nul || goto err
echo Test 6 passed

REM If input stream contains a non-negative value than ouptut message is NON-MAGIC
%MyProgram% < non_negative_value.txt > output.txt || goto err
fc output.txt non-magic.txt > nul || goto err
echo Test 7 passed

REM If input stream contains a overflow value than ouptut message is ERROR
%MyProgram% < overflow_number.txt > output.txt || goto err
fc output.txt error.txt > nul || goto err
echo Test 8 passed

REM If input stream contains a overflow value than ouptut message is ERROR
%MyProgram% < max_value_uint64.txt > output.txt || goto err
fc output.txt non-magic.txt > nul || goto err
echo Test 9 passed

echo All test passed succesfuly
exit /B 0

:err
echo Test failed
exit /B 1
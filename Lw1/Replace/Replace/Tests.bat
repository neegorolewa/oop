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
%MyProgram% input.txt output.txt 1 && goto err
echo Test 2 passed

REM If search string with search is not specified, program must be fail
%MyProgram% input.txt output.txt a && goto err
echo Test 3 passed

REM If output file is not specified, program must be fail
%MyProgram% input.txt 1 q && goto err
echo Test 4 passed

REM If input file is not specified, program must be fail
%MyProgram% output.txt q && goto err
echo Test 5 passed

REM If input is empty than output is empty
%MyProgram% empty.txt output.txt 1 q || goto err 
fc empty.txt output.txt > nul || goto err
echo Test 6 passed

REM If search string is empty with empty input file, output is empty
%MyProgram% empty.txt output.txt "" q || goto err 
fc empty.txt output.txt > nul || goto err
echo Test 7 passed

REM If search string is empty with normal input file, than output must be like input 
%MyProgram% input.txt output.txt "" q || goto err
fc input.txt output.txt > nul || goto err
echo Test 8 passed

REM If the symbol is on itself the file will not change  
%MyProgram% input.txt output.txt Q Q || goto err
fc input.txt output.txt > nul || goto err
echo Test 9 passed

REM If you search for a non-existent substring, the file will not change 
%MyProgram% input.txt output.txt qwerty # || goto err
fc input.txt output.txt > nul || goto err
echo Test 10 passed

SET Test11="test11.txt"

REM "1231234" should be correct replace in "12312312345"
%MyProgram% input.txt output.txt 1231234 @ || goto err
fc output.txt %Test11% > nul || goto err
echo Test 11 passed

SET Test12="test12.txt"

REM output.txt should be equal test12.txt
%MyProgram% input.txt output.txt "it's program for replace text" "HELLO WORLD!" || goto err
fc output.txt %Test12% > nul || goto err
echo Test 12 passed

SET Test13="test13.txt"

REM BIG input file must be correct processed
%MyProgram% big_input.txt output.txt "APPLE" "COOKIE" || goto err
fc output.txt %Test13% > nul || goto err
echo Test 13 passed

SET Test14="test14.txt"

REM
%MyProgram% input.txt output.txt ma mama || goto err
fc output.txt %Test14% > nul || goto err
echo Test 14 passed

echo All test passed succesfuly
exit /B 0

:err
echo Test failed
exit /B 1
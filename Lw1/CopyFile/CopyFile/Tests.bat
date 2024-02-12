@echo off

REM ���� � ����������� ��������� ��������� ����� 1-� �������� ��������� ������
SET MyProgram="%~1"

REM ������ �� ������� ��� ���������, ��������� ���� � ���������
if %MyProgram%=="" (
	echo Please specify path to program 
	exit /B 1
) 

REM Copy empty file
%MyProgram% Empty.txt "%TEMP%\output.txt" || goto err
fc Empty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 1 passed

REM Copy non-empty file
%MyProgram% NonEmpty.txt "%TEMP%\output.txt" || goto err
fc NonEmpty.txt "%TEMP%\output.txt" > nul || goto err
echo Test 2 passed

REM Copy missing file should fail
%MyProgram% MissingFile.txt "%TEMP%\output.txt" && goto err
echo Test 3 passed

REM If output file is not specified, program must fail 
%MyProgram% MissingFile.txt && goto err
echo Test 4 passed

REM If input and output files are not specified. program must fail
%MyProgram% && goto err
echo Test 5 passed

REM ����� ������ �������
echo All tests passed succesfuly
exit /B 0

REM �������� ���� � ������ ������
:err
echo Test failed
exit /B 1
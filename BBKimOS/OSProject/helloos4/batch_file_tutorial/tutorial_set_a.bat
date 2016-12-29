@echo off

echo simple add batchfile
set /p num1=Input number :
set /p num2=Input number :
set /a sum=%num1% + %num2%

echo %num1% + %num2% = %sum%

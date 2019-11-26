@echo off
:loop
REM if exist "Input.cpp" (
REM g++ "Input.cpp" -o "Input.exe"
    Input.exe %random% > Input.in
REM if exist "E4-2.cpp" (
REM g++ "E4-2.cpp" -o "E4-2.exe"
    E4-2.exe < Input.in > Answer.out
REM     )
REM )
REM if exist "a.exe"(
    a.exe < Input.in > RightAnswer.out
    fc Answer.out RightAnswer.out
REM )
if not errorlevel 1 goto loop
pause
goto loop

@echo off
:loop
    Input.exe %random% > Input.in
    E4-2.exe < Input.in > Answer.out
    a.exe < Input.in > RightAnswer.out
    fc Answer.out RightAnswer.out
if not errorlevel 1 goto loop
pause
goto loop

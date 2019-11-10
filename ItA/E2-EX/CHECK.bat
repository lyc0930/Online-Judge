@echo off
:loop
    Input.exe %random% > Input.in
    a.exe < Input.in > Right_Answer.out
    E2-EX.exe < Input.in > Answer.out
    fc Answer.out Right_Answer.out
if not errorlevel 1 goto loop
pause
goto loop

@echo off
:loop
gen.exe
std.exe
c1.exe
fc c.out c1.out
if not errorlevel 1 goto loop
pause
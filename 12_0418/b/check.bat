@echo off
:loop
gen.exe
b.exe
std.exe
fc b.out std.out
if not errorlevel 1 goto loop
pause
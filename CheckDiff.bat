@echo off
setlocal enabledelayedexpansion

echo Use %1

FOR /F %%i IN ('DIR /b *.in') DO (
  echo test %%i
  set fileid=%%i
  set fileid=!fileid:~0,-3!
  set outfile=!fileid!.out.tmp
  set outfile2=!fileid!.out
  %1<%%i>!outfile!
  fc !outfile! !outfile2!
)
pause
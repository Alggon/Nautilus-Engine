@echo off
cd /d "%~dp0"

set "CMAKE_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"

if exist build rmdir /s /q build

"%CMAKE_PATH%" -B build -G "Visual Studio 17 2022"
   
pause
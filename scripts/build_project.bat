@echo off

REM This is a swick way of running your premake5.lua script... Run it however you perfer :D

REM What build_project.bat does: Used the default build type or asks for a build type and 
REM calls the premake5.exe with the build type to build your project

REM ------------------------------USER----------------------------

REM Change this to the root path of your project (default=%~dp0\..\)
set "root_dir=%~dp0..\"
REM Change this to the path of your premake5.exe file (default=%~dp0\..\vendor\bin\premake\premake5.exe)
set "path_to_premake=%~dp0..\vendor\bin\premake\premake5.exe"
REM Change this to the default build type of your choosing (default=vs2019)
set default_build_type=vs2019

REM -----------------------------CORE-----------------------------

REM This gets %cmdcmdline% and removes "", removes the first path, and extracts a character from the orig value
set mode=%cmdcmdline%
set mode=%mode:"=%
set mode=%mode:* =%
set mode=%mode:~1,2%
REM if c, this was run by a double click; if s, this was run from an open cmd window
if %mode%==c goto default

if [%1]==[] goto default
set type=%1
goto build_with_premake

:default
set type=%default_build_type%
goto build_with_premake

:build_with_premake
pushd %root_dir%
echo Building for a %type% project...
call %path_to_premake% %type%
popd
if %mode%==c pause
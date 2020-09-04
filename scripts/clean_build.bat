@echo off

REM Don't waste your time deleting build directories... Run this script and it will delete them for you!

REM What clean_build.bat does: Deletes the provided folders
REM Warning: This does not scan your premake5.lib file for the output directories 

REM ------------------------------USER----------------------------

REM Change this to the root path of your project (default=%~dp0\..\)
set "root_dir=%~dp0..\"
REM Change this to the path of your premake5.exe file (default=%~dp0\..\vendor\bin\premake\premake5.exe)
set "path_to_premake=%~dp0..\vendor\bin\premake\premake5.exe"
REM Change these to the folders you wish to delete (default=bin bin-int)
set default_delete=bin bin-int

REM -----------------------------CORE-----------------------------

REM This gets %cmdcmdline% and removes "", removes the first path, and extracts a character from the orig value
set mode=%cmdcmdline%
set mode=%mode:"=%
set mode=%mode:* =%
set mode=%mode:~1,2%
REM if c, this was run by a double click; if s, this was run from an open cmd window

:delete
pushd %root_dir%
( for %%a in (%default_delete%) do (
   echo Deleting folder %%a...
   RMDIR /Q/S %%a
) )
echo Done.
popd
if %mode%==c pause
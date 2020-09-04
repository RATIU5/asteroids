@echo off

REM Renaming your project with a batch script is cooler
REM than manually changing your name everywhere ;)

REM What rename.bat does: Grabs the name of the premake5.lua workspace, and replaces all
REM occurences of that name with a new name in that file and renames the project folder too

REM ------------------------------USER----------------------------

REM Change this to the root of your project (default=%~dp0\..\)
set "root_dir=%~dp0\..\"
REM Change this to the name of your premake file (default=premake5.lua)
set file_to_rename=premake5.lua
REM Change this to 0 if you do not want to rename the folder (default=1)
set rename_folder=1

REM -----------------------------CORE-----------------------------

REM This gets %cmdcmdline% and removes "", removes the first path, and extracts a character from the orig value
set mode=%cmdcmdline%
set mode=%mode:"=%
set mode=%mode:* =%
set mode=%mode:~1,2%
REM if c, this was run by a double click; if s, this was run from an open cmd window
if %mode%==c goto ask_name

if [%1]==[] goto ask_name
set new_name=%1
goto replace_name

:ask_name
    set /p new_name=New name (no spaces):
    goto replace_name

REM This works assuming that the first line of your premake5.lua file starts with "workspace"
REM and that there are no spaces in the name
:get_current_name
    REM Get the first line of premake5.lua
    set /p _line_str=< %file_to_rename%
    REM Get the second "word" of the line
    for /f "tokens=2" %%i in ("%_line_str%") do set _name_str=%%i
    REM Remove the "" around the name
    set curr_name=%_name_str:"=%
    goto :eof

:replace_name
    pushd %root_dir%
    call :get_current_name
    REM Powershell command that replaces the current name with the new one
    powershell -Command "(Get-Content %file_to_rename%) -replace '%curr_name%', '%new_name%' | Out-File -encoding ASCII %file_to_rename%"
    if not %ERRORLEVEL% equ 0 goto ps_error
    echo file rename: success
    if %rename_folder% equ 0 goto skip_folder
    rename %curr_name% %new_name%
    if not %ERRORLEVEL% equ 0 goto folder_error
    echo folder rename: success
    echo Done.
    goto end

:skip_folder
    echo Done.
    goto end

:ps_error
    echo file rename: failed
    echo.
    echo An error (%ERRORLEVEL%) occured trying to ^rename all occurences of %curr_name% to %new_name% in file %file_to_rename%
    goto end

:folder_error
    echo folder rename: failed
    echo.
    echo An error (%ERRORLEVEL%) occured trying to ^rename the folder %curr_name% to %new_name%...
    goto end

:end
popd
if %mode%==c pause
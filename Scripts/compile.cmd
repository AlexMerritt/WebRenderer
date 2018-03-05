@echo off
setlocal enabledelayedexpansion

set filename=App.pro

if "%appdir%"=="" (
  set EnvError="appdir" not defined. 
  GOTO EnvNotSet
)
if "%bindir%"=="" (
  set EnvError="bindir" not defined. 
  GOTO EnvNotSet
)

if "%libdir%"=="" (
  set EnvError="libdir" not defined. 
  GOTO EnvNotSet
)

REM If there are no issues with the env file paths try start the build

set file=%appdir%\%filename%
if EXIST %file% (
  GOTO Build
) ELSE (
  GOTO FileNotFound
)

:Build
  set /A i=0
  for /F "usebackq delims=" %%a in ("%file%") do (
    set /A i+=1
    call set array[%%i%%]=%%a
    call set n=%%i%%
  )

  for /L %%i in (1,1,%n%) do (
    call set something=%%array[%%i]%%
    set coll=!coll! %appdir%\!something!
  )

  set buildcall=call emcc -o %bindir%\Index.html !coll! -O1 -s WASM=1 --shell-file %libdir%/template.html -s EXPORTED_FUNCTIONS="['_Initialize', '_Update']"  -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall']" -s ASSERTIONS=1  
  call :Compile buildcall
  EXIT /b 0
:end


:EnvNotSet
  echo Exiting: Build environment not setup correctly. %EnvError%Did you run setupenv.cmd yet?
  EXIT /b 0
:end

:FileNotFound
  echo "%file%" not found
  EXIT /b 0
:end

REM Sample emcc call for reference
REM call emcc -o %bindir%\Index.html %appdir%\Application.cpp %appdir%\main.cpp -O1 -s WASM=1 --shell-file %libdir%/template.html -s EXPORTED_FUNCTIONS="['_Initialize', '_Update']"  -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall']" -s ASSERTIONS=1
:Compile
  setlocal
  call echo ---------- Starting Compile ----------
  call echo !%1!
  call !%1!

  call echo.
  call echo Build Succeeded
  call echo ---------- Compile Finished ----------
  call echo.
  endlocal
:end
endlocal
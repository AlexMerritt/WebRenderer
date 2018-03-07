@echo off
setlocal enabledelayedexpansion

set filename=App.pro
set outFile=Index.html
set htmlTemplate=template.html
set optimizationLevel=-O1
set /a numAdditionalFlags=0
REM set additionalFlags=WASM=1,EXPORTED_FUNCTIONS="['_Initialize', '_Update']",EXTRA_EXPORTED_RUNTIME_METHODS="['ccall']"

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
    set sourceFiles=!sourceFiles! %appdir%\!something!
    
  )

  call :SetupAdditionalBuildFlags

  set buildcall=call emcc -o %bindir%\%outFile%!sourceFiles! %optimizationLevel% --shell-file %libdir%/%htmlTemplate%

  for /L %%j in (0,1,%numAdditionalFlags%) do (
    call set addtl=%%additionalFlags[%%j]%%
    call set buildcall=!buildcall! !addtl!
  )

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

:SetupAdditionalBuildFlags
  call :AddFlag WASM 1
  call :AddFlag ASSERTIONS 1
  call :AddFlag ALLOW_MEMORY_GROWTH 1
  call :AddFlag USE_WEBGL2 1
  call :AddFlag FULL_ES3 1
  call :AddFlag EXPORTED_FUNCTIONS "['_Initialize', '_Update']"
  call :AddFlag EXTRA_EXPORTED_RUNTIME_METHODS "['ccall']"

  EXIT /b
:end

:AddFlag
  call set additionalFlags[%%numAdditionalFlags%%]=-s %1=%2
  set /a numAdditionalFlags+=1
  EXIT /b
:end

REM Sample emcc call for reference
REM call emcc -o %bindir%\Index.html %appdir%\Application.cpp %appdir%\main.cpp -O1 -s WASM=1 --shell-file %libdir%/template.html -s EXPORTED_FUNCTIONS="['_Initialize', '_Update']"  -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall']" -s ASSERTIONS=1
:Compile
  setlocal
  call echo ---------- Starting Compile ----------
  call echo !%1!
  call echo.
  call !%1!
  
  call echo.
  call echo ---------- Compile Finished ----------
  call echo.
  endlocal
  EXIT /b
:end
endlocal
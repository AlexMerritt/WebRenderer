@echo off
set src=C:\Projects\WebRenderer
set scriptdir=%src%\Scripts

set appdir=%src%\App

set libdir=%src%\Lib
set jssrc=%libdir%\JS

set bindir=%src%\Bin
set jsdst=%bindir%\JS

"C:\Program Files\Emscripten\emsdk" activate latest
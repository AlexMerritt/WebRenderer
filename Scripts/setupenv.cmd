@echo off
set src=C:\Projects\WebRenderer
set scriptdir=%src%\Scripts

set appdir=%src%\App
set jssrc=%appdir%\JS

set libdir=%src%\Lib

set bindir=%src%\Bin
set jsdst=%bindir%\JS

"C:\Program Files\Emscripten\emsdk" activate latest
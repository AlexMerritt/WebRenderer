echo ---------- Starting Compile ----------

call emcc -o %bindir%\Index.html %appdir%\Application.cpp %appdir%\main.cpp -O1 -s WASM=1 --shell-file %libdir%/template.html -s EXPORTED_FUNCTIONS="['_Initialize', '_Update']"  -s EXTRA_EXPORTED_RUNTIME_METHODS="['ccall']" -s ASSERTIONS=1

echo ---------- Compile Finished ----------
echo.
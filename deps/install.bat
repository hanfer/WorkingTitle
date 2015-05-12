@echo off

echo.
pushd .
echo ----------------
echo installing libuv
echo ----------------
git clone --branch v1.5.0 https://github.com/libuv/libuv.git
cd libuv
call vcbuild.bat
popd

echo.
pushd .
echo ----------------
echo installing jansson
echo ----------------
git clone --branch v2.7 https://github.com/akheron/jansson.git
setlocal
call "%VS120COMNTOOLS%..\..\VC\vcvarsall.bat"
cd jansson
cmake . -G "NMake Makefiles"
nmake
endlocal
popd
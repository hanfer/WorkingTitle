@echo off

echo.
pushd .
echo ----------------
echo installing libuv
echo ----------------
git clone --depth 1 --branch v1.5.0 https://github.com/libuv/libuv.git
cd libuv
call vcbuild.bat
popd

echo.
pushd .
echo ----------------
echo installing jansson
echo ----------------
git clone --depth 1 --branch v2.7 https://github.com/akheron/jansson.git
setlocal
call "%VS120COMNTOOLS%..\..\VC\vcvarsall.bat"
cd jansson
cmake . -DJANSSON_BUILD_DOCS=0 -DJANSSON_STATIC_CRT=1 -DSTATIC_CRT=1 -G "Visual Studio 12 2013"
msbuild jansson.sln /target:jansson /p:Configuration=Release
msbuild jansson.sln /target:jansson /p:Configuration=Debug
endlocal
popd

echo.
pushd .
echo ----------------
echo installing http-parser
echo ----------------
git clone --depth 1 --branch v2.5.0 https://github.com/joyent/http-parser.git
setlocal
cd http-parser
git clone --depth 1 https://chromium.googlesource.com/external/gyp gyp
set GYP_MSVS_VERSION=2013
%python% gyp\gyp_main.py --depth=. http_parser.gyp
call "%VS120COMNTOOLS%..\..\VC\vcvarsall.bat"
msbuild http_parser.sln /target:http_parser /p:Configuration=Release
msbuild http_parser.sln /target:http_parser /p:Configuration=Debug
endlocal
popd
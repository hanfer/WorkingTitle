@echo off

echo 
echo installing libuv
echo 

git clone https://github.com/libuv/libuv.git
pushd libuv
vcbuild.bat
popd
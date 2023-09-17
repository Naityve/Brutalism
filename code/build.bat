@echo off

mkdir ..\build
pushd ..\build
cl -FC -Zi ..\code\Brutalism.cpp user32.lib gdi32.lib
popd
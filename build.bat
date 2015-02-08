@echo off
IF NOT EXIST _build GOTO BUILD
rmdir _build /s /q
:BUILD
mkdir _build
cd _build
cmake -DCMAKE_INSTALL_PREFIX=./install %* ..
cd ..
if EXIST %CD%\_build\GLRender.sln (
start /B "%VS120COMNTOOLS%\..\IDE\devenv.exe" "%CD%\_build\GLRender.sln"
) ELSE (
echo %CD%\_build\GLRender.sln not found
)

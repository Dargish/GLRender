@echo off
IF NOT EXIST _build GOTO BUILD
rmdir _build /s /q
:BUILD
mkdir _build
cd _build
cmake -DCMAKE_INSTALL_PREFIX=./install %* ..
cd ..
xcopy %CD%\..\GLRenderDependencies\bin\*.dll %CD%\_build\GLRender\Debug\ /Q
xcopy %CD%\..\GLRenderDependencies\bin\*.dll %CD%\_build\GLRender\Release\ /Q
xcopy %CD%\GLRender\data %CD%\_build\GLRender\ /Q
if EXIST %CD%\_build\GLRender.sln (
start /B "%VS120COMNTOOLS%\..\IDE\devenv.exe" "%CD%\_build\GLRender.sln"
) ELSE (
echo %CD%\_build\GLRender.sln not found
)

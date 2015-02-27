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
xcopy %CD%\Pioneer\data %CD%\_build\Pioneer\data\ /E /Q
xcopy %CD%\Tests\LoadModelTest\data %CD%\_build\Tests\LoadModelTest\data\ /E /Q
xcopy %CD%\Tests\LoadShaderTest\data %CD%\_build\Tests\LoadShaderTest\data\ /E /Q
if EXIST %CD%\_build\GLRender.sln (
start /B "%VS120COMNTOOLS%\..\IDE\devenv.exe" "%CD%\_build\GLRender.sln"
) ELSE (
echo %CD%\_build\GLRender.sln not found
)

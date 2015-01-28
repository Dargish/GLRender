IF NOT EXIST _build GOTO BUILD
rmdir _build /s /q
:BUILD
mkdir _build
cd _build
cmake -DCMAKE_INSTALL_SUFFIX=./install %* ..
cd ..
mkdir _build/Tests/Debug/
mkdir _build/Tests/Release/
xcopy ..\GLRenderDependencies\jsoncpp\jsoncpp-1.3.0\lib\jsoncpp.dll _build\Tests\Debug\
xcopy ..\GLRenderDependencies\jsoncpp\jsoncpp-1.3.0\lib\jsoncpp.dll _build\Tests\Release\
start /B "%VS120COMNTOOLS%\..\IDE\devenv.exe" "%CD%\_build\GLRender.sln"
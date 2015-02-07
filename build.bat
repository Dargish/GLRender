IF NOT EXIST _build GOTO BUILD
rmdir _build /s /q
:BUILD
mkdir _build
cd _build
cmake -DCMAKE_INSTALL_SUFFIX=./install %* ..
cd ..
start /B "%VS120COMNTOOLS%\..\IDE\devenv.exe" "%CD%\_build\GLRender.sln"
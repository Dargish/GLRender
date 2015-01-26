IF NOT EXIST _build GOTO BUILD
rmdir _build /s /q
:BUILD
mkdir _build
cd _build
cmake -DCMAKE_INSTALL_SUFFIX=./install ..
"D:\Program Files (x86)\Microsoft Visual Studio 12.0\Common7\IDE\devenv.exe" "%CD%\GLRender.sln"
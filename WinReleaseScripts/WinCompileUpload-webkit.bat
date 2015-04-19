:: Used to automate everything for Alex so he can be lazy.
:: Requirements - Everything needs to be located in your windows path, except MSVC2013
:: 7Zip
:: WINSCP - Optional, it will just not upload the file automatically if you don't have it.
::  - "open downloads" is the command that selects the downloads alias in winscp, which for me is the simulationcraft server. Change downloads to whatever suits you.
:: MSVC 2013 - Fully updated
:: Git
:: QT 5.4.1, or whatever version we are currently using
:: Inno Setup - http://www.jrsoftware.org/isinfo.php - Used to make the installer, optional if you just want a compressed file.
:: OpenSSL - https://slproweb.com/products/Win32OpenSSL.html - Optional, the program will work fine even without these. The only time it will matter is if the person attempts to load a https website inside the gui, which is probably never going to happen.

set simcversion=612-02
:: For bumping the minor version, just change the above line. 
set simcfiles=E:\Simulationcraft\
:: Location of source files
set ssllocation32=C:\OpenSSL-Win32\bin
set ssllocation64=C:\OpenSSL-Win64\bin
:: Location of openssl32/64
set qt_dir=C:\Qt\Qt5.4.1\5.4\
:: Location of QT
set redist=C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\
:: This is a really standard location for VS2013, but change it if you installed it somewhere else.

cd ..
git clean -f -x -d
:: Clean the directory up, otherwise it'll zip up all sorts of stuff.
For /f "tokens=2-4 delims=/ " %%a in ('date /t') do (set mydate=%%a-%%b)
:: Get the date, because I guess that's important.
git log --no-merges -1 --pretty="%%h">bla.txt
:: Gives the git revision
set /p revision=<bla.txt
:: Hacky hack because windows command prompt is annoying.
del bla.txt

:: Script below
set install=simc-%simcversion%-source
cd>bla.txt
set /p download=<bla.txt
del bla.txt

robocopy . %install% /s *.* /xd .git %install% /xf *.pgd /xn
set filename=%install%-%mydate%-%revision%
7z a -r -tzip %filename% %install% -mx9
call start winscp /command "open downloads" "put %download%\%filename%.zip -nopreservetime -nopermissions -transfer=binary" "exit"

::Webkit compilation.
set install=simc-%simcversion%-win64
rd %install% /s /q

for /f "skip=2 tokens=2,*" %%A in ('reg.exe query "HKLM\SOFTWARE\Microsoft\MSBuild\ToolsVersions\12.0" /v MSBuildToolsPath') do SET MSBUILDDIR=%%B

"%MSBUILDDIR%msbuild.exe" %simcfiles%\simc_vs2013.sln /p:configuration=WebKit /p:platform=x64 /nr:true

robocopy "%redist%x64\Microsoft.VC120.CRT" %install%\ msvcp120.dll msvcr120.dll vccorlib120.dll
robocopy locale\ %install%\lib\locale sc_de.qm sc_zh.qm sc_it.qm
robocopy %qt_dir%msvc2013_64\bin\ %install%\lib\ Qt5Core.dll Qt5Quick.dll Qt5Qml.dll Qt5Svg.dll Qt5Gui.dll Qt5Widgets.dll Qt5Network.dll Qt5WebKit.dll Qt5WebKitWidgets.dll libGLESv2.dll icudt53.dll icuin53.dll icuuc53.dll libEGL.dll D3DCompiler_47.dll Qt5WebChannel.dll Qt5Multimedia.dll Qt5MultimediaWidgets.dll Qt5Sensors.dll Qt5PrintSupport.dll Qt5Qml.dll Qt5Sql.dll Qt5Svg.dll Qt5Positioning.dll Qt5OpenGl.dll
robocopy winreleasescripts\ %install%\ qt.conf
robocopy %qt_dir%msvc2013_64\ %install%\lib\ icudtl.dat
robocopy %qt_dir%msvc2013_64\plugins\platforms %install%\lib\platforms\ qwindows.dll
robocopy %qt_dir%msvc2013_64\plugins\imageformats %install%\lib\imageformats qdds.dll qgif.dll qicns.dll qico.dll qjp2.dll qjpeg.dll qmng.dll qsvg.dll qtga.dll qtiff.dll qwbmp.dll qwebp.dll
robocopy . %install%\ Welcome.html Welcome.png Simulationcraft64.exe simc64.exe readme.txt Error.html COPYING
robocopy %ssllocation64% %install%\lib\ libeay32.dll ssleay32.dll 
robocopy Profiles\ %install%\profiles\ *.* /S

cd winreleasescripts
iscc.exe "setup64.iss"
cd ..
call start winscp /command "open downloads" "put %download%\SimcSetup-%simcversion%-win64.exe -nopreservetime -nopermissions -transfer=binary" "exit"
7z a -r %install% %install% -mx9 -md=32m
call start winscp /command "open downloads" "put %download%\%install%.7z -nopreservetime -nopermissions -transfer=binary" "exit"

set install=simc-%simcversion%-win32
"%MSBUILDDIR%msbuild.exe" %simcfiles%\simc_vs2013.sln /p:configuration=WebKit /p:platform=win32 /nr:true /m:8

robocopy "%redist%x86\Microsoft.VC120.CRT" %install%\ msvcp120.dll msvcr120.dll vccorlib120.dll
robocopy locale\ %install%\lib\locale sc_de.qm sc_zh.qm sc_it.qm
robocopy %qt_dir%msvc2013\bin\ %install%\lib\ Qt5Core.dll Qt5Quick.dll Qt5Qml.dll Qt5Svg.dll Qt5Gui.dll Qt5Widgets.dll Qt5Network.dll Qt5WebKit.dll Qt5WebKitWidgets.dll libGLESv2.dll icudt53.dll icuin53.dll icuuc53.dll libEGL.dll D3DCompiler_47.dll Qt5WebChannel.dll Qt5Multimedia.dll Qt5MultimediaWidgets.dll Qt5Sensors.dll Qt5PrintSupport.dll Qt5Qml.dll Qt5Sql.dll Qt5Svg.dll Qt5Positioning.dll Qt5OpenGl.dll
robocopy winreleasescripts\ %install%\ qt.conf
robocopy %qt_dir%msvc2013\ %install%\lib\ icudtl.dat
robocopy %qt_dir%msvc2013\plugins\platforms %install%\lib\platforms\ qwindows.dll
robocopy %qt_dir%msvc2013\plugins\imageformats %install%\lib\imageformats qdds.dll qgif.dll qicns.dll qico.dll qjp2.dll qjpeg.dll qmng.dll qsvg.dll qtga.dll qtiff.dll qwbmp.dll qwebp.dll
robocopy . %install%\ Welcome.html Welcome.png Simulationcraft.exe simc.exe readme.txt Error.html COPYING
robocopy %ssllocation32% %install%\lib\ libeay32.dll ssleay32.dll 
robocopy Profiles\ %install%\profiles\ *.* /S

cd winreleasescripts
iscc.exe "setup32.iss"
cd ..
call start winscp /command "open downloads" "put %download%\SimcSetup-%simcversion%-win32.exe -nopreservetime -nopermissions -transfer=binary" "exit"
7z a -r %install% %install% -mx9 -md=32m
winscp /command "open downloads" "put %download%\%install%.7z -nopreservetime -nopermissions -transfer=binary" "exit"
pause
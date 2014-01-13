@REM Batch file to build the library from the Visual Studio command shell
@REM (or the Windows SDK command shell)

@setlocal

@REM *******************************************************************
@REM TODO: Customize these lines for your library and Lua file locations
@REM *******************************************************************
@set LIBNAME=lua_template
@set LUAINC="c:\program files (x86)\lua\5.2\include"
@set LUALIB="c:\program files (x86)\lua\5.2\lib\lua52.lib"



@REM **************************************************
@REM Generally no need to customize anything below here
@REM **************************************************

@set MYCOMPILE=cl /nologo /MD /O2 /W3 /c /D_CRT_SECURE_NO_DEPRECATE
@set MYLINK=link /nologo
@set MYMT=mt /nologo


@echo.
@echo  *** CLEAN STAGE ***
@echo.
if exist *.obj ( del *.obj )
if exist *.dll.manifest ( del %LIBNAME%.dll.manifest )
if exist *.dll ( del %LIBNAME%.dll )
@echo.
@echo  *** COMPILE STAGE ***
@echo.
%MYCOMPILE%  /I%LUAINC% *.c
@echo.
@echo  *** LINK STAGE ***
@echo.
%MYLINK% /DLL /out:%LIBNAME%.dll *.obj %LUALIB%
@echo.
@echo  *** MANIFEST STAGE ***
@echo.
if exist %LIBNAME%.dll.manifest (
  %MYMT% -manifest %LIBNAME%.dll.manifest -outputresource:%LIBNAME%.dll;2
)
@echo.


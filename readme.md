Template for a Lua libary
=========================
Library template providing boilerplate code with a fill-in-the-blanks approach.

* use single command to create a new working module
* can be used from Windows and *nix (API declaration)
* supports Lua 5.1 to Lua 5.3
* has default close/shutdown methods
* optional global module table (for Lua 5.1 only)
* includes an SCM rockspec for use with LuaRocks

LICENSE
-------
Copyright 2012-2014, Thijs Schreijer. License is MIT/X11, the same as Lua itself

USAGE
-----
The simplest way to use the libary is by installing it through LuaRocks `sudo luarocks install lualibrarytemplate`.
When done so a command line script `luacmodule` is available to create an instantly running c module.

Here's how to create and test a new module 'testmod';
````
luacmodule testmod
cd testmod
luarocks make
lua -e "require([[testmod]]).somefunction([[one]], two, 3)"
````
This is the output on Windows;
````
C:\Temp>luacmodule testmod
Succesfully generated project; testmod

C:\Temp>cd testmod

C:\Temp\testmod>luarocks make
mingw32-gcc -O2 -c -o testmod.o -IC:/Program Files (x86)/Lua/5.1/include/ testmod.c
mingw32-gcc -shared -o testmod.dll testmod.o C:/Program Files (x86)/Lua/5.1/bin/lua51.dll -lm
Updating manifest for C:\Program Files (x86)\LuaRocks\systree/lib/luarocks/rocks

testmod scm-1 is now built and installed in C:\Program Files (x86)\LuaRocks\systree (license: MIT)

C:\Temp\testmod>lua -e "require([[testmod]]).somefunction([[one]], two, 3)"
Now initializing module 'required' as:  testmod
Now running somefunction...
--------Start stack from somefunction()------------
`one'  nil  3
--------End Dump------------
Now closing the Lua template library

C:\Temp\testmod>
````

Alternatively it can be used manually, see below for platform specifics

UNIX
-----
* Copy and rename the following files;
    * template/lua_template.c
    * template/lua_template.h
    * template/lua_template-scm-1.rockspec
* Check the TODO comments in the template

WINDOWS - VISUAL STUDIO
----------------------------
The template itself can simply be copied into a solution and then
adapted for use.

Steps;

* in your solution create a new project directory
* copy the following files into that directory
    * template/lua_template.h
    * template/lua_template.c
    * template/lua_template-scm-1.rockspec
    * template/lua_template.vcxproj
    * template/lua_template.vcxproj.filters (optional)
* Rename the 'lua_template.vcxproj' (and the .filters file)
* In visual studio add the project to your solution
* Rename the .c and .h files from within VS
* See the VS tasklist for the TODO's in the template.

Alternatively;
* use `compile.bat` from the Visual Studio/WinSDK command shell
(check the file for 'TODO' comments)


Creating Lua libraries from scratch in VS
=========================================
* Create a new project and select; Visual C++, win32, win32 project
* In the wizard select 'DLL' and 'empty project'
* Add a new C file to the project (must be done first, otherwise the C/C++ options won't show in VS2008)
* Open the new project properties (rightclick -> properties) and set
the following options;
  * C/C++, General, Additional Include Directories
      * Add the path to the Lua header files, Lua for Windows; "C:\Program Files\Lua\5.1\include"
  * C/C++, Code Generation, Runtime Libary;
      * Mutithreaded DLL (for VS2005 and before, default in 2008)
  * Linker, General, Additional Libary Directories;
      * Add the path to the Lua library files, Lua for Windows;
        "C:\Program Files\Lua\5.1\lib"
   * Linker, Input, Additional Dependencies;
      * Add the lua51.lib files, Lua for Windows;
        "lua51.lib"

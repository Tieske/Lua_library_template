VS2008 template for a Lua libary
================================
The template itself can simply be copied into a solution and then
adapted for use. See the VS tasklist for the TODO's in the template.


Creating Lua libraries from scratch
===================================
Create a new project and select; Visual C++, win32, win32 project
In the wizard select 'DLL' and 'empty project'
Add a new C file to the project (must be done first, otherwise the
C/C++ options won't show in VS2008)

Open the new project properties (rightclick -> properties) and set
the following options;
C/C++, General, Additional Include Directories
        Add the path to the Lua header files, Lua for Windows; 
        "C:\Program Files\Lua\5.1\include"
C/C++, Code Generation, Runtime Libary;
        Mutithreaded DLL (for VS2005 and before, default in 2008)
Linker, General, Additional Libary Directories;
        Add the path to the Lua library files, Lua for Windows; 
        "C:\Program Files\Lua\5.1\lib"
Linker, Input, Additional Dependencies;
        Add the lua51.lib files, Lua for Windows; 
        "lua51.lib"

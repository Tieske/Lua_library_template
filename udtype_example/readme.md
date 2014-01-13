Sample library using the Lua libary template
=========================
Module has a single function 'type()' that is identical to the regular Lua type() function, except that it returns a second value in case of a userdata; its metatable name.

The first time a metatable is searched for it will be searched for in the registry, once collected it will be stored in a proxy table for quicker retrieval the next time it is requested.

LICENSE
-------
Copyright 2012-2014, Thijs Schreijer. License is MIT/X11, the same as Lua itself

Example
-------
see test and sample Lua scripts.

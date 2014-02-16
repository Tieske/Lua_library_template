package = "lualibrarytemplate"
version = "scm-1"

source = {
    url = "git://github.com/Tieske/Lua_library_template.git",
}
description = {
   summary = "Lua template for C libraries",
   detailed = [[
      Quickly setup a new C library, using a fill-in-the-blanks
      aproach.
      This rock also contains a commandline script to create an
      instantaneously, compiling and working, module.
   ]],
   homepage = "https://github.com/Tieske/Lua_library_template",
   license = "MIT"
}
dependencies = {
   "lua >= 5.1, < 5.2",
   "luafilesystem",
   "datafile",
}
build = {
  type = "builtin",
  modules = {
    ["lualibrarytemplate.dummy"] = "dummy.lua",
  },
  copy_directories = { "template" },
  install = {
    bin = {
      luacmodule = "luacmodule.lua",
    }
  } 
}

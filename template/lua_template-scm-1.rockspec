package = "lua_template"
version = "scm-1"

source = {
    url = "git://github.com/Tieske/Lua_library_template.git",
}
description = {
   summary = "Lua template for C libraries",
   detailed = [[
      Quickly setup a new C library, only a
      fill-in-the-blanks action is required to run it.
   ]],
   homepage = "https://github.com/Tieske/Lua_library_template",
   license = "MIT"
}
dependencies = {
   "lua >= 5.1, < 5.4"
}
build = {
  type = "builtin",
  modules = {
    ["lua_template"] = {
      sources = {
        "lua_template.c",
      },
    },
  },
}

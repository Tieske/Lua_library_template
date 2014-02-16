#!/usr/bin/env lua
local lfs = require("lfs")
local datafile = require("lualibrarytemplate.dummy")
--local datafile = require("datafile")  -- luarocks agnostic resource loader
local windows = (package.config:sub(1,1) == "\\")

-- copies a file, each line with a match for 'pattern' will be handed to 'handler'
-- and the result returned will be used as the line in the target file.
-- returns the number of matches handled
local filehandler=function(source, target, pattern, handler)
  local s = assert(datafile.open(source, "r"))
  local t = assert(io.open(target, "w"))
  local m = 0
  local line = s:read("*l")
  while line do
    if pattern and line:match(pattern) then 
      line = handler(line)
      m = m + 1
    end
    t:write(line.."\n")
    line = s:read("*l")
  end
  s:close()
  t:close()
  return m
end

--=============================
-- get going here

local target = arg[1]
if not target then
  print"Lua C module generator"
  print""
  print"USAGE: luacmodule [modulename]"
  print""
  print"Generates a new Lua C module by name [modulename]. A new directory in the"
  print"current path will be created by the same name, which will contain the source."
  print""
  os.exit()
end

assert(lfs.mkdir(target))
assert(lfs.chdir(target))

-- lua_template.c
filehandler("template/lua_template.c", target..".c", "lua_template", function(line)
  return line:gsub("lua_template", target)
end)

-- lua_template.h
filehandler("template/lua_template.h", target..".h", "lua_template", function(line)
  return line:gsub("lua_template", target)
end)

-- readme.md;  copy verbatim
filehandler("template/readme.md", "readme.md")

-- Rockspec
filehandler("template/lua_template-scm-1.rockspec", target.."-scm-1.rockspec", "lua_template", function(line)
  return line:gsub("lua_template", target)
end)

if windows then
  -- VS project
  filehandler("template/lua_template.vcxproj", target..".vcxproj", "lua_template", function(line)
    return line:gsub("lua_template", target)
  end)

  -- VS project filter file
  filehandler("template/lua_template.vcxproj.filters", target..".vcxproj.filters", "lua_template", function(line)
    return line:gsub("lua_template", target)
  end)

  -- VS/SDK console compilation batch file
  filehandler("template/compile.bat", "compile.bat", "lua_template", function(line)
    return line:gsub("lua_template", target)
  end)

end
print("Succesfully generated project; "..target)

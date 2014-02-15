#!/usr/bin/env lua
local lfs = require("luafilesystem")
local datafile = require("datafile")  -- luarocks agnostic resource loader
local windows = (package.config:sub(1,1) == "\\")

-- copies a file, each line with a match for 'pattern' will be handed to 'handler'
-- and the result returned will be used as the line in the target file.
-- returns the number of matches handled
local filehandler=function(source, target, pattern, handler);
  local s = assert(datafile.open(source, "r"))
  local t = assert(io.open(target, "w"))
  local m = 0
  local line = s:read("*l")
  while line do
    if pattern and file:match(pattern) then 
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

assert(lfs.mkdir(target))
assert(lfs.chdir(target))

-- lua_template.c
filehandler("lua_template.c", target..".c", "lua_template", function(line)
  return line:gsub("lua_template", target)
end

-- lua_template.h
filehandler("lua_template.h", target..".h", "lua_template", function(line)
  return line:gsub("lua_template", target)
end

-- readme.md;  copy verbatim
filehandler("readme.md", "readme.md")

-- Rockspec
filehandler("lua_template-scm-1.rockspec", target.."-scm-1.rockspec", "lua_template", function(line)
  return line:gsub("lua_template", target)
end

if windows then
  -- VS project
  filehandler("lua_template.vcxproj", target..".vcxproj", "lua_template", function(line)
    return line:gsub("lua_template", target)
  end

  -- VS project filter file
  filehandler("lua_template.vcxproj.filters", target..".vcxproj.filters", "lua_template", function(line)
    return line:gsub("lua_template", target)
  end

  -- VS/SDK console compilation batch file
  filehandler("compile.bat", "compile.bat", "lua_template", function(line)
    return line:gsub("lua_template", target)
  end

end
print("Succesfully generated project; "..target)

local udtype = require("udtype")
local typex = udtype.type

print ("Commencing module test for 'udtype'")
--io.read()

assert(typex("hello") == "string", "expected string")
assert(typex(nil) == "nil", "expected nil")
assert(typex(13) == "number", "expected number")
assert(typex(true) == "boolean", "expected boolean")
assert(typex( {} ) == "table", "expected table")

local socket = require("socket")
local sock = socket.tcp()
local sock2 = socket.tcp()
assert(typex(sock) == typex(sock2), "expected both sockets to have same metatable")

print ("Module udtype test succeeded!")

--io.read()

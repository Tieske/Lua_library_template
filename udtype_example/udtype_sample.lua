--io.read()

local socket = require("socket")
type = require("udtype").type		-- replace global type with new version


function checktype(x)
	local t,udt = type(x)
	if t == "userdata" then
		print(t, "of type", udt)
	else
		print(t)
	end
end

function shorttype(x)
	local t,udt = type(x)
	return udt or t
end

checktype("just a string")   --> string
checktype(socket.tcp())      --> userdata of type tcp{master}
checktype(socket.udp())      --> userdata of type udp{unconnected}
checktype(10)                --> number
print()
print(shorttype("just a string"))   --> string
print(shorttype(socket.tcp()))      --> tcp{master}
print(shorttype(socket.udp()))      --> udp{unconnected}
print(shorttype(10))                --> number

--io.read()
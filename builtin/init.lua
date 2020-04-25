dragonblocks = {}
dragonblocks.settings = {}

dofile("builtin/register.lua")
dofile("builtin/functions.lua")

local popenfile = io.popen("ls mods")
for modname in popenfile:lines() do
	dofile("mods/" .. modname .. "/init.lua")
end
popenfile:close()


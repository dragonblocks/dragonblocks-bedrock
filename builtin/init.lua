core = {}
dragonblocks = {}
dragonblocks.settings = {}

dofile("builtin/register.lua")
dofile("builtin/functions.lua")
dofile("builtin/cpp.lua")

--local popenfile = io.popen("ls game")
--for filename in popenfile:lines() do
--	dofile("game/"..filename.."/init.lua")
--end
--popenfile:close()

dofile("game/init.lua")

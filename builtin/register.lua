core.nodes = {}
dragonblocks.register_node = function(obj)
	if obj and obj.name and obj.texture then
		core.nodes[#core.nodes+1] = {}
		core.nodes[#core.nodes].name = obj.name
		core.nodes[#core.nodes].texture = obj.texture
		core.nodes[#core.nodes].stable = false
		if obj.stable == nil or obj.stable == true then
			core.nodes[#core.nodes].stable = true
		end
		core.nodes[#core.nodes].hidden = false
		if obj.hidden then
			core.nodes[#core.nodes].hidden = true
		end
		core.nodes[#core.nodes].translucent = false
		if obj.translucent then
			core.nodes[#core.nodes].translucent = true
		end
	end		
end

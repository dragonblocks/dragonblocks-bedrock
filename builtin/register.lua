dragonblocks.registered_nodes = {}
dragonblocks.nodes = {}
dragonblocks.register_node = function(proto)
	if proto and proto.name and proto.texture then
		local node = {}
		node.name = proto.name
		node.texture = proto.texture
		node.stable = false
		if proto.stable == nil or proto.stable == true then
			node.stable = true
		end
		node.hidden = false
		if proto.hidden then
			node.hidden = true
		end
		node.translucent = false
		if proto.translucent then
			node.translucent = true
		end
		dragonblocks.nodes[node.name] = node
		dragonblocks.registered_nodes[#dragonblocks.registered_nodes+1] = node
		
	end		
end

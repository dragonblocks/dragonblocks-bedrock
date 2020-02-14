local cpp_last_node = 0
function cpp_get_next_node()
    cpp_last_node = cpp_last_node + 1
    return core.nodes[cpp_last_node]		
end

#include "node.h"
#include "inventory.h" 
Inventory::Inventory(){
	count = 0;
	selected = 0;
	for(int i = 0; i < Node::count; i++){
		if(! Node::getNodeById(i) -> hidden){
			list[count] = Node::getNodeById(i);
			count++;
		}
	}
}
Node *Inventory::getSlot(int nr){
	if(nr >= 0 && nr < count)
		return list[nr];
	return list[0]; 
}
void Inventory::select(int nr){
	if(nr >= 0 && nr < count)
		selected = nr;
}
Node *Inventory::getSelectedSlot(){
	return list[selected];
}

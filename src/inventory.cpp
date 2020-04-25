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
	return NULL; 
}
void Inventory::select(int nr){
	if(nr >= 0 && nr < count)
		selected = nr;
}
void Inventory::selectUp(){
	select(selected - 1);
}
void Inventory::selectDown(){
	select(selected + 1);
}
Node *Inventory::getSelectedSlot(){
	return list[selected];
}

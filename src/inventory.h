#ifndef _INVENTORY_H_
#define _INVENTORY_H_

#include "node.h" 

class Inventory{
	public:
		int count;
		int selected;
		Node *list[MAXNODES];
		Node *getSlot(int);
		void select(int);
		Node *getSelectedSlot();
		Inventory();
};

#endif

#ifndef _MAP_H_
#define _MAP_H_

#include <string>

#include "node.h"

#define MAPWIDTH 500
#define MAPHEIGHT 100

class Map{
	public:
		Node *getNode(int, int);
		void setNode(int, int, Node *);
		void setNode(int, int, std::string);
		void load();
		void save();
	private: 
		Node *content[MAPWIDTH][MAPHEIGHT];
};
#endif

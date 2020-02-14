#ifndef _NODE_H_
#define _NODE_H_
#include <string>
#include "texture.h"
#define MAXNODES 1024


class Node{
	public:
		int id;
		std::string name;
		static Node *getNodeById(int);
		static Node *getNodeByName(std::string);
		static Node *list[MAXNODES];
		static int count;
		bool operator==(Node *);
		bool operator==(std::string);
		Texture *texture;
		bool hidden;
		bool stable;
		bool translucent;
		Node(std::string, std::string, bool, bool, bool);
};
#endif


#include <string>
#include <stdlib.h>
#include <iostream>
#include "node.h"
#include "game.h"
#include "texture.h"
using namespace std;

int Node::count = 0;
Node *Node::list[MAXNODES];

Node::Node(string n, string t, bool h, bool s, bool tr){
	if (Node::count >= MAXNODES)
		Game::log("Too many registered Nodes", ERROR);
	else{
		name = n;
		id = Node::count;
		hidden = h;
		stable = s;
		Node::list[id] = this;
		texture = new Texture(t,tr);
		Node::count++;
	}
}
Node *Node::getNodeById(int id){
	if(id < count && id > -1)
		return list[id];
	return list[0];	
}
Node *Node::getNodeByName(string name){
	for(int i = 0; i < count; i++){
		if(list[i]->name == name ){
			return list[i];
		}
	}
	Game::log("Node "+name+" not found", WARNING);	
	return list[0];		
}	
bool Node::operator==(Node *node){
	return id == node->id;
}
bool Node::operator==(string n){
	return name == n;
}

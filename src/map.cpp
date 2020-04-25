#include <string>
#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include "map.h"
#include "node.h"
#include "game.h"
using namespace std;
Node *Map::getNode(int x, int y){
	if(x < MAPWIDTH && y < MAPHEIGHT && x > -1 && y > -1)
		return content[x][y];
	return NULL;	
}
void Map::setNode(int x, int y, Node *n){
	if(x < MAPWIDTH && y < MAPHEIGHT && x > -1 && y > -1)
		content[x][y] = n;
}
void Map::setNode(int x, int y, string n){
	setNode(x, y, Node::getNodeByName(n));
}
void Map::load(){
	Game::log((string)"Loading Map from " + Game::worlddir + "/map");
	FILE *mapfile = fopen((Game::worlddir + "/map").c_str(), "r");
	if(mapfile){
		for(int x = 0; x < MAPWIDTH; x++)
			for(int y = 0; y < MAPHEIGHT; y++){
				char buffer[512] = {0};
				fscanf(mapfile, "%s", buffer);
				setNode(x, y, buffer);
			}
		fclose(mapfile);
		Game::log("Loaded Map");
	}
	else{
		Game::log("Could not Load Map.", ERROR);
		exit(EXIT_FAILURE);
	}
}
void Map::save(){
	Game::log((string)"Saving Map to " + Game::worlddir + "/map");
	FILE *mapfile = fopen((Game::worlddir + "/map").c_str(), "w");
	if(mapfile){
		for(int x = 0; x < MAPWIDTH; x++){
			for(int y = 0; y < MAPHEIGHT; y++)
				fprintf(mapfile,"%s ", getNode(x,y)->name.c_str());
			fprintf(mapfile, "\n");
		}
		fclose(mapfile);
		Game::log("Saved Map");
	}
	else
		Game::log("Could not Save Map.", ERROR);
}

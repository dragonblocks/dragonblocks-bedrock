#include <string>
#include <iostream>
#include <stdlib.h>
#include <math.h>  

#include "mapgen.h"
#include "map.h"
#include "node.h"
#include "util.h"
#include "game.h"

using namespace std;
void Mapgen(){
	Game::log("Generating Map");
	//Air
	for(int x = 0; x < MAPWIDTH; x++){
		for(int y = 0; y < MAPHEIGHT; y++){
			Game::map->setNode(x,y,MAPGEN_AIR);
			}
		}
	//Seed 13 Easteregg
	if(Game::seed == 13){
		for(int x = 0; x < MAPWIDTH; x++){
			for(int y = 0; y < MAPHEIGHT; y++){
				Game::map->setNode(x,y,MAPGEN_BEDROCK);
			}
		}
		Game::log("LOL Seed 13", EASTEREGG);
		return;
	}
	//Bottom
	int bottom[MAPWIDTH];
	bottom[0] = random(MAPHEIGHT/2 - MAPHEIGHT/10, MAPHEIGHT/2);
	for(int x = 1; x < MAPWIDTH; x++){
		bottom[x] = bottom[x-1] + random(-1,1);
		}
	//Smooth	
	for(int x = 1; x < MAPWIDTH-1; x++){
		if(bottom[x] > bottom[x+1] && bottom[x] > bottom[x-1]) bottom[x]--;
		else if(bottom[x] < bottom[x+1] && bottom[x] < bottom[x-1])bottom[x]++;	
		}
	//Dirt with Grass
	for(int x = 0; x < MAPWIDTH; x++){
		Game::map->setNode(x,bottom[x],MAPGEN_GRASS);
		}
	//Dirt 		
	for(int x = 0; x < MAPWIDTH; x++){
		for(int y = bottom[x]+1; y < bottom[x]+5; y++){
			Game::map->setNode(x,y,MAPGEN_DIRT);
			}
		}
	//Stone
	for(int x = 0; x < MAPWIDTH; x++){
		for(int y = bottom[x]+5; y < MAPHEIGHT; y++){
			Game::map->setNode(x,y,MAPGEN_STONE);
			}
		}
	//Mese
	for(int x = 0; x < MAPWIDTH; x++){
		for(int y = bottom[x]+10; y < MAPHEIGHT; y++){
			if((rand() % 100) == 0) Game::map->setNode(x,y,MAPGEN_MESE);
			}
		}		
	//Bedrock
	for(int x = 0; x < MAPWIDTH; x++){
		Game::map->setNode(x,MAPHEIGHT-1,MAPGEN_BEDROCK);
		if(random(0,1) == 0){
			Game::map->setNode(x,MAPHEIGHT-2,MAPGEN_BEDROCK);
			if(random(0,2) == 0){
				Game::map->setNode(x,MAPHEIGHT-3,MAPGEN_BEDROCK);
				}
			}
		}
	//Water
	int flatcount = 0;
	for(int x = 1; x < MAPWIDTH; x++){
		if(bottom[x] == bottom[x-1]) flatcount++;
		else if(flatcount > 7){
			int leftborder = rand() % 2;
			int rightborder = rand() % 2;
			for(int mx = x-flatcount-3; mx < x+2; mx++){
				for(int y = bottom[mx];y < bottom[mx]+5;y++){
					if(Game::map->getNode(mx,y) == MAPGEN_STONE) break;
					if(Game::map->getNode(mx,y) == MAPGEN_DIRT || Game::map->getNode(mx,y) == MAPGEN_GRASS) Game::map->setNode(mx,y,MAPGEN_SAND);
					}
				}
			for(int mx = x-flatcount+leftborder;mx < x-1-rightborder;mx++) Game::map->setNode(mx,bottom[x-1],MAPGEN_WATER);
			for(int mx = x-flatcount+1+leftborder;mx < x-2-rightborder;mx++) Game::map->setNode(mx,bottom[x-1]+1,MAPGEN_WATER);
			for(int mx = x-flatcount+2+leftborder; mx < x-3-rightborder;mx++) Game::map->setNode(mx,bottom[x-1]+2,MAPGEN_WATER);
			flatcount = 0;
			}
		else flatcount = 0;
		}	
	//Tree
	int treecount = rand() % MAPWIDTH/10;
	int treepos[treecount];
	for(int i = 0; i < treecount; i++){
		while(true){
			bool cont = true;
			treepos[i] = rand() % MAPWIDTH;
			for(int j = 0; j < i; j++){
				if(abs(treepos[j]-treepos[i]) < 3) cont = false; 
				}
			if(!(Game::map->getNode(treepos[i],bottom[treepos[i]]) == MAPGEN_GRASS)) cont = false; 	
			if(cont) break;	
			}
		int x = treepos[i];
		int y = bottom[x] - 1;	
		Game::map->setNode(x,y,MAPGEN_WOOD);
		Game::map->setNode(x,y-1,MAPGEN_WOOD);
		Game::map->setNode(x,y-2,MAPGEN_LEAVES);
		Game::map->setNode(x,y-3,MAPGEN_LEAVES);
		Game::map->setNode(x,y-4,MAPGEN_LEAVES);
		Game::map->setNode(x-1,y-2,MAPGEN_LEAVES);
		Game::map->setNode(x-1,y-3,MAPGEN_LEAVES);
		Game::map->setNode(x-1,y-4,MAPGEN_LEAVES);
		Game::map->setNode(x+1,y-2,MAPGEN_LEAVES);
		Game::map->setNode(x+1,y-3,MAPGEN_LEAVES);
		Game::map->setNode(x+1,y-4,MAPGEN_LEAVES);	
		}
	}

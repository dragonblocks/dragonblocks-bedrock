#ifndef _MAPGEN_H_
#define _MAPGEN_H_

#include "map.h"

#define MAPGEN_AIR Node::getNodeByName("dragonblocks:air")
#define MAPGEN_GRASS Node::getNodeByName("dragonblocks:grass")
#define MAPGEN_DIRT Node::getNodeByName("dragonblocks:dirt")
#define MAPGEN_STONE Node::getNodeByName("dragonblocks:stone")
#define MAPGEN_BEDROCK Node::getNodeByName("dragonblocks:bedrock")
#define MAPGEN_MESE Node::getNodeByName("dragonblocks:mese")
#define MAPGEN_LEAVES Node::getNodeByName("dragonblocks:leaves")
#define MAPGEN_WOOD Node::getNodeByName("dragonblocks:wood")
#define MAPGEN_WATER Node::getNodeByName("dragonblocks:water")
#define MAPGEN_SAND Node::getNodeByName("dragonblocks:sand")

void Mapgen();



#endif

#include <iostream>
#include <math.h>
#include "texture.h"
#include "entity.h"
#include "player.h"
#include "map.h"
#include "mapgen.h"
#include "graphics.h"
#include "game.h"
using namespace std;
Player::Player(){
	name = "player";
	texture = new Texture("textures/player.png", true);
	width = 1;
	height = 2;
	int spawnposX = MAPWIDTH / 2;
	int spawnposY = MAPHEIGHT - 2;
	while((Game::map->getNode(spawnposX, spawnposY) != MAPGEN_AIR) || (Game::map->getNode(spawnposX, spawnposY + 1) != MAPGEN_AIR))
		spawnposY--;
	spawn(spawnposX, spawnposY, true);
	inventory = new Inventory();
}
void Player::left(){
	if(vx == -PLAYER_SPEED)
		return;
	physics_reset_x();
	vx = -PLAYER_SPEED;
}
void Player::right(){
	if(vx == PLAYER_SPEED)
		return;
	physics_reset_x();
	vx = PLAYER_SPEED;
}
void Player::stop(){
	physics_reset_x();
}
void Player::jump(){
	vy = -PLAYER_JUMPSPEED;
}

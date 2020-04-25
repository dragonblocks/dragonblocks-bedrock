#include <string>
#include <math.h>
#include "game.h"
#include "entity.h"
#include "texture.h"
#include "graphics.h"
#include <iostream>
using namespace std;
Entity *Entity::list[MAX_ENTITIES];
double Entity::t = 0;
int Entity::count;
Entity::Entity(){
	if(Entity::count < MAX_ENTITIES){
		Entity::list[Entity::count] = this;
		Entity::count++;
	}
	else 
		for(int i = 0; i < MAX_ENTITIES; i++)
			if(Entity::list[i] == NULL)
				Entity::list[i] = this;
}
void Entity::physics_all(){
	for(int i = 0; i < count; i++)
		if(list[i] == NULL)
			continue;
		else
			list[i]->physics();
}
void Entity::spawn(double sx, double sy, bool gravity){
	x = sx;
	y = sy;
	ax = 0;
	ay = 0;
	if(gravity)
		ay = GRAVITY;
	physics_reset_x();
	physics_reset_y();
	Game::log((string)"Spawning entity '" + name + "' at (" + to_string(x) + ", " + to_string(y) + ")", INFO);
}
bool Entity::physics_check_x(){
	if(x < 0)
		return false;
	if(x + width > MAPWIDTH)
		return false;
	return physics_check_both();
}
bool Entity::physics_check_y(){
	if(y < 0)
		return false;
	if(y + height > MAPHEIGHT)
		return false;
	return physics_check_both();
}
bool Entity::physics_check_both(){
	for(int ix = floor(x); ix <= ceil(x + width - 0.01) - 1; ix++)
		for(int iy = floor(y); iy <= ceil(y + height - 0.01) - 1; iy++)
			if(Game::map->getNode(ix, iy)->stable)
				return false;
	return true;
}
void Entity::physics_reset_x(){
	vx = 0;
	tx0 = Entity::t;
	x0 = x;
	x = (double)(round(x * 10)) / 10;
}
void Entity::physics_reset_y(){
	vy = 0;
	ty0 = Entity::t;
	y0 = y;
	y = (double)(round(y * 10)) / 10;
}
void Entity::physics(){
	double old_x = x;
	double dtx = Entity::t - tx0;
	if(ax)
		x = ax * dtx * dtx / 2 + vx * dtx + x0;
	else if(vx)
		x = vx * dtx + x0;
	if(!physics_check_x())
	{
		x = old_x;
		physics_reset_x();
	}
	double old_y = y;
	double dty = Entity::t - ty0;
	if(ay)
		y = ay * dty * dty / 2 + vy * dty + y0;
	else if(vy)
		y = vy * dty + y0;
	if(!physics_check_y())
	{
		y = old_y;
		physics_reset_y();
	}
}

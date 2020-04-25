#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "entity.h"
#include "inventory.h"
#define PLAYER_SPEED 4
#define PLAYER_JUMPSPEED 6
class Player : public Entity{
	public:
		void left();
		void right();
		void jump();
		void stop();
		Inventory *inventory;
		Player();
};
#endif

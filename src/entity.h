#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <string>
#include "texture.h"
#include "util.h"
#define MAX_ENTITIES 16
#define GRAVITY 9.81
class Entity{
	public:
		std::string name;
		Texture *texture;
		double width;
		double height;
		double x;
		double y;
		double tx0;
		double vx;
		double x0;
		double ax;
		double ty0;
		double vy;
		double y0;
		double ay;
		void physics();
		void physics_reset_x();
		void physics_reset_y();
		bool physics_check_x();
		bool physics_check_y();
		bool physics_check_both();
		void spawn(double, double, bool);
		Entity();
		static Entity *list[MAX_ENTITIES];
		static int count;
		static double t;
		static void physics_all();
};
#endif

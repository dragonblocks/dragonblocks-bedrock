#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <string>
#include "texture.h"
#include "util.h"


#define BLOCKWIDTH 32
#define DISPLAYWIDTH 25
#define DISPLAYHEIGHT 25
#define INVBLOCKWIDTH 64
#define INVWIDTH 80

#define COLOR_WHITE {1,1,1}
#define COLOR_BLACK {0,0,0}


class Graphics{
	public:
		static void init();
		
		static position pointed;
		static position pos;
		
		//handlers
		static void display();
		static void keyboard(unsigned char, int, int);
		static void mouse(int, int, int, int);
		static void special(int, int, int);
		static void reshape(int, int);
		static void motion(int, int);
		
		//functions
		static void drawRectangle(int, int, int, int, color);
		static void writeText(int, int, std::string, void*, color);
};
#endif

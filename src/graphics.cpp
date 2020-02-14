#include <GL/freeglut.h>
#include <cstring>
#include <string>
#include <iostream>
#include "graphics.h"
#include "util.h"
#include "game.h"
#include "mapgen.h"

position Graphics::pointed;
position Graphics::pos = {MAPWIDTH/2 - DISPLAYWIDTH/2, MAPHEIGHT/2 - DISPLAYHEIGHT/2};

using namespace std;
void Graphics::display(){
	glClear(GL_COLOR_BUFFER_BIT);
	//sky
	drawRectangle(0, 0, DISPLAYWIDTH*BLOCKWIDTH, DISPLAYHEIGHT*BLOCKWIDTH, "#87CEEB");
	//map
	for(int x = 0; x < DISPLAYWIDTH; x++){
		for(int y = 0; y < DISPLAYHEIGHT; y++){
			Game::map -> getNode(x+pos.x, y+pos.y) -> texture -> draw(x*BLOCKWIDTH, y*BLOCKWIDTH, BLOCKWIDTH, BLOCKWIDTH);
		}
	}
	//pointed block
	if(pointed.x < DISPLAYWIDTH){
		drawRectangle(pointed.x * BLOCKWIDTH, pointed.y * BLOCKWIDTH, BLOCKWIDTH, 1, COLOR_BLACK);
		drawRectangle(pointed.x * BLOCKWIDTH + BLOCKWIDTH - 1, pointed.y * BLOCKWIDTH, 1, BLOCKWIDTH, COLOR_BLACK);
		drawRectangle(pointed.x * BLOCKWIDTH, pointed.y * BLOCKWIDTH + BLOCKWIDTH - 1, BLOCKWIDTH, 1, COLOR_BLACK);
		drawRectangle(pointed.x * BLOCKWIDTH, pointed.y * BLOCKWIDTH, 1, BLOCKWIDTH, COLOR_BLACK);
	}
	//inventory
	
	drawRectangle(DISPLAYWIDTH*BLOCKWIDTH, 0, INVWIDTH, DISPLAYHEIGHT*BLOCKWIDTH, "#B4B4B4");
	drawRectangle(DISPLAYWIDTH*BLOCKWIDTH, Game::inventory->selected * INVWIDTH, INVWIDTH, INVWIDTH, "#636363");
	for(int i = 0; i < Game::inventory->count; i++)
		Game::inventory -> getSlot(i) -> texture -> draw(BLOCKWIDTH*DISPLAYWIDTH + (INVWIDTH-INVBLOCKWIDTH)/2, i * INVWIDTH + (INVWIDTH-INVBLOCKWIDTH)/2, INVBLOCKWIDTH, INVBLOCKWIDTH);
	//infotext
	writeText(5, 5, (string)"Dragonblocks "+VERSION, GLUT_BITMAP_9_BY_15, COLOR_WHITE);
	string infotext = "pos: ("+to_string(pos.x)+", "+to_string(pos.y)+"), seed: "+to_string(Game::seed);
	if(pointed.x < DISPLAYWIDTH)
		infotext += ", pointed: "+ Game::map->getNode(pointed.x+pos.x, pointed.y+pos.y)->name + "("+to_string(pointed.x+pos.x)+", "+to_string(pointed.y+pos.y)+")";
	writeText(5, 20, infotext, GLUT_BITMAP_9_BY_15, COLOR_WHITE);
	//writeText(5, 35, "world: "+Game::mapfile, GLUT_BITMAP_9_BY_15, COLOR_WHITE);
	glFlush();
}
void Graphics::reshape(int width, int height){
	glViewport(0, 0, width, height);       /* Establish viewing area to cover entire window. */
	glMatrixMode(GL_PROJECTION);  /* Start modifying the projection matrix. */
	glLoadIdentity();             /* Reset project matrix. */
	glOrtho(0, width, 0, height, -1, 1);   /* Map abstract coords directly to window coords. */
	glScalef(1, -1, 1);           /* Invert Y axis so increasing Y goes down. */
	glTranslatef(0, -height, 0);       /* Shift origin up to upper-pos.x corner. */
}
void Graphics::init(){
	glutInit(Game::argc, Game::argv);
	glutCreateWindow("Dragonblocks");
	glutReshapeWindow(DISPLAYWIDTH*BLOCKWIDTH+INVWIDTH, DISPLAYHEIGHT*BLOCKWIDTH);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);
	glutMotionFunc(motion);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glutMainLoop();
}
void Graphics::keyboard(unsigned char key, int x, int y){
}
void Graphics::special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
			if(pos.x > 0)
				pos.x--;
			break;
		case GLUT_KEY_UP:
			if(pos.y > 0)
				pos.y--;
			break;
		case GLUT_KEY_RIGHT:
			if(pos.x < MAPWIDTH-DISPLAYWIDTH)
				pos.x++;
			break;
		case GLUT_KEY_DOWN:
			if(pos.y < MAPHEIGHT-DISPLAYHEIGHT)
				pos.y++;
			break;
	}
}
void Graphics::mouse(int key, int action, int x, int y){
	if(action == 0){
		if(x < BLOCKWIDTH*DISPLAYWIDTH){
			switch(key){
				case 0:
					if(Game::map -> getNode(pointed.x+pos.x, pointed.y+pos.y)->stable)
						Game::map -> setNode(pointed.x+pos.x, pointed.y+pos.y, MAPGEN_AIR);
					break;
				case 2:
					if(! Game::map -> getNode(pointed.x+pos.x, pointed.y+pos.y)->stable)
						Game::map -> setNode(pointed.x+pos.x, pointed.y+pos.y, Game::inventory->getSelectedSlot());
					break;
			}
		}
		else{
			Game::inventory->select(y/INVWIDTH);
		}
	}
}
void Graphics::motion(int x, int y){
	pointed.x = x / BLOCKWIDTH;
	pointed.y = y / BLOCKWIDTH;
}
void Graphics::writeText(int x, int y, string text, void *font, color c){
	glColor3f(c.red, c.green, c.blue);
	glRasterPos2i(x, y+10);
	char *s = strdup(text.c_str());
	--s;
	while(*++s)
		glutBitmapCharacter(font, *s);
}
void Graphics::drawRectangle(int x, int y, int width, int height, color c){
	glColor3f(c.red, c.green, c.blue);
	glBegin(GL_POLYGON);
	glVertex2i(x, y);
	glVertex2i(x+width, y);
	glVertex2i(x+width, y+height);
	glVertex2i(x, y+height);
	glEnd();
}

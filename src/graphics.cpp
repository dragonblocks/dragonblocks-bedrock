#include <GL/freeglut.h>
#include <cstring>
#include <string>
#include <iostream>
#include "graphics.h"
#include "util.h"
#include "game.h"
#include "mapgen.h"
#include "entity.h"

position Graphics::pointed;
position Graphics::scroll = {MAPWIDTH/2 - DISPLAYWIDTH/2, MAPHEIGHT/2 - DISPLAYHEIGHT/2};
int Graphics::inventory_scroll;

using namespace std;
void Graphics::drawSky(){
	drawRectangle(0, 0, DISPLAYWIDTH*BLOCKWIDTH, DISPLAYHEIGHT*BLOCKWIDTH, "#87CEEB");
}
void Graphics::drawMap(){
	for(int x = 0; x < DISPLAYWIDTH; x++){
		for(int y = 0; y < DISPLAYHEIGHT; y++){
			Game::map -> getNode(x+scroll.x, y+scroll.y) -> texture -> draw(x*BLOCKWIDTH, y*BLOCKWIDTH, BLOCKWIDTH, BLOCKWIDTH);
		}
	}
}
void Graphics::drawEntities(){
	for(int i = 0; i < Entity::count; i++){
		if(Entity::list[i] == NULL)
			continue;
		Entity *entity = Entity::list[i];
		entity -> texture -> draw((entity->x - scroll.x) * BLOCKWIDTH, (entity->y - scroll.y) * BLOCKWIDTH, entity->width * BLOCKWIDTH, entity->height * BLOCKWIDTH);	
	}
}
void Graphics::drawPointedBlock(){
	if(pointed.x < DISPLAYWIDTH){
		drawRectangle(pointed.x * BLOCKWIDTH, pointed.y * BLOCKWIDTH, BLOCKWIDTH, 1, COLOR_BLACK);
		drawRectangle(pointed.x * BLOCKWIDTH + BLOCKWIDTH - 1, pointed.y * BLOCKWIDTH, 1, BLOCKWIDTH, COLOR_BLACK);
		drawRectangle(pointed.x * BLOCKWIDTH, pointed.y * BLOCKWIDTH + BLOCKWIDTH - 1, BLOCKWIDTH, 1, COLOR_BLACK);
		drawRectangle(pointed.x * BLOCKWIDTH, pointed.y * BLOCKWIDTH, 1, BLOCKWIDTH, COLOR_BLACK);
	}
}
void Graphics::drawInventory(){
	Inventory *inv = Game::player->inventory;
	int x = DISPLAYWIDTH*BLOCKWIDTH;
	drawRectangle(x, 0, INVWIDTH, DISPLAYHEIGHT*BLOCKWIDTH, "#B4B4B4");
	drawRectangle(x, (inv->selected - inventory_scroll) * INVWIDTH, INVWIDTH, INVWIDTH, "#636363");
	x = BLOCKWIDTH*DISPLAYWIDTH + (INVWIDTH-INVBLOCKWIDTH)/2;
	int yf = (INVWIDTH-INVBLOCKWIDTH)/2;
	for(int i = 0; i < Game::player->inventory->count; i++){
		int nr = i + inventory_scroll;
		if(inv -> getSlot(nr))
			inv -> getSlot(nr) -> texture -> draw(x, i * INVWIDTH + yf, INVBLOCKWIDTH, INVBLOCKWIDTH);
		else
			drawRectangle(x, i * INVWIDTH + yf, INVBLOCKWIDTH, INVBLOCKWIDTH, "#3E3E3E");
	}
}
void Graphics::drawInfotext(){
	writeText(5, 5, (string)"Dragonblocks "+VERSION, GLUT_BITMAP_9_BY_15, COLOR_WHITE);
	string infotext = "pos: ("+to_string(Game::player->x)+", "+to_string(Game::player->y)+") | seed: "+to_string(Game::seed);
	if(pointed.x < DISPLAYWIDTH)
		infotext += " | pointed: "+ Game::map->getNode(pointed.x+scroll.x, pointed.y+scroll.y)->name + "("+to_string(pointed.x+scroll.x)+", "+to_string(pointed.y+scroll.y)+")";
	writeText(5, 20, infotext, GLUT_BITMAP_9_BY_15, COLOR_WHITE);
}
void Graphics::display(){
	glClear(GL_COLOR_BUFFER_BIT);
	drawSky();
	drawEntities();
	drawMap();
	drawPointedBlock();
	drawInventory();
	drawInfotext();
	glFlush();
}
void Graphics::reshape(int width, int height){
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
	glScalef(1, -1, 1);
	glTranslatef(0, -height, 0);
}
void Graphics::init(){
	glutInit(Game::argc, Game::argv);
	glutCreateWindow("Dragonblocks");
	glutReshapeWindow(DISPLAYWIDTH*BLOCKWIDTH+INVWIDTH, DISPLAYHEIGHT*BLOCKWIDTH);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutSpecialUpFunc(special_up);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);
	glutMotionFunc(motion);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glutMainLoop();
}
void Graphics::keyboard(unsigned char key, int x, int y){
	switch(key){
		case ' ':
			Game::player->jump();
			break;
	}
}
void Graphics::special(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
			Game::player->left();
			break;
		case GLUT_KEY_RIGHT:
			Game::player->right();
			break;
		case GLUT_KEY_UP:
			Game::player->inventory->selectUp();
			ajustInventoryScroll();
			break;
		case GLUT_KEY_DOWN:
			Game::player->inventory->selectDown();
			ajustInventoryScroll();
			break;
	}
}
void Graphics::special_up(int key, int x, int y){
	switch(key){
		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			Game::player->stop();
			break;
	}
}
void Graphics::ajustScroll(){
	if(Game::player->y - scroll.y < 2)
		if(scroll.y > 0)
			scroll.y--;
	if(Game::player->x - scroll.x < 2)
		if(scroll.x > 0)
			scroll.x--;
	if(scroll.y + DISPLAYHEIGHT - Game::player->y - Game::player->height < 2)
		if(scroll.y < MAPHEIGHT-DISPLAYHEIGHT)
			scroll.y++;
	if(scroll.x + DISPLAYWIDTH - Game::player->x - Game::player->width < 2)
		if(scroll.x < MAPWIDTH-DISPLAYWIDTH)
			scroll.x++;
}
void Graphics::ajustInventoryScroll(){
	Inventory *inv = Game::player->inventory;
	int invblocks_displayed = DISPLAYHEIGHT * BLOCKWIDTH / INVWIDTH;
	if(inv->selected < inventory_scroll)
		inventory_scroll = inv->selected;
	else if(inv->selected >= inventory_scroll + invblocks_displayed)
		inventory_scroll = inv->selected - invblocks_displayed + 1;
}
void Graphics::mouse(int key, int action, int x, int y){
	if(action == 0){
		if(x < BLOCKWIDTH*DISPLAYWIDTH){
			switch(key){
				case 0:
					if(Game::map -> getNode(pointed.x+scroll.x, pointed.y+scroll.y)->stable)
						Game::map -> setNode(pointed.x+scroll.x, pointed.y+scroll.y, MAPGEN_AIR);
					break;
				case 2:
					if(! Game::map -> getNode(pointed.x+scroll.x, pointed.y+scroll.y)->stable)
						Game::map -> setNode(pointed.x+scroll.x, pointed.y+scroll.y, Game::player->inventory->getSelectedSlot());
					break;
			}
		}
		else{
			Game::player->inventory->select(y/INVWIDTH + inventory_scroll);
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

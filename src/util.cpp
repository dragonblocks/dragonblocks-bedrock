#include <stdlib.h>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <string>

#include "util.h"
#include "game.h"

using namespace std;
int random(int min, int max){
	return min + rand() % (max - min + 1);
}
color::color(const char *htmlcolor){
	unsigned int r, g, b;
	sscanf(htmlcolor, "#%2x%2x%2x", &r, &g, &b);
	red = (float) r / 255;
	green = (float) g / 255;
	blue = (float) b / 255;
}
color::color(float r, float g, float b){
	red = r;
	green = g;
	blue = b;
}
void create_dir_if_not_exists(string d){
	const char *dir = d.c_str();
	struct stat dir_exists_st = {0};	
	if(stat(dir, &dir_exists_st) == -1){
		Game::log((string)dir + " doesn't exist, creating", INFO);
		#ifdef _WIN32
		mkdir(dir);
		#else
		mkdir(dir, 0700);
		#endif
	}
}

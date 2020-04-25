#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <cstdio>
#include "map.h"
#include "inventory.h"
#include "player.h"

#define WARNING 1
#define ERROR 2
#define INFO -1
#define EASTEREGG 17
#define LOG 0

#define CODE_BLACK 0
#define CODE_RED 1
#define CODE_GREEN 2
#define CODE_ORANGE 3
#define CODE_BLUE 4
#define CODE_VIOLET 5
#define CODE_LIGHTBLUE 6
#define CODE_GREY 7

#define VERSION "3.2-dev"

class Game{
	public:
		static int *argc;
		static char **argv;
		static int seed;
		static std::string worlddir;
		static std::string logfile_path;
		static FILE *logfile;
		static Map *map;
		static void save();
		static void log(std::string);
		static void log(std::string, int);
		static void help();
		static void version();
		static void worldlist();
		static std::string userdir;
		static Player *player;
};

#endif

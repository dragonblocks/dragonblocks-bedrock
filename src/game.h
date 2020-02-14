#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <cstdio>

#include "map.h"
#include "inventory.h"

#define WARNING 1
#define ERROR 2
#define INFO -1
#define EASTEREGG 17
#define LOG 0

#define VERSION "3.0"

#define BLACK 0
#define RED 1
#define GREEN 2
#define ORANGE 3
#define BLUE 4
#define VIOLET 5
#define LIGHTBLUE 6
#define GREY 7

class Game{
	public:
		static int *argc;
		static char **argv;
		static int seed;
		static std::string mapfile;
		static std::string logfile;
		static FILE *logfile_fd;
		static Map *map;
		static void log(std::string);
		static void log(std::string, int);
		static void help();
		static void version();
		static void worldlist();
		static Inventory *inventory;
};

#endif

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>
#include <iostream>
#include <cstdio> 
#include <unistd.h>
#include "graphics.h"
#include "map.h"
#include "game.h"
#include "node.h"
#include "mapgen.h"
#include "mods.h"
#include "threads.h"
#include "inventory.h"

using namespace std;

Map *Game::map;
string Game::mapfile;
string Game::logfile;
int Game::seed;
char **Game::argv;
int *Game::argc;
FILE *Game::logfile_fd;
Inventory *Game::inventory;

int main(int argc, char **argv){
	if((string)argv[0] != "bin/dragonblocks"){
		string command = "cd ..; bin/dragonblocks -w world ";
		while(*++argv)
			command += *argv;
		exit(system(command.c_str()));
	}
	create_dir_if_not_exists((string)getenv("HOME")+"/.dragonblocks");
	create_dir_if_not_exists((string)getenv("HOME")+"/.dragonblocks/worlds");
	Game::argc = &argc;
	Game::argv = argv;
	Game::seed = time(0);
	Game::logfile = (string)getenv("HOME")+"/.dragonblocks/dragonblocks.log";
	const char *short_options = "hrvs:l:w:p:";
	const struct option long_options[] = {
		{"help", 0, NULL, 'h'},
		{"version", 0, NULL, 'v'},
		{"worldname", 1, NULL, 'w'},
		{"worldpath", 1, NULL, 'p'},
		{"worldlist", 0, NULL, 'r'},
		{"seed", 1, NULL, 's'},
		{"logfile", 1, NULL, 'l'},
		{NULL, 0, NULL, 0},
	};
	int next_option;
	while((next_option = getopt_long(argc, argv, short_options, long_options, NULL)) != -1){
		switch(next_option){
			case 'h':
				Game::help();
				exit(EXIT_SUCCESS);
				break;
			case 'v':
				Game::version();
				exit(EXIT_SUCCESS);
				break;
			case 'p':
				Game::mapfile = optarg;
				break;
			case 'w':
				Game::mapfile = (string)getenv("HOME")+"/.dragonblocks/worlds/"+optarg;
				break;
			case 's':
				Game::seed = atoi(optarg);
				break;
			case 'l':
				Game::logfile = optarg;
				break;
			case 'r':
				Game::worldlist();
				exit(0);
				break;	
			case '?':
				Game::log("Invalid Usage", ERROR);
				Game::help();
				exit(EXIT_FAILURE);
				break;
		};
	}
	if(Game::logfile_fd = fopen(Game::logfile.c_str(), "a"))
		fprintf(Game::logfile_fd, "\n--------------------------------------------------\n");
	else
		Game::log((string)"Failed to open log file " + Game::logfile, WARNING);
	Game::log((string)"Welcome to Dragonblocks "+VERSION);
	srand(Game::seed);
	new Node("unknown_node", "textures/unknown_node.png", true, true, false);
	Mods::init();
	Game::inventory = new Inventory();
	Game::map = new Map();
	if(Game::mapfile == ""){
		Game::log("No World Specified", ERROR);
		exit(EXIT_FAILURE);
	}
	if(fopen(Game::mapfile.c_str(), "r"))
		Game::map->load();
	else
		Mapgen();
	Threads::startMapBackupThread();
	Threads::startGraphicUpdateThread();
	Threads::addSignalHandlers();
	Graphics::init();
	Game::log("Closed Window, Exiting.");
	Game::map -> save();
	return 0;
}


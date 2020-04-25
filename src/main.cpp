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
#include "player.h"

using namespace std;

int main(int argc, char **argv){
	Game::argc = &argc;
	Game::argv = argv;
	Game::userdir = (string)getenv("HOME")+"/.dragonblocks";
	Game::logfile_path = Game::userdir + "/dragonblocks.log";
	create_dir_if_not_exists(Game::userdir);
	create_dir_if_not_exists(Game::userdir + "/worlds");
	Game::seed = time(0);
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
				Game::worlddir = optarg;
				break;
			case 'w':
				Game::worlddir = Game::userdir + "/worlds/" + optarg;
				break;
			case 's':
				Game::seed = atoi(optarg);
				break;
			case 'l':
				Game::logfile_path = optarg;
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
	if(Game::logfile = fopen(Game::logfile_path.c_str(), "a"))
		fprintf(Game::logfile, "\n--------------------------------------------------\n");
	else
		Game::log((string)"Failed to open log file " + Game::logfile_path, WARNING);
	Game::log((string)"Welcome to Dragonblocks "+VERSION);
	if(Game::worlddir == ""){
		Game::log("No World Specified", ERROR);
		exit(EXIT_FAILURE);
	}
	create_dir_if_not_exists(Game::worlddir);
	new Node("unknown_node", "textures/unknown_node.png", true, true, false);
	Mods::init();
	Mods::nodedef();
	Game::map = new Map();
	srand(Game::seed);
	if(fopen((Game::worlddir + "/map").c_str(), "r"))
		Game::map->load();
	else
		Mapgen();
	Game::player = new Player();
	Threads::add_signal_handlers();
	Threads::start(Threads::worldBackupThread);
	Threads::start(Threads::graphicRedrawThread);
	Threads::start(Threads::entityPhysicsThread);
	Graphics::init();
	Game::log("Closed Window, Exiting.");
	Game::save();
	return 0;
}


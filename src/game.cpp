#include <string>
#include <iostream>
#include <cstdio>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "mods.h"
#include "game.h"
using namespace std;

void Game::log(string text, int level){
	string prefix;
	int color;
	switch(level){
		case WARNING: 
			color = ORANGE;
			prefix = "WARNING"; 
			break;
		case ERROR:
			color = RED;
			prefix = "ERROR"; 
			break;
		case INFO:
			color = LIGHTBLUE;
			prefix = "INFO"; 
			break;
		case LOG:
			color = BLUE;
			prefix = "LOG"; 
			break;
		case EASTEREGG:
			color = VIOLET;
			prefix = "EASTEREGG";
		default: break;
	}
	cout << "\e[3" << color << "m" << "[" << prefix << "] \e[0m" << text << endl;
	if(logfile_fd)
		fprintf(logfile_fd, "[%s] %s\n", prefix.c_str(), text.c_str());
}
void Game::log(string text){
	log(text, LOG);
}
void Game::help(){
	cout << "Usage: " << argv[0] << "[OPTIONS]" << endl;
	cout << "Options:" << endl;
	cout << "\t" << "-h" << "\t" << "--help" << "\t\t\t" << "Display this help and exit." << endl;
	cout << "\t" << "-v" << "\t" << "--version" << "\t\t" << "Display version info." << endl;
	cout << "\t" << "-p" << "\t" << "--worldpath [PATH]" << "\t" << "Set world path." << endl;
	cout << "\t" << "-w" << "\t" << "--worldname [PATH]" << "\t" << "Select world by name (Worlds are placed in ~/.dragonblocks/worlds/)." << endl;
	cout << "\t" << "-r" << "\t" << "--worldlist" << "\t\t" << "Show a list of your worlds." << endl;
	cout << "\t" << "-s" << "\t" << "--seed [NUMBER]" << "\t\t" << "Set seed." << endl;
	cout << "\t" << "-l" << "\t" << "--logfile [PATH]" << "\t" << "Set logfile." << endl;
}
void Game::version(){
	cout << "DRAGONBLOCKS BEDROCK EDITION" << endl;
	cout <<	"Written in C++" << endl;
	cout << "An Open Source Project by Elias Fleckenstein" << endl;
	cout << "Dragonblocks " << VERSION << endl;
}
void Game::worldlist(){
	log("Your worlds:");
	DIR *folder;
    struct dirent *entry;
    int files = 0;

    folder = opendir(((string)getenv("HOME")+"/.dragonblocks/worlds/").c_str());
    if(!folder){
		Game::log("Cant Open World Directory", ERROR);
		exit(EXIT_FAILURE);
	}
    while(entry = readdir(folder))
    {
        files++;
		if(files > 2)
			cout << "\t" << entry->d_name;
    }
	if(files <= 2)
		cout << "\tYou have no Worlds yet.";
    cout << endl;
	closedir(folder);

    return;
}

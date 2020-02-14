#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <GL/glut.h>
#include <iostream>
#include <algorithm>
#include "threads.h"
#include "graphics.h"
#include "game.h"


using namespace std;

void Threads::startMapBackupThread(){
	Game::log("Starting Map Backup Thread");
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, &mapBackupThread, NULL);
}
void *Threads::mapBackupThread(void *unused){
	while(true){
		sleep(MAP_BACKUP_INTERVAL);
		Game::map -> save();
	}
	return NULL;
}
void Threads::startGraphicUpdateThread(){
	Game::log("Starting Graphic Update Thread");
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, &graphicUpdateThread, NULL);
}
void *Threads::graphicUpdateThread(void *unused){
	while(true){
		usleep(1);
		if(glutGetWindow())
			glutPostRedisplay();
	}
	return NULL;
}
void Threads::addSignalHandlers(){
#ifndef _WIN32
	struct sigaction sa_sigterm;
	sa_sigterm.sa_handler = &signal_handler;
	sigaction(SIGTERM, &sa_sigterm, NULL);
	
	struct sigaction sa_sigint;
	sa_sigint.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa_sigint, NULL);
#endif
}
void Threads::signal_handler(int signal_number){
#ifndef _WIN32
	Game::log((string)"Got "+sys_siglist[signal_number]+" Signal, Exiting.");
	Game::map -> save();
	exit(0);
#endif	
}

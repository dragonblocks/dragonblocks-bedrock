#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <GL/glut.h>
#include "threads.h"
#include "graphics.h"
#include "game.h"
using namespace std;
void Threads::add_signal_handlers(){
	Game::log("Adding Signal Handlers");
	struct sigaction sa_sigterm;
	sa_sigterm.sa_handler = &signal_handler;
	sigaction(SIGTERM, &sa_sigterm, NULL);
	struct sigaction sa_sigint;
	sa_sigint.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa_sigint, NULL);
}
void Threads::signal_handler(int signal_number){
	Game::log((string)"Got "+sys_siglist[signal_number]+" Signal, Exiting.");
	Game::save();
	exit(0);
}
void Threads::start(void *(*callback)(void *)){
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, callback, NULL);
}
void *Threads::worldBackupThread(void *unused){
	Game::log("Starting World Backup");
	while(true){
		sleep(BACKUP_INTERVAL);
		Game::save();
	}
	return NULL;
}
void *Threads::graphicRedrawThread(void *unused){
	Game::log("Starting Graphic Redraw");
	while(true){
		usleep(1);
		if(glutGetWindow())
			glutPostRedisplay();
	}
	return NULL;
}
void *Threads::modRuntimeThread(void *unused){
	Game::log("Starting Mod Runtime");
	while(true){
		usleep(10);
		// Mods::runtime();
	}
	return NULL;
}
void *Threads::entityPhysicsThread(void *unused){
	Game::log("Starting Entity Physics");
	while(true){
		usleep(PHYSIC_TIME_TICK);
		Entity::t += (double)PHYSIC_TIME_TICK / 1000000;
		Entity::physics_all();
		Graphics::ajustScroll();
	}
	return NULL;
}

#ifndef _THREADS_H_
#define _THREADS_H_

#define BACKUP_INTERVAL 60
#define PHYSIC_TIME_TICK 1000000/100

class Threads{
	public:
		static void add_signal_handlers();
		static void signal_handler(int);		
		static void start(void *(*)(void *));
		static void *worldBackupThread(void *);
		static void *graphicRedrawThread(void *);
		static void *modRuntimeThread(void *);
		static void *entityPhysicsThread(void *);
		static void *timeThread(void *);
};
#endif


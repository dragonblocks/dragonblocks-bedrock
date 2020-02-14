#ifndef _THREADS_H_
#define _THREADS_H_

#define MAP_BACKUP_INTERVAL 15

class Threads{
	public:
		static void startMapBackupThread();
		static void addSignalHandlers();
		static void startGraphicUpdateThread();
	private:
		static void *mapBackupThread(void *);
		static void *graphicUpdateThread(void *);
		static void signal_handler(int);
};
#endif


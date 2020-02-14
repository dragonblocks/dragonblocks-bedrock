#ifndef _UTIL_H_
#define _UTIL_H_
#include <string>
class color{
	public:
		float red;
		float green;
		float blue;
		color(const char *);
		color(float, float, float);
};
class position{
	public:
		int x;
		int y;
};

int random(int, int);
void create_dir_if_not_exists(std::string d);
#endif

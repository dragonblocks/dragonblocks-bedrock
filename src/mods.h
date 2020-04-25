#ifndef _MODS_H_
#define _MODS_H_

#include <string>

extern "C"{
	#include <lua5.3/lua.h>
	#include <lua5.3/lauxlib.h>
	#include <lua5.3/lualib.h>
}

class Mods{
	public:
		static lua_State *lua_vm;
		static bool check_lua(int);
		static void error(std::string);
		static void init();
		static void nodedef();
};
#endif

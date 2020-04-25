#include <cstring>
#include <cstdio>
#include <cerrno>
#include <string>
#include <iostream>
#include "node.h"
#include "mods.h"
#include "game.h"
#include "util.h"
#include "graphics.h"

using namespace std;

lua_State *Mods::lua_vm;

void Mods::init(){
	Game::log("Initializing Mods");
	lua_vm = luaL_newstate();
	luaL_openlibs(lua_vm);
	if(! check_lua(luaL_dofile(lua_vm, "builtin/init.lua"))){
		Game::log("Failed to load Builtin: File 'builtin/init.lua' does not exist or contains an error", ERROR);
		exit(EXIT_FAILURE);
		return;
	}
}
void Mods::nodedef(){
	Game::log("Initializing Nodes");
	lua_getglobal(lua_vm, "dragonblocks");
	if(! lua_istable(lua_vm, -1)){
		Game::log("Failed to load Builtin: 'dragonblocks' does not exist or is not a table", ERROR);
		exit(EXIT_FAILURE);
		return;
	}
	lua_pushstring(lua_vm, "registered_nodes");
	lua_gettable(lua_vm, -2);
	if(!lua_istable(lua_vm,-1)){
		Game::log("Failed to load Builtin: 'dragonblocks.registered_nodes' does not exist or is not a table", ERROR);
		exit(EXIT_FAILURE);
		return;
	}
	lua_pushnil(lua_vm);
	for(int i = 1;; i++){
		lua_pop(lua_vm, 1);
		lua_pushnumber(lua_vm, i);
		lua_gettable(lua_vm, -2);
		if(!lua_istable(lua_vm, -1))
			break;
		
		
		lua_pushstring(lua_vm, "name");
		lua_gettable(lua_vm, -2);
		if(!lua_isstring(lua_vm,-1))
			continue;
		string name = lua_tostring(lua_vm,-1);
		lua_pop(lua_vm, 1);
		
		lua_pushstring(lua_vm, "texture");
		lua_gettable(lua_vm, -2);
		if(!lua_isstring(lua_vm,-1))
			continue;
		string texture = lua_tostring(lua_vm,-1);
		lua_pop(lua_vm, 1);
		
		lua_pushstring(lua_vm, "hidden");
		lua_gettable(lua_vm, -2);
		if(!lua_isboolean(lua_vm,-1))
			continue;
		bool hidden = lua_toboolean(lua_vm,-1);
		lua_pop(lua_vm, 1);
		
		lua_pushstring(lua_vm, "stable");
		lua_gettable(lua_vm, -2);
		if(!lua_isboolean(lua_vm,-1))
			continue;
		bool stable = lua_toboolean(lua_vm,-1);
		lua_pop(lua_vm, 1);
		
		lua_pushstring(lua_vm, "translucent");
		lua_gettable(lua_vm, -2);
		if(!lua_isboolean(lua_vm,-1))
			continue;
		bool translucent = lua_toboolean(lua_vm,-1);
		lua_pop(lua_vm, 1);
		
		new Node(name, texture, hidden, stable, translucent);
		Game::log("Registered Node " + name, INFO);
	}
}
bool Mods::check_lua(int code){
	if(code == LUA_OK)
		return true;
	else{
		error(lua_tostring(lua_vm, -1));
		return false;
	}
}
void Mods::error(string text){
	Game::log("\e[34mlua: \e[0m" + text, ERROR);
}

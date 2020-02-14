cmake_minimum_required(VERSION 3.0)
project(dragonblocks)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
add_executable(dragonblocks
	src/game.cpp
    src/graphics.cpp
    src/inventory.cpp
	src/main.cpp
	src/map.cpp
	src/mapgen.cpp
	src/mods.cpp
	src/node.cpp
    src/texture.cpp
    src/threads.cpp
	src/util.cpp
)

target_link_libraries(dragonblocks
	GL
	freeglut
	lua5.3
	pthread
	png16
	m
)

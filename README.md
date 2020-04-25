# DRAGONBLOCKS BEDROCK EDITION
Written in C++  
An Open Source Project by Elias Fleckenstein
## General
### What this is about
Dragonblocks originaly was a Browsergame I made that should be some kind of 2D Minetest (Minetest (www.minetest.net) is a game similar to Minecraft, except Minetest is free & open source and is meant to be modded). The JavaScript Edition is hosted at www.elidragon.com/projects/Dragonblocks and further developed then this C++ Version, through the C++ Version has advantages like map saving and lot larger map. I decided to call the C++ Version "Bedrock Edition" as a joke for the Minecraft C++ Version is Called Bedrock or Pocket Edition.
### Version
This is the Dragonblocks Bedrock Edition 3.1.
### Bugs
Please Report Bugs to eliasfleckenstein@web.de.
### License
		Copyright 2020 Elias Fleckenstein <eliasfleckenstein@web.de>
		
		This program is free software; you can redistribute it and/or modify
		it under the terms of the GNU General Public License as published by
		the Free Software Foundation; either version 3 of the License, or
		(at your option) any later version.
		
		This program is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
		GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
		along with this program; if not, write to the Free Software
		Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
		MA 02110-1301, USA.
## Starting the Game
### Platform Compability
This Game was developed on linux, therefore following instructions are only for linux users, basically because I have no idea how to port the game to other platforms. Feel free to add building instructions for other systems over github.
### Download
You can download the game using git:  
`$ git clone https://github.com/EliasFleckenstein03/dragonblocks.git`
### Dependencies:
You need Freeglut, OpenGl, Cmake, Liblua and Libpng.  
If you are on Debian/Ubuntu You can install them over apt:   
`$ sudo apt install liblua5.3-dev freeglut3-dev libgl1-mesa-dev cmake libpng-dev`
### Building
to Build dragonblocks run:  
`$ cmake .`  
`$ make`
### Exectute
#### Run-In-Place
Invoke dragonblocks by typing:  
`$ bin/dragonblocks --worldname <your_worldname>`  
To see a list of worlds do:  
`$ bin/dragonblocks --worldlist`  
You can select a world from this list or create a new one.  
For more info run:  
`$ bin/dragonblocks --help`
#### Installation
You can install dragonblocks by doing:  
`$ sudo ./install.sh`

DRAGONBLOCKS BEDROCK EDITION
Written in C++
An Open Source Project by Elias Fleckenstein

1. General
	1.1. What this is about
		Dragonblocks originaly was a Browsergame I made that should be some kind of 2D Minetest (Minetest (www.minetest.net) is a game similar to 
		Minecraft, except Minetest is free & open source and is meant to be modded). The JavaScript Edition is hosted at www.dragonblocks.tk and 
		further developed then this C++ Version, through the C++ Version has advantages like map saving and lot larger map. I decided to call the 
		C++ Version "Bedrock Edition" as a joke for the Minecraft C++ Version is Called Bedrock or Pocket Edition.
	1.2. Version
		This is the Dragonblocks Bedrock Edition 3.0.
	1.4. Bugs
		Please Report Bugs to eliasfleckenstein@web.de.
	1.5. License
		Copyright 2020 Elias Fleckenstein <eliasfleckenstein@web.de>
		
		This program is free software; you can redistribute it and/or modify
		it under the terms of the GNU General Public License as published by
		the Free Software Foundation; either version 2 of the License, or
		(at your option) any later version.
		
		This program is distributed in the hope that it will be useful,
		but WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
		GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
		along with this program; if not, write to the Free Software
		Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
		MA 02110-1301, USA.

2. Starting the Game
	2.1. Platform Compability
		This Game was developed on linux, therefore following instructions are only for linux users, basically because I have no idea how to
		port the game to other platforms. Feel free to add building instructions for other systems over github.
	2.3. Download
		You can download the game using git:
			$ git clone https://
	2.2. Dependencies:
		You need Freeglut, OpenGl, Cmake, Liblua and Libpng.
		If you are on Debian/Ubuntu You can install them over apt: 
			$ sudo apt install liblua5.3-dev freeglut3-dev libgl1-mesa-dev cmake libpng-dev
    2.3. Building
        to Build dragonblocks run:
            $ cd dragonblocks
            $ cmake .
            $ make
	2.4. Exectute
		2.4.1. Run-In-Place
			Invoke dragonblocks by typing:
                $ cd dragonblocks
                $ bin/dragonblocks --worldname <your_worldname>
            To see a list of worlds do:
                $ bin/dragonblocks --worldlist
            You can select a world from this list or create a new one.
            For more info run:
				$ bin/dragonblocks --help
		2.4.2. Installation
			You can install dragonblocks by doing:
				$ sudo ./install.sh
			It will copy the dragonblocks directory to /usr/share/dragonblocks and place a script in
			/usr/bin/dragonblocks that starts dragonblocks.

3. Developing
	3.1. The Lua Modding API
		If you want to add a lua file to the game, place it in the game folder and add a dofile() in game/init.lua
		Note: The lua api currently consists of only two functions. If you want to add something I'm open to ideas or code.
		dragonblocks.register_node(obj)
			Register a new node
			obj has to contain:
				name: string - the itemstring. It should follow the convention "modulename:nodename"
				texture: string - the texture path. Textures should be placed in the textures folder and have to be 16 x 16 px.
			obj can contain:
				stable: boolean - Nodes like water or air are unstable. [default = true]
				hidden: boolean - The Node will be hidden in the invenotry. [default = false]
				translucent: boolean - Whether the node's texture should be transparent. [default = false]
		dragonblocks.log(text)
			Log something.
	3.2. The C++ API
		The C++ API is probably to big to explain here, but if you do C++ you should understand it. In case you have questions, feel free to
		ask them on github. You can also contribute code if you want.

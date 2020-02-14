#include <GL/freeglut.h>
#include <png.h>
#include <string>
#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdio>

#include "game.h"
#include "graphics.h"
#include "texture.h"


using namespace std;


Texture::Texture(string filename, bool t){
	translucent = t;
	dummyimage = false;
	FILE *file = fopen(filename.c_str(), "rb");
	if(!file){
		Game::log("Failed to Load Image " + filename + ": File not found. Using a dummy Image.", WARNING);
		dummyimage = true;
		return;
	}
	png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	assert(png);
	png_infop info = png_create_info_struct(png);
	assert(info);
	png_init_io(png, file);
	png_read_info(png, info);
	width = png_get_image_width(png, info);
	height = png_get_image_height(png, info);
	color_type = png_get_color_type(png, info);
	bit_depth  = png_get_bit_depth(png, info);
	if(bit_depth == 16)
		png_set_strip_16(png);
	if(color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png);
	#ifndef _WIN32
	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png);
	#endif
	if(png_get_valid(png, info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png);
	if(color_type == PNG_COLOR_TYPE_RGB || color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
	if(color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png);
	png_read_update_info(png, info);
	row_pointers = (png_bytep*)malloc(sizeof(png_bytep) *height);
	for(int y = 0; y < height; y++) {
		row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
	}
	png_read_image(png, row_pointers);
	fclose(file);
	png_destroy_read_struct(&png, &info, NULL);
}
void Texture::draw(int displayX, int displayY, int displayWidth, int displayHeight){
	if(dummyimage){
		Graphics::drawRectangle(displayX, displayY, displayWidth, displayHeight, {0, 0, 0});
		return;
	}
	int scaleX = (float)displayWidth/width;
	int scaleY = (float)displayHeight/height;
	for(int y = 0; y < height; y++) {
		png_bytep row = row_pointers[y];
		for(int x = 0; x < width; x++) {
			png_bytep px = &(row[x * 4]);
			if(!translucent || px[0] || px[1] || px[2])
				Graphics::drawRectangle(x*scaleX + displayX, y*scaleY + displayY, scaleX, scaleY, {(float)px[0]/255, (float)px[1]/255, (float)px[2]/255});
		}
	}
}

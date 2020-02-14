#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <png.h>
#include <string>

class Texture{
	public:
		int width;
		int height;
		void draw(int, int, int, int);
		Texture(std::string, bool);
	private:
		png_byte color_type;
		png_byte bit_depth;
		png_bytep *row_pointers;
		bool dummyimage;
		bool translucent;
};
#endif

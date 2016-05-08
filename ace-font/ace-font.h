#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

namespace ace_font {

	class AceType {
		FT_Library  library;

	public:
		int advance;
		int glyph_index;

		FT_Face face;

		AceType(const char *fontpath);

		~AceType();

		FT_Bitmap* draw(char c, int height);
	};

	class CharAtlas {
	public:
		int width, height;
		unsigned char* buffer;

		CharAtlas(FT_Bitmap *bitmap);
		~CharAtlas();
	};

	class Atlas {
	public:
		int atlasWidth, atlasHeight;

		int charX[128];
		int charWidth[128];
		int charHeight[128];
		int charGlyphIndex[128];

		int charAdvance[128];

		int charBitmapTop[128];
		int charBitmapLeft[128];

		unsigned char* buffer;
		AceType* ace;

	private:
		int charCount;
		int next;
		CharAtlas ** charatlases;
		char* alpha;
		char *fontpath;

	public:
		int getKerning(char a, char b);

		Atlas(char* fontpath);

		~Atlas();

	public:
		void load(int height);

		void toFile(char* filename);

	private:
		void saveImage(char* szPathName, void* lpBits, int w, int h);

		int getMaxHeight();

		void copy(CharAtlas * charatlas, unsigned char* buffer, int bufferWidth, int startX, int height);

		void allocate();

		void add(char c, FT_Bitmap *bitmap);
	};

	class CoreDraw {
	public:
		// for when rendering to buffer
		void core(char* str, int x, int y, Atlas* atlas, int* coords);

		// for when rendering to texture
		void core2(char* str, int x, int y, Atlas* atlas, int* coords, char phantomChar);
	};
}


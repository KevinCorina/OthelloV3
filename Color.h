#include <string>
#ifndef COLOR_H
#define COLOR_H

enum Color { BLACK, WHITE };

struct ColorInfo {
	static const char colorChar[2];
	static const Color opponent[2];
	static const std::string colorName[2];
};
typedef ColorInfo ci;
#endif

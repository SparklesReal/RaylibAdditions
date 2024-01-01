#include "pch.h"
#include "framework.h"

#include <raylib.h>
#include <string>

namespace RaylibAdditions {
	// Draws text in the center of a Rectangle 
	static void drawTextCenterRect(Rectangle &rect, std::string &text, int fontSize, Color color) {
		DrawText(text.c_str(),
			rect.x/2 - MeasureText(text.c_str(), fontSize)/2,
			rect.y/2, 
			fontSize,
			color
			);
	}

	// Draws text in the center of Rectangle custom text args
	static void drawTextCenterRect(Rectangle& rect, std::string& text, int fontsize, float spacing, Color tint, Font font = GetFontDefault()) {
		DrawTextEx(font,
			text.c_str(),
			{ rect.x / 2 - MeasureTextEx(font, text.c_str(), fontsize, spacing).x / 2, rect.y / 2 },
			fontsize,
			spacing,
			tint);
	}

	// Draws a Rectangle with an outline
	static void drawRectWOutline(Rectangle& rect, float lineThick, Color color, Color outlineColor) {
		DrawRectangle(rect.x, rect.y, rect.width, rect.height, color);
		DrawRectangleLinesEx(rect, lineThick, outlineColor);
	}

	// Draws a Rectangle with an outline and text
	static void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor) {
		drawRectWOutline(rect, lineThick, rectColor, outlineColor);
		drawTextCenterRect(rect, text, fontSize, textColor);
	}

	// Draws a Rectangle with an outline and text using custom text args
	static void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor, float textSpacing, Font font = GetFontDefault()) {
		drawRectWOutline(rect, lineThick, rectColor, outlineColor);
		drawTextCenterRect(rect, text, fontSize, textSpacing, textColor, font);
	}
}

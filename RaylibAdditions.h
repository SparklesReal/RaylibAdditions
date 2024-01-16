#pragma once

#include <raylib.h>
#include <string>
#include <unordered_map>

namespace RaylibAdditions { // Define classes here
	// Window class, construct using title, width, heigth. All args can be changed and then run updateWindow to resize and rename window
	class ProgramWindowClass {
	public:
		std::string title;
		int width;
		int height;

		ProgramWindowClass(std::string windowTitle, int windowWidth, int windowHeight) {
			title = windowTitle;
			width = windowWidth;
			height = windowHeight;
			InitWindow(width, height, title.c_str());
		};

		~ProgramWindowClass() {
			CloseWindow();
		}

		void updateWindow() {
			SetWindowTitle(title.c_str());
			SetWindowSize(width, height);
		}
	};
	
	// Button class, consturct using all args (some are optional)
	class ButtonClass {
	public:
		Rectangle rect;
		std::string text;
		int textSize;
		Color color;
		Color outlineColor;
		Color textColor;
		int outlineThickness;
		// state, 1 = hover, 2 = pressed
		int state;

		ButtonClass(Rectangle ButtonRect, std::string ButtonText, int buttonTextSize, Color buttonColor, Color buttonOutlineColor, Color buttonTextColor, int buttonOutlineThickness, int buttonState = 0, bool buttonPressed = false) {
			rect =				ButtonRect;
			text =				ButtonText;
			textSize =			buttonTextSize;
			color =				buttonColor;
			outlineColor =		buttonOutlineColor;
			textColor =			buttonTextColor;
			outlineThickness =	buttonOutlineThickness;
			state =				buttonState;
		}
	};
}

namespace RaylibAdditions { // Define functions here
	// Draws text in the center of a Rectangle 
	static void drawTextCenterRect(Rectangle& rect, std::string& text, int fontSize, Color color);
	// Draws text in the center of Rectangle custom text args
	static void drawTextCenterRect(Rectangle& rect, std::string& text, int fontsize, float spacing, Color tint, Font font = GetFontDefault());
	// Draws a Rectangle with an outline
	static void drawRectWOutline(Rectangle& rect, float lineThick, Color color, Color outlineColor);
	// Draws a Rectangle with an outline and text
	static void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor);
	// Draws a Rectangle with an outline and text using custom text args
	static void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor, float textSpacing, Font font = GetFontDefault());
	// Draws a button using the ButtonClass
	static void drawButton(RaylibAdditions::ButtonClass* button);
	// Draws all the buttons in a std::unordererd_map
	static void drawButtons(std::unordered_map<std::string, ButtonClass>* buttons);
	// Updates the state of all buttons in a std::unordererd_map
	static void updateButtonstates(std::unordered_map<std::string, ButtonClass>* buttons);
	// Creates a normal Camera2D
	static Camera2D createCamera();
}
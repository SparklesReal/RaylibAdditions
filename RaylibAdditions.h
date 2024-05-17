#pragma once

#include <raylib.h>
#include <string>
#include <unordered_map>

namespace RaylibAdditions { // Define classes here
	// Window class, construct using title, width, heigth. All args can be changed and then run updateWindow to resize and rename window
	class WindowClass {
	public:
		std::string title;
		int width;
		int height;

		WindowClass(std::string windowTitle, int windowWidth, int windowHeight) {
			title = windowTitle;
			width = windowWidth;
			height = windowHeight;
			InitWindow(width, height, title.c_str());
		};

		~WindowClass() {
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
		float scale;
		// state, 0 = off, 1 = hover, 2 = pressed, 3 = released (only one cycle)
		int state;
		//optional sound
		Sound pressedSound;
		Sound releasedSound;

		ButtonClass(Rectangle buttonRect, std::string buttonText, int buttonTextSize, Color buttonColor, Color buttonOutlineColor, Color buttonTextColor, int buttonOutlineThickness, float buttonScale, Sound buttonPressedSound = Sound(), Sound buttonReleasedSound = Sound(), int buttonState = 0) {
			rect =				buttonRect;
			text =				buttonText;
			textSize =			buttonTextSize;
			color =				buttonColor;
			outlineColor =		buttonOutlineColor;
			textColor =			buttonTextColor;
			outlineThickness =	buttonOutlineThickness;
			scale =				buttonScale;
			state =				buttonState;
			pressedSound = 		buttonPressedSound;
			releasedSound = 	buttonReleasedSound;
		}
	};

	class LoadedButtonClass {
	public:
		Texture2D texture;
		Vector2 pos;
		float scale;
		// state, 0 = off, 1 = hover, 2 = pressed, 3 = released (only one cycle)
		int state;
		//optional sound
		Sound pressedSound;
		Sound releasedSound;

		LoadedButtonClass(Texture2D buttonTexture, Vector2 buttonPos, float buttonScale, Sound buttonPressedSound = Sound(), Sound buttonReleasedSound = Sound(), int buttonState = 0) {
			texture = 			buttonTexture;
			pos =				buttonPos;
			scale =				buttonScale;
			state =				buttonState;
			pressedSound = 		buttonPressedSound;
			releasedSound = 	buttonReleasedSound;
		}
	};
}

namespace RaylibAdditions { // Define functions here
	// Draws text in the center of a Rectangle 
	void drawTextCenterRect(Rectangle& rect, std::string& text, int fontSize, Color color);
	// Draws text in the center of Rectangle custom text args
	void drawTextCenterRect(Rectangle& rect, std::string& text, int fontsize, float spacing, Color tint, Font font = GetFontDefault());
	// Draws a Rectangle with an outline
	void drawRectWOutline(Rectangle& rect, float lineThick, Color color, Color outlineColor);
	// Draws a Rectangle with an outline and text
	void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor);
	// Draws a Rectangle with an outline and text using custom text args
	void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor, float textSpacing, Font font = GetFontDefault());
	// Draws a button using the ButtonClass
	void drawButton(RaylibAdditions::ButtonClass* button);
	// Draws all the buttons in a std::unordererd_map
	void drawButtons(std::unordered_map<std::string, ButtonClass>* buttons);
	// Updates the state of all buttons in a std::unordererd_map
	void updateButtonstates(std::unordered_map<std::string, ButtonClass>* buttons);
	// Creates a normal Camera2D
	Camera2D createCamera();
	// Creates camera zooming into game area using getScreenHeight()
	Camera2D createCamera(int gameHeight);
	// Draws an FPS counter at the position supplied 1 = top left, 2 = top middle, 3 = top right, 4 = middle left and so on
	void drawFPSCounter(int position, int fontSize);
}
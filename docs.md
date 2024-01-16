### RaylibAdditions documentation

```C++
void drawTextCenterRect(Rectangle &rect, std::string &text, int fontSize, Color color);															// Draws text in the center of a Rectangle 
void drawTextCenterRect(Rectangle& rect, std::string& text, int fontsize, float spacing, Color tint, Font font = GetFontDefault());									// Draws text in the center of Rectangle custom text args (Font is optional)
void drawRectWOutline(Rectangle& rect, float lineThick, Color color, Color outlineColor);														// Draws a Rectangle with an outline
void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor);							// Draws a Rectangle with an outline and text
void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor, float textSpacing, Font font = GetFontDefault());	// Draws a Rectangle with an outline and text using custom text args (Font is optional)
void drawButton(RaylibAdditions::ButtonClass* button);																			// Draws a button using the ButtonClass
void drawButtons(std::unordered_map<std::string, ButtonClass>* buttons);																	// Draws all the buttons in a std::unordererd_map
void updateButtonstates(std::unordered_map<std::string, ButtonClass>* buttons);																// Updates the state of all buttons in a std::unordererd_map
Camera2D createCamera();																							// Creates a normal Camera2D
```

## Classes

```C++
// Window class, construct using title, width, heigth. All args can be changed and then run updateWindow to resize and rename window
class ProgramWindowClass {
public:
	std::string title;	// Window title
	int width;		// Window width
	int height;		// Window height

	ProgramWindowClass(std::string windowTitle, int windowWidth, int windowHeight)	// Constructor
	~ProgramWindowClass()								// De-Constructor (runs CloseWindow())
	void updateWindow()								// Updates window (run after changing varibles)
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
	int state;	// state, 1 = hover, 2 = pressed

	ButtonClass(Rectangle ButtonRect, std::string ButtonText, int buttonTextSize, Color buttonColor, Color buttonOutlineColor, Color buttonTextColor, int buttonOutlineThickness, int buttonState = 0, bool buttonPressed = false)
};
```

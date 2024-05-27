### RaylibAdditions documentation

```C++
void drawTextCenterRect(Rectangle &rect, std::string &text, int fontSize, Color color);	// Draws text in the center of a Rectangle 
void drawTextCenterRect(Rectangle& rect, std::string& text, int fontsize, float spacing, Color tint, Font font = GetFontDefault());	// Draws text in the center of Rectangle custom text args (Font is optional)
void drawRectWOutline(Rectangle& rect, float lineThick, Color color, Color outlineColor);	// Draws a Rectangle with an outline
void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor);	// Draws a Rectangle with an outline and text
void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor, float textSpacing, Font font = GetFontDefault());	// Draws a Rectangle with an outline and text using custom text args (Font is optional)
void drawButton(RaylibAdditions::ButtonClass* button);	// Draws a button using the ButtonClass
void drawButtons(std::unordered_map<std::string, ButtonClass>* buttons);	// Draws all the buttons in a std::unordererd_map
void updateButtonstates(std::unordered_map<std::string, ButtonClass>* buttons);	// Updates the state of all buttons in a std::unordererd_map
Camera2D createCamera();	// Creates a normal Camera2D
Camera2D createCamera(int gameHeight);	// Creates camera zooming into game area using getScreenHeight()
void drawFPSCounter(int position, int fontSize); // Draws an FPS counter at the position supplied 1 = top left, 2 = top middle, 3 = top right, 4 = middle left and so on
```

## Classes

```C++
// Window class, construct using title, width, heigth. All args can be changed and then run updateWindow to resize and rename window
class WindowClass {
public:
	std::string title;	// Window title
	int width;	// Window width
	int height;	// Window height

	WindowClass(std::string windowTitle, int windowWidth, int windowHeight)	// Constructor
	~WindowClass()	// De-Constructor (runs CloseWindow())
	void updateWindow()	// Updates window (run after changing varibles)
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
	int state;	// state, 1 = hover, 2 = pressed
	Sound pressedSound;
	Sound releasedSound;

	ButtonClass(Rectangle buttonRect, std::string buttonText, int buttonTextSize, Color buttonColor, Color buttonOutlineColor, Color buttonTextColor, int buttonOutlineThickness, float buttonScale, Sound buttonPressedSound = Sound(), Sound buttonReleasedSound = Sound(), int buttonState = 0) // Sounds are optional
};

class FrameClass {
public:
std::vector<Texture2D> textures;
std::vector<Vector2>   texturePos;
std::vector<float>     textureScales;
};

class LoadedRoomClass {
public:
std::vector<FrameClass>                         frames;
std::vector<RaylibAdditions::LoadedButtonClass> Buttons;
Sound                                           music;
bool                                            isValid = true;
}; 

class RoomClass {
public:
int ID = 0;
Camera2D camera = RaylibAdditions::createCamera();

// Loads a .gui room made with RaylibGuiCreator https://github.com/SparklesReal/RaylibGuiCreator also this needs to be rewritten
LoadedRoomClass loadRoom(std::string path, std::string fileName);
// Draws a single frameclass
void drawFrameClass(FrameClass* frame);
};
```

### RaylibAdditions functions documentation

```C++
bool stringIsInt(std::string string); // Goes trough string, returns false if it is not of data type integer
```
### RaylibAdditions documentation

```C++
void drawTextCenterRect(Rectangle &rect, std::string &text, int fontSize, Color color)																													// Draws text in the center of a Rectangle 
void drawTextCenterRect(Rectangle& rect, std::string& text, int fontsize, float spacing, Color tint, Font font = GetFontDefault())																		// Draws text in the center of Rectangle custom text args (Font is optional)
void drawRectWOutline(Rectangle& rect, float lineThick, Color color, Color outlineColor)																												// Draws a Rectangle with an outline
void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor)														// Draws a Rectangle with an outline and text
void drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor, float textSpacing, Font font = GetFontDefault())	// Draws a Rectangle with an outline and text using custom text args (Font is optional)
```
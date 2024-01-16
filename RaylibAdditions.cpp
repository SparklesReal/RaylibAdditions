#include "pch.h"
#include "framework.h"

#include "RaylibAdditions.h"

#include <raylib.h>
#include <string>

static void RaylibAdditions::drawTextCenterRect(Rectangle &rect, std::string &text, int fontSize, Color color) {
	DrawText(text.c_str(),
		rect.x/2 - MeasureText(text.c_str(), fontSize)/2,
		rect.y/2, 
		fontSize,
		color
		);
}

static void RaylibAdditions::drawTextCenterRect(Rectangle& rect, std::string& text, int fontsize, float spacing, Color tint, Font font = GetFontDefault()) {
	DrawTextEx(font,
		text.c_str(),
		{ rect.x / 2 - MeasureTextEx(font, text.c_str(), fontsize, spacing).x / 2, rect.y / 2 },
		fontsize,
		spacing,
		tint);
}

static void RaylibAdditions::drawRectWOutline(Rectangle& rect, float lineThick, Color color, Color outlineColor) {
	DrawRectangle(rect.x, rect.y, rect.width, rect.height, color);
	DrawRectangleLinesEx(rect, lineThick, outlineColor);
}

static void RaylibAdditions::drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor) {
	drawRectWOutline(rect, lineThick, rectColor, outlineColor);
	drawTextCenterRect(rect, text, fontSize, textColor);
}

static void RaylibAdditions::drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor, float textSpacing, Font font = GetFontDefault()) {
	drawRectWOutline(rect, lineThick, rectColor, outlineColor);
	drawTextCenterRect(rect, text, fontSize, textSpacing, textColor, font);
}

static void RaylibAdditions::drawButton(RaylibAdditions::ButtonClass* button) {
	drawRectWOutlineWText(button->rect, button->outlineThickness, button->color, button->outlineColor, button->text, button->textSize, button->textColor);
}

static void RaylibAdditions::drawButtons(std::unordered_map<std::string, ButtonClass>* buttons) {
	for (int i = 0; i < buttons->size(); i++) {
		auto it = std::next(buttons->begin(), i);
		drawButton(&it->second);
	}
}

static void RaylibAdditions::updateButtonstates(std::unordered_map<std::string, ButtonClass>* buttons) {
	for (int i = 0; i < buttons->size(); i++) {
		auto it = std::next(buttons->begin(), i);
		if (CheckCollisionPointRec(GetMousePosition(), it->second.rect)) {
			it->second.state = 1;
			if (IsMouseButtonPressed(0))
				it->second.state = 2;
		}
		else
			it->second.state = 0;
	}
}

Camera2D RaylibAdditions::createCamera() {
	Camera2D camera{ 0 };
	camera.target = Vector2{ 0, 0 };
	camera.offset = Vector2{ 0, 0 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	return camera;
}


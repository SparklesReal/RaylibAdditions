#include "RaylibAdditions.hpp"
#include "Functions.hpp"

#include <raylib.h>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>

void RaylibAdditions::drawTextCenterRect(Rectangle &rect, std::string &text, int fontSize, Color color) {
	DrawText(text.c_str(),
		(rect.x + rect.width / 2) - MeasureText(text.c_str(), fontSize) / 2,
		(rect.y + rect.height / 2) - fontSize / 2, 
		fontSize,
		color
		);
}

void RaylibAdditions::drawTextCenterRect(Rectangle& rect, std::string& text, int fontsize, float spacing, Color tint, Font font) {
	DrawTextEx(font,
		text.c_str(),
		{ (rect.x + rect.width / 2) - MeasureTextEx(font, text.c_str(), fontsize, spacing).x / 2, 
		(rect.y + rect.height / 2) + MeasureTextEx(font, text.c_str(), fontsize, spacing).y / 2},
		fontsize,
		spacing,
		tint
		);
}

void RaylibAdditions::drawRectWOutline(Rectangle& rect, float lineThick, Color color, Color outlineColor) {
	DrawRectangle(rect.x, rect.y, rect.width, rect.height, color);
	DrawRectangleLinesEx(rect, lineThick, outlineColor);
}

void RaylibAdditions::drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor) {
	drawRectWOutline(rect, lineThick, rectColor, outlineColor);
	drawTextCenterRect(rect, text, fontSize, textColor);
}

void RaylibAdditions::drawRectWOutlineWText(Rectangle& rect, float lineThick, Color rectColor, Color outlineColor, std::string& text, int fontSize, Color textColor, float textSpacing, Font font) {
	drawRectWOutline(rect, lineThick, rectColor, outlineColor);
	drawTextCenterRect(rect, text, fontSize, textSpacing, textColor, font);
}

void RaylibAdditions::drawButton(RaylibAdditions::ButtonClass* button) {
	drawRectWOutlineWText(button->rect, button->outlineThickness, button->color, button->outlineColor, button->text, button->textSize, button->textColor);
}

void RaylibAdditions::drawButtons(std::unordered_map<std::string, ButtonClass>* buttons) {
	for (int i = 0; i < buttons->size(); i++) {
		auto it = std::next(buttons->begin(), i);
		drawButton(&it->second);
	}
}

void RaylibAdditions::updateButtonstates(std::unordered_map<std::string, ButtonClass>* buttons) {
	for (int i = 0; i < buttons->size(); i++) {
		auto it = std::next(buttons->begin(), i);
		if (CheckCollisionPointRec(GetMousePosition(), it->second.rect)) {
			it->second.state = 1;
			if (IsMouseButtonPressed(0)) {
				it->second.state = 2;
				if(IsSoundReady(it->second.pressedSound))
					PlaySound(it->second.pressedSound);
			}
		}
		else
			it->second.state = 0;
	}
}

Camera2D RaylibAdditions::createCamera() {
	Camera2D camera{};
	camera.target = Vector2{ 0, 0 };
	camera.offset = Vector2{ 0, 0 };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	return camera;
}

Camera2D RaylibAdditions::createCamera(int gameHeight) {
	Camera2D camera{};
	camera.target = Vector2{ 0, 0 };
	camera.offset = Vector2{ 0, 0 };
	camera.rotation = 0.0f;
	camera.zoom = GetScreenHeight() / gameHeight;
	return camera;
}

void RaylibAdditions::drawFPSCounter(int position, int fontSize, Color color) {
	int positionX = 0, positionY = 0;
	std::string FPSString = std::to_string(GetFPS());
	if (position == 2 || position == 5 || position == 8)
		positionX = float(GetScreenWidth()) / 2.0 - float(MeasureText(FPSString.c_str(), fontSize)) / 2.0;
	if (position == 3 || position == 6 || position == 9)
		positionX = float(GetScreenWidth()) - float(MeasureText(FPSString.c_str(), fontSize));
	if (position == 4 || position == 5 || position == 6)
		positionY = float(GetScreenHeight()) / 2.0 - fontSize / 2.0;
	if (position == 7 || position == 8 || position == 9)
		positionY = float(GetScreenHeight()) - fontSize;
	DrawText(FPSString.c_str(), positionX, positionY, fontSize, color);
	return;
}

RaylibAdditions::LoadedRoomClass RaylibAdditions::RoomClass::loadRoom(std::string path, std::string fileName) {
    std::ifstream file;
	file.open(path + fileName);
	if (!file.is_open()) {
		std::cerr << "Failed to load: " << path << std::endl;
		LoadedRoomClass failedClass;
		failedClass.isValid = false;
	}
	std::string line;
	int currentFrame = 0;
	bool buttons = false, music = false;
	LoadedRoomClass LoadedRoom{};
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		size_t index = line.find("!!!");
 		if (index != std::string::npos) {
			std::string value = line.substr(3, line.length());
			value = value.substr(0, value.find(':'));
			if (functions::stringIsInt(value)) {
				currentFrame = std::stoi(value); // use later when frame system is in place
				continue;
			}
			if (value == "buttons") {
				buttons = true;
				continue;
			}
			if (value == "music") {
				buttons = false;
				music = true;
				continue;
			}
		}
		if(buttons == true) {
			std::string texture = line.substr(line.find(" - ") + 3, line.find(" -- ") - line.find(" - ") - 3);
			float textureX = stof(line.substr(line.find(" -- ") + 4, line.find(" --- ") - line.find(" -- ") - 4));
			float textureY = stof(line.substr(line.find(" --- ") + 5, line.find(" ---- ") - line.find(" --- ") - 5));
			float scale = stof(line.substr(line.find(" ---- ") + 7, line.find(" ----- ") - line.find(" ---- ") - 6));
			std::string texturePressed = line.substr(line.find(" ----- ") + 7, line.find(" ! ") - line.find(" ----- ") - 7);
			if(line.find(" !") + 4 >= line.length()) {
				LoadedRoom.Buttons.push_back(RaylibAdditions::LoadedButtonClass(LoadTexture((path + "Textures/" + texture + ".png").c_str()), {textureX, textureY}, scale));
				continue;
			}
			Sound soundPressed = LoadSound((path + "Sounds/" + line.substr(line.find(" ! ") + 3, line.find(" !! ") - line.find(" ! ") - 3) + ".wav").c_str());
			Sound soundReleased = LoadSound((path + "Sounds/" + line.substr(line.find(" !! ") + 4, line.length() - line.find(" !! ") - 4) + ".wav").c_str());
			LoadedRoom.Buttons.push_back(RaylibAdditions::LoadedButtonClass(LoadTexture((path + "Textures/" + texture + ".png").c_str()), {textureX, textureY}, scale, soundPressed, soundReleased));
			continue;
		}
		if (music == true) {
			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			LoadedRoom.music = LoadSound((path + "Music/" + line + ".wav").c_str());
			break;
		}
		std::string texture = line.substr(line.find(" - ") + 3, line.find(" -- ") - line.find(" - ") - 3);
		float textureX = stof(line.substr(line.find(" -- ") + 4, line.find(" --- ") - line.find(" -- ") - 4));
		float textureY = stof(line.substr(line.find(" --- ") + 5, line.find(" ---- ") - line.find(" --- ") - 5));
		float scale = stof(line.substr(line.find(" ---- ") + 7, line.length() - line.find(" ---- ") - 6));
		FrameClass CurrentLoadedFrame;
		CurrentLoadedFrame.textures.push_back(LoadTexture((path + "Textures/" + texture + ".png").c_str()));
		std::cout << "Log: texture placed in frame: " << path + "Textures/" + texture + ".png" << std::endl;
		CurrentLoadedFrame.texturePos.push_back(Vector2{textureX, textureY});
		std::cout << "Log: texturePos placed in frame: " << textureX << " " << textureY << std::endl;
		CurrentLoadedFrame.textureScales.push_back(scale);
		std::cout << "Log: textureScale placed in frame: " << scale << std::endl;
		LoadedRoom.frames.push_back(CurrentLoadedFrame);
		std::cout << "Log: frame placed in LoadedRoom" << std::endl;
	}
	file.close();
	return LoadedRoom;
}

void RaylibAdditions::RoomClass::drawFrameClass(FrameClass* frame) {
	for(int i = 0; i < frame->texturePos.size(); i++) {
		if (i > frame->textures.size() || i > frame->textureScales.size()) {
			std::cout << "drawFrameClass error dumping frame info: " << frame->textures.data() << std::endl;
			return;
		}
		DrawTexture(frame->textures.at(i), frame->texturePos.at(i).x, frame->texturePos.at(i).y, WHITE );
	}
}
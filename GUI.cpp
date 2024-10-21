#include "GUI.hpp"

#include "Functions.hpp"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>

std::vector<std::string> RaylibAdditions::splitString(std::string string, std::string seperator) {
    std::vector<std::string> returnString;
    std::string modString = string;
    bool seperatorLeft = true;
    while (seperatorLeft) {
        if (modString.find(seperator) == std::string::npos) {
            seperatorLeft = false;
            returnString.push_back(modString);
            break;
        }
        returnString.push_back(modString.substr(0, modString.find(seperator) - 1));
        modString = modString.substr(modString.find(seperator) + seperator.size() + 1, modString.length());
    }
    return returnString;
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
	int currentFrame = 0, lastFrame = 0;
	bool buttons = false, music = false, tag = false;
	LoadedRoomClass LoadedRoom{};
	FrameClass CurrentLoadedFrame;
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		
        if (line.find('[') == 0 && line.find(']') == line.size() - 1) {
            tag = true;
        }

		if (tag == false && line.find("-----") == std::string::npos) {
			continue; // if it is first line aka defining size of room for editor
		}

        std::string tagType;
        std::string tagData;
        if (tag) {
            tagType = line.substr(1, line.size() - 2);
            if (tagType.find("frame") == 0) {
                tagType = "frame";
                tagData = line.substr(line.find(':') + 1);
                tagData = tagData.substr(0, tagData.length() - 1);
            }
        }

        if (tagType == "frame") {
            lastFrame = currentFrame;
            currentFrame = std::stoi(tagData);

            if (currentFrame != lastFrame) {
				LoadedRoom.frames.push_back(CurrentLoadedFrame);
				std::cout << "Log: frame placed in LoadedRoom" << std::endl;
				CurrentLoadedFrame = FrameClass();
			}

            continue;
        }

        if (tagType == "buttons") {
            buttons = true;
            continue;
        }

        if (tagType == "music") {
            buttons = false;
			music = true;
			continue;
        }

		if(buttons == true) {
            std::vector<std::string> splitString = RaylibAdditions::splitString(line, "-----");

			std::string texture = splitString[1];
			float textureX = stof(splitString[2]);
			float textureY = stof(splitString[3]);
			float scale = stof(splitString[4].substr(1));
			if(3 == splitString.size()) {
				LoadedRoom.Buttons.push_back(RaylibAdditions::LoadedButtonClass(LoadTexture((path + "Textures/" + texture + ".png").c_str()), {textureX, textureY}, scale));
				continue;
			}
			Sound soundPressed = LoadSound((path + "Sounds/" + splitString[5] + ".wav").c_str());
			Sound soundReleased = LoadSound((path + "Sounds/" + splitString[6] + ".wav").c_str());
			LoadedRoom.Buttons.push_back(RaylibAdditions::LoadedButtonClass(LoadTexture((path + "Textures/" + texture + ".png").c_str()), {textureX, textureY}, scale, soundPressed, soundReleased));
			continue;
		}
		if (music == true) {
			line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
			LoadedRoom.music = LoadSound((path + "Music/" + line + ".wav").c_str());
			break;
		}
        std::vector<std::string> splitString = RaylibAdditions::splitString(line, "-----");

		std::string texture = splitString[1];
		float textureX = stof(splitString[2]);
		float textureY = stof(splitString[3]);
		float scale = stof(splitString[4].substr(1));
		if (!LoadedRoom.textures.contains(texture))
			LoadedRoom.textures.emplace(texture, LoadTexture((path + "Textures/" + texture + ".png").c_str()));
		CurrentLoadedFrame.textures.push_back(&LoadedRoom.textures.at(texture));
		std::cout << "Log: texture placed in frame: " << path + "Textures/" + texture + ".png" << std::endl;
		CurrentLoadedFrame.texturePos.push_back(Vector2{textureX, textureY});
		std::cout << "Log: texturePos placed in frame: " << textureX << " " << textureY << std::endl;
		CurrentLoadedFrame.textureScales.push_back(scale);
		std::cout << "Log: textureScale placed in frame: " << scale << std::endl;
	}

	LoadedRoom.frames.push_back(CurrentLoadedFrame);
	std::cout << "Log: frame placed in LoadedRoom" << std::endl;

	file.close();
	return LoadedRoom;
}

RaylibAdditions::LoadedRoomClass RaylibAdditions::RoomClass::unloadRoom(RaylibAdditions::LoadedRoomClass room) {
	for (auto& frame : room.frames) {
		for (auto& texture : room.textures) {
			UnloadTexture(texture.second);
		}
	}

	for (auto& button : room.Buttons) {
		UnloadTexture(button.texture);
		UnloadSound(button.pressedSound);
		UnloadSound(button.releasedSound);
	}

	UnloadSound(room.music);

	return RaylibAdditions::LoadedRoomClass();
}

void RaylibAdditions::RoomClass::drawFrameClass(FrameClass* frame) {
	for(int i = 0; i < frame->texturePos.size(); i++) {
		if (i > frame->textures.size() || i > frame->textureScales.size()) {
			std::cout << "drawFrameClass error dumping frame info: " << frame->textures.data() << std::endl;
			return;
		}
		DrawTexture(*(frame->textures[i]), frame->texturePos[i].x, frame->texturePos[i].y, WHITE);
	}
}

void RaylibAdditions::Menu::Menu::DrawAndUpdate() {
	Rectangle MenuBox = {};
	if (centered) {
		MenuBox.x = (GetScreenWidth() / 2) - (menuSize.x / 2);
		MenuBox.y = (GetScreenHeight() / 2) - (menuSize.y / 2);
	} else {
		MenuBox.x = xPos;
		MenuBox.y = yPos;
	}
	MenuBox.width = menuSize.x;
	MenuBox.height = menuSize.y;

	std::vector<Rectangle> MenuTabs = {};
	for (int i = 0; i < pageTitles.size(); i++) {
		MenuTabs.push_back( {MenuBox.x + outlineThickness + i * ((MenuBox.width - (outlineThickness * 2)) / pageTitles.size()),
		MenuBox.y,
		((MenuBox.width - (outlineThickness * 2)) / pageTitles.size()),
		titleBoxHeight } );
	}

	int i = 0;
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		for (Rectangle& MenuTab : MenuTabs) {
			if (CheckCollisionPointRec(GetMousePosition(), MenuTab))
				selectedPage = i;
			i++;
		}
	}

	RaylibAdditions::drawRectWOutline(MenuBox, outlineThickness, background, outline);
	for (int i = 0; i < MenuTabs.size(); i++) {
		if (i == selectedPage)
			drawRectWOutlineWText(MenuTabs.at(i), outlineThickness, LIGHTGRAY, outline, pageTitles.at(i), titleFontSize, textColor);
		else
			drawRectWOutlineWText(MenuTabs.at(i), outlineThickness, background, outline, pageTitles.at(i), titleFontSize, textColor);
	}

	i = 0;
	std::vector<Rectangle> settingsEntry = {};
	std::vector<std::string> settingsEntryText;
	for (auto& setting : settings.at(selectedPage)) {
		settingsEntry.push_back({MenuBox.x + outlineThickness + 10, 
		MenuBox.y + titleBoxHeight + float(outlineThickness) + i * (entryFontSize + 5.0f), 
		MenuBox.width - (float(outlineThickness) * 2.0f), 
		float(entryFontSize) + 5.0f});
		settingsEntryText.push_back(setting.first);
		i++;
	}

	for (int i = 0; i < settingsEntry.size(); i++) {
		RaylibAdditions::drawTextLeftCenterRect(settingsEntry.at(i), settingsEntryText.at(i), entryFontSize, textColor);
		if (auto value = std::get_if<toggleBox>(&settings.at(selectedPage).find(settingsEntryText.at(i))->second)) {
			Rectangle box {settingsEntry.at(i).x + MeasureText(settingsEntryText.at(i).c_str(), entryFontSize) + 10,
			settingsEntry.at(i).y,
			float(entryFontSize), float(entryFontSize)};
			DrawRectangleLinesEx(box, 1, BLACK);

			if (value->state == true) {
				DrawLineEx({box.x, box.y}, {box.x + box.width, box.y + box.height}, entryFontSize/10, BLACK);
				DrawLineEx({box.x, box.y + box.height}, {box.x + box.width, box.y}, entryFontSize/10, BLACK);
			}
		}

		if (auto value = std::get_if<slider>(&settings.at(selectedPage).find(settingsEntryText.at(i))->second)) {
			Rectangle sliderBox {settingsEntry.at(i).x + MeasureText(settingsEntryText.at(i).c_str(), entryFontSize) + 10,
			settingsEntry.at(i).y,
			float(entryFontSize) * 5.0f, float(entryFontSize)};
			value->procentageRect = {sliderBox.x + 1, sliderBox.y + 1, (sliderBox.width - 2) * (value->procentage / 100), sliderBox.height - 2};

			DrawRectangleLinesEx(sliderBox, 1, BLACK);
			DrawRectangleRec(value->procentageRect, GREEN);

			
		}
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		i = 0;
		for (Rectangle& entry : settingsEntry) {
        if (CheckCollisionPointRec(GetMousePosition(), entry)) {
            auto& settingMap = settings.at(selectedPage);
            auto it = settingMap.find(settingsEntryText.at(i));

            if (it != settingMap.end()) {
                if (auto value = std::get_if<toggleBox>(&it->second)) {
					if (value->state == false)
                    	value->state = true;
					else 
						value->state = false;
                }

				if (auto value = std::get_if<slider>(&it->second)) {
					// DO THING
                }
            }
        }
        i++;
    }
	}
}
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

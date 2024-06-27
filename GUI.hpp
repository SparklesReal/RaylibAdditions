#include "RaylibAdditions.hpp"

#include <vector>
#include <raylib.h>
#include <variant>
#include <string>

namespace RaylibAdditions {

    std::vector<std::string> splitString(std::string string, std::string seperator);

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
        Camera2D camera;

        // Loads a .gui room made with RaylibGuiCreator https://github.com/SparklesReal/RaylibGuiCreator also this needs to be rewritten
        LoadedRoomClass loadRoom(std::string path, std::string fileName);
        // Unloads a LoadedRoomClass
        RaylibAdditions::LoadedRoomClass unloadRoom(LoadedRoomClass room);
        // Draws a single frameclass
        void drawFrameClass(FrameClass* frame);
    };
}
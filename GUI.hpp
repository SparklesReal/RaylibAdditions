#include "RaylibAdditions.hpp"

#include <vector>
#include <raylib.h>
#include <variant>
#include <string>

namespace RaylibAdditions {

    std::vector<std::string> splitString(std::string string, std::string seperator);

    class FrameClass {
        public:
        std::vector<Texture2D*> textures;
        std::vector<Vector2>   texturePos;
        std::vector<float>     textureScales;
    };

    class LoadedRoomClass {
        public:
        std::unordered_map<std::string, Texture2D>      textures;
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

    namespace Menu {

        class slider {

        };
        
        class toggleBox {
            public:
            bool state = false;
        };

        class stringList {
            public:
            std::vector<std::string> items;
        };

        class Menu {
            bool centered = false;
            float xPos, yPos = 0;
            std::vector<std::string> pageTitles;
            int selectedPage = 0;
            Vector2 menuSize {500, 500};

            public:
                Menu(bool center, std::vector<std::string> pageNames, Vector2 size = {800, 800}, float x = 0, float y = 0) : centered(center), pageTitles(pageNames), menuSize(size), xPos(x), yPos(y) {};

                std::vector<std::unordered_map<std::string, std::variant<toggleBox, slider, stringList>>> settings; // Name, type
                int fontSize = 20;
                int outlineThickness = 10;
                float titleBoxHeight = 50.0;
                Color background = DARKGRAY;
                Color outline = BLACK;
                Color textColor = BLACK;

                void DrawAndUpdate();
        };
    }
}
#include <raylib.h>
#include <string>

namespace DrawStructs {

    struct DrawRectRectStruct {
        Rectangle* rect;
        Color color;
    };

    struct DrawTextCenterRectStruct {
        Rectangle* rect;
        std::string* text;
        int fontSize;
        Color color;
    };

    struct DrawTextureStruct {
        Texture2D* texture;
        Vector2* pos;
    };

}

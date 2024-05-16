// This File is for testing code please undo all changes to this file before committing if you are not trying to in some way improve this file
#include "RaylibAdditions.h"
#include <raylib.h>

int main() {
    RaylibAdditions::WindowClass Window("RaylibAdditions test", GetScreenWidth(), GetScreenHeight());

    Rectangle testTextRect{100, 100, 600, 600};
    std::string testTextString = "Test";

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        RaylibAdditions::drawRectWOutlineWText(testTextRect, 10, GRAY, LIGHTGRAY, testTextString, 10, BLACK);
        EndDrawing();
    }

    return 0;
}
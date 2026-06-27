#include "raylib.h"

#define SCREEN_WIDTH 987
#define SCREEN_HEIGHT 610

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jet Game");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Hello, World!", 400, 250, 42, WHITE);
        EndDrawing();
    }
    CloseWindow();  
    return 0;
}

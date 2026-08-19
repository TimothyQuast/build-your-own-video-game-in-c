#include "raylib.h"

#define SCREEN_WIDTH 987
#define SCREEN_HEIGHT 610
#define TARGET_FPS 60

#define JET_HEIGHT 30
#define JET_WIDTH 50

typedef struct Jet {
    Vector2 position;
    Vector2 v1;
    Vector2 v2;
    Vector2 v3;
} Jet;

Jet jet = (Jet){ 
    .position = (Vector2){ 100, 100 }
};

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jet Game");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) {
        
        jet.v1 = (Vector2) {
            .x = jet.position.x,
            .y = jet.position.y + JET_HEIGHT,
        };
        
        jet.v2 = (Vector2) {
            .x = jet.position.x + JET_WIDTH,
            .y = jet.position.y + JET_HEIGHT
        };
        
        jet.v3 = (Vector2) {
            .x = jet.position.x + JET_WIDTH / 2,
            .y = jet.position.y 
        };


        BeginDrawing();
            ClearBackground(BLACK);

            DrawRectangleV(jet.position, (Vector2){10, 10}, BLUE);
            
            DrawTriangle(jet.v1, jet.v2, jet.v3, BLUE);
            //DrawText("Hello, World!", 400, 250, 42, WHITE);
        EndDrawing();
    }
    CloseWindow();  
    return 0;
}

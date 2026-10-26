#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 987
#define SCREEN_HEIGHT 610
#define TARGET_FPS 60
#define NUM_ASTEROIDS 10

typedef struct Jet {
    Vector2 position;
    Vector2 v1;
    Vector2 v2;
    Vector2 v3;
} Jet;
const Vector2 JET_SIZE = (Vector2){34, 55};
float jet_speed = 5.0;
Jet jet = (Jet) {
    .position = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT * 2 / 3 }
};

typedef struct Asteroid {
    Vector2 position;
    int exists;
} Asteroid;
const Vector2 ASTEROID_SIZE = (Vector2){34, 55};
const float ASTEROID_SPEED = 2.0;
Asteroid asteroids[NUM_ASTEROIDS];

void handle_movement() {
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        jet.position.y += jet_speed;
    }
    
    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        jet.position.y -= jet_speed;
    }
    
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        jet.position.x -= jet_speed;
    }
    
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        jet.position.x += jet_speed;
    }
     
}

void set_jet_vertices() {
    jet.v1.x = JET_SIZE.x / 2 + jet.position.x;
    jet.v1.y = jet.position.y;

    jet.v2 = (Vector2) {
        JET_SIZE.x + jet.position.x,
        JET_SIZE.y + jet.position.y 
    };
    jet.v3 = (Vector2) {
        jet.position.x,
        JET_SIZE.y + jet.position.y 
    };

}

void maybe_generate_asteroid() {
    double g;
    double r;
    for (int i = 0; i < NUM_ASTEROIDS; i++){
        if (!asteroids[i].exists) {
            g = rand() / (double)RAND_MAX;      
            if (g < .05) {
                r = rand() / (double)RAND_MAX; 
                asteroids[i].exists = 1;
                asteroids[i].position.x = r * (SCREEN_WIDTH - ASTEROID_SIZE.x);
                asteroids[i].position.y = 0;
            }
            return;
        }
    }
}

void step_asteroids() {
    for (int i = 0; i < NUM_ASTEROIDS; i++){
        if (asteroids[i].exists) {
            asteroids[i].position.y += ASTEROID_SPEED;
            if (asteroids[i].position.y > SCREEN_HEIGHT) {
                asteroids[i].exists = 0;
            }
        }
    }
}

int main(void) {
    srand((unsigned)time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Jet Game");
    SetTargetFPS(TARGET_FPS);

    while (!IsWindowReady()) {}
    SetWindowFocused();
    
    // make sure that no asteroids exist at game start
    for (int i = 0; i < NUM_ASTEROIDS; i++) {
        asteroids[i].exists = 0;
    }

    while (!WindowShouldClose()) {

        handle_movement();
        set_jet_vertices();
        maybe_generate_asteroid();
        step_asteroids();

        BeginDrawing();
            ClearBackground(BLACK);
            // DrawRectangleV(jet.position, JET_SIZE, BLUE);
            DrawTriangle(jet.v3, jet.v2, jet.v1, BLUE);
            for (int i = 0; i < NUM_ASTEROIDS; i++) {
                if (asteroids[i].exists) {
                    DrawRectangleV(asteroids[i].position, ASTEROID_SIZE, GRAY);
                }

            }
        EndDrawing();
    }
    CloseWindow();  
    return 0;
}

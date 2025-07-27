#include <raylib/raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>
#include "conf.h"
#include <cstdlib>
#include <ctime>

static Color particleColors[4] = {
    PARTICLE_COLOR_1,
    PARTICLE_COLOR_2,
    PARTICLE_COLOR_3,
    PARTICLE_COLOR_4
};

Color getRandomParticleColor() {
    return particleColors[rand() % 4];
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetExitKey(KEY_Q);
    SetTargetFPS(60);
    srand(time(NULL)); // Seed RNG once

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            static bool paused = false;

            const char* welcomeMsg = "Particle Life Simulator\n(Press Q to quit)";
            int textWidth = MeasureText("Particle Life Simulator", 20);
            int textHeight = 40;
            DrawText(welcomeMsg,
                WINDOW_WIDTH / 2 - textWidth / 2,
                WINDOW_HEIGHT / 2 - textHeight / 2,
                20,
                GRAY);

            for (int y = 50; y < WINDOW_HEIGHT - 50; y += 50) {
                for (int x = 50; x < WINDOW_WIDTH - 50; x += 50) {
                    if (not paused) {
                        DrawCircle(x + 25, y + 25, 3, getRandomParticleColor());
                    } else {
                        DrawCircle(x + 25, y + 25, 5, GRAY);
                    }
                    
                }
            }

            // --- raygui controls panel placeholder ---
            Rectangle panel = { WINDOW_WIDTH - 230, 30, 200, 120 };
            GuiGroupBox(panel, "Controls");

            GuiCheckBox((Rectangle){panel.x + 15, panel.y + 30, 20, 20}, "Paused", &paused);

            GuiLabel((Rectangle){panel.x + 15, panel.y + 60, 170, 20}, "No features implemented yet.");

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

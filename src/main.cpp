#include <array>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "raylib/raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raylib/raygui.h"

#include "conf.h"

enum class PType
{
    P_RED,
    P_CYAN,
    P_YELLOW,
    P_MAGENTA
};

static constexpr int TYPE_COUNT = 4;

static const std::array<Color, TYPE_COUNT> TYPE_COLOR = {
    Color{255, 85, 85, 255},  // P_RED
    Color{85, 255, 255, 255}, // P_CYAN
    Color{255, 255, 85, 255}, // P_YELLOW
    Color{255, 85, 255, 255}  // P_MAGENTA
};

struct Vec
{
    float x, y;
    Vec(float a = 0, float b = 0) : x(a), y(b) {}
};

struct Particle
{
    Vec pos;
    Vec vel;
    PType type;
    Particle(Vec p, PType t) : pos(p), vel{0, 0}, type(t) {}
};

static float randomx()
{
    return (static_cast<float>(rand()) / RAND_MAX) * WINDOW_WIDTH + 1;
}

static float randomy()
{
    return (static_cast<float>(rand()) / RAND_MAX) * WINDOW_HEIGHT + 1;
}

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetExitKey(KEY_Q);
    SetTargetFPS(60);
    srand(static_cast<unsigned int>(time(nullptr)));

    // Interaction matrix rule[target][source]
    std::array<std::array<float, TYPE_COUNT>, TYPE_COUNT> rule = {{
        {-101.0f, 13.5f, -331.0f, -57.5f}, // P_RED
        {-42.0f, -56.5f, -81.0f, 34.5f},   // P_CYAN
        {-6.5f, -41.1f, -21.0f, -35.0f},   // P_YELLOW
        {-71.5f, 13.5f, 46.75f, -20.5f}    // P_MAGENTA
    }};

    std::vector<Particle> particles;
    particles.reserve(3000);

    auto spawn = [&](int count, PType t)
    {
        for (int i = 0; i < count; ++i)
            particles.emplace_back(Vec{randomx(), randomy()}, t);
    };

    spawn(500, PType::P_RED);
    spawn(500, PType::P_CYAN);
    spawn(500, PType::P_YELLOW);
    spawn(500, PType::P_MAGENTA);

    constexpr float minDistSq = 10.0f * 10.0f;
    constexpr float maxDistSq = 80.0f * 80.0f;
    constexpr float bounceRadius = 3.0f;

    float timeScale = 1.0f;

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime() * timeScale;

        // Update physics
        for (size_t i = 0; i < particles.size(); ++i)
        {
            auto &pi = particles[i];
            Vec f{0, 0};
            int ti = static_cast<int>(pi.type);

            for (size_t j = 0; j < particles.size(); ++j)
            {
                if (i == j)
                    continue;

                auto &pj = particles[j];
                int tj = static_cast<int>(pj.type);

                if (ti < 0 || ti >= TYPE_COUNT || tj < 0 || tj >= TYPE_COUNT)
                {
                    TraceLog(LOG_ERROR, TextFormat("Particle type out of bounds: ti=%d tj=%d", ti, tj));
                    continue;
                }

                Vec d{pi.pos.x - pj.pos.x, pi.pos.y - pj.pos.y};
                float distSq = d.x * d.x + d.y * d.y;

                if (distSq > minDistSq && distSq < maxDistSq)
                {
                    float dist = sqrtf(distSq);
                    float g = rule[ti][tj] / dist;

                    f.x += g * d.x;
                    f.y += g * d.y;
                }
                else if (distSq <= minDistSq)
                {
                    float g = 20.0f / (distSq + 1.0f);
                    f.x += g * d.x;
                    f.y += g * d.y;
                }
            }

            pi.vel.x = (f.x + pi.vel.x) * 0.5f;
            pi.vel.y = (f.y + pi.vel.y) * 0.5f;

            pi.pos.x += pi.vel.x * dt;
            pi.pos.y += pi.vel.y * dt;

            // Bounce from walls
            if (pi.pos.x < bounceRadius)
            {
                pi.pos.x = bounceRadius;
                pi.vel.x *= -1.5f;
            }
            else if (pi.pos.x > WINDOW_WIDTH - bounceRadius)
            {
                pi.pos.x = WINDOW_WIDTH - bounceRadius;
                pi.vel.x *= -1.5f;
            }

            if (pi.pos.y < bounceRadius)
            {
                pi.pos.y = bounceRadius;
                pi.vel.y *= -1.5f;
            }
            else if (pi.pos.y > WINDOW_HEIGHT - bounceRadius)
            {
                pi.pos.y = WINDOW_HEIGHT - bounceRadius;
                pi.vel.y *= -1.5f;
            }
        }

        // Draw
        BeginDrawing();
        ClearBackground(DARKGRAY);

        for (auto &p : particles)
            DrawCircleV(Vector2{p.pos.x, p.pos.y}, bounceRadius, TYPE_COLOR[static_cast<int>(p.type)]);

        // GUI: Sliders in a single long column, good spacing
        int sliderWidth = 300;
        int sliderHeight = 20;
        int startX = WINDOW_WIDTH - sliderWidth - 20; // right-aligned
        int startY = 10;
        int rowSpacing = sliderHeight + 25; // vertical spacing between sliders

        GuiSetStyle(SLIDER, BORDER_COLOR_NORMAL, 0x550000FF); // Dark red border (RGBA)
        GuiSetStyle(SLIDER, BASE_COLOR_NORMAL, 0xFFFF55FF);   // Bright yellow base (RGBA)
        GuiSetStyle(SLIDER, TEXT_COLOR_NORMAL, 0xFFFFFFFF);   // White text (RGBA)
        GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, 0xFFFFFFFF); // White text (RGBA)

        // Labels for mapping indices to types
        const char *typeNames[TYPE_COUNT] = {"Red", "Cyan", "Yellow", "Magenta"};

        int sliderIndex = 0;
        for (int t = 0; t < TYPE_COUNT; ++t)
        {
            for (int s = 0; s < TYPE_COUNT; ++s)
            {
                float &g = rule[t][s];
                int y = startY + sliderIndex * rowSpacing;

                GuiLabel(Rectangle{static_cast<float>(startX), static_cast<float>(y - sliderHeight / 2), static_cast<float>(sliderWidth), static_cast<float>(sliderHeight)},
                         TextFormat("%s x %s:", typeNames[t], typeNames[s]));

                GuiSlider(Rectangle{static_cast<float>(startX), static_cast<float>(y + 12), static_cast<float>(sliderWidth), static_cast<float>(sliderHeight)},
                          nullptr, nullptr, &g, -500.0f, 500.0f);

                char valueLabel[32];
                snprintf(valueLabel, sizeof(valueLabel), "%.1f", g);
                GuiLabel(Rectangle{static_cast<float>(startX + sliderWidth + 8), static_cast<float>(y + 12), 40.0f, static_cast<float>(sliderHeight)}, valueLabel);

                ++sliderIndex;
            }
        }

        // Time Scale slider below all interaction sliders
        int timeScaleY = startY + sliderIndex * rowSpacing + 20;
        GuiLabel(Rectangle{static_cast<float>(startX), static_cast<float>(timeScaleY - sliderHeight / 2), static_cast<float>(sliderWidth), static_cast<float>(sliderHeight)},
                 "Time Scale:");
        GuiSlider(Rectangle{static_cast<float>(startX), static_cast<float>(timeScaleY + 12), static_cast<float>(sliderWidth), static_cast<float>(sliderHeight)},
                  nullptr, nullptr, &timeScale, 0.1f, 3.0f);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#include <raylib/raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>

#include "conf.h"
#include "utils.h"

static const Color PARTICLE_RED = (Color){255, 85, 85, 255};
static const Color PARTICLE_CYAN = (Color){85, 255, 255, 255};
static const Color PARTICLE_YELLOW = (Color){255, 255, 85, 255};
static const Color PARTICLE_MAGENTA = (Color){255, 85, 255, 255};

struct Vec
{
    float x, y;
    Vec(float a = 0, float b = 0) : x(a), y(b) {}
};

struct Atom
{
    Vec pos;
    Vec vel;
    Color col;
    Atom(Vec position, Color color) : pos(position), vel(0, 0), col(color) {};
};

static std::vector<Atom *> atoms;

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetExitKey(KEY_Q);
    SetTargetFPS(60);
    srand(time(NULL)); // Seed RNG once

    static std::vector<Atom> red = create(500, PARTICLE_RED);
    static std::vector<Atom> cyan = create(500, PARTICLE_CYAN);
    static std::vector<Atom> yellow = create(500, PARTICLE_YELLOW);
    static std::vector<Atom> magenta = create(500, PARTICLE_MAGENTA);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);
        static bool paused = false;

        if (!paused) // update particles only if not paused
        { // this is an example ruleset, pls make your own or copy some from the examples.txt file.
            rule(&red, &red, -0.5f);
            rule(&red, &cyan, 3.2f);
            rule(&red, &yellow, -23.4f);
            rule(&red, &magenta, 17.8f);
            rule(&cyan, &red, 1.3f);
            rule(&cyan, &cyan, -7.7f);
            rule(&cyan, &yellow, -0.33f);
            rule(&cyan, &magenta, 20.0f);
            rule(&yellow, &red, -2.0f);
            rule(&yellow, &cyan, -28.7f);
            rule(&yellow, &yellow, -2.5f);
            rule(&yellow, &magenta, 27.0f);
            rule(&magenta, &red, 6.0f);
            rule(&magenta, &cyan, 8.0f);
            rule(&magenta, &yellow, 19.4f);
            rule(&magenta, &magenta, 22.3f);

            for (int i = 0; i < atoms.size(); i++)
            {
                Atom *atom = atoms[i];
                DrawCircleV((Vector2){atom->pos.x, atom->pos.y}, 3, atom->col);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

float randomx()
{
    return static_cast<float>(rand()) / RAND_MAX * WINDOW_WIDTH + 1;
}

float randomy()
{
    return static_cast<float>(rand()) / RAND_MAX * WINDOW_HEIGHT + 1;
}

std::vector<Atom> create(int n, Color color)
{

    std::vector<Atom> group;
    group.reserve(n);

    for (int i = 0; i < n; i++)
    {
        Vec pos(randomx(), randomy());
        group.push_back(Atom(pos, color));
        atoms.push_back(&group.back());
    }

    return group;
}

void rule(std::vector<Atom> *atoms1, const std::vector<Atom> *atoms2, float g)
{
    for (int i = 0; i < atoms1->size(); i++)
    {
        Vec f(0, 0);
        Atom *a = &(*atoms1)[i];

        for (int j = 0; j < atoms2->size(); j++)
        {
            Atom b = (*atoms2)[j];

            Vec d(
                a->pos.x - b.pos.x,
                a->pos.y - b.pos.y);

            float dist = sqrt(d.x * d.x + d.y * d.y);

            if (dist > 10.0f && dist < 80.0f)
            {
                float F = g / dist;
                f.x = F * d.x;
                f.y = F * d.y;
            }
            else if (dist >= 0.0f && dist <= 10.0f)
            {
                // strong repulsive force to avoid overlap
                float F = 20.0f / (dist * dist + 1.0f); // inverse-square for very short range
                f.x += F * d.x;
                f.y += F * d.y;
            }
        }

        a->vel.x = (f.x + a->vel.x) / 2;
        a->vel.y = (f.y + a->vel.y) / 2;
        float radius = 3.0f;
        a->pos.x += a->vel.x;
        a->pos.y += a->vel.y;

        // Bounce and clamp X
        if (a->pos.x < radius)
        {
            a->pos.x = radius;
            a->vel.x *= -1.5f;
        }
        else if (a->pos.x > WINDOW_WIDTH - radius)
        {
            a->pos.x = WINDOW_WIDTH - radius;
            a->vel.x *= -1.5f;
        }

        // Bounce and clamp Y
        if (a->pos.y < radius)
        {
            a->pos.y = radius;
            a->vel.y *= -1.5f;
        }
        else if (a->pos.y > WINDOW_HEIGHT - radius)
        {
            a->pos.y = WINDOW_HEIGHT - radius;
            a->vel.y *= -1.5f;
        }
    }
}

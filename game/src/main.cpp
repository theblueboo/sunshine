#include "rlImGui.h"
#include "Physics.h"
#include "Collision.h"

#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;



int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Sunshine");
    rlImGuiSetup(true);

    const float radius = 20.0f;
    Vector2 position{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
    Vector2 velocity{0.0f, 0.0f};
    Vector2 acceleration{0.0f, 0.0};

    Vector2 target = GetMousePosition();
    float speed = 500.0f;

    bool useGUI = false;
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        if (IsKeyDown(KEY_E))
            playerRotation += playerRotationSpeed * dt;
        if (IsKeyDown(KEY_Q))
            playerRotation -= playerRotationSpeed * dt;

        const Vector2 playerPosition = GetMousePosition();
        const Vector2 playerDirection = Direction(playerRotation * DEG2RAD);
        const Vector2 playerEnd = playerPosition + playerDirection * playerRange;
        const Rectangle playerRec{ playerPosition.x, playerPosition.y, playerWidth, playerHeight };

        target = GetMousePosition();
        acceleration = Normalize(target - position) * speed - velocity;
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt + acceleration * dt * dt * 0.5f;

        const bool collision = NearestIntersection(playerPosition, playerEnd, obstacles, poi);
        const bool rectangleVisible = IsRectangleVisible(playerPosition, playerEnd, rectangle, obstacles);
        const bool circleVisible = IsCircleVisible(playerPosition, playerEnd, circle, obstacles);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Render player
        DrawRectanglePro(playerRec, { playerWidth * 0.5f, playerHeight * 0.5f }, playerRotation, PURPLE);
        DrawLine(playerPosition.x, playerPosition.y, playerEnd.x, playerEnd.y, BLUE);
        DrawCircleV(playerPosition, 10.0f, BLUE);

        // Render geometry
        for (const Rectangle& obstacle : obstacles)
            DrawRectangleRec(obstacle, GREEN);
        DrawRectangleRec(rectangle, rectangleVisible ? GREEN : RED);
        DrawCircleV(circle.position, circle.radius, circleVisible ? GREEN : RED);

        // Render labels
        DrawText(circleText, nearestCirclePoint.x - circleTextWidth * 0.5f, nearestCirclePoint.y - fontSize * 2, fontSize, BLUE);
        DrawCircleV(nearestRecPoint, 10.0f, BLUE);
        DrawText(recText, nearestRecPoint.x - recTextWidth * 0.5f, nearestRecPoint.y - fontSize * 2, fontSize, BLUE);
        DrawCircleV(nearestCirclePoint, 10.0f, BLUE);
        if (collision)
        {
            DrawText(poiText, poi.x - poiTextWidth * 0.5f, poi.y - fontSize * 2, fontSize, BLUE);
            DrawCircleV(poi, 10.0f, BLUE);
        }

        // Render GUI
        if (IsKeyPressed(KEY_GRAVE)) demoGUI = !demoGUI;
        if (demoGUI)
        {
            rlImGuiBegin();
            ImGui::ShowDemoWindow(nullptr);
            rlImGuiEnd();
        }

        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();

    return 0;
}

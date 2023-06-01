#include "rlImGui.h"
#include "Math.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

Vector2 WraparoundScreen(Vector2 position)
{
    Vector2 outPosition =
    {
        fmodf(position.x + SCREEN_WIDTH, SCREEN_WIDTH),
        fmodf(position.y + SCREEN_HEIGHT, SCREEN_HEIGHT)
    };

    return outPosition;
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(240);

    const float radius = 20.0f;
    Vector2 position{ SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f };
    Vector2 velocity{0.0f, 0.0f};
    Vector2 acceleration{0.0f, 0.0};

    Vector2 target = GetMousePosition();
    float speed = 500.0f;

    bool useGUI = false;
    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();

        target = GetMousePosition();
        acceleration = Normalize(target - position) * speed - velocity;
        velocity = velocity + acceleration * dt;
        position = position + velocity * dt + acceleration * dt * dt * 0.5f;

        if (position.x < 0.0f) position.x = SCREEN_WIDTH;
        if (position.x > SCREEN_WIDTH) position.x = 0.0f;
        if (position.y > SCREEN_HEIGHT) position.y = 0.0f;
        if (position.y < 0.0f) position.y = SCREEN_HEIGHT;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV(position, radius, RED);

        if (IsKeyPressed(KEY_GRAVE)) useGUI = !useGUI;
        if (useGUI)
        {
            rlImGuiBegin();
            ImGui::SliderFloat2("Position", &position.x, 0.0f, SCREEN_WIDTH);
            ImGui::SliderFloat2("Velocity", &velocity.x, -100.0f, 100.0f);
            ImGui::SliderFloat2("Acceleration", &acceleration.x, -10.0f, 10.0f);
            ImGui::Separator();
            ImGui::SliderFloat("Seeker Speed", &speed, -100.0f, 100.0f);
            rlImGuiEnd();
        }

        DrawFPS(10, 10);
        DrawText("Press ~ to open/close GUI", 10, 30, 20, GRAY);
        DrawText(TextFormat("Position: (%f, %f)", position.x, position.y), 10, 50, 20, RED);
        DrawText(TextFormat("Velocity: (%f, %f)", velocity.x, velocity.y), 10, 70, 20, RED);
        DrawText(TextFormat("Acceleration: (%f, %f)", acceleration.x, acceleration.y), 10, 90, 20, RED);
        EndDrawing();
    }

    rlImGuiShutdown();
    CloseWindow();
    return 0;
}
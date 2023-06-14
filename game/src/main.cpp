#include "rlImGui.h"
#include "Physics.h"
#include "Collision.h"
#include "Math.h"
#include "raylib.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720



using namespace std;

Vector2 WraparoundScreen(Vector2 position)
{
    Vector2 outPosition =
    {
        fmodf(position.x + SCREEN_WIDTH, SCREEN_WIDTH),
        fmodf(position.y + SCREEN_HEIGHT, SCREEN_HEIGHT)
    };

    return outPosition;
}

//Vector2 LimitMagnitude(const Vector2& toLimit, float maxLength)
//{
  //  float lengthSq = LengthSqr(toLimit);
//    if (lengthSq > maxLength * maxLength)
//}


//void Restart()
//{

//}


//std::vector<Agent*> 
int main(void)
{


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(240);




    enum GameState
    {
        NONE,
        SEEK,
        FLEE,
        ARRIVAL,
        AVOID
    };

    const float radius = 20.0f;
    Vector2 position{ (rand() % SCREEN_WIDTH) + 1, (rand() % SCREEN_HEIGHT) + 1 };
    Vector2 velocity{0.0f, 0.0f};
    Vector2 acceleration{0.0f, 0.0};
    Vector2 target;
    float speed = 100.0f;
    float Maxspeed = 200.0f;


    enum GameState currentState;
    currentState = NONE;

    bool useGUI = false;
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        float dt = GetFrameTime();

        velocity = velocity + acceleration * dt;
        position = position + velocity * dt + acceleration * dt * dt * 0.5f;
        //speed = ((target*) - (position*)(velocity));
        //if (Maxspeed < speed)
        //{
          //  velocity = velocity * (Maxspeed / speed);
        //}
    


    
            

        if (IsKeyPressed(KEY_ZERO)) currentState = NONE;
        if (IsKeyPressed(KEY_ONE)) currentState = SEEK;
        if (IsKeyPressed(KEY_TWO)) currentState = FLEE;
        if (IsKeyPressed(KEY_THREE)) currentState = ARRIVAL;
        if (IsKeyPressed(KEY_FOUR)) currentState = AVOID;
        //if (IsKeyPressed(KEY_SPACE)) return ;

            if (currentState==SEEK)
            {
                DrawText(TextFormat("Current Mode: SEEK"), 500, 30, 20, BLACK);
                    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                    {
                        target = GetMousePosition();

                        acceleration = Normalize(target - position) * speed - velocity;

                        
                    }
            }
            else if (currentState == FLEE)
            {
                DrawText(TextFormat("Current Mode: FLEE"), 500, 30, 20, BLACK);
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    target = GetMousePosition();

                    acceleration = (Normalize(target - position)) * -1 * speed - velocity;
                }
            }
            if (currentState == ARRIVAL)
            {
                DrawText(TextFormat("Current Mode: ARRIVAL"), 500, 30, 20, BLACK);
            }
            if (currentState == AVOID)
            {
                DrawText(TextFormat("Current Mode: AVOID"), 500, 30, 20, BLACK);
            }
            else if (currentState == NONE)
            {
               DrawText(TextFormat("Current Mode: NONE"), 500, 30, 20, BLACK);
            }
            
        
        

        if (position.x < 0.0f) position.x = SCREEN_WIDTH;
        if (position.x > SCREEN_WIDTH) position.x = 0.0f;
        if (position.y > SCREEN_HEIGHT) position.y = 0.0f;
        if (position.y < 0.0f) position.y = SCREEN_HEIGHT;


        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawCircleV (position, radius, RED);
        

        

        // Render GUI
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

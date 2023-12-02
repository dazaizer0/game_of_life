#include "sollib/ellibs.h"
#include "sollib/solnms.h"

int main()
{
    // INITIALIZATION
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game of life");
    SetTargetFPS(8);

    // CREATE A NEW SYSTEM OF LIFE
    sol::system_of_life sol;

    bool paused = false;

    // SETUP CAMERA
    Camera2D camera = { 0 };
    camera.target = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    camera.offset = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    camera.zoom += (float)GetMouseWheelMove() * 0.05f;

    // MAIN LOOP
    while (!WindowShouldClose())
    {
        if (!paused)
        {
            // UPDATE CAMERA
            if (IsKeyDown(KEY_RIGHT)) camera.target.x += 10;
            if (IsKeyDown(KEY_LEFT)) camera.target.x -= 10;
            if (IsKeyDown(KEY_DOWN)) camera.target.y += 10;
            if (IsKeyDown(KEY_UP)) camera.target.y -= 10;

            camera.zoom += (float)GetMouseWheelMove() * 0.05f;

            if (IsKeyDown(KEY_R))
            {
                camera.target = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
                camera.zoom = 1.0f;
            }

            // UPDATE SYSTEM OF LIFE
            sol.update_system();

            // DRAW
            BeginDrawing();

            // SET BACKGROUND COLOR
            ClearBackground(BLACK);
            BeginMode2D(camera);

            // GENERATE SYSTEM
            sol.generate_system();

            // ADD CELL BY PLAYER
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                Vector2 mouse_position = GetMousePosition();

                // Place square at the mouse click position
                //mouse_position.x = mouse_position.x * CELL_SIZE;
                //mouse_position.y = mouse_position.y * CELL_SIZE;

                sol.add_cell(mouse_position);
            }

            EndMode2D();

            // UI PANEL
            DrawRectangle(0, 0, SCREEN_WIDTH, 70, BLACK);

            // GENERATE BUTTON
            if (IsKeyDown(KEY_S))
            {
                sol.create_artificial_generation(128);
            }

            // TEXT
            DrawText("you can only place new cells with default camera position and zoom", 10, 10, 24, GREEN);
            DrawText("> press 'r' to restore camera |'s' to spawn artificial generation |'left mouse' to spawn one cell", 10, 38, 20, GREEN);

            EndDrawing();
        }
        else
        {
            continue;
        }
    }

    // DE-INITIALIZATION
    CloseWindow();

    return 0;
}

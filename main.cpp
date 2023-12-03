#include "mollib/ellibs.h"
#include "mollib/molnms.h"

int main()
{
    // INITIALIZATION
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "manager of - game of life");
    SetTargetFPS(8);

    // CREATE A NEW SYSTEM OF LIFE
    mol::game_of_life mol;

    bool start_screen = true;

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

        if (IsKeyDown(KEY_C)) start_screen = false;

        // UPDATE SYSTEM OF LIFE
        mol.update_system();

        // DRAW
        BeginDrawing();

        // SET BACKGROUND COLOR
        ClearBackground(BLACK);
        BeginMode2D(camera);

        // GENERATE SYSTEM
        mol.generate_system();

        // ADD CELL BY PLAYER
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mouse_position = GetMousePosition();
            mol.add_cell(mouse_position);
        }

        EndMode2D();

        // UI PANEL
        if (start_screen)
        {
            Vector2 ssp = {102, 160};
            DrawRectangle(ssp.x, ssp.y, 800, 400, GREEN);
            DrawRectangle(ssp.x + 5, ssp.y + 5, 790, 390, BLACK);

            DrawText("> you can only place new cells with default camera position and zoom",
                     ssp.x + 10, ssp.y + 10, 22, GREEN);

            DrawText("> press: \n "
                     ">  >r<  to restore camera \n "
                     ">  >esc<  to quit the game \n "
                     ">  >s<  to spawn artificial generation \n "
                     ">  >left mouse<  to spawn one cell \n "
                     ">  >c<  to close this window and continue ",
                     ssp.x + 10, ssp.y + 38, 21, GREEN);
        }

        // GENERATE BUTTON
        if (IsKeyDown(KEY_S))
        {
            mol.create_artificial_generation(128);
        }

        EndDrawing();
    }

    // DE-INITIALIZATION
    CloseWindow();

    return 0;
}

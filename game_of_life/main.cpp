#include "sollib/ellibs.h"
#include "sollib/solnms.h"

int main()
{
    // INITIALIZATION
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game of life");
    SetTargetFPS(8);

    // CREATE A NEW SYSTEM OF LIFE
    sol::system_of_life sol;

    // CREATING ARTIFICIAL GENERATION PROPERTIES
    const int duration = 32;
    int refresh_counter = 0;

    // MAIN LOOP
    while (!WindowShouldClose())
    {
        // UPDATE SYSTEM OF LIFE
        sol.update_system();

        // DRAW
        BeginDrawing();

        // SET BACKGROUND COLOR
        ClearBackground(BLACK);

        // GENERATE SYSTEM
        sol.generate_system();

        // CREATE A NEW ARTIFICIAL GENERATION TO SUPPORT THE POPULATION
        /*if (refresh_counter == duration)
        {
            sol.create_artificial_generation(128);
            refresh_counter = 0;
        }
        else
        {
            refresh_counter += 1;
        }*/

        EndDrawing();
    }

    // DE-INITIALIZATION
    CloseWindow();

    return 0;
}

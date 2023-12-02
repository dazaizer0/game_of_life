#ifndef GAME_OF_LIFE_SOLNMS_H
#define GAME_OF_LIFE_SOLNMS_H

#include "ellibs.h"

// CONSTANT VARIABLES
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 720;

const int CELL_SIZE = 5;

const int ROWS = SCREEN_HEIGHT / CELL_SIZE;
const int COLS = SCREEN_WIDTH / CELL_SIZE;

// SOL
namespace sol
{
    // SYSTEM
    class system_of_life
    {
    public:
        // CONSTRUCTOR
        system_of_life() : system(ROWS, std::vector<bool>(COLS, false))
        {
            // INITIALIZE SYSTEM
            system_init();
        }

        // UPDATE
        void update_system()
        {
            // CREATE TEMPORARY SYSTEM
            auto new_system = system;

            for (int i = 0; i < ROWS; ++i)
            {
                for (int j = 0; j < COLS; ++j)
                {
                    // UPDATE SYSTEM
                    int alive_neightbors = count_alive_neightbors(i, j);
                    new_system[i][j] = (system[i][j] && alive_neightbors >= 2 && alive_neightbors <= 3) ||
                                     (!system[i][j] && alive_neightbors == 3);
                }
            }

            // REPLACE SYSTEM BY TEMPORARY SYSTEM
            system = new_system;
        }

        // ADD NEW CELL
        void add_cell(Vector2 position)
        {
            int cell_x = static_cast<int>(position.x / CELL_SIZE);
            int cell_y = static_cast<int>(position.y / CELL_SIZE);

            if (cell_x >= 0 && cell_x < COLS && cell_y >= 0 && cell_y < ROWS)
            {
                system[cell_y][cell_x] = !system[cell_y][cell_x];

                // GENERATE CELL
                Color cell_color = system[cell_y][cell_x] ? RED : BLACK;
                DrawRectangle(cell_x * CELL_SIZE, cell_y * CELL_SIZE, CELL_SIZE, CELL_SIZE, cell_color);
            }
        }

        // GENERATE / DRAW
        void generate_system()
        {
            for (int i = 0; i < ROWS; ++i)
            {
                for (int j = 0; j < COLS; ++j)
                {
                    // GENERATE CELLS
                    Color cell_color = system[i][j] ? GREEN : BLACK;
                    DrawRectangle(j * CELL_SIZE, i * CELL_SIZE, CELL_SIZE, CELL_SIZE, cell_color);
                }
            }
        }

        // GENERATE NEW ARTIFICIAL GENERATION TO SUPPORT SYSTEM
        void create_artificial_generation(int newborns_amount)
        {
            std::random_device rd;
            std::mt19937 gen(rd());

            std::uniform_int_distribution<int> dist_x(0, ROWS - 1);
            std::uniform_int_distribution<int> dist_y(0, COLS - 1);

            for (int i = 0; i < newborns_amount; ++i)
            {
                // GENERATE RANDOM POSITION
                int random_x = dist_x(gen);
                int random_y = dist_y(gen);
                 // ADD CELL TO SYSTEM
                system[random_x][random_y] = true;

                // GENERATE CELL
                Color cell_color = system[random_x][random_y] ? PINK : BLACK;
                DrawRectangle(random_y * CELL_SIZE, random_x * CELL_SIZE, CELL_SIZE, CELL_SIZE, cell_color);
            }
        }

    private:
        // SYSTEM VECTOR
        std::vector<std::vector<bool>> system;

        // INITIALIZATION
        void system_init()
        {
            std::srand(std::time(0));

            for (int i = 0; i < ROWS; ++i)
            {
                for (int j = 0; j < COLS; ++j)
                {
                    // CREATE CELL
                    system[i][j] = std::rand() % 2 == 1;
                }
            }
        }

        // COUNT ALIVE CELLS IN RANGE
        int count_alive_neightbors(int x, int y)
        {
            int neightbors_counter = 0;

            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    // CONTINUE IF 0,0
                    if (i == 0 && j == 0)
                    {
                        continue;
                    }

                    int another_x = x + i;
                    int another_y = y + j;

                    // IF THE CONDITIONS AGREE = COUNT
                    if (another_x >= 0 && another_x < ROWS && another_y >= 0 && another_y < COLS)
                    {
                        if (system[another_x][another_y])
                        {
                            ++neightbors_counter;
                        }
                    }
                }
            }

            return neightbors_counter;
        }
    };
};
#endif
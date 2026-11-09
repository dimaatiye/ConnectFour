#include "main.h"
#include "raylib.h"
#include "Buttons.h"

int main(void)
{
    InitWindow(1900, 1300, "raylib example - basic window");
    Buttons button;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        button.DrawButton();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
#include "main.h"
#include "raylib.h"
#include "Buttons.h"
#include "Board.h"
int main(void)
{
    InitWindow(1900, 1300, "raylib example - basic window");
    Buttons button;
    Board board;


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        button.DrawButton();
        board.DrawBoard();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
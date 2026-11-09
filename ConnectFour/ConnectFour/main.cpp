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

		int selectedColumn = button.CheckButtonClick();//check if any button is clicked and get the column index
		if (selectedColumn != -1)//check if a valid column is selected
		{
			board.PlacePiece(selectedColumn, 'X');//place player x's piece in the selected column
		}
        BeginDrawing();
        ClearBackground(BLACK);
        button.DrawButton();
        board.DrawBoard();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
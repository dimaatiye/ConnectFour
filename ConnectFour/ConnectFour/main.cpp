#include "main.h"
#include "raylib.h"
#include "Buttons.h"
#include "Board.h"
int main(void)
{
    InitWindow(1900, 1300, "raylib example - basic window");
    Buttons button;
    Board board;
    char currentPlayer = 'X'; // Player X starts
    bool gameOver = false;
    while (!WindowShouldClose())
    {

		int selectedColumn = button.CheckButtonClick();//check if any button is clicked and get the column index
		if (!gameOver && selectedColumn != -1)//check if a valid column is selected
		{
			board.PlacePiece(selectedColumn, currentPlayer);//place player's piece in the selected column
            if (board.CheckWin(currentPlayer))
            {
                // Player has won
                gameOver = true;
            }
            if (currentPlayer == 'X')
            {
                currentPlayer = 'O'; // Switch to player O
            }
            else
            {
                currentPlayer = 'X'; // Switch back to player X
            }
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
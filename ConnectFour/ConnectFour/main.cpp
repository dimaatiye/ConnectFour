#include "main.h"
#include "raylib.h"
#include "Buttons.h"
#include "Board.h"
#include "Constants.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,  "Gravity Shift Connect 4");
    SetTargetFPS(60);

    Buttons button;
    Board board;
    char currentPlayer = 'X'; // Player X starts
    char winner = ' ';
    bool gameOver = false;


    while (!WindowShouldClose())
    {

		int selectedColumn = button.CheckButtonClick(board.GetCols());//check if any button is clicked and get the column index

		if (!gameOver && selectedColumn != -1 && selectedColumn < board.GetCols() && !board.IsColumnFull(selectedColumn)) //check if a valid column is selected
		{
			board.PlacePiece(selectedColumn, currentPlayer);//place player's piece in the selected column

            if (board.CheckWin(currentPlayer))
            {
                // Player has won
                gameOver = true;
                winner = currentPlayer;
            }
            else {
                if (currentPlayer == 'X')
                {
                    currentPlayer = 'O'; // Switch to player O
                }
                else
                {
                    currentPlayer = 'X'; // Switch back to player X
                }
            }
        }

        // Temporary for testing
        if (IsKeyReleased(KEY_R))
        {
            board.RotateClockwise();
            board.ApplyGravityShift();
        }


        BeginDrawing();
        ClearBackground(BLACK);


        button.DrawButton(board.GetCols());
        board.DrawBoard();

        if (gameOver)
        {
            if (winner == 'X')
            {
                DrawText("Game Over, Red Wins!", 740, 20, 50, RED);
            }
            else
            {
                DrawText("Game Over, Yellow Wins!", 740, 20, 50, YELLOW);
            }
        }
        else
        {
            if (currentPlayer == 'X')
            {
                DrawText("Reds Turn", 800, 20, 50, RED);
            }
            else
            {
                DrawText("Yellows Turn", 800, 20, 50, YELLOW);
            }
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
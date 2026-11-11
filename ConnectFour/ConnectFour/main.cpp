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
    bool gameOver = false;


    while (!WindowShouldClose())
    {
        // Allow the players to reset the game if a win or draw is reached
        if (IsKeyReleased(KEY_R))
        {
            board = Board();
            currentPlayer = 'X';
            gameOver = false;
        }

		int selectedColumn = button.CheckButtonClick(board.GetCols());//check if any button is clicked and get the column index

		if (!gameOver && selectedColumn != -1 && selectedColumn < board.GetCols() && !board.IsColumnFull(selectedColumn)) //check if a valid column is selected
		{
            board.MakeMove(selectedColumn, currentPlayer);

            if (board.GetWinner() != ' ')
            {
                // Player has won
                gameOver = true;
            }
            else
            {
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

        BeginDrawing();
        ClearBackground(BLACK);


        button.DrawButton(board.GetCols());
        board.DrawBoard();

        if (gameOver)
        {
            if (board.GetWinner() == 'X')
            {
                DrawText("Game Over, Red Wins!", 740, 20, 50, RED);
            }
            else if (board.GetWinner() == 'O')
            {
                DrawText("Game Over, Yellow Wins!", 740, 20, 50, YELLOW);
            }
            else
            {
                DrawText("Game is a draw!", 730, 20, 50, WHITE);
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

        if (gameOver)
        {
            DrawText("Press R to restart", 1350, 20, 40, WHITE);
        }
        else
        {
            int movesUntilGravityShift = 4 - (board.GetMoveCount() % 4);
            DrawText(TextFormat("Gravity Shift in: %d", movesUntilGravityShift), 1350, 20, 40, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
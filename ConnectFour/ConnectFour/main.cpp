#include "main.h"
#include "raylib.h"
#include "Buttons.h"
#include "Board.h"
#include "Constants.h"
#include "Menu.h"      
#include "AiPlayer.h"  
int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,  "Gravity Shift Connect 4");
    SetTargetFPS(60);

    Buttons button;
    Board board;
    char currentPlayer = 'X'; // Player X starts
    bool gameOver = false;
    Menu menu;
    bool inMenu = true;
    AiPlayer* aiX = nullptr; 
    AiPlayer* aiO = nullptr; 
    double lastMoveTime = 0; 

    while (!WindowShouldClose())
    {
        if (inMenu)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            menu.UpdateAndDraw();
            EndDrawing();

            if (menu.IsFinished())
            {
                board = Board();
                currentPlayer = 'X';
                gameOver = false;
                delete aiX;
                delete aiO;
                aiX = nullptr;
                aiO = nullptr;

                if (menu.GetGameMode() == PLAYER_VS_AI)
                {
                    aiO = menu.CreateAi('O'); 
                }
                else if (menu.GetGameMode() == AI_VS_AI)
                {
                    aiX = menu.CreateAi('X');
                    aiO = menu.CreateAi('O');
                }

                lastMoveTime = GetTime();
                inMenu = false;
            }

            continue; 
        }

        if (IsKeyReleased(KEY_M))
        {
            menu.Reset();
            inMenu = true;
            continue;
        }

        if (IsKeyReleased(KEY_R))
        {
            board = Board();
            currentPlayer = 'X';
            gameOver = false;
        }
        int selectedColumn = -1;
        AiPlayer* currentAi = aiO;
        if (currentPlayer == 'X')
        {
            currentAi = aiX;
        }

        if (currentAi == nullptr)
        {
            selectedColumn = button.CheckButtonClick(board.GetCols());//check if any button is clicked and get the column index
        }
        else if (!gameOver && GetTime() - lastMoveTime >= 0.6) // wait 0.6 seconds so you can see the AI move
        {
            selectedColumn = currentAi->ChooseMove(board);
        }

		if (!gameOver && selectedColumn != -1 && selectedColumn < board.GetCols() && !board.IsColumnFull(selectedColumn))
		{
            board.MakeMove(selectedColumn, currentPlayer);
            lastMoveTime = GetTime();
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
    delete aiX;
    delete aiO;
    CloseWindow();

    return 0;
}
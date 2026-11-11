#include "Buttons.h"
#include "Constants.h"

Rectangle Buttons::GetButtonRect(int index, int cols)
{
    int left = GetBoardLeft(cols);

    Rectangle rect;
    rect.x = (float)(left + index * CELL_SIZE + 10); // 10 pixle gap on the left
    rect.y = (float)BUTTON_TOP;
    rect.width = (float)(CELL_SIZE - 20); // 10 pixel gap on each side
    rect.height = (float)BUTTON_HEIGHT;
    return rect;
}


void Buttons::DrawButton(int cols)
{
	for (int i = 0; i < cols; i++)
	{
        Rectangle rect = GetButtonRect(i, cols);
        DrawRectangleRec(rect, WHITE);

        int textWidth = MeasureText("Drop", 25);
        int textX = (int)(rect.x + (rect.width - textWidth) / 2);
        int textY = (int)(rect.y + 12);
        DrawText("Drop", textX, textY, 25, BLACK);
	}
}

int Buttons::CheckButtonClick(int cols)
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mousePosition = GetMousePosition();

        for (int i = 0; i < cols; i++)
        {
            if (CheckCollisionPointRec(mousePosition, GetButtonRect(i, cols)))
            {
                return i;
            }
        }
    }

    return -1;
}


#include "scorecounter.hpp"

ScoreCounter::ScoreCounter()
{
    score = 0;

    //store the score as a string in scorestring
    sprintf(scorestring, "%u", score);

    behindScore = gfx_MallocSprite(gfx_GetStringWidth(scorestring) + 8, UNSCALED_TEXT_HEIGHT * TEXT_SCALE);;
}

void ScoreCounter::IncreaseScore()
{
    score++;
}

void ScoreCounter::PreDraw()
{
    free(behindScore);
    behindScore = gfx_MallocSprite(gfx_GetStringWidth(scorestring) + 8, UNSCALED_TEXT_HEIGHT * TEXT_SCALE);
    gfx_GetSprite_NoClip(behindScore, (LCD_WIDTH - gfx_GetStringWidth(scorestring)) / 2 - 4, LCD_HEIGHT / 6);
}

void ScoreCounter::Draw()
{
    sprintf(scorestring, "%u", score);
    gfx_PrintStringXY(scorestring, (LCD_WIDTH - gfx_GetStringWidth(scorestring)) / 2, LCD_HEIGHT / 6);
}

void ScoreCounter::Cleanup()
{
    gfx_Sprite_NoClip(behindScore, (LCD_WIDTH - gfx_GetStringWidth(scorestring)) / 2 - 4, LCD_HEIGHT / 6);
}

void ScoreCounter::Reset()
{
    score = 0;
    sprintf(scorestring, "%u", score);
}

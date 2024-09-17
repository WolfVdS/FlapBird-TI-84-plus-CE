#include "scorecounter.hpp"

ScoreCounter::ScoreCounter()
{
    score = 0;

    //store the score as a string in scorestring
    sprintf(scorestring, "%u", score);

    behindScore = gfx_MallocSprite(gfx_GetStringWidth(scorestring) + BEHIND_SCORE_PADDING, UNSCALED_TEXT_HEIGHT * TEXT_SCALE);
}

void ScoreCounter::IncreaseScore()
{
    score++;

    sprintf(scorestring, "%u", score);
    free(behindScore);
    behindScore = gfx_MallocSprite(gfx_GetStringWidth(scorestring) + BEHIND_SCORE_PADDING, UNSCALED_TEXT_HEIGHT * TEXT_SCALE);
}

void ScoreCounter::PreDraw()
{
    gfx_GetSprite_NoClip(behindScore, static_cast<int>((LCD_WIDTH - gfx_GetStringWidth(scorestring) - BEHIND_SCORE_PADDING) / 2), LCD_HEIGHT / 6);
}

void ScoreCounter::Draw()
{
    sprintf(scorestring, "%u", score);
    gfx_PrintStringXY(scorestring, static_cast<int>((LCD_WIDTH - gfx_GetStringWidth(scorestring)) / 2), LCD_HEIGHT / 6);
}

void ScoreCounter::Cleanup()
{
    gfx_Sprite_NoClip(behindScore, static_cast<int>((LCD_WIDTH - gfx_GetStringWidth(scorestring) - BEHIND_SCORE_PADDING) / 2), LCD_HEIGHT / 6);
}

void ScoreCounter::Reset()
{
    score = 0;
    sprintf(scorestring, "%u", score);
}

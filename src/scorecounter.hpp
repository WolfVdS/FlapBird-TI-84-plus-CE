#ifndef SCORECOUNTER
#define SCORECOUNTER

#include <tice.h>
#include <stdio.h>
#include <graphx.h>

//Defines.
const int TEXT_SCALE {3};
const int UNSCALED_TEXT_HEIGHT {8};
const int SCORE_STRING_SIZE {6};
//The amount of extra pixels in width for the buffer that stores the background behind the score.
//This is needed to stop artifacts from appearing
const int BEHIND_SCORE_PADDING {8};

class ScoreCounter
{
    public:
    ScoreCounter();
    void IncreaseScore();
    void PreDraw();
    void Draw();
    void Cleanup();
    void Reset();

    private:
    int score;
    //Buffer to hold the score as a string.
    char scorestring[SCORE_STRING_SIZE];
    //Buffer to hold background behind the score.
    gfx_sprite_t* behindScore;
};

#endif

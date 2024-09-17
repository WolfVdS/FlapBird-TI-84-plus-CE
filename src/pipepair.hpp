#ifndef PIPEPAIR
#define PIPEPAIR

#include "gfx/gfx.h"
#include <graphx.h>
#include <tice.h>

//Defines.
const int SCROLL_SPEED {2};
const int VERTICAL_SPACE_BETWEEN_PIPES {96};
const int MIN_PIPE_VISIBILITY {-pipe_height + 40};
const int MAX_PIPE_VISIBILITY {-VERTICAL_SPACE_BETWEEN_PIPES - 40};
//The amount of pipes on screen at 1 point in time.
const int PIPE_AMOUNT {2};

class PipePair
{
    public:
    //The position of the upperPipe.
    int upperx, uppery;
    //The position of the lowerPipe.
    int lowerx, lowery;
    
    //The sprites of the pipes.
    static gfx_rletsprite_t* upperSprite;
    static gfx_rletsprite_t* lowerSprite;

    //Constructor.
    PipePair(int upperx, int uppery);
    //Methods.
    //This method should be called before draw and is used for partial redraw.
    void PreDraw();
    //The method that draws the pipes.
    void Draw();
    //This method cleans up the buffer so it can be re-used.
    void Cleanup();
    //The method that moves the pipes.
    void Move();
    //Resets the pipes.
    void Reset();

    private:
    //The sprites that contain the background behind the pipes from the previous frame.
    gfx_sprite_t* behindUpper;
    gfx_sprite_t* behindLower;
    //The previous frame's position of the pipes.
    int oldUpperx, oldUppery;
    int oldLowerx, oldLowery;
    //The original x-coordinate the upperpipe was instantiated with.
    int originalUpperx;
};

#endif

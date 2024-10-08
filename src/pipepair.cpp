#include "pipepair.hpp"

PipePair::PipePair(int upperx, int uppery)
{
    this->upperx = upperx;
    this->uppery = uppery;
    this->lowerx = upperx;
    this->lowery = uppery + VERTICAL_SPACE_BETWEEN_PIPES + pipe_height;
    oldUpperx = this->upperx;
    oldUppery = this->uppery;
    oldLowerx = this->lowerx;
    oldLowery = this->lowery;
    originalUpperx = this->upperx;

    //Create the sprites that will hold the background.
    behindUpper = gfx_MallocSprite(pipe_width, LCD_HEIGHT + uppery);
    behindLower = gfx_MallocSprite(pipe_width, LCD_HEIGHT - lowery);

    //Assign the sprites.
    gfx_GetSprite(behindUpper, upperx, 0);
    gfx_GetSprite(behindLower, lowerx, lowery);
}

void PipePair::PreDraw()
{
    //Get the background behind the pipes' new position.
    gfx_GetSprite(behindUpper, oldUpperx, 0);
    gfx_GetSprite(behindLower, oldLowerx, oldLowery);
}

void PipePair::Draw()
{
    //Draw the sprites.
    gfx_RLETSprite(pipe, upperx, uppery);
    gfx_RLETSprite(pipe_flipped, lowerx, lowery);
}

void PipePair::Cleanup()
{
    //Draw the backgrounds over the sprite.
    gfx_Sprite(behindUpper, oldUpperx, 0);
    gfx_Sprite(behindLower, oldLowerx, oldLowery);

    //Set the old positions as the current positions.
    oldUpperx = upperx;
    oldUppery = uppery;
    oldLowerx = lowerx;
    oldLowery = lowery;
}

void PipePair::Move()
{
    //If the pipe goes of the screen
    if (upperx + pipe_width <= 0)
    {
        upperx = LCD_WIDTH;
        uppery = randInt(MIN_PIPE_VISIBILITY, MAX_PIPE_VISIBILITY);
        lowery = uppery + VERTICAL_SPACE_BETWEEN_PIPES + pipe_height;

        //Free the memory and allocate new memory.
        free(behindUpper);
        behindUpper = gfx_MallocSprite(pipe_width, LCD_HEIGHT + uppery);
        free(behindLower);
        behindLower = gfx_MallocSprite(pipe_width, LCD_HEIGHT - lowery);
    }
    else
    {
        upperx -= SCROLL_SPEED;
    }
        
    lowerx = upperx;
}

void PipePair::Reset()
{
    upperx = originalUpperx;
    uppery = randInt(MIN_PIPE_VISIBILITY, MAX_PIPE_VISIBILITY);
    lowerx = originalUpperx;
    lowery = uppery + VERTICAL_SPACE_BETWEEN_PIPES + pipe_height;

    //Free the memory and allocate new memory.
    free(behindUpper);
    behindUpper = gfx_MallocSprite(pipe_width, LCD_HEIGHT + uppery);
    free(behindLower);
    behindLower = gfx_MallocSprite(pipe_width, LCD_HEIGHT - lowery);
}

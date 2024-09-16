#include "ground.hpp"

Ground::Ground()
{
    //Initialize the x-Coordiantes.
    for (int i = 0; i < 3; i++)
    {
        x[i] = ground_0_width * i;
    }
    
    //Draw the ground once.
    Draw();
}

void Ground::Draw()
{
    for (int i = 0; i < 3; i++)
        gfx_Sprite(ground_0, x[i], Y);
}

void Ground::Move()
{
    for (int i = 0; i < 3; i++)
    {
        x[i] -= GROUND_ANIMATION_SPEED;
        //If the ground is of the left side of the screen we will wrap it to the right side.
        if(x[i] <= -ground_0_width)
            x[i] = LCD_WIDTH;
    }
}

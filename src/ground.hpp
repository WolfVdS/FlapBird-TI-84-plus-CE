#pragma once
#include <graphx.h>
#include "gfx/gfx.h"
#include <tice.h>

//Defines.
//The Y-Coordinat to draw the ground at.
#define Y LCD_HEIGHT - ground_0_height
//The higher this value, the faster the ground animates.
#define GROUND_ANIMATION_SPEED 2

class Ground
{
    public:
    //Constructor.
    Ground();
    //Methods.
    //This draw the ground.
    void Draw();
    //This animates the ground.
    void Move();

    private:
    //The x-coordinates of the ground parts.
    int x[3] = {0, ground_0_width, ground_0_width * 2};
};
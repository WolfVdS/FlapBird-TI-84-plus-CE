#ifndef GROUND
#define GROUND

#include "gfx/gfx.h"
#include <graphx.h>
#include <tice.h>

//Defines.
//The Y-Coordinat to draw the ground at.
const int GROUND_Y {LCD_HEIGHT - ground_0_height};
//The higher this value, the faster the ground animates.
const int GROUND_ANIMATION_SPEED {2};

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
    int x[3];
};

#endif

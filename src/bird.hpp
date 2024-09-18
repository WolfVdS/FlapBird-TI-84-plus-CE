#ifndef BIRD
#define BIRD

#include "gfx/gfx.h"
#include "math.hpp"
#include "pipepair.hpp"
#include "scorecounter.hpp"
#include <graphx.h>
#include <keypadc.h>
#include <tice.h>

//Defines.
//The speed at wich the bird switches animation keyframes, higher numbers result in slower animations, as a keyframe is shown for longer.
const int BIRD_ANIMATION_SPEED {5};
//The amount of pixels the bird will fall down when not affected by other forces everytime the Move() function is called.
const int GRAVITY {5};
//The velocity that is added everytime the Bird jumps.
const int JUMP_VELOCITY {-14};
//The amount of jump velocity that the bird loses when not jumping.
const int JUMP_VELOCITY_DECREASE {-1};
//How fast the bird moves when idle.
const double BIRD_IDLE_MOVE_SPEED {0.5};

class Bird
{
    public:
    //The position variables of the bird.
    int x, y;
    //The velocity of the Bird on the y-axis.
    int vy;
    //The sprite that is currently used to render the bird.
    gfx_rletsprite_t* currentSprite;
    //This indicates if the Bird has hit a pipe.
    bool hitPipe;

    //Constructor.
    Bird(int x, int y);
    //Methods.
    //This method should be called before draw and is used for partial redraw.
    void PreDraw();
    //The method that draws the bird.
    void Draw(bool animate);
    //This method cleans up the buffer so it can be re-used.
    void Cleanup();
    //The method that moves the bird across the screen.
    void Move();
    //This method moves the bird when a round hasn't yet been started.
    void Idle();
    //This method returns true when the bird is alive.
    bool IsAlive();
    //This method handles the pipes, it checks if the bird has hit a pipe and if it has passed one.
    void HandlePipes(PipePair** pipes, ScoreCounter* score);
    //Resets the bird to it's original state.
    void Reset();

    private:
    //The sprite that conatins the background behind the bird from the previous frame.
    gfx_sprite_t* behindBird;
    //The previous frame's position of the bird.
    int oldx, oldy;
    //The original position variables the bird was instantiated with.
    int originalx, originaly;
    //This indicates if the bird has recently scored.
    bool scored;
    gfx_rletsprite_t* GetSpriteToDraw();
    void Jump();
    void DecreaseJumpVelocity();
};

#endif

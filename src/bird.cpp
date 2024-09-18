#include "bird.hpp"

Bird::Bird(int x, int y)
{
    this->x = x;
    this->y = y;
    vy = 0;
    oldx = x;
    oldy = y;
    originalx = x;
    originaly = y;

    hitPipe = false;
    scored = false;
    
    currentSprite = bird_1;

    //Create the sprite that will hold the background.
    behindBird = gfx_MallocSprite(bird_0_width, bird_0_height);

    //Assign the sprite.
    gfx_GetSprite(behindBird, x, y);

    //Jump once so that the bird won't fall down before the player is able to react.
    Jump();
}

void Bird::PreDraw()
{
    //Get the background behind the sprite's old position.
    gfx_GetSprite(behindBird, oldx, oldy);
}

void Bird::Draw(bool animate)
{
    //Only animate the sprite when it should animate.
    if (animate)
        currentSprite = GetSpriteToDraw();
    //Draw the sprite.
    gfx_RLETSprite(currentSprite, x, y);
}

void Bird::Cleanup()
{
    //Draw the background over the old sprite on the buffer.
    gfx_Sprite(behindBird, oldx, oldy);

    //Set the old position as the current/new position.
    oldx = x;
    oldy = y;
}

void Bird::Move()
{
    static bool key;
    static bool prevkey;

    key = (kb_Data[7] & kb_Up);
    if (key && !prevkey)
        Jump();
    else
        DecreaseJumpVelocity();

    //Take care of forces.
    y += hitPipe ? GRAVITY : GRAVITY + vy;
    
    prevkey = key;
}

void Bird::Idle()
{
    //indicates if the bird is going up.
    static bool isGoingUp = true;
    //The offset on the y-axis relative to the original y.
    static float offset = 0;
    
    //Check if we should change directions and change directions when needed.
    if (y <= (originaly - (bird_0_height / 4)))
        isGoingUp = false;
    if(y >= (originaly + (bird_0_height / 4)))
        isGoingUp = true;

    //If the bird should go up, we move it up, if it should go down, we move it down.
    if (isGoingUp)
        offset -= BIRD_IDLE_MOVE_SPEED;
    if (!isGoingUp)
        offset += BIRD_IDLE_MOVE_SPEED;

    //Apply the offset
    y = originaly + (int)offset; 
}

bool Bird::IsAlive()
{
    //If the bird touches the ground, it dies.
    if(y >= LCD_HEIGHT - bird_0_height - ground_0_height)
        return false;
    else
        return true;
}

void Bird::HandlePipes(PipePair** pipes, ScoreCounter* score)
{
    //If we have already hit a pipe, we won't check another time.
    if (hitPipe)
        return;

    //Check for collisions with the pipes.
    for (int i = 0; i < PIPE_AMOUNT; i++)
    {
        //Check if the bird is in between the two pipes on the x-axis or touches one of them on the x-axis.
        if (((x + bird_0_width >= pipes[i]->upperx) && (x + bird_0_width <= pipes[i]->upperx + pipe_width)) || ((x >= pipes[i]->upperx) && (x <= pipes[i]->upperx + pipe_width)))
        {
            //Check if the bird is in the upper pipe or touches it.
            if (y <= pipes[i]->uppery + pipe_height)
                hitPipe = true;
            
            //Check if the bird is in the lower pipe or touches it.
            if (y + bird_0_height >= pipes[i]->lowery)
                hitPipe = true;
        }

        //If the bird is in between the two pipes and we haven't scored recently.
        if ((x >= pipes[i]->upperx) && (x <= pipes[i]->upperx + pipe_width) && (!scored))
        {
            scored = true;
            score->IncreaseScore();
        }

        //If we have scored recently and we aren't in between the pipes anymore, we'll we able to score again.
        if ((x > pipes[i]->upperx + pipe_width) && (scored))
            scored = false;
        
    }
}

void Bird::Reset()
{
    x = originalx;
    y = originaly;
    vy = 0;
    currentSprite = bird_1;
    hitPipe = false;
    scored = false;
    Jump();
}

gfx_rletsprite_t* Bird::GetSpriteToDraw()
{
    //If the bird is dead or it has hit a pipe, it won't animate anymore.
    if (!IsAlive() || hitPipe)
        return bird_1;
    
    static int spriteIndex = 0;
    //Increase the spriteIndex everytime this method is ran.
    spriteIndex++;

    //If spriteIndex is a multiple of BIRD_ANIMATION_SPEED, this will only be true once every BIRD_ANIMATION_SPEED time(s).
    if ((spriteIndex % BIRD_ANIMATION_SPEED) == 0)
    {
        int relativeSpriteIndex = (spriteIndex / BIRD_ANIMATION_SPEED);

        //If we divide spriteIndex by BIRD_ANIMATION_SPEED we get the number of times we have entered this if clause.
        if (relativeSpriteIndex % 2 == 0)
            return bird_1;

        else if(relativeSpriteIndex % 3 == 0)
            return bird_2;

        else if(relativeSpriteIndex % 1 == 0)
            return bird_0;

        else
            return currentSprite;
    }

    //If it isn't time yet to switch keyframes we will return the current sprite.
    else
        return currentSprite;
}

void Bird::Jump()
{
    //Never let the yJumpVelocity go under the JUMP_VELOCITY.
    vy = fmax(vy + JUMP_VELOCITY, JUMP_VELOCITY);
}

void Bird::DecreaseJumpVelocity()
{
    //Never let the yJumpVelocity become a positif number.
    vy = fmin(vy - JUMP_VELOCITY_DECREASE, 0);
}

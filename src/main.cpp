/*
 *--------------------------------------
 * Program Name: FlapBird
 * Author: WolfVdS
 * License: BSD 3-Clause
 * Description: A FlappyBird-type game for the TI-84 plus CE calculator.
 *--------------------------------------
*/

#include "gfx/gfx.h"
#include "bird.hpp"
#include "pipepair.hpp"
#include "ground.hpp"
#include "scorecounter.hpp"
#include <tice.h>
#include <stdio.h>
#include <keypadc.h>
#include <graphx.h>

void Initialize();
void End();
void Gameplay();
void Draw();
void DrawBackground();
void Reset();

Bird* bird;
PipePair* pipes[PIPE_AMOUNT];
Ground* ground;
ScoreCounter* score;
//This bool indicates if the game has started with a round.
bool started = false;

int main(void)
{
    Initialize();
    //While the del key isn't pressed.
    while (!(kb_Data[1] & kb_Del))
    {
        kb_Scan();

        //If the round hasn't started and we press the up key, the round will start.
        if(!started && (kb_Data[7] & kb_Up))
            started = true;
        //If the bird is dead and the player presses the up key, we will reset so a new round can bes started.
        if(!bird->IsAlive() && (kb_Data[1] & kb_2nd))
            Reset();

        Gameplay();
        Draw();
    }

    End();
    return 0;
}

void Initialize()
{
    //Initialize the graphics.
    gfx_Begin();

    //First draw the background on the screen.
    //If we only assign it on the buffer the screen will flicker because we use swapdraw, wich swaps the background and the screen.
    //We need to draw the background only once on each buffer because we use partial redraw.
    DrawBackground();

    //Draw on the buffer instead of directly drawing to the screen;
    gfx_SetDrawBuffer();

    //Set the global pallet as the pallet defined in convimg.yaml.
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    //Set the transparent color to be the one defined as index 1 in convimg.yaml.
    gfx_SetTransparentColor(1);

    //Text.
    gfx_SetTextFGColor(2);
    gfx_SetTextBGColor(1);
    gfx_SetTextTransparentColor(1);
    gfx_SetTextScale(TEXT_SCALE, TEXT_SCALE);

    //Draw the background on the buffer.
    //We need to draw the background only once on each buffer because we use partial redraw.
    DrawBackground();

    //Set the random seed based off the real time clock.
    srand(rtc_Time());

    //Initialize the Bird.
    bird = new Bird((LCD_WIDTH / 2) - bird_0_width, (LCD_HEIGHT - bird_0_height) / 2);

    //Initialize the pipes.
    //Because the upper and lower sprites are shared beatween each PipePair they are static 
    //to save memory and stop the program from crashing.
    //Because they are static they cant be assigned via the constructor.
    //And because the transparent color must be set first they can also not be assigned in the pipepair.cpp file,
    //and thus they need to be assigned here.
    gfx_sprite_t* temp = gfx_MallocSprite(pipe_width, pipe_height);
    gfx_RotateSpriteHalf(pipe, temp);
    PipePair::upperSprite = gfx_ConvertMallocRLETSprite(pipe);
    PipePair::lowerSprite = gfx_ConvertMallocRLETSprite(temp);
    free(temp);

    for (int i = 0; i < PIPE_AMOUNT; i++)
    {
        int x = ((i + 1) * (LCD_WIDTH / 2)) - ((PIPE_AMOUNT - i) * (pipe_width / 2)) + LCD_WIDTH;
        int y = randInt(MIN_PIPE_VISIBILITY, MAX_PIPE_VISIBILITY);
        pipes[i] = new PipePair(x, y);
    }

    //Initialize the ground.
    ground = new Ground();

    //Initialize the score.
    score = new ScoreCounter();

    //Scan the keyboard for new input.
    kb_Scan();
}

void End()
{
    delete bird;
    for (int i = 0; i < PIPE_AMOUNT; i++)
        delete &pipes[i];
    delete ground;
    delete score;
    gfx_End();
}

void Gameplay()
{   
    //If a round has started we will begin handling the pipes(checking for collisions hand scoring).
    if(started)
        bird->HandlePipes(pipes, score);

    if (bird->IsAlive())
    {
        //If the bird is alive and hasn't hit a pipe, we will move the pipes and the ground.
        if (!bird->hitPipe)
        {
            if(started)
            {
                for (int i = 0; i < PIPE_AMOUNT; i++)
                    pipes[i]->Move();
            }
            
            ground->Move();
        }

        //Only react to input when the round has started and the bird is still alive.
        if (started)
            bird->Move();
        else
            bird->Idle();
    }
}

void Draw()
{
    //Predraw, used to get the background behind the sprites for partial redraw.
    for (int i = 0; i < PIPE_AMOUNT; i++)
        pipes[i]->PreDraw();
    bird->PreDraw();
    score->PreDraw();
    
    //Draw the pipes.
    for (int i = 0; i < PIPE_AMOUNT; i++)
        pipes[i]->Draw();

    //Draw the ground
    ground->Draw();
    
    //Draw the bird and only animate it when the round has been started.
    if (started)
        bird->Draw(true);
    else
        bird->Draw(false);

    //If the round has started, print the score on the screen.
    if (started)
        score->Draw();
    
    //Swap the buffer and the screen to show the results on screen.
    gfx_SwapDraw();
    
    //Clean up the buffer so it can be re-used.
    if(started)
        score->Cleanup();
    bird->Cleanup();
    for (int i = 0; i < PIPE_AMOUNT; i++)
        pipes[i]->Cleanup();
}

void DrawBackground()
{
    gfx_Sprite_NoClip(background_0, 0, 0);
    gfx_Sprite_NoClip(background_1, background_0_width, 0);
}

void Reset()
{
    started = false;
    srand(rtc_Time());

    gfx_SetDrawScreen();
    bird->Cleanup();
    for (int i = 0; i < PIPE_AMOUNT; i++)
        pipes[i]->Cleanup();
    score->Cleanup();
    gfx_SetDrawBuffer();
    bird->Cleanup();
    for (int i = 0; i < PIPE_AMOUNT; i++)
        pipes[i]->Cleanup();
    score->Cleanup();

    bird->Reset();
    for (int i = 0; i < PIPE_AMOUNT; i++)
        pipes[i]->Reset();
    score->Reset();
}



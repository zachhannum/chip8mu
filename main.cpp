/*
* File: main.cpp
* Author: Zach Hannum
* Created: December 7, 2017
*/

#include <iostream>
#include <stdio.h>
#include "cpu.h"
#include "graphics.h"
#include "SDL/SDL.h"

Chip_8 chip8;
Display display;

int pauseFlag;
void pollPause();
void cycleCPU();

//Emulation loop
unsigned int t1;
unsigned int t2;
unsigned int elapsed;
unsigned int remaining;
unsigned int interval = 17;

int main(int argc, char* args[]){

  chip8.name = args[1];

  //Initialize display Graphics
  display.initGraphics();

  //Initialize Chip8
  chip8.initialize();
  chip8.loadGame();

  //set debug flag and pause flag
  chip8.debugFlag = 0;
  pauseFlag = 0;

  while(1){

    if(!pauseFlag){
      cycleCPU();
    }
    else{
      pollPause();
      SDL_Delay(10);
    }
  }

  return 0;
}

void cycleCPU(){
  //Use t1 and t2 to ensure timers get 60hz
  t1 = SDL_GetTicks();

  //Cycle cpu
  chip8.cycle();
  //Update graphics
  if(chip8.drawFlag){
    display.drawGraphics(chip8.gfx);
    chip8.drawFlag = 0;
  }

  //store key presses
  chip8.setKeys();

  t2 = SDL_GetTicks();

  elapsed = t2 - t1;
  remaining = interval - elapsed;
  if(elapsed < interval){
    SDL_Delay(remaining);
    elapsed = interval;
  }
}

void pollPause(){
  SDL_Event event;
  while (SDL_PollEvent (&event)){
    //store pressed down keys
    if(event.type == SDL_KEYDOWN){
      switch(event.key.keysym.sym){
        case SDLK_p: {
          chip8.debugFlag ^= 1;
          break;
        }
        case SDLK_RIGHT: {
          cycleCPU();
          break;
        }
        case SDLK_SPACE: {
          pauseFlag ^= 1;
          if(pauseFlag) chip8.cycleCount = 1;
          else chip8.cycleCount = chip8.cycleControl;
          break;
        }
        case SDLK_UP: {
          if(chip8.cycleControl < 12){
            chip8.cycleControl++;
            chip8.cycleCount = chip8.cycleControl;
            break;
          }
        }
        case SDLK_DOWN: {
          if(chip8.cycleControl > 1){
            chip8.cycleControl--;
            chip8.cycleCount = chip8.cycleControl;
            break;
          }
        }
        case SDLK_ESCAPE: exit(1); break;
        default: break;
      }
    }
  }
}

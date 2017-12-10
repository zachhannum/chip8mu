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

int main(int argc, char* args[]){

  //Initialize display Graphics
  display.initGraphics();

  //Initialize Chip8
  chip8.initialize();
  chip8.loadGame();

  // Initialize 60Hz timer
  //setTimer();

  //Emulation loop
  unsigned int t1;
  unsigned int t2;
  unsigned int elapsed;
  unsigned int remaining;
  unsigned int interval = 17;
  while(1){



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

return 0;
}

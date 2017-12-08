/*
* File: main.cpp
* Author: Zach Hannum
* Created: December 7, 2017
*/

#include <iostream>
#include "cpu.h"

Chip_8 chip8;

int main(){

  //Initialize render system and register input callbacks
  //initGraphics();
  //initInput();


  //
  chip8.initialize();
  chip8.loadGame();

  //Emulation loop
  while(1){
    chip8.cycle();

    //if(chip_8.drawFlag)
    //  drawGraphics();

    //store key presses
    //chip8.setKeys();
  }

return 0;
}

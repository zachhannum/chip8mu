/*
* File: cpu.cpp
* Author: Zach Hannum
* Created: December 7, 2017
*/

#include <iostream>
#include "cpu.h"

const char *Chip_8::name = "pong.rom";


//initialize registers and memory
void Chip_8::initialize(){
    pc     = 0x200; //program counter start
    opcode = 0;     //Reset opcode
    index  = 0;     //Reset index reg
    sp     = 0;     //Reset stack pointer

    //clear memory
    for(int i = 0; i < 4096; i++){
      mem[i] = 0;
    }



    //TODO
    //clear stack
    //clear display
    //clear v registers

    //load fontset
    //reset timers

}

//fetch opcode
//decode opcode
//execute opcode
//update timers
void Chip_8::cycle(){

  //fetch opcode
  opcode = mem[pc] << 8 | mem[pc + 1];
  printf("opcode %04x fetched.\n", opcode);


  //decode opcode
  switch(opcode & 0xF000){

    case 0x0000:
      switch (opcode & 0x000F){

        // 0x00E0: CLS - Clear the display - Type: Display
        case 0x0000:
        break;

        // 0x00EE: RET - Return from subroutine - Type: Flow
        case 0x000E:
        break;

        default: perror("Opcode error: Unknown opcode.");
      }
    break;

    // 0x1NNN: JP addr - Jump to address NNN - Type: Flow
    // set PC to NNN
    case 0x1000:
    break;

    // 0x2NNN: CALL addr - Call subroutine at NNN  - type: Flow
    // increment stack pointer, put current PC on top of stack. PC is set to NNN.
    case 0x2000:
    break;

    // 0x3XKK: SE Vx, byte - Skip next instruction if Vx = kk. - type: Cond
    // check Vx == kk. If true, increment PC by 2.
    case 0x3000:
    break;

    // 0x4XKK - SNE Vx, byte - Skip next instruction if Vx != kk. - type: Cond
    //check Vx != kk. If true, increment PC by 2.
    case 0x4000:
    break;

    // 0x5XY0 - SE Vx, Vy - type: Cond
    // If Vx == Vy, then increment PC by 2.
    case 0x5000:
    break;

    // 0x6XNN - LD Vx, byte - type: Const
    // Set Vx = NN
    case 0x6000:
    break;

    // 0x7XKK - ADD Vx, byte - type: Const
    // Set Vx = Vx + KK
    case 0x7000:
    break;

    case 0x8000:
      switch(opcode & 0x000F){

        // 0x8XY0 - LD Vx, Vy - type: Assign
        // Set Vx = Vy
        case 0x0000:
        break;

        // 0x8XY1 - OR Vx, Vy - type: BitOp
        // Set Vx = Vx | Vy
        case 0x0001:
        break;

        // 0x8XY2 - AND Vx, Vy - type: BitOp
        // Set Vx = Vx & Vy
        case 0x0002:
        break;

        // 0x8XY3 - XOR Vx, Vy - type: BitOp
        // Set Vx = Vx ^ Vy
        case 0x0003:
        break;

        // 0x8XY4 - 
        case 0x0004:
        break;

        case 0x0005:
        break;

        case 0x0006:
        break;

        case 0x0007:
        break;

        case 0x000E:
        break;

        default: perror("Opcode error: Unknown opcode.");
      }
    break;

    case 0x9000:
    break;

    case 0xA000:
    break;

    case 0xB000:
    break;

    case 0xC000:
    break;

    case 0xD000:
    break;

    case 0xE000:
    break;

    case 0xF000:
    break;
  }


}

void Chip_8::loadGame(){

  readRom();

}

void Chip_8::readRom(){

  //temporary memory buffer
  unsigned char buf[MAX_GAME_SIZE];

  //open rom file
  FILE* game = fopen(name, "rb");

  //error if game file does not exist
  if(game == NULL){
    perror("Failed to open game.\n");
  }

  //read rom data into temporary buffer
  fread(buf, sizeof(char), MAX_GAME_SIZE, game);
  fclose(game);

  //copy memory buffer into memory starting at 0x200
  int memIndex = 512;
  for(int i=0; i < MAX_GAME_SIZE; i++){
    mem[memIndex++] = buf[i];
  }


}

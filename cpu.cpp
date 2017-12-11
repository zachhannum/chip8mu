/*
* File: cpu.cpp
* Author: Zach Hannum
* Created: December 7, 2017
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include "cpu.h"
#include "SDL/SDL.h"

extern int pauseFlag;


unsigned char chip8Font[80] =
{
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


//initialize registers and memory
void Chip_8::initialize(){
  pc     = 0x200; //program counter start
  opcode = 0;     //Reset opcode
  I      = 0;     //Reset index reg
  sp     = 0;     //Reset stack pointer


  cycleCount = 8; //set initial instruction speed
  cycleControl = 8; // used for speed controls

  //clear memory and load font
  memset(mem, 0, sizeof mem);
  for(int i = 0; i < 80; i++){
    mem[i] = chip8Font[i];
  }


  //TODO
  //clear stack
  //clear display
  //clear v registers
  //reset timers

  //initInput();
}

void Chip_8::setKeys(){
  SDL_Event event;
    while (SDL_PollEvent (&event)){
      //store pressed down keys
      if(event.type == SDL_KEYDOWN){
        switch(event.key.keysym.sym){
          case SDLK_1: key[0x1] = 1; break;
          case SDLK_2: key[0x2] = 1; break;
          case SDLK_3: key[0x3] = 1; break;
          case SDLK_4: key[0xC] = 1; break;
          case SDLK_q: key[0x4] = 1; break;
          case SDLK_w: key[0x5] = 1; break;
          case SDLK_e: key[0x6] = 1; break;
          case SDLK_r: key[0xD] = 1; break;
          case SDLK_a: key[0x7] = 1; break;
          case SDLK_s: key[0x8] = 1; break;
          case SDLK_d: key[0x9] = 1; break;
          case SDLK_f: key[0xE] = 1; break;
          case SDLK_z: key[0xA] = 1; break;
          case SDLK_x: key[0x0] = 1; break;
          case SDLK_c: key[0xB] = 1; break;
          case SDLK_v: key[0xF] = 1; break;
          case SDLK_p: {
            debugFlag ^= 1;
            break;
          }
          case SDLK_SPACE: {
            pauseFlag ^= 1;
            if(pauseFlag) cycleCount = 1;
            else cycleCount = cycleControl;
            break;
          }
          case SDLK_UP: {
            if(cycleControl < 12){
              cycleControl++;
              cycleCount = cycleControl;
              break;
            }
          }
          case SDLK_DOWN: {
            if(cycleControl > 1){
              cycleControl--;
              cycleCount = cycleControl;
              break;
            }
          }
          case SDLK_ESCAPE: exit(1); break;
          default: break;
        }
      }
      else if(event.type == SDL_KEYUP){
        switch(event.key.keysym.sym) {
          case SDLK_1: key[0x1] = 0; break;
          case SDLK_2: key[0x2] = 0; break;
          case SDLK_3: key[0x3] = 0; break;
          case SDLK_4: key[0xC] = 0; break;
          case SDLK_q: key[0x4] = 0; break;
          case SDLK_w: key[0x5] = 0; break;
          case SDLK_e: key[0x6] = 0; break;
          case SDLK_r: key[0xD] = 0; break;
          case SDLK_a: key[0x7] = 0; break;
          case SDLK_s: key[0x8] = 0; break;
          case SDLK_d: key[0x9] = 0; break;
          case SDLK_f: key[0xE] = 0; break;
          case SDLK_z: key[0xA] = 0; break;
          case SDLK_x: key[0x0] = 0; break;
          case SDLK_c: key[0xB] = 0; break;
          case SDLK_v: key[0xF] = 0; break;
          default: break;
        }
    }
  }
}

//fetch opcode
//decode opcode
//execute opcode
//update timers
//TODO: 0xFX0A
void Chip_8::cycle(){

  //fetch and execute cycleCount instructions
  //set i to 1 for debugging step by step
  for(int i = 0; i < cycleCount; i++){

    //fetch opcode
    opcode = mem[pc] << 8 | mem[pc + 1];

    //decode opcode
    switch(opcode & 0xF000){

      case 0x0000:
      switch (opcode & 0x000F){

        // 0x00E0: CLS - Clear the display - Type: Display
        case 0x0000:
        memset(gfx, 0, sizeof gfx);
        drawFlag = 1;
        pc += 2;
        break;

        // 0x00EE: RET - Return from subroutine - Type: Flow
        // Set PC to address at top of stack, subtract 1 from stack pointer
        case 0x000E:
        sp--;
        pc = stack[sp] + 2;
        break;

        default: printf("Opcode error: Unknown opcode %04x.\n" , opcode);
      }
      break;

      // 0x1NNN: JP addr - Jump to address NNN - Type: Flow
      // set PC to NNN
      case 0x1000:
      pc = opcode & 0x0FFF;
      break;

      // 0x2NNN: CALL addr - Call subroutine at NNN  - type: Flow
      // increment stack pointer, put current PC on top of stack. PC is set to NNN.
      case 0x2000:
      stack[sp] = pc;
      ++sp;
      pc = opcode & 0x0FFF;
      break;

      // 0x3XKK: SE Vx, byte - Skip next instruction if Vx = kk. - type: Cond
      // check Vx == kk. If true, increment PC by 2.
      case 0x3000:
      if(v[VX_MASK(opcode)] == (opcode & 0x00FF))
      pc += 4;
      else
      pc += 2;
      break;

      // 0x4XKK - SNE Vx, byte - Skip next instruction if Vx != kk. - type: Cond
      //check Vx != kk. If true, increment PC by 2.
      case 0x4000:
      if(v[VX_MASK(opcode)] != (opcode & 0x00FF))
      pc += 4;
      else
      pc += 2;
      break;

      // 0x5XY0 - SE Vx, Vy - type: Cond
      // If Vx == Vy, then increment PC by 2.
      case 0x5000:
      if(v[VX_MASK(opcode)] == v[VY_MASK(opcode)])
      pc += 4;
      else
      pc += 2;
      break;

      // 0x6XNN - LD Vx, byte - type: Const
      // Set Vx = NN
      case 0x6000:
      v[VX_MASK(opcode)] = opcode & 0x00FF;
      pc += 2;
      break;

      // 0x7XKK - ADD Vx, byte - type: Const
      // Set Vx = Vx + KK
      case 0x7000:
      v[VX_MASK(opcode)] += opcode & 0x00FF;
      pc += 2;
      break;

      case 0x8000:
      switch(opcode & 0x000F){

        // 0x8XY0 - LD Vx, Vy - type: Assign
        // Set Vx = Vy
        case 0x0000:
        v[VX_MASK(opcode)] = v[VY_MASK(opcode)];
        pc += 2;
        break;

        // 0x8XY1 - OR Vx, Vy - type: BitOp
        // Set Vx = Vx | Vy
        case 0x0001:
        v[VX_MASK(opcode)] |= v[VY_MASK(opcode)];
        pc += 2;
        break;

        // 0x8XY2 - AND Vx, Vy - type: BitOp
        // Set Vx = Vx & Vy
        case 0x0002:
        v[VX_MASK(opcode)] &= v[VY_MASK(opcode)];
        pc += 2;
        break;

        // 0x8XY3 - XOR Vx, Vy - type: BitOp
        // Set Vx = Vx ^ Vy
        case 0x0003:
        v[VX_MASK(opcode)] ^= v[VY_MASK(opcode)];
        pc += 2;
        break;

        // 0x8XY4 - ADD Vx, Vy - type: Math
        // Set Vx = Vx + Vy and set VF = carry
        // If result > 255 VF = 1, else VF = 0. Only lowest 8 bits are kept.
        case 0x0004:
        v[VX_MASK(opcode)] += v[VY_MASK(opcode)];
        if(v[VX_MASK(opcode)] > 255){
          v[0xF] = 1;
        }

        else{
          v[0xF] = 0;
        }
        pc += 2;
        break;

        // 0x8XY5 - SUB Vx, Vy - type: Math
        // Set Vx = Vx - Vy, set VF = NOT borrow
        // If Vx > Vy, VF = 1, else 0.
        case 0x0005:
        if(v[VX_MASK(opcode)] > v[VY_MASK(opcode)]){
          v[0xF] = 1;
        }
        else{
          v[0xF] = 0;
        }
        v[VX_MASK(opcode)] -= v[VY_MASK(opcode)];
        pc += 2;
        break;

        // 0x8XY6 - SHR Vx {, Vy} - type: BitOp
        // If LSB of Vx is 1, VF = 1, else 0. Set Vx = Vx / 2.
        case 0x0006:
        v[0xF] = v[VX_MASK(opcode)] & 1;
        v[VX_MASK(opcode)] /= 2;
        pc += 2;
        break;

        // 0x8XY7 - SUBN Vx, Vy - type: Math
        // Set Vx = Vy - Vx, set VF = NOT borrow
        // If Vy > Vx, VF = 1, else 0.
        case 0x0007:
        if(v[VY_MASK(opcode) > VX_MASK(opcode)])
        v[0xF] = 1;
        else
        v[0xF] = 0;
        v[VX_MASK(opcode)] = v[VY_MASK(opcode)] - v[VX_MASK(opcode)];
        pc += 2;
        break;

        // 0x8XYE - SHL Vx {, Vy} - type: BitOp
        // If MSB of VX = 1, VF = 1, else 0. Set Vx = Vx * 2
        case 0x000E:
        v[0xF] = v[VX_MASK(opcode)] & 8;
        v[VX_MASK(opcode)] *= 2;
        pc += 2;
        break;

        default: printf("Opcode error: Unknown opcode %04x.\n" , opcode);
      }
      break;

      // 0x9XY0 - SNE Vx, Vy - type: Cond
      // If Vx != Vy, PC = PC + 4
      case 0x9000:
      if(v[VX_MASK(opcode)] != v[VY_MASK(opcode)])
      pc += 4;
      else
      pc += 2;
      break;

      // 0xANNN - LD I, address - type: MEM
      // Set I = NNN
      case 0xA000:
      I = opcode & 0x0FFF;
      pc += 2;
      break;

      // 0xBNNN - JP V0, addr - type: Flow
      // PC = NNN + V0
      case 0xB000:
      pc = (opcode & 0x0FFF) + v[0];
      break;

      // 0xCXKK - RND Vx, byte - type: Rand
      // Vx = Random byte (0 to 255) & KK
      case 0xC000:
      v[VX_MASK(opcode)] = rand() + (opcode & 0x00FF);
      pc += 2;
      break;

      // 0xDXYN - DRW Vx, Vy, nibble - type: Disp
      // Dislay n-byte sprite at mem location I at (Vx, Vy), set VF = collision
      //
      // Read N bytes from memory, starting at address stored at I. Bytes are
      // displayed as sprites on screen at (Vx, Vy). Sprites are XORed onto
      // existing screen. If this causes pixels to be erased, VF = 1, else VF = 0.
      // If sprite is positioned so part is outside coordinates of display, it
      // wraps to opposite side of the screen.
      case 0xD000: {
        unsigned char vx = v[VX_MASK(opcode)];
        unsigned char vy = v[VY_MASK(opcode)];
        unsigned char n = opcode & 0x000F;
        unsigned char p;

        //set VF
        v[0xF] = 0;

        //update gfx
        //iterate over height
        for(unsigned char y = 0; y < n; y++){
          p = mem[I + y];
          //iterate over width - 8 pixels
          for(unsigned char x = 0; x < 8; x++){
            //insert pixel into graphics
            unsigned char t_x = (vx + x)%64;
            unsigned char t_y = (vy + y)%32;
            if(p & (0x80 >> x)){
              //check to make sure pixel is in valid range
              if((t_x < 64) && (t_y < 32)){
                //check for collision
                if(gfx[t_x][t_y]) v[0xF] = 1;
                //XORFWI pixel onto screen
                gfx[t_x][t_y] ^= 1;
              }
            }
          }
        }

        //set draw flag
        drawFlag = 1;
        pc += 2;
        break;
      }

      case 0xE000:
      switch(opcode & 0x00FF){

        // 0xEX9E - SKP Vx - type: KeyOp
        // If key value at Vx is pressed, PC = PC + 2
        case 0x009E:
        if(key[v[VX_MASK(opcode)]]){
          pc += 4;
        }
        else{
          pc += 2;
        }
        break;

        // 0xEXA1 - SKNP Vx - type: KeyOp
        // If key value at Vx is not pressed, PC = PC + 2
        case 0x00A1:
        if(!key[v[VX_MASK(opcode)]]){
          pc += 4;
        }

        else{
          pc += 2;
        }

        break;

        default: printf("Opcode error: Unknown opcode %04x.\n" , opcode);
      }
      break;

      case 0xF000:
      switch(opcode & 0x00FF){

        // 0xFX07 - LD Vx, DT - type: Timer
        // Set Vx = delay timer value
        case 0x0007:
        v[VX_MASK(opcode)] = delayTimer;
        pc += 2;
        break;

        // 0xFX0A - LD Vx, K - type: KeyOp
        // Wait for key press, store value in Vx
        case 0x000A:
          for(int i=0; i < 0xF; i++){
            if(key[i]){
              v[VX_MASK(opcode)] = i;
              pc += 2;
            }
          }
        break;

        // 0xFX15 - LD DT, Vx - type: Timer
        // Set delay timer = Vx
        case 0x0015:
        delayTimer = v[VX_MASK(opcode)];
        pc += 2;
        break;

        // 0xFX18 - LD ST, Vx - type: Sound
        // Set sound timer = Vx
        case 0x0018:
        soundTimer = v[VX_MASK(opcode)];
        pc += 2;
        break;

        // 0xFX1E - ADD I, Vx - type: MEM
        // Set I = I + Vx
        case 0x001E:
        I += v[VX_MASK(opcode)];
        pc += 2;
        break;

        // 0xFX29 - LD F, Vx - type: MEM
        // Set I = location of sprite for digit Vx
        //
        // The value I is set to the location for the hex sprite
        // corresponding to the value of Vx.
        case 0x0029:
        I = v[VX_MASK(opcode)] * 5; //Font is 5 bytes wide, starting at mem[0]
        pc += 2;
        break;

        // 0xFX33 - LD B, Vx - type: BCD
        //
        // Store BCD representation of Vx in memory locations I, I+1, and I+2
        // Take decimal value of Vx, place 100s digit in memory at location I,
        // 10s digit at I+1, and 1s digit at I+2.
        case 0x0033:
        mem[I] = v[VX_MASK(opcode)] / 100;
        mem[I + 1] = (v[VX_MASK(opcode)] / 10) % 10;
        mem[I + 2] = v[VX_MASK(opcode)] % 10;
        pc += 2;
        break;

        // 0xFX55 - LD [I], Vx - type: MEM
        // Store registers V0 through Vx in memory starting at I.
        case 0x0055:
        for(int i = 0; i <= VX_MASK(opcode); i++){
          mem[I + i] = v[i];
        }
        pc += 2;
        break;

        // 0xFX65 - LD Vx, [I] - type: MEM
        // Read registers V0 through Vx from memory starting at I.
        case 0x0065:
        for(int i = 0; i <= VX_MASK(opcode); i++){
          v[i] = mem[I + i];
        }
        pc += 2;
        break;

        default: printf("Opcode error: Unknown opcode %04x.\n" , opcode);
      }
      break;

      default: printf("Opcode error: Unknown opcode %04x.\n" , opcode);
    }
  }
  timers();

  //debugging instruction by intstruction
  if(debugFlag){
    printf("Opcode = %04x\n" , opcode);
    for(int i = 0; i < 16; i++){
      printf("v[%x] = %02x    stack[%x] = %02x   key[%x] = %02x\n",i,v[i],i,stack[i], i, key[i]);
    }
    printf("pc = %x\n", pc);
    printf("sp = %x\n" , sp);
    printf("I  = %x\n", I);
    printf("delayTimer = %d\n", delayTimer);
    printf("soundTimer = %d\n" , soundTimer);
  }





}

void Chip_8::timers(){
  if(delayTimer > 0){
    delayTimer--;
  }
  if(soundTimer > 0){
    soundTimer--;
  }
}


void Chip_8::loadGame(){

  //temporary memory buffer
  unsigned char buf[MAX_GAME_SIZE];

  //open rom file
  FILE* game = fopen(name, "rb");

  //error if game file does not exist
  if(game == NULL){
    printf("Failed to open game.\n");
    exit(0);
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

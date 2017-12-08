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

    //TODO
    //clear stack
    //clear display
    //clear v registers
    //clear memory
    //load fontset
    //reset timers

}

//fetch opcode
//decode opcode
//execute opcode
//update timers
void Chip_8::cycle(){



}

void Chip_8::loadGame(){


}

void Chip_8::readRom(){

}

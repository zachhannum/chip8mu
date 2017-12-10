
#define MAX_GAME_SIZE 3584
#define VX_MASK(x) ((x & 0x0F00) >> 8)
#define VY_MASK(y) ((y & 0x00F0) >> 4)

class Chip_8{

private:
  //current opcode
  unsigned short opcode;

  /*
    4k Memory
    =========
    (0x200-0xFFF) - Program ROM and RAM
    (0xF00-0xFFF) - display refresh
    (0xEA0-0xEFF) call stack, internal, other vars
    (0x000-0x200) - font data
  */
  unsigned char mem[4096];

  //CPU registers
  unsigned char v[16];

  //Index register and Program Counter
  unsigned short I;
  unsigned short pc;

  //Timers
  unsigned char delayTimer;
  unsigned char soundTimer;

  //stack
  unsigned short stack[16];
  unsigned short sp;

  //Keypad
  unsigned char key[16];

  //Game name
  static const char * name;

  void readRom();

public:

  //Graphics
  /*
   ________________
  |0,0         63,0|
  |                |
  |                |
  |0,31_______63,31|

  */
  unsigned char gfx[64][32];

  unsigned int drawFlag;

  void initialize();
  void cycle();
  void loadGame();
  void timers();
  void setKeys();

};

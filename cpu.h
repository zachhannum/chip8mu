class Chip_8
{

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
  unsigned short index;
  unsigned short pc;

  //Graphics
  unsigned char gfx[64 * 32];

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
  void initialize();
  void cycle();
  void loadGame();

};

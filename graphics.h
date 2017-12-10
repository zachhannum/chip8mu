#include "SDL/SDL.h"

class Display {

private:
  SDL_Surface* screen = NULL;

public:
  void initGraphics();
  void drawGraphics(unsigned char const gfx[64][32]);

};

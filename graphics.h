#include "SDL/SDL.h"

class Display {

private:
  SDL_Surface* screen = NULL;

  //Themes
  int currentTheme[6];
  int themeCounter;

public:
  void initGraphics();
  void drawGraphics(unsigned char const gfx[64][32]);
  void cycleTheme();

};

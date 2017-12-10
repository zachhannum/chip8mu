#include "SDL/SDL.h"
#include "graphics.h"

#define SCREEN_SCALE 10

void Display::initGraphics(){

  //start SDL
  SDL_Init( SDL_INIT_EVERYTHING );

  //initialize display
  screen = SDL_SetVideoMode(64*SCREEN_SCALE, 32*SCREEN_SCALE, 32, SDL_SWSURFACE );

}

void Display::drawGraphics(unsigned char const gfx[64][32]){
  SDL_Rect rect;

  for(int x = 0; x < 64; x++){
    for(int y = 0; y < 32; y++){
      rect.x = x*SCREEN_SCALE;
      rect.y = y*SCREEN_SCALE;
      rect.w = SCREEN_SCALE;
      rect.h = SCREEN_SCALE;
      if(gfx[x][y])
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 255, 255));
      else
        SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 0, 0, 0));
    }
  }
  SDL_Flip(screen);

}

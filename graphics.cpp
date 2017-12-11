#include <stdlib.h>
#include "SDL/SDL.h"
#include "graphics.h"

#define SCREEN_SCALE 10
#define NUM_THEMES 5

//Color Themes
//Each row is a theme defined by RGB colors
//First 3 values define foreground RGB
//Last 3 values define background RGB
const int themes[][6]  = {
  {255, 255, 255,   0,   0,   0}, //default white on black
  {  4, 135,   0,   0,   0,   0}, //retro command line
  {255, 255, 255,  48,  10,  36}, //ubuntu command line
  {140, 108,  82,  66,  51,  39}, //Cafe
  {  0,   0,   0, 255, 255, 255}, //default white on black
};

void Display::initGraphics(){

  //start SDL
  SDL_Init( SDL_INIT_EVERYTHING );

  //initialize display
  screen = SDL_SetVideoMode(64*SCREEN_SCALE, 32*SCREEN_SCALE, 32, SDL_SWSURFACE );

  //Initialize theme
  themeCounter = 0;
  for(int i = 0; i < 6; i++){
    currentTheme[i] = themes[themeCounter][i];
  }

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
          SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, currentTheme[0], currentTheme[1], currentTheme[2]));
        else
          SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, currentTheme[3], currentTheme[4], currentTheme[5]));
      }
  }
  SDL_Flip(screen);

}

void Display::cycleTheme(){
  if(++themeCounter < NUM_THEMES){
    for(int i = 0; i < 6; i++){
      currentTheme[i] = themes[themeCounter][i];
    }
  }
  else{
    themeCounter = 0;
    for(int i = 0; i < 6; i++){
      currentTheme[i] = themes[themeCounter][i];
    }
  }

}

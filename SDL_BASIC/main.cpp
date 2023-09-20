#include <SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Quit();
  printf("SDL2 initialized and quit successfully!\n");
  return 0;
}

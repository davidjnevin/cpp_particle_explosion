#include <SDL.h>
#include <stdio.h>

#include <iostream>

#include "Screen.h"

using namespace davidjnevin;

int main() {
  Screen screen;

  if (screen.init() == false) {
    std::cout << "Error initializing SDL." << std::endl;
  }

  bool quit = false;
  SDL_Event event;

  // Game loop
  while (!quit) {
    // Update particles
    // Draw particles
    // Check for messages/events
    while (SDL_PollEvent(&event) != 0) {
      if (event.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  screen.close();

  return 0;
}

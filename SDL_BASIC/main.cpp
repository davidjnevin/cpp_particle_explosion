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

  // Game loop
  while (!quit) {
    // Update particles
    // Draw particles
    for (int y = 0; y < Screen::SCREEN_HEIGHT; y++) {
      for (int x = 0; x < Screen::SCREEN_WIDTH; x++) {
        screen.setPixel(x, y, 128, 0, 255);
      }
    }

    screen.setPixel(400, 300, 255, 255, 255);

    // Draw the screen
    screen.update();

    if (screen.processEvents() == false) {
      quit = true;
    }
  }

  screen.close();

  return 0;
}

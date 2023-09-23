#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include <cmath>
#include <iostream>

#include "Particle.h"
#include "Screen.h"
#include "Swarm.h"

using namespace davidjnevin;

int main() {
  srand(time(NULL));
  Screen screen;

  if (screen.init() == false) {
    std::cout << "Error initializing SDL." << std::endl;
  }

  Swarm swarm;

  bool quit = false;

  // Game loop
  while (!quit) {
    // Update particles

    // Draw particles
    int elapsed = SDL_GetTicks();
    swarm.update(elapsed);

    double green_speed = 0.0001;
    unsigned char green =
        (unsigned char)(sin(elapsed * green_speed) * 128 + 128);

    double red_speed = 0.0002;
    unsigned char red = (unsigned char)(sin(elapsed * red_speed) * 128 + 128);

    double blue_speed = 0.0003;
    unsigned char blue = (unsigned char)(sin(elapsed * blue_speed) * 128 + 128);

    const Particle *const pParticles = swarm.getParticles();
    for (int i = 0; i < Swarm::NPARTICLES; i++) {
      Particle particle = pParticles[i];

      // Range of -1 to 1 for x and y, so we need to scale it
      // to the screen size
      // We add 1 to the x and y to get a range of 0 to 2
      // We then divide by 2 to get a range of 0 to 1
      int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
      int y =
          (particle.m_y * Screen::SCREEN_WIDTH / 2) + Screen::SCREEN_HEIGHT / 2;

      screen.setPixel(x, y, red, green, blue);
    }
    // Apply burr
    screen.boxBlur();

    // Draw the screen
    screen.update();

    if (screen.processEvents() == false) {
      quit = true;
    }
  }

  screen.close();

  return 0;
}

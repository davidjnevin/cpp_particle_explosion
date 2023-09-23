#include "Screen.h"

namespace davidjnevin {

Screen::Screen()
    : m_window(NULL),
      m_renderer(NULL),
      m_texture(NULL),
      m_buffer1(NULL),
      m_buffer2(NULL) {}

bool Screen::init() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return false;
  }
  m_window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (m_window == NULL) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  m_renderer = SDL_CreateRenderer(
      m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (m_renderer == NULL) {
    SDL_DestroyWindow(m_window);
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  m_texture =
      SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

  if (m_texture == NULL) {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
    SDL_Quit();
    return false;
  }

  m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
  m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
  // could check for null pointer here

  // Set all pixels to white
  // Using hexidecimal notation for colors to make it easier to read
  memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
  memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

  return true;
}

bool Screen::processEvents() {
  SDL_Event m_event;
  while (SDL_PollEvent(&m_event) != 0) {
    if (m_event.type == SDL_QUIT) {
      return false;
    }
  }
  return true;
}

void Screen::boxBlur() {
  // Swap the buffers, so pixel is in m_buffer2 and we are drawing to m_buffer1
  Uint32 *temp = m_buffer1;
  m_buffer1 = m_buffer2;
  m_buffer2 = temp;

  for (int y = 0; y < SCREEN_HEIGHT; y++) {
    for (int x = 0; x < SCREEN_WIDTH; x++) {
      /*
       * 0 0 0
       * 0 1 0
       * 0 0 0
       */
      int redTotal = 0;
      int greenTotal = 0;
      int blueTotal = 0;

      for (int row = -1; row <= 1; row++) {
        for (int col = -1; col <= 1; col++) {
          int currentX = x + col;
          int currentY = y + row;

          if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 &&
              currentY < SCREEN_HEIGHT) {
            Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];

            Uint8 red = color >> 24;
            Uint8 green = color >> 16;
            Uint8 blue = color >> 8;

            redTotal += red;
            greenTotal += green;
            blueTotal += blue;
          }
        }
      }

      Uint8 red = redTotal / 9;
      Uint8 green = greenTotal / 9;
      Uint8 blue = blueTotal / 9;

      setPixel(x, y, red, green, blue);
    }
  }

  // delete[] temp;
}

void Screen::update() {
  SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
  SDL_RenderClear(m_renderer);
  SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
  SDL_RenderPresent(m_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
  // Check if the pixel is within the screen
  // If it is not, do not set the pixel
  // This is a simple way to avoid a segmentation fault
  // This is inefficient, but it is a good way to start
  if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
    return;
  }
  Uint32 color = 0;

  // Using bit shifting to set the complete color
  color += red;
  color <<= 8;
  color += green;
  color <<= 8;
  color += blue;
  color <<= 8;
  color += 0xFF;

  m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}
void Screen::close() {
  delete[] m_buffer1;
  delete[] m_buffer2;
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyTexture(m_texture);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

} /* namespace davidjnevin */

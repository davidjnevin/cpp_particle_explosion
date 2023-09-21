#include "Screen.h"

namespace davidjnevin {

Screen::Screen()
    : m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer(NULL) {}

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

  m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
  // could check for null pointer here

  // Set all pixels to white
  // Using hexidecimal notation for colors to make it easier to read
  memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

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

void Screen::clear() {
  memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
}

void Screen::close() {
  delete[] m_buffer;
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyTexture(m_texture);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

void Screen::update() {
  SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
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

  m_buffer[(y * SCREEN_WIDTH) + x] = color;
}
} /* namespace davidjnevin */

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

  // Set some pixels to green
  // Using hexidecimal notation for colors to make it easier to read
  for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++) {
    m_buffer[i] = 0x000000FF;
  }

  // buffer[3000] = 0xFFFFFFFF;
  SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
  SDL_RenderClear(m_renderer);
  SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
  SDL_RenderPresent(m_renderer);
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

void Screen::close() {
  delete[] m_buffer;
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyTexture(m_texture);
  SDL_DestroyWindow(m_window);
  SDL_Quit();
}

} /* namespace davidjnevin */
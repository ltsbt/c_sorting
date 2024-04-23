#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;
const int ARRAY_SIZE = 512;

int main() {
  SDL_Window *window;
  SDL_Renderer *renderer;
  window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Event event;

  int arr[ARRAY_SIZE];
  for (int i = 0; i < ARRAY_SIZE; i++) {
    arr[i] = i + 1;
  }

  // Shuffle the array
  srand(time(0));
  for (int i = 0; i < ARRAY_SIZE; i++) {
    int temp = arr[i];
    int randomIndex = rand() % ARRAY_SIZE;
    arr[i] = arr[randomIndex];
    arr[randomIndex] = temp;
  }

  while (1) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < ARRAY_SIZE; i++) {
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderDrawLine(renderer, i, SCREEN_HEIGHT, i, SCREEN_HEIGHT - arr[i]);
    }

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
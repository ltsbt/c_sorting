#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int SCREEN_WIDTH = 512;
const int SCREEN_HEIGHT = 512;
const int ARRAY_SIZE = 512;
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

void drawArray(SDL_Renderer *renderer, int *arr);
void shuffleArray(int *arr);
void swap(int *a, int *b);
void bubbleSort(SDL_Renderer *renderer, SDL_Event *event, int *arr);
void handleEvents(SDL_Event *event, bool *quit, bool *start_sorting);

int main() {
  SDL_Window *window;
  SDL_Renderer *renderer;
  window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Event event;
  bool quit = false;
  bool start_sorting = false;

  int arr[ARRAY_SIZE];
  for (int i = 0; i < ARRAY_SIZE; i++) {
    arr[i] = i + 1;
  }

  shuffleArray(arr);

  while (!quit) {
    handleEvents(&event, &quit, &start_sorting);

    if (start_sorting) {
      bubbleSort(renderer, &event, arr);
      start_sorting = false;
    }

    drawArray(renderer, arr);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

void drawArray(SDL_Renderer *renderer, int *arr) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  int width = SCREEN_WIDTH / ARRAY_SIZE;
  for (int i = 0; i < ARRAY_SIZE; i++) {
    int height = (int)((float)arr[i] * SCREEN_HEIGHT) / ARRAY_SIZE;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect rect = {i * width, SCREEN_HEIGHT - height, width, height};
    SDL_RenderFillRect(renderer, &rect);
  }

  SDL_RenderPresent(renderer);
}

void shuffleArray(int *arr) {
  srand(time(0));
  for (int i = 0; i < ARRAY_SIZE; i++) {
    int j = rand() % ARRAY_SIZE;
    swap(&arr[i], &arr[j]);
  }
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(SDL_Renderer *renderer, SDL_Event *event, int *arr) {
  for (int i = 0; i < ARRAY_SIZE - 1; i++) {
    for (int j = 0; j < ARRAY_SIZE - i - 1; j++) {
      while (SDL_PollEvent(event)) {
        if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_SPACE) {
          return;
        }
      }
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        drawArray(renderer, arr);
        SDL_Delay(FRAME_DELAY);
      }
    }
  }
}

void handleEvents(SDL_Event *event, bool *quit, bool *start_sorting) {
  while (SDL_PollEvent(event)) {
    if (event->type == SDL_QUIT) {
      *quit = true;
    } else if (event->type == SDL_KEYDOWN) {
      if (event->key.keysym.sym == SDLK_SPACE) {
        *start_sorting = true;
      }
    }
  }
}
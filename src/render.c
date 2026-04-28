#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <wchar.h>

#define SCREEN_HEIGHT 640
#define SCREEN_WIDTH 480

SDL_Window* window;
SDL_GLContext context;

void init() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL2 could not initialize video subsystem\n");
    exit(1);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  window = SDL_CreateWindow("Triangle", 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SDL_WINDOW_OPENGL);

  if (window == NULL) {
    printf("SDL_Window was not able to be created");
    exit(1);
  }

  context = SDL_GL_CreateContext(window);

  if (context == NULL) {
    printf("OpenGL context was not able to be created");
    exit(1);
  }

}

void main_loop() {
}

void clean() {
  SDL_Quit();
}

int main() {

  init();

  main_loop();

  clean();

}


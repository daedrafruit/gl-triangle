#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include <glad/glad.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

SDL_Window* g_window;
SDL_GLContext g_context;

bool g_quit = false;

void print_gl_info() {
  printf("Vendor: %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version: %s\n", glGetString(GL_VERSION));
  printf("Shading Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void init() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL2 could not initialize video subsystem\n");
    exit(1);
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  g_window = SDL_CreateWindow("Triangle", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

  if (g_window == NULL) {
    printf("SDL_Window was not able to be created\n");
    exit(1);
  }

  g_context = SDL_GL_CreateContext(g_window);

  if (g_context == NULL) {
    printf("OpenGL context was not able to be created\n");
    exit(1);
  }

  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
    printf("glad was not initialized\n");
    exit(1);
  }

  print_gl_info();

}

void input() {
  SDL_Event e;

  while(SDL_PollEvent(&e) != 0) {
    if (e.type == SDL_QUIT) {
      printf("Goodbye");
      g_quit = true;
    }
  }
}

void pre_draw() {
}

void draw() {
}


void main_loop() {
  while(!g_quit) {
    input();
    pre_draw();
    draw();
    SDL_GL_SwapWindow(g_window);
  }
}

void clean() {
  SDL_DestroyWindow(g_window);
  SDL_Quit();
}

int main() {

  init();

  main_loop();

  clean();

}


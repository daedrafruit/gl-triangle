#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include <glad/glad.h>

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640

SDL_Window* g_window;
SDL_GLContext g_context;

GLuint VAO = 0;
GLuint VBO = 0;

bool g_quit = false;

void print_gl_info() {
  printf("Vendor: %s\n", glGetString(GL_VENDOR));
  printf("Renderer: %s\n", glGetString(GL_RENDERER));
  printf("Version: %s\n", glGetString(GL_VERSION));
  printf("Shading Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void vertex_spec() {

  // init vertex
  const GLfloat vertex_positions[9] = {
    -0.8f, -0.8f, 0.0f,
    0.8f, -0.8f, 0.0f,
    0.8f, 0.8f, 0.0f
  };

  // generate vertex array object
  // this is essentially just an ID (object name, GLuint)
  // VAO describes how the vertex data should be read
  glGenVertexArrays(1, &VAO);
  // bind vertex array object
  // this tells opengl to reference our VAO
  // only one can be active at once
  glBindVertexArray(VAO);

  // generate array buffer
  // this is essentially just an ID (object name, GLuint)
  glGenBuffers(1, &VBO);
  // bind buffer
  // only one can be active at once
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // allocates and copies vector data to gpu
  glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), &vertex_positions, GL_STATIC_DRAW);

  //enables attribute, eg 0 could be x,y,z and 1 could be color etc
  glEnableVertexAttribArray(0);
  // create actual information for VAO (how data should be read)
  // only one attribute (coords, color etc.) per call
  glVertexAttribPointer(0, //index
                        3, //size (x,y,z in our case)
                        GL_FLOAT, //type
                        GL_FALSE, // normalized
                        0, //stride (offset between different attributes, may use padding for allignment etc, ours is compact so 0)
                        (void*)0 //offset, pointer for legacy reasons, just an offset to first attribute
                       );
  
  // cleanup
  glBindVertexArray(0);
  glDisableVertexAttribArray(0);

}

void create_graphics_pipeline() {
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

  vertex_spec();

  create_graphics_pipeline();

  main_loop();

  clean();

}


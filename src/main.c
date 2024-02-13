#include <SDL.h>

// opengl
#include <GL/glew.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include<SDL_opengl.h>
#include <GL/glu.h>

#include "shader_loader.h"

#include <SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

const int WIDTH = 800, HEIGHT = 800;

int main(void) {
    int quit = 0;
    SDL_Event e;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow("SDL Template", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (gl_context == NULL) {
        fprintf(stderr, "boo!\n");
        return 1;
    }



    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "boo!\n");
        return 1;
    }

    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    static const GLfloat vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f,
         0.0f,  1.0f, 0.0f,
    };

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);


    GLuint program_id = load_shader("../vertex.vert", "../fragment.frag");

    while(!quit) {
        SDL_PollEvent(&e);

        switch (e.type) {
            case SDL_QUIT: quit=1; break;
            case SDL_KEYDOWN:  
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE: quit=1; break;
                };
            break;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(program_id);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);

        SDL_GL_SwapWindow(window);
    }

    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &vertex_array_id);
    glDeleteProgram(program_id);

    SDL_DestroyWindow(window);
    return 0;
}

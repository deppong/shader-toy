#include "shader_loader.h"
#include <stddef.h>
#include <stdio.h>

GLuint load_shader(const char* vertex_path, const char* fragment_path) {
    GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    char* vertex_shader_code = NULL, *fragment_shader_code = NULL;
    size_t vertex_shader_code_len, fragment_shader_code_len; 

    FILE* vertex_shader_file = fopen(vertex_path, "r");
    if ( vertex_shader_file == NULL) {
        fprintf(stderr, "Error opening file at path: %s\n", vertex_path);
        return 0;
    }

    if (getdelim(&vertex_shader_code, &vertex_shader_code_len, '\0', vertex_shader_file) == -1) {
        fprintf(stderr, "failed to read shader file\n");
        return 0;
    }

    FILE* fragment_shader_file = fopen(fragment_path, "r");
    if ( fragment_shader_file == NULL ) {
        fprintf(stderr, "Error opening file at path: %s\n", fragment_path);
        return 0;
    }

    if (getdelim(&fragment_shader_code, &fragment_shader_code_len, '\0', fragment_shader_file) == -1) {
        fprintf(stderr, "failed to read shader file\n");
        return 0;
    }

    GLint result = GL_FALSE;

    glShaderSource(vertex_shader_id, 1, &vertex_shader_code, NULL);
    glCompileShader(vertex_shader_id);

    glShaderSource(fragment_shader_id, 1, &fragment_shader_code, NULL);
    glCompileShader(fragment_shader_id);

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);
    glLinkProgram(program_id);

    glDetachShader(program_id, vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    fclose(vertex_shader_file);
    fclose(fragment_shader_file);
    printf("loaded shaders successfully!\n");
    return program_id;
}
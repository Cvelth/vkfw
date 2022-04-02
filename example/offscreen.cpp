//========================================================================
// Offscreen rendering example
// Copyright (c) Camilla Löwy <elmindreda@glfw.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================
//
// Conversion to vkfw (and C++): John Cvelth <cvelth.mail@gmail.com>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define VKFW_NO_INCLUDE_VULKAN_HPP

#include <cstdio>
#include <cstdlib>

#include "linmath.h"
#include "stb_image_write.h"

#include "glad/glad.h"
#include "vkfw/vkfw.hpp"

#if USE_NATIVE_OSMESA
  #define GLFW_EXPOSE_NATIVE_OSMESA
  #include <GLFW/glfw3native.h>
#endif

static const struct {
  float x, y;
  float r, g, b;
} vertices[3] = { { -0.6f, -0.4f, 1.f, 0.f, 0.f },
                  { 0.6f, -0.4f, 0.f, 1.f, 0.f },
                  { 0.f, 0.6f, 0.f, 0.f, 1.f } };

static const char *vertex_shader_text = R"(
#version 110
uniform mat4 MVP;
attribute vec3 vCol;
attribute vec2 vPos;
varying vec3 color;
void main() {
  gl_Position = MVP * vec4(vPos, 0.0, 1.0);
  color = vCol;
}
)";

static const char *fragment_shader_text = R("
#version 110
                                            varying vec3 color;
                                            void main() { gl_FragColor = vec4(color, 1.0); }) ";

  static void
  error_callback(int error, const char *description) {
  fprintf(stderr, "Error #%d: %s\n", error, description);
}

int main(void) {
  try {
    vkfw::setErrorCallback(error_callback);

    vkfw::InitHints init_hints;
    init_hints.cocoaMenubar = false;
    auto instance = vkfw::initUnique(init_hints);

    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    hints.contextVersionMajor = 2u;
    hints.contextVersionMinor = 0u;
    hints.visible = false;
    auto window = vkfw::createWindowUnique(640, 480, "Simple example", hints);

    window->makeContextCurrent();
    gladLoadGLLoader((GLADloadproc) &vkfw::getProcAddress);

    // NOTE: OpenGL error checks have been omitted for brevity
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    GLint mvp_location, vpos_location, vcol_location;
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
                          (void *) (sizeof(float) * 2));

    auto size = window->getFramebufferSize();
    int width = static_cast<int>(std::get<0>(size)), height = static_cast<int>(std::get<1>(size));

    float ratio = (float) width / (float) height;
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glClear(GL_COLOR_BUFFER_BIT);

    mat4x4 mvp;
    mat4x4_ortho(mvp, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *) mvp);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glFinish();

#if USE_NATIVE_OSMESA
    char *buffer;
    glfwGetOSMesaColorBuffer(window, &width, &height, NULL, (void **) &buffer);
#else
    char *buffer = static_cast<char *>(calloc(4, width * height));
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
#endif

    // Write image Y-flipped because OpenGL
    stbi_write_png("offscreen.png", width, height, 4, buffer + (width * 4 * (height - 1)),
                   -width * 4);

#if USE_NATIVE_OSMESA
    // Here is where there's nothing
#else
    free(buffer);
#endif
  } catch (std::system_error &err) {
    char error_message[] = "An error has occured: ";
    strcat(error_message, err.what());
    fprintf(stderr, error_message);
    return -1;
  }
}

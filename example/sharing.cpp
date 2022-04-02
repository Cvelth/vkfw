//========================================================================
// Context sharing example
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

#define VKFW_NO_INCLUDE_VULKAN_HPP

#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "linmath.h"

#include "glad/glad.h"
#include "vkfw/vkfw.hpp"

static const char *vertex_shader_text = R("
#version 110
                                          uniform mat4 MVP;
                                          attribute vec2 vPos; varying vec2 texcoord; void main() {
                                            gl_Position = MVP * vec4(vPos, 0.0, 1.0);
                                            texcoord = vPos;
                                          }) ";

  static const char *fragment_shader_text
  = R"(
#version 110
uniform sampler2D texture;
uniform vec3 color;
varying vec2 texcoord;
void main() {
  gl_FragColor = vec4(color * texture2D(texture, texcoord).rgb, 1.0);
}
)";

static const vec2 vertices[4] = { { 0.f, 0.f }, { 1.f, 0.f }, { 1.f, 1.f }, { 0.f, 1.f } };

static void error_callback(int, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(vkfw::Window const &window, vkfw::Key key, int, vkfw::KeyAction action,
                         vkfw::ModifierKeyFlags) {
  if (action == vkfw::KeyAction::ePress && key == vkfw::Key::eEscape)
    window.setShouldClose(true);
}

int main() {
  try {
    vkfw::setErrorCallback(error_callback);

    auto instance = vkfw::initUnique();

    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    hints.contextVersionMajor = 2u;
    hints.contextVersionMinor = 0u;
    vkfw::UniqueWindow window_0 = vkfw::createWindowUnique(400, 400, "First", hints);

    window_0->callbacks()->on_key = &key_callback;
    window_0->makeContextCurrent();

    // Only enable vsync for the first of the windows to be swapped to
    // avoid waiting out the interval for each window
    vkfw::swapInterval(1);

    // The contexts are created with the same APIs so the function
    // pointers should be re-usable between them
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

    GLuint texture, program, vertex_buffer;
    GLint mvp_location, color_location, texture_location, vpos_location;

    // Create the OpenGL objects inside the first context, created above
    // All objects will be shared with the second context, created below
    {
      int x, y;
      char pixels[16 * 16];
      GLuint vertex_shader, fragment_shader;

      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);

      srand((unsigned int) glfwGetTimerValue());

      for (y = 0; y < 16; y++)
        for (x = 0; x < 16; x++)
          pixels[y * 16 + x] = rand() % 256;

      glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 16, 16, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE,
                   pixels);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

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

      mvp_location = glGetUniformLocation(program, "MVP");
      color_location = glGetUniformLocation(program, "color");
      texture_location = glGetUniformLocation(program, "texture");
      vpos_location = glGetAttribLocation(program, "vPos");

      glGenBuffers(1, &vertex_buffer);
      glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }

    glUseProgram(program);
    glUniform1i(texture_location, 0);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *) 0);

    auto window_1 = vkfw::createWindowUnique(400, 400, "Second", hints, nullptr, *window_0);

    // Place the second window to the right of the first
    window_1->setPos(static_cast<int>(window_0->getPosX() + window_0->getFramebufferWidth()
                                      + window_0->getLeftFrameSize()
                                      + window_0->getRightFrameSize()),
                     static_cast<int>(window_0->getPosY()));

    window_1->callbacks()->on_key = key_callback;
    window_1->makeContextCurrent();

    // While objects are shared, the global context state is not and will
    // need to be set up for each context

    glUseProgram(program);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void *) 0);

    std::array windows = { *window_0, *window_1 };
    constexpr vec3 colors[2] = { { 0.8f, 0.4f, 1.f }, { 0.3f, 0.4f, 1.f } };
    while (!window_0->shouldClose() && !window_1->shouldClose()) {
      for (size_t i = 0; i < windows.size(); i++) {
        windows[i].makeContextCurrent();
        glViewport(0, 0, static_cast<GLsizei>(windows[i].getFramebufferWidth()),
                   static_cast<GLsizei>(windows[i].getFramebufferHeight()));

        mat4x4 mvp;
        mat4x4_ortho(mvp, 0.f, 1.f, 0.f, 1.f, 0.f, 1.f);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *) mvp);
        glUniform3fv(color_location, 1, colors[i]);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        windows[i].swapBuffers();
      }

      vkfw::waitEvents();
    }

    return 0;
  } catch (std::system_error &err) {
    char error_message[] = "An error has occured: ";
    strcat(error_message, err.what());
    fprintf(stderr, error_message);
    return -1;
  }
}

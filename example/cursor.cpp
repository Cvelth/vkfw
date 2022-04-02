//========================================================================
// Cursor & input mode tests
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
// This test provides an interface to the cursor image and cursor mode
// parts of the API.
//
// Custom cursor image generation by urraka.
//
//========================================================================
//
// Conversion to vkfw (and C++): John Cvelth <cvelth.mail@gmail.com>

#if defined(_MSC_VER)
  // Make MS math.h define M_PI
  #define _USE_MATH_DEFINES
#endif

#define VKFW_NO_INCLUDE_VULKAN_HPP

#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <optional>

#include "linmath.h"

#include "glad/glad.h"
#include "vkfw/vkfw.hpp"

#define CURSOR_FRAME_COUNT 60

static const char *vertex_shader_text = R(
  "
#version 110
  uniform mat4 MVP;
  attribute vec2 vPos; void main() { gl_Position = MVP * vec4(vPos, 0.0, 1.0); }) ";

  static const char *fragment_shader_text
  = R("
#version 110
      void main() { gl_FragColor = vec4(1.0); }) ";

  static void
  error_callback(int, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static float star(int x, int y, float t) {
  const float c = 64 / 2.f;

  const float i = (0.25f * (float) sin(2.f * M_PI * t) + 0.75f);
  const float k = 64 * 0.046875f * i;

  const float dist = (float) sqrt((x - c) * (x - c) + (y - c) * (y - c));

  const float salpha = 1.f - dist / c;
  const float xalpha = (float) x == c ? c : k / (float) fabs(x - c);
  const float yalpha = (float) y == c ? c : k / (float) fabs(y - c);

  return (float) fmax(0.f, fmin(1.f, i * salpha * 0.2f + salpha * xalpha * yalpha));
}

static auto create_cursor_frame(float t) {
  int i = 0, x, y;
  unsigned char buffer[64 * 64 * 4];
  const GLFWimage image = { 64, 64, buffer };

  for (y = 0; y < image.width; y++) {
    for (x = 0; x < image.height; x++) {
      buffer[i++] = 255;
      buffer[i++] = 255;
      buffer[i++] = 255;
      buffer[i++] = (unsigned char) (255 * star(x, y, t));
    }
  }

  return vkfw::createCursorUnique(image, image.width / 2, image.height / 2);
}

static auto create_tracking_cursor(void) {
  int i = 0, x, y;
  unsigned char buffer[32 * 32 * 4];
  const GLFWimage image = { 32, 32, buffer };

  for (y = 0; y < image.width; y++) {
    for (x = 0; x < image.height; x++) {
      if (x == 7 || y == 7) {
        buffer[i++] = 255;
        buffer[i++] = 0;
        buffer[i++] = 0;
        buffer[i++] = 255;
      } else {
        buffer[i++] = 0;
        buffer[i++] = 0;
        buffer[i++] = 0;
        buffer[i++] = 0;
      }
    }
  }

  return vkfw::createCursorUnique(image, 7, 7);
}

class CursorExample {
public:
  void on_move(vkfw::Window const &window, double x, double y);
  void on_key(vkfw::Window const &window, vkfw::Key key, vkfw::KeyAction action,
              vkfw::ModifierKeyFlags mods);
  CursorExample();
  int run();

private:
  vkfw::UniqueInstance instance;

  double cursor_x = 0.0, cursor_y = 0.0;
  bool animate_cursor = false;
  bool wait_events = true;
  bool track_cursor = false;
  int swap_interval = 1;

  std::array<vkfw::UniqueCursor, CURSOR_FRAME_COUNT> star_cursors;
  std::array<vkfw::UniqueCursor, 6> standard_cursors;
  vkfw::UniqueCursor tracking_cursor;
};

void CursorExample::on_move(vkfw::Window const &, double x, double y) {
  printf("%0.3f: Cursor position: %f %f (%+f %+f)\n", vkfw::getTime(), x, y, x - cursor_x,
         y - cursor_y);
  cursor_x = x;
  cursor_y = y;
}
void CursorExample::on_key(vkfw::Window const &window, vkfw::Key key, vkfw::KeyAction action,
                           vkfw::ModifierKeyFlags mods) {
  if (action == vkfw::KeyAction::ePress)
    switch (key) {
    case vkfw::Key::eA:
      animate_cursor = !animate_cursor;
      if (!animate_cursor)
        window.setCursor(vkfw::Cursor{});
      break;

    case vkfw::Key::eEscape:
      if (window.get<vkfw::InputMode::eCursor>() != vkfw::CursorMode::eDisabled) {
        window.setShouldClose(true);
        break;
      }
      [[fallthrough]];

    case vkfw::Key::eN:
      window.set<vkfw::InputMode::eCursor>(vkfw::CursorMode::eNormal);
      std::tie(cursor_x, cursor_y) = window.getCursorPos();
      printf("(( cursor is normal ))\n");
      break;

    case vkfw::Key::eD:
      window.set<vkfw::InputMode::eCursor>(vkfw::CursorMode::eDisabled);
      printf("(( cursor is disabled ))\n");
      break;

    case vkfw::Key::eH:
      window.set<vkfw::InputMode::eCursor>(vkfw::CursorMode::eHidden);
      printf("(( cursor is hidden ))\n");
      break;

    case vkfw::Key::eR:
      if (vkfw::rawMouseMotionSupported())
        if (window.get<vkfw::InputMode::eRawMouseMotion>()) {
          window.set<vkfw::InputMode::eRawMouseMotion>(false);
          printf("(( raw input is disabled ))\n");
        } else {
          window.set<vkfw::InputMode::eRawMouseMotion>(true);
          printf("(( raw input is enabled ))\n");
        }
      break;

    case vkfw::Key::eSpace:
      swap_interval = 1 - swap_interval;
      printf("(( swap interval: %i ))\n", swap_interval);
      vkfw::swapInterval(swap_interval);
      break;

    case vkfw::Key::eW:
      wait_events = !wait_events;
      printf("(( %sing for events ))\n", wait_events ? "wait" : "poll");
      break;

    case vkfw::Key::eT:
      track_cursor = !track_cursor;
      if (track_cursor)
        window.setCursor(*tracking_cursor);
      else
        window.setCursor(vkfw::Cursor{});
      break;

    case vkfw::Key::eP: {
      auto [x, y] = window.getCursorPos();
      printf("Query before set: %f %f (%+f %+f)\n", x, y, x - cursor_x, y - cursor_y);
      cursor_x = x;
      cursor_y = y;

      window.setCursorPos(cursor_x, cursor_y);
      std::tie(x, y) = window.getCursorPos();

      printf("Query after set: %f %f (%+f %+f)\n", x, y, x - cursor_x, y - cursor_y);
      cursor_x = x;
      cursor_y = y;
      break;
    }

    case vkfw::Key::eUp:
      window.setCursorPos(0, 0);
      std::tie(cursor_x, cursor_y) = window.getCursorPos();
      break;

    case vkfw::Key::eDown: {
      auto [width, height] = window.getSize();
      window.setCursorPos(static_cast<double>(width - 1), static_cast<double>(height - 1));
      std::tie(cursor_x, cursor_y) = window.getCursorPos();
      break;
    }

    case vkfw::Key::e0: window.setCursor(vkfw::Cursor{}); break;

    case vkfw::Key::e1: window.setCursor(*standard_cursors[0]); break;

    case vkfw::Key::e2: window.setCursor(*standard_cursors[1]); break;

    case vkfw::Key::e3: window.setCursor(*standard_cursors[2]); break;

    case vkfw::Key::e4: window.setCursor(*standard_cursors[3]); break;

    case vkfw::Key::e5: window.setCursor(*standard_cursors[4]); break;

    case vkfw::Key::e6: window.setCursor(*standard_cursors[5]); break;

    case vkfw::Key::eF11:
    case vkfw::Key::eEnter:
      if (mods == vkfw::ModifierKeyBits::eAlt) {
        static int x, y;
        static size_t width, height;
        if (window.getMonitor())
          window.setMonitor(vkfw::Monitor{}, x, y, width, height);
        else {
          auto monitor = vkfw::getPrimaryMonitor();
          auto mode = monitor.getVideoMode();
          std::tie(x, y) = window.getPos();
          std::tie(width, height) = window.getSize();
          window.setMonitor(monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
        std::tie(cursor_x, cursor_y) = window.getCursorPos();
      }
      break;
    }
}

CursorExample::CursorExample() {
  instance = vkfw::initUnique();
  tracking_cursor = create_tracking_cursor();

  std::ranges::generate(star_cursors, []() {
    static size_t i = 0;
    return create_cursor_frame(i++ / (float) CURSOR_FRAME_COUNT);
  });
#ifndef NDEBUG
  for (auto &cursor : star_cursors)
    assert(cursor);
#endif

  std::ranges::generate(standard_cursors, []() {
    static size_t i = 0;
    constexpr std::array shapes = { vkfw::CursorShape::eArrow,     vkfw::CursorShape::eIBeam,
                                    vkfw::CursorShape::eCrosshair, vkfw::CursorShape::eHand,
                                    vkfw::CursorShape::eHResize,   vkfw::CursorShape::eVResize };
    return vkfw::createStandardCursorUnique(shapes[i]);
  });
#ifndef NDEBUG
  for (auto &cursor : standard_cursors)
    assert(cursor);
#endif
}

int CursorExample::run() {
  vkfw::WindowHints hints;
  hints.clientAPI = vkfw::ClientAPI::eOpenGL;
  hints.contextVersionMajor = 2u;
  hints.contextVersionMinor = 0u;
  auto window = vkfw::createWindowUnique(640, 480, "Cursor Test", hints);
  window->makeContextCurrent();
  gladLoadGLLoader((GLADloadproc) vkfw::getProcAddress);

  GLuint vertex_buffer, vertex_shader, fragment_shader, program;
  GLint mvp_location, vpos_location;

  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

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
  vpos_location = glGetAttribLocation(program, "vPos");

  glEnableVertexAttribArray(vpos_location);
  glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void *) 0);
  glUseProgram(program);

  std::tie(cursor_x, cursor_y) = window->getCursorPos();
  printf("Cursor position: %f %f\n", cursor_x, cursor_y);

  window->callbacks()->on_cursor_move = [this](auto const &w, auto x, auto y) { on_move(w, x, y); };
  window->callbacks()->on_key = [this](auto const &w, auto k, auto, auto a, auto m) {
    on_key(w, k, a, m);
  };

  while (!window->shouldClose()) {
    glClear(GL_COLOR_BUFFER_BIT);

    if (track_cursor) {
      auto [window_width, window_height] = window->getSize();
      auto [framebuffer_width, framebuffer_height] = window->getFramebufferSize();

      glViewport(0, 0, static_cast<GLsizei>(framebuffer_width),
                 static_cast<GLsizei>(framebuffer_height));

      vec2 vertices[4];
      auto scale = (float) framebuffer_width / (float) window_width;
      vertices[0][0] = 0.5f;
      vertices[0][1] = (float) (framebuffer_height - floor(cursor_y * scale) - 1.f + 0.5f);
      vertices[1][0] = (float) framebuffer_width + 0.5f;
      vertices[1][1] = (float) (framebuffer_height - floor(cursor_y * scale) - 1.f + 0.5f);
      vertices[2][0] = (float) floor(cursor_x * scale) + 0.5f;
      vertices[2][1] = 0.5f;
      vertices[3][0] = (float) floor(cursor_x * scale) + 0.5f;
      vertices[3][1] = (float) framebuffer_height + 0.5f;

      glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STREAM_DRAW);

      mat4x4 mvp;
      mat4x4_ortho(mvp, 0.f, (float) framebuffer_width, 0.f, (float) framebuffer_height, 0.f, 1.f);
      glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *) mvp);

      glDrawArrays(GL_LINES, 0, 4);
    }

    window->swapBuffers();

    static vkfw::Cursor current;
    if (animate_cursor) {
      auto i = static_cast<int>(vkfw::getTime() * 30.0) % CURSOR_FRAME_COUNT;
      if (current != *star_cursors[i])
        window->setCursor(current = *star_cursors[i]);
    } else
      current = vkfw::Cursor{};

    if (wait_events) {
      if (animate_cursor)
        vkfw::waitEventsTimeout(1.0 / 30.0);
      else
        vkfw::waitEvents();
    } else
      vkfw::pollEvents();

    // Workaround for an issue with msvcrt and mintty
    fflush(stdout);
  }
  return 0;
}

int main() {
  vkfw::setErrorCallback(error_callback);
  try {
    CursorExample example;
    return example.run();
  } catch (std::system_error &err) {
    char error_message[] = "An error has occured: ";
    strcat(error_message, err.what());
    fprintf(stderr, error_message);
    return -1;
  }
}

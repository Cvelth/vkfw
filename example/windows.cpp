//========================================================================
// Simple multi-window test
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
// This test creates four windows and clears each in a different color
//
//========================================================================
//
// Conversion to vkfw (and C++): John Cvelth <cvelth.mail@gmail.com>

#define VKFW_NO_INCLUDE_VULKAN_HPP

#include <array>
#include <cstdio>
#include <cstdlib>

#include "glad/glad.h"
#include "vkfw/vkfw.hpp"

static const char *titles[] = { "Red", "Green", "Blue", "Yellow" };

static const struct {
  float r, g, b;
} colors[] = { { 0.95f, 0.32f, 0.11f },
               { 0.50f, 0.80f, 0.16f },
               { 0.f, 0.68f, 0.94f },
               { 0.98f, 0.74f, 0.04f } };

static void usage(void) {
  printf("Usage: windows [-h] [-b] [-f] \n");
  printf("Options:\n");
  printf("  -b create decorated windows\n");
  printf("  -f set focus on show off for all but first window\n");
  printf("  -h show this help\n");
}

static void error_callback(int, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(vkfw::Window const &window, vkfw::Key key, int, vkfw::KeyAction action,
                         vkfw::ModifierKeyFlags) {
  if (action == vkfw::KeyAction::ePress)
    switch (key) {
    case vkfw::Key::eSpace: window.setPos(window.getPos()); break;
    case vkfw::Key::eBackspace: window.setShouldClose(true); break;
    }
}

int main(int argc, char **argv) {
  using namespace std::string_view_literals;
  bool decorated = false, focus_on_show = true, running = true;
  for (int i = 1; i < argc; ++i)
    if (argv[i] == "-b"sv)
      decorated = true;
    else if (argv[i] == "-f"sv)
      focus_on_show = false;
    else if (argv[i] == "-h"sv) {
      usage();
      return 0;
    } else {
      usage();
      return 1;
    }

  vkfw::setErrorCallback(error_callback);

  try {
    auto instance = vkfw::initUnique();

    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    hints.decorated = decorated;
    hints.visible = false;

    std::array<vkfw::UniqueWindow, 4> windows;
    for (size_t i = 0; i < 4; ++i) {
      if (i)
        hints.focusOnShow = focus_on_show;
      windows[i] = vkfw::createWindowUnique(200, 200, titles[i], hints);
      windows[i]->callbacks()->on_key = key_callback;
      windows[i]->makeContextCurrent();

      static bool once = true;
      if (once) {
        once = false;
        gladLoadGLLoader((GLADloadproc) vkfw::getProcAddress);
      }

      glClearColor(colors[i].r, colors[i].g, colors[i].b, 1.f);

      size_t left_and_right = windows[i]->getLeftFrameSize() + windows[i]->getRightFrameSize();
      size_t top_and_bottom = windows[i]->getTopFrameSize() + windows[i]->getBottomFrameSize();
      windows[i]->setPos(int(100 + (i & 1) * (200 + left_and_right)),
                         int(100 + (i >> 1) * (200 + top_and_bottom)));
    }

    for (auto const &window : windows)
      window->show();

    while (running) {
      for (auto const &window : windows) {
        window->makeContextCurrent();
        glClear(GL_COLOR_BUFFER_BIT);
        window->swapBuffers();
        if (window->shouldClose())
          running = false;
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

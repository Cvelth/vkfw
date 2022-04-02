//========================================================================
// Iconify/restore test program
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
// This program is used to test the iconify/restore functionality for
// both full screen and windowed mode windows
//
//========================================================================
//
// Conversion to vkfw (and C++): John Cvelth <cvelth.mail@gmail.com>

#define VKFW_NO_INCLUDE_VULKAN_HPP

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <vkfw/vkfw.hpp>

static void usage(void) {
  printf("Usage: iconify [-h] [-f] [-a]\n");
  printf("Options:\n");
  printf("  -a create windows for all monitors\n");
  printf("  -f create full screen window(s)\n");
  printf("  -h show this help\n");
}

static void error_callback(int, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(vkfw::Window const &window, vkfw::Key key, int, vkfw::KeyAction action,
                         vkfw::ModifierKeyFlags mods) {
  printf("%0.2f Key %s\n", vkfw::getTime(),
         action == vkfw::KeyAction::ePress ? "pressed" : "released");

  static int windowed_xpos = 0, windowed_ypos = 0;
  static size_t windowed_width = 640, windowed_height = 480;

  if (action == vkfw::KeyAction::ePress)
    switch (key) {
    case vkfw::Key::eI: window.iconify(); break;
    case vkfw::Key::eM: window.maximize(); break;
    case vkfw::Key::eR: window.restore(); break;
    case vkfw::Key::eEscape: window.setShouldClose(true); break;
    case vkfw::Key::eA:
      window.set<vkfw::Attribute::eAutoIconify>(!window.get<vkfw::Attribute::eAutoIconify>());
      break;
    case vkfw::Key::eB:
      window.set<vkfw::Attribute::eResizable>(!window.get<vkfw::Attribute::eResizable>());
      break;
    case vkfw::Key::eD:
      window.set<vkfw::Attribute::eDecorated>(!window.get<vkfw::Attribute::eDecorated>());
      break;
    case vkfw::Key::eF:
      window.set<vkfw::Attribute::eFloating>(!window.get<vkfw::Attribute::eFloating>());
      break;
    case vkfw::Key::eF11:
    case vkfw::Key::eEnter:
      if (mods == vkfw::ModifierKeyBits::eAlt)
        if (window.getMonitor())
          window.setMonitor(nullptr, windowed_xpos, windowed_ypos, windowed_width, windowed_height,
                            0);
        else if (auto monitor = vkfw::getPrimaryMonitor(); monitor) {
          std::tie(windowed_xpos, windowed_ypos) = window.getPos();
          std::tie(windowed_width, windowed_height) = window.getSize();

          auto mode = monitor.getVideoMode();
          window.setMonitor(monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }
      break;
    }
}

static void window_size_callback(vkfw::Window const &, size_t width, size_t height) {
  printf("%0.2f Window resized to %zix%zi\n", vkfw::getTime(), width, height);
}

static void framebuffer_size_callback(vkfw::Window const &, size_t width, size_t height) {
  printf("%0.2f Framebuffer resized to %zix%zi\n", vkfw::getTime(), width, height);
}

static void window_focus_callback(vkfw::Window const &, bool focused) {
  printf("%0.2f Window %s\n", vkfw::getTime(), focused ? "focused" : "defocused");
}

static void window_iconify_callback(vkfw::Window const &, bool iconified) {
  printf("%0.2f Window %s\n", vkfw::getTime(), iconified ? "iconified" : "uniconified");
}

static void window_maximize_callback(vkfw::Window const &, bool maximized) {
  printf("%0.2f Window %s\n", vkfw::getTime(), maximized ? "maximized" : "unmaximized");
}

static void window_refresh_callback(vkfw::Window const &window) {
  printf("%0.2f Window refresh\n", vkfw::getTime());

  window.makeContextCurrent();

  glClear(GL_COLOR_BUFFER_BIT);
  window.swapBuffers();
}

static auto create_window(vkfw::Monitor const &monitor, bool is_fullscreen) {
  vkfw::UniqueWindow output;
  vkfw::WindowHints hints;
  hints.clientAPI = vkfw::ClientAPI::eOpenGL;
  if (is_fullscreen) {
    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    hints.refreshRate = static_cast<unsigned>(mode->refreshRate);
    hints.redBits = static_cast<unsigned>(mode->redBits);
    hints.greenBits = static_cast<unsigned>(mode->greenBits);
    hints.blueBits = static_cast<unsigned>(mode->blueBits);
    output = vkfw::createWindowUnique(static_cast<size_t>(mode->width),
                                      static_cast<size_t>(mode->height), "Iconify", hints, monitor);
  } else
    output = vkfw::createWindowUnique(640, 480, "Iconify", hints, monitor);
  output->makeContextCurrent();
  gladLoadGLLoader((GLADloadproc) vkfw::getProcAddress);
  return output;
}

int main(int argc, char **argv) {
  using namespace std::string_view_literals;
  bool fullscreen = false, every_monitor = false;
  for (int i = 1; i < argc; ++i)
    if (argv[i] == "-a"sv)
      every_monitor = true;
    else if (argv[i] == "-h"sv) {
      usage();
      return 0;
    } else if (argv[i] == "-f"sv)
      fullscreen = true;
    else {
      usage();
      return 1;
    }

  vkfw::setErrorCallback(error_callback);
  try {
    auto instance = vkfw::initUnique();

    std::vector<vkfw::UniqueWindow> windows;
    if (every_monitor) {
      auto monitors = vkfw::getMonitors();
      windows.reserve(monitors.size());
      for (auto const &monitor : monitors)
        windows.push_back(create_window(monitor, fullscreen));
    } else
      windows.push_back(create_window(nullptr, fullscreen));
    for (auto const &window : windows) {
      window->callbacks()->on_key = key_callback;
      window->callbacks()->on_framebuffer_resize = framebuffer_size_callback;
      window->callbacks()->on_window_resize = window_size_callback;
      window->callbacks()->on_window_focus = window_focus_callback;
      window->callbacks()->on_window_iconify = window_iconify_callback;
      window->callbacks()->on_window_maximize = window_maximize_callback;
      window->callbacks()->on_window_refresh = window_refresh_callback;

      window_refresh_callback(*window);

      printf("Window is %s and %s\n",
             window->get<vkfw::Attribute::eIconified>() ? "iconified" : "restored",
             window->get<vkfw::Attribute::eFocused>() ? "focused" : "defocused");
    }

    while (true) {
      glfwWaitEvents();
      for (auto const &window : windows)
        if (window->shouldClose())
          return 0;
    }
  } catch (std::system_error &err) {
    char error_message[] = "An error has occured: ";
    strcat(error_message, err.what());
    fprintf(stderr, error_message);
    return -1;
  }
}

//========================================================================
// Event linter (event spewer)
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
// This test hooks every available callback and outputs their arguments
//
// Log messages go to stdout, error messages to stderr
//
// Every event also gets a (sequential) number to aid discussion of logs
//
//========================================================================
//
// Conversion to vkfw (and C++): John Cvelth <cvelth.mail@gmail.com>

#define VKFW_NO_INCLUDE_VULKAN_HPP

#include <cctype>
#include <charconv>
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string_view>

#include "glad/glad.h"
#include "vkfw/vkfw.hpp"

// Event index
static unsigned int counter = 0;

struct Slot {
  vkfw::UniqueWindow window;
  size_t number;
  bool closeable;
};

static void error_callback(int, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void window_pos_callback(vkfw::Window const &window, int x, int y) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Window position: %i %i\n", counter++, slot->number, vkfw::getTime(),
         x, y);
}

static void window_size_callback(vkfw::Window const &window, size_t width, size_t height) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Window size: %zi %zi\n", counter++, slot->number, vkfw::getTime(),
         width, height);
}

static void framebuffer_size_callback(vkfw::Window const &window, size_t width, size_t height) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Framebuffer size: %zi %zi\n", counter++, slot->number,
         vkfw::getTime(), width, height);
}

static void window_content_scale_callback(vkfw::Window const &window, float xscale, float yscale) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Window content scale: %0.3f %0.3f\n", counter++, slot->number,
         vkfw::getTime(), xscale, yscale);
}

static void window_close_callback(vkfw::Window const &window) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Window close\n", counter++, slot->number, vkfw::getTime());

  window.setShouldClose(slot->closeable);
}

static void window_refresh_callback(vkfw::Window const &window) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Window refresh\n", counter++, slot->number, vkfw::getTime());

  window.makeContextCurrent();
  glClear(GL_COLOR_BUFFER_BIT);
  window.swapBuffers();
}

static void window_focus_callback(vkfw::Window const &window, bool focused) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Window %s\n", counter++, slot->number, vkfw::getTime(),
         focused ? "focused" : "defocused");
}

static void window_iconify_callback(vkfw::Window const &window, bool iconified) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Window was %s\n", counter++, slot->number, vkfw::getTime(),
         iconified ? "iconified" : "uniconified");
}

static void window_maximize_callback(vkfw::Window const &window, bool maximized) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Window was %s\n", counter++, slot->number, vkfw::getTime(),
         maximized ? "maximized" : "unmaximized");
}

static void mouse_button_callback(vkfw::Window const &window, vkfw::MouseButton button,
                                  vkfw::MouseButtonAction action, vkfw::ModifierKeyFlags mods) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: %s mouse button %s (%i) (with %s)\n", counter++, slot->number,
         vkfw::getTime(), vkfw::to_string(action).data(), vkfw::to_string(button).data(), button,
         vkfw::to_string(mods).data());
}

static void cursor_position_callback(vkfw::Window const &window, double x, double y) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Cursor position: %f %f\n", counter++, slot->number, vkfw::getTime(),
         x, y);
}

static void cursor_enter_callback(vkfw::Window const &window, bool entered) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Cursor %s window\n", counter++, slot->number, vkfw::getTime(),
         entered ? "entered" : "left");
}

static void scroll_callback(vkfw::Window const &window, double x, double y) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  printf("%08x to %zi at %0.3f: Scroll: %0.3f %0.3f\n", counter++, slot->number, vkfw::getTime(), x,
         y);
}

static void key_callback(vkfw::Window const &window, vkfw::Key key, int scancode,
                         vkfw::KeyAction action, vkfw::ModifierKeyFlags mods) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  auto name = vkfw::getKeyName(key, scancode);

  if (name != "")
    printf("%08x to %zi at %0.3f: %s %s (0x%04x) key (with %s). Scancode: 0x%04x (%s)\n", counter++,
           slot->number, vkfw::getTime(), vkfw::to_string(action).data(),
           vkfw::to_string(key).data(), key, vkfw::to_string(mods).data(), scancode, name.data());
  else
    printf("%08x to %zi at %0.3f: %s %s (0x%04x) key (with %s)\n", counter++, slot->number,
           vkfw::getTime(), vkfw::to_string(action).data(), vkfw::to_string(key).data(), key,
           vkfw::to_string(mods).data());

  if (action == vkfw::KeyAction::ePress)
    switch (key) {
    case vkfw::Key::eC:
      printf("(( closing %s ))\n",
             bool(slot->closeable = !slot->closeable) ? "enabled" : "disabled");
      break;

    case vkfw::Key::eL: {
      auto state = window.get<vkfw::InputMode::eLockKeyModifiers>();
      window.set<vkfw::InputMode::eLockKeyModifiers>(!state);
      printf("(( lock key mods %s ))\n", !state ? "enabled" : "disabled");
      break;
    }
    }
}

static void char_callback(vkfw::Window const &window, unsigned int codepoint) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());
  char string[5] = "";
  size_t i = 0;

  if (codepoint < 0x80)
    string[i++] = static_cast<char>(codepoint);
  else if (codepoint < 0x800) {
    string[i++] = static_cast<char>((codepoint >> 6) | 0xc0);
    string[i++] = static_cast<char>((codepoint & 0x3f) | 0x80);
  } else if (codepoint < 0x10000) {
    string[i++] = static_cast<char>((codepoint >> 12) | 0xe0);
    string[i++] = static_cast<char>(((codepoint >> 6) & 0x3f) | 0x80);
    string[i++] = static_cast<char>((codepoint & 0x3f) | 0x80);
  } else if (codepoint < 0x110000) {
    string[i++] = static_cast<char>((codepoint >> 18) | 0xf0);
    string[i++] = static_cast<char>(((codepoint >> 12) & 0x3f) | 0x80);
    string[i++] = static_cast<char>(((codepoint >> 6) & 0x3f) | 0x80);
    string[i++] = static_cast<char>((codepoint & 0x3f) | 0x80);
  }

  printf("%08x to %zi at %0.3f: Character 0x%08x (%s) input\n", counter++, slot->number,
         vkfw::getTime(), codepoint, string);
}

static void drop_callback(vkfw::Window const &window, std::vector<std::string_view> const &paths) {
  Slot *slot = reinterpret_cast<Slot *>(window.getUserPointer());

  printf("%08x to %zi at %0.3f: Drop input\n", counter++, slot->number, vkfw::getTime());

  for (size_t i = 0; i < paths.size(); i++)
    printf("  %zi: \"%s\"\n", i, paths[i].data());
}

static void monitor_callback(GLFWmonitor *raw_monitor, int raw_status) {
  vkfw::Monitor monitor(raw_monitor);
  auto status = vkfw::Status(raw_status);

  if (status == vkfw::Status::eConnected) {
    auto video_mode = vkfw::Monitor(monitor).getVideoMode();
    auto [x, y] = monitor.getPos();
    auto [widthMM, heightMM] = monitor.getPhysicalSize();

    printf("%08x at %0.3f: Monitor %s (%ix%i at %ix%i, %zix%zi mm) was connected\n", counter++,
           vkfw::getTime(), monitor.getName().data(), video_mode->width, video_mode->height, x, y,
           widthMM, heightMM);
  } else if (status == vkfw::Status::eDisconnected) {
    printf("%08x at %0.3f: Monitor %s was disconnected\n", counter++, vkfw::getTime(),
           monitor.getName().data());
  }
}

static void joystick_callback(int jid, int event) {
  if (vkfw::Status(event) == vkfw::Status::eConnected) {
    int axisCount, buttonCount, hatCount;

    [[maybe_unused]] auto a = vkfw::getJoystickAxes(vkfw::Joystick(jid), &axisCount);
    [[maybe_unused]] auto b = vkfw::getJoystickButtons(vkfw::Joystick(jid), &buttonCount);
    [[maybe_unused]] auto h = vkfw::getJoystickHats(vkfw::Joystick(jid), &hatCount);

    printf("%08x at %0.3f: Joystick %i (%s) was connected with %i axes, %i buttons, and %i hats\n",
           counter++, vkfw::getTime(), jid, vkfw::getJoystickName(vkfw::Joystick(jid)).data(),
           axisCount, buttonCount, hatCount);
  } else {
    printf("%08x at %0.3f: Joystick %i was disconnected\n", counter++, vkfw::getTime(), jid);
  }
}

int main(int argc, char **argv) {
  try {
    vkfw::setErrorCallback(error_callback);

    auto instance = vkfw::initUnique();

    printf("Library initialized\n");

    vkfw::setMonitorCallback(monitor_callback);
    vkfw::setJoystickCallback(joystick_callback);

    using namespace std::string_view_literals;
    vkfw::Monitor monitor = nullptr;
    size_t window_count = 1;
    for (size_t i = 1; i < argc; i++)
      if (argv[i] == "-h"sv) {
        printf("Usage: events [-f] [-h] [-n WINDOWS]\n");
        printf("Options:\n");
        printf("  -f use full screen\n");
        printf("  -h show this help\n");
        printf("  -n the number of windows to create\n");
        return 0;
      } else if (argv[i] == "-f"sv)
        monitor = vkfw::getPrimaryMonitor();
      else if (argv[i] == "-n"sv && i + 1 < argc) {
        auto [ptr, error] = std::from_chars(argv[i + 1],
                                            argv[i + 1] + std::string_view(argv[i + 1]).size(),
                                            window_count);
        if (error != std::errc()) {
          printf("Fail to parse a number (%s) after '-n'\n", argv[i + 1]);
          return 1;
        }
        ++i;
      } else {
        printf("Usage: events [-f] [-h] [-n WINDOWS]\n");
        printf("Options:\n");
        printf("  -f use full screen\n");
        printf("  -h show this help\n");
        printf("  -n the number of windows to create\n");
        return 2;
      }

    size_t width, height;
    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    if (monitor) {
      const GLFWvidmode *mode = vkfw::Monitor(monitor).getVideoMode();
      hints.refreshRate = static_cast<unsigned>(mode->refreshRate);
      hints.redBits = static_cast<unsigned>(mode->redBits);
      hints.greenBits = static_cast<unsigned>(mode->greenBits);
      hints.blueBits = static_cast<unsigned>(mode->blueBits);

      width = mode->width;
      height = mode->height;
    } else {
      width = 640;
      height = 480;
    }
    std::vector<Slot> slots(window_count);

    for (size_t i = 0; i < window_count; i++) {
      slots[i].closeable = true;
      slots[i].number = i + 1;

      char title[128];
      snprintf(title, sizeof(title), "Event Linter (Window %zi)", slots[i].number);

      if (monitor) {
        printf("Creating full screen window %zi (%zix%zi on %s)\n", slots[i].number, width, height,
               vkfw::Monitor(monitor).getName().data());
      } else {
        printf("Creating windowed mode window %zi (%zix%zi)\n", slots[i].number, width, height);
      }

      slots[i].window = vkfw::createWindowUnique(width, height, title, hints, monitor);
      slots[i].window->setUserPointer(&slots[i]);
      slots[i].window->callbacks()->on_window_move = window_pos_callback;
      slots[i].window->callbacks()->on_window_resize = window_size_callback;
      slots[i].window->callbacks()->on_framebuffer_resize = framebuffer_size_callback;
      slots[i].window->callbacks()->on_window_content_scale_change = window_content_scale_callback;
      slots[i].window->callbacks()->on_window_close = window_close_callback;
      slots[i].window->callbacks()->on_window_refresh = window_refresh_callback;
      slots[i].window->callbacks()->on_window_focus = window_focus_callback;
      slots[i].window->callbacks()->on_window_iconify = window_iconify_callback;
      slots[i].window->callbacks()->on_window_maximize = window_maximize_callback;
      slots[i].window->callbacks()->on_mouse_button = mouse_button_callback;
      slots[i].window->callbacks()->on_cursor_move = cursor_position_callback;
      slots[i].window->callbacks()->on_cursor_enter = cursor_enter_callback;
      slots[i].window->callbacks()->on_scroll = scroll_callback;
      slots[i].window->callbacks()->on_key = key_callback;
      slots[i].window->callbacks()->on_character = char_callback;
      slots[i].window->callbacks()->on_drop = drop_callback;

      static bool once = true;
      if (once) {
        once = false;
        slots[i].window->makeContextCurrent();
        gladLoadGLLoader((GLADloadproc) vkfw::getProcAddress);
        vkfw::swapInterval(1);
      }
    }

    printf("Main loop starting\n");

    for (;;) {
      for (size_t i = 0; i < window_count; i++) {
        if (slots[i].window->shouldClose())
          return 0;
      }

      vkfw::waitEvents();

      // Workaround for an issue with msvcrt and mintty
      fflush(stdout);
    }

    return 0;
  } catch (std::system_error &err) {
    char error_message[] = "An error has occured: ";
    strcat(error_message, err.what());
    fprintf(stderr, error_message);
    return -1;
  }
}

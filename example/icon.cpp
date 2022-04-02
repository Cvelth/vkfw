//========================================================================
// Window icon test program
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
// This program is used to test the icon feature.
//
//========================================================================
//
// Conversion to vkfw (and C++): John Cvelth <cvelth.mail@gmail.com>

#define VKFW_NO_INCLUDE_VULKAN_HPP

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "glad/glad.h"
#include "vkfw/vkfw.hpp"

// a simple glfw logo
const char *const glfw_logo[] =
  R"(................
................
...0000..0......
...0.....0......
...0.00..0......
...0..0..0......
...0000..0000...
................
................
...000..0...0...
...0....0...0...
...000..0.0.0...
...0....0.0.0...
...0....00000...
................
................)";

// a simple vkfw logo
const char *const vkfw_logo[] =
  R"(................
................
...0..0..0..0...
...0..0..0.0....
...0..0..00.....
....00...0.0....
....00...0..0...
................
................
...000..0...0...
...0....0...0...
...000..0.0.0...
...0....0.0.0...
...0....00000...
................
................)";

const unsigned char icon_colors[6][4] = {
  { 0, 0, 0, 255 },      // black
  { 255, 0, 0, 255 },    // red
  { 0, 255, 0, 255 },    // green
  { 0, 0, 255, 255 },    // blue
  { 128, 0, 128, 255 },  // purple
  { 255, 255, 255, 255 } // white
};

int main() {
  try {
    auto instance = vkfw::initUnique();
    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    auto window = vkfw::createWindowUnique(200, 200, "Window Icon", hints);
    window->makeContextCurrent();
    gladLoadGLLoader((GLADloadproc) vkfw::getProcAddress);

    bool is_vkfw = true;
    size_t current_color = 0;
    auto update_icon = [&window, &is_vkfw, &current_color]() {
      unsigned char pixels[16 * 16 * 4];
      unsigned char *iterator = pixels;

      vkfw::Image img = { 16, 16, pixels };

      for (int y = 0; y < img.width; y++) {
        for (int x = 0; x < img.height; x++) {
          if ((is_vkfw ? vkfw_logo : glfw_logo)[y][x] == '0')
            memcpy(iterator, icon_colors[current_color], 4);
          else
            memset(iterator, 0, 4);

          iterator += 4;
        }
      }
      window->setIcon({ img });
    };
    window->callbacks()->on_key = [&is_vkfw, &current_color, &update_icon](auto const &window,
                                                                           auto key, auto,
                                                                           auto action, auto) {
      if (action == vkfw::KeyAction::ePress)
        switch (key) {
        case vkfw::Key::eEscape: window.setShouldClose(true); break;
        case vkfw::Key::eSpace:
          current_color = (current_color + 1) % 6;
          update_icon();
          break;
        case vkfw::Key::eV:
          is_vkfw = true;
          update_icon();
          break;
        case vkfw::Key::eG:
          is_vkfw = false;
          update_icon();
          break;
        case vkfw::Key::eX: window.setIcon(0, nullptr); break;
        }
    };

    update_icon();
    while (!window->shouldClose()) {
      glClear(GL_COLOR_BUFFER_BIT);
      window->swapBuffers();
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

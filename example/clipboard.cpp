//========================================================================
// Clipboard test program
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
// This program is used to test the clipboard functionality.
//
//========================================================================
//
// Conversion to vkfw (and C++): John Cvelth <cvelth.mail@gmail.com>

#define VKFW_NO_INCLUDE_VULKAN_HPP

#include <cstdio>
#include <cstdlib>

#include "glad/glad.h"
#include "vkfw/vkfw.hpp"

#if defined(__APPLE__)
  #define MODIFIER vkfw::ModifierKeyBits::eSuper
#else
  #define MODIFIER vkfw::ModifierKeyBits::eControl
#endif

static void error_callback(int, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(vkfw::Window const &window, vkfw::Key key, int, vkfw::KeyAction action,
                         vkfw::ModifierKeyFlags mods) {
  if (action == vkfw::KeyAction::ePress)
    switch (key) {
    case vkfw::Key::eEscape: window.setShouldClose(true); break;

    case vkfw::Key::eV:
      if (mods == MODIFIER)
        if (auto string = vkfw::getClipboardString(); string != "")
          printf("Clipboard contains \"%s\"\n", string.data());
        else
          printf("Clipboard does not contain a string\n");
      break;

    case vkfw::Key::eC:
      if (mods == MODIFIER) {
        const char *string = "Hello GLFW World!";
        vkfw::setClipboardString(string);
        printf("Setting clipboard to \"%s\"\n", string);
      }
      break;
    }
}

int main() {
  try {
    vkfw::setErrorCallback(error_callback);

    auto instance = vkfw::initUnique();

    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    auto window = vkfw::createWindowUnique(200, 200, "Clipboard Test", hints);
    window->makeContextCurrent();

    gladLoadGLLoader((GLADloadproc) vkfw::getProcAddress);
    vkfw::swapInterval(1);

    window->callbacks()->on_key = key_callback;

    glClearColor(0.5f, 0.5f, 0.5f, 0);

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

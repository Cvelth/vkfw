//========================================================================
// Empty event test
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
// This test is intended to verify that posting of empty events works
//
//========================================================================
//
// Conversion to vkfw (and C++): John Cvelth <cvelth.mail@gmail.com>

#define VKFW_NO_INCLUDE_VULKAN_HPP

#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <thread>

#include "glad/glad.h"
#include "vkfw/vkfw.hpp"

static void error_callback(int, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

int main() {
  try {
    vkfw::setErrorCallback(error_callback);

    auto instance = vkfw::initUnique();

    vkfw::WindowHints hints;
    hints.clientAPI = vkfw::ClientAPI::eOpenGL;
    auto window = vkfw::createWindowUnique(640, 480, "Empty Event Test", hints);
    window->callbacks()->on_key = [](vkfw::Window const &window, vkfw::Key key, int,
                                     vkfw::KeyAction action, vkfw::ModifierKeyFlags) {
      if (key == vkfw::Key::eEscape && action == vkfw::KeyAction::ePress)
        window.setShouldClose(true);
    };

    window->makeContextCurrent();
    gladLoadGLLoader((GLADloadproc) vkfw::getProcAddress);

    static volatile bool running = true;
    std::thread thread([]() {
      while (running) {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(1s);
        vkfw::postEmptyEvent();
      }
    });

    while (running) {
      static std::mt19937_64 generator(std::random_device{}());
      static std::uniform_real_distribution distribution(0.f, 1.f);

      glViewport(0, 0, static_cast<GLsizei>(window->getFramebufferWidth()),
                 static_cast<GLsizei>(window->getFramebufferHeight()));
      glClearColor(distribution(generator), distribution(generator), distribution(generator), 1.f);
      glClear(GL_COLOR_BUFFER_BIT);
      window->swapBuffers();

      vkfw::waitEvents();
      if (window->shouldClose())
        running = false;
    }
    window->hide();
    if (thread.joinable())
      thread.join();

    return 0;
  } catch (std::system_error &err) {
    char error_message[] = "An error has occured: ";
    strcat(error_message, err.what());
    fprintf(stderr, error_message);
    return -1;
  }
}

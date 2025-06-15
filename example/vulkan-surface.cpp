// A simple vulkan surface creation test

#include <cstdio>

#include "vkfw/vkfw.hpp"

static void error_callback(int, const char *description) {
  fprintf(stderr, "Error callback triggered: %s\n", description);
}

int main() {
  try {
    vkfw::setErrorCallback(error_callback);

    auto vkfw_instance = vkfw::initUnique();
    
    auto window = vkfw::createWindowUnique(640, 480, "Surface Test");
    window->callbacks()->on_key = [](vkfw::Window const &window, vkfw::Key key, int,
                                     vkfw::KeyAction action, vkfw::ModifierKeyFlags) {
      if (key == vkfw::Key::eEscape && action == vkfw::KeyAction::ePress)
        window.setShouldClose(true);
    };
    
    auto vulkan_instance = vk::createInstanceUnique(vk::InstanceCreateInfo{});
    auto surface = vkfw::createWindowSurfaceUnique(*vulkan_instance, *window);
    
    while (not window->shouldClose()) {
      vkfw::waitEvents();
    }

    return 0;
  } catch (std::system_error &err) {
    fprintf(stderr, "An error was caught: %s", err.what());
    return -1;
  }
}

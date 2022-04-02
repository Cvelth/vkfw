# VKFW: C++ Bindings for GLFW
It's easy to notice how similar VKFW API is to [Vulkan-Hpp](https://github.com/KhronosGroup/Vulkan-Hpp). That's by design. The goal is to provide a middle step helping your code look and feel like C++ in contrast with having to call C function when interacting with underlying OS.
It focuses on features like type safety with enums and bitfields, STL containers and optional exception support.

If you find any bugs or problems, I'd appreciate an [issue](https://github.com/Cvelth/vkfw/issues).

## Getting Started
All you need is to include `vkfw/vkfw.hpp` and you're ready to go.
That is to say, you still need to link against [glfw](https://github.com/glfw/glfw). These are just bindings, not a full-fledged library.

### Minimum Requirements
VKFW requires a C++11 capable compiler to compile. The following compilers are expected to work:
- Visual Studio >= 2015
- GCC >= 4.8.2
- Clang >= 3.3

Note that there are advantages of going with a more modern compiler: `std::string_view`, `std::span`, etc.

## Usage
### Default API
As these bindings are mainly designed to work with Vulkan, `GLFW_CLIENT_API` hint is set to `GLFW_NO_API` by default. So if you require OpenGL support, you need to explicitly set this hint.

### namespace `vkfw`
To avoid name collisions with the GLFW C API the C++ bindings reside in the `vkfw` namespace. The rules apply to the naming:

- All functions, enums, handles, and structs have the `glfw`/`GLFW` prefix removed. In addition to this the first letter of functions is lower case, and the first letter of structs is upper case
    - `glfwInit` can be accessed as `vkfw::init`
    - `GLFWwindow` can be accessed as `vkfw::Window`
- Enums are mapped to scoped enums to provide compile time type safety. The names have been changed to 'e' + CamelCase with `GLFW_` prefix removed.
    - `GLFW_KEY_C` is now `vkfw::Key::eC`
    - `GLFW_JOYSTICK_2` is now `vkfw::Joystick::e2`
    - `GLFW_ARROW_CURSOR` is now `vkfw::Cursor::eArrow`

### Handles
VKFW declares a class for all handles to ensure full type safety and to add support for member functions on handles. A member function has been added to a handle class for each function which accepts the corresoinding handle as first parameter. Instead of `glfwSetWindowTitle(&window, title)` one can write
- `window.setTitle(title)` (available only in "enhanced" mode)
- `vkfw::setWindowTitle(window, title)` (available only if "enhanced" mode is disabled)
- `glfwSetWindowTitle(window, title)` (yes, really, the compatibility with original GLFW API is not broken. `vkfw::Window` is implicitly convertible to `GLFWwindow *`, so you can call a `glfw` alternative if you choose to, for example, to avoid an unwanted exceptions from a specific function call, etc.)

### Return values, Error Codes & Exceptions
By default VKFW has exceptions enabled. This means than VKFW checks both the return value of the function and the error code returned by `vkfw::getError()` (`glfwGetError()`). If it indicates a failure a `std::runtime_error` will be thrown.

If exception handling is disabled (by defining `VKFW_HPP_NO_EXCEPTIONS`), the type of `vkfw::ResultValue<SomeType>::type` is a struct holding a `vkfw::Result` success indicator and the value itself. This struct supports unpacking the return values by using `std::tie`, alternatively you can just access struct members as you normally would, for example:
```c++
auto [result_code, my_brand_new_window] = vkfw::createWindow(...);
// OR
vkfw::Result result_code;
vkfw::Window my_brand_new_window;
std::tie(result_code, my_brand_new_window) = vkfw::createWindow(...);
// OR
auto create_window_output = vkfw::createWindow(...);
auto result_code = create_window_output.result;
auto my_brand_new_window = create_window_output.value;
```

### C++17: `[[nodiscard]]`
With C++17 and above, some functions are attributed with `[[nodiscard]]`, resulting in a warning if you don't use the return value. You can switch those warnings off by defining `VKFW_HPP_NO_NODISCARD_WARNINGS`.

### UniqueHandle for automatic resource management
VKFW provides a `vkfw::UniqueHandle<Type>` interface. For each GLFW handle type `vkfw::Type` there is a unique handle `vkfw::UniqueType` which will delete the underlying GLFW resource upon destruction, e.g. `vkfw::UniqueWindow` is the unique handle for `vkfw::Window`.

For each function which constructs a GLFW handle of type `vkfw::Type` VKFW provides a second version which returns a `vkfw::UniqueType`. E.g. for `vkfw::createWindow(...)` there is `vkfw::createWindowUnique(...)`.

As all the deleters are known at compiler time and don't need to store anything extra - the only downside is a slight compilation time increase.

### Callbacks
To allow using lambdas as callbacks, `GLFWwindow` user pointer is used internally to store `std::function` objects instead of c-style function pointers.
These objects are accessible through `vkfw::Window::callbacks()` (or `accessWindowCallbacks(GLFWwindow *)` if enhanced mode is disabled) function and can be set directly, for example:
```c++
my_window.callbacks().on_key = [](vkfw::Window const &, vkfw::Key key, int32_t, 
                                  vkfw::KeyAction action, vkfw::ModifierKeyFlags) {
  std::cout << vkfw::to_string(action) << ' ' << vkfw::to_string(key) << ".\n";
};
```
Supported callbacks:
| `Name` | `Type` | `GLFW Setter` |
|:-:|:-:|:-:|
| `on_window_move` | `std::function<void(window_type, int, int)>` | `glfwSetWindowPosCallback` |
| `on_window_resize` | `std::function<void(window_type, size_t, size_t)>` | `glfwSetWindowSizeCallback` |
| `on_window_close` | `std::function<void(window_type)>` | `glfwSetWindowCloseCallback` |
| `on_window_refresh` | `std::function<void(window_type)>` | `glfwSetWindowRefreshCallback` |
| `on_window_focus` | `std::function<void(window_type, bool)>` | `glfwSetWindowFocusCallback` |
| `on_window_iconify` | `std::function<void(window_type, bool)>` | `glfwSetWindowIconifyCallback` |
| `on_window_maximize` | `std::function<void(window_type, bool)>` | `glfwSetWindowMaximizeCallback` |
| `on_framebuffer_resize` | `std::function<void(window_type, size_t, size_t)>` | `glfwSetFramebufferSizeCallback` |
| `on_window_content_scale_change` | `std::function<void(window_type, float, float)>` | `glfwSetWindowContentScaleCallback` |
| `on_mouse_button` | `std::function<void(window_type, MouseButton, MouseButtonAction, ModifierKeyFlags)>` | `glfwSetMouseButtonCallback` |
| `on_cursor_move` | `std::function<void(window_type, double, double)>` | `glfwSetCursorPosCallback` |
| `on_cursor_enter` | `std::function<void(window_type, bool)>` | `glfwSetCursorEnterCallback` |
| `on_scroll` | `std::function<void(window_type, double, double)>` | `glfwSetScrollCallback` |
| `on_key` | `std::function<void(window_type, Key, int32_t, KeyAction, ModifierKeyFlags)>` | `glfwSetKeyCallback` |
| `on_character` | `std::function<void(window_type, uint32_t)>` | `glfwSetCharCallback` |
| `on_drop` | `std::function<void(window_type, std::vector<string_type>)>` | `glfwSetDropCallback` |

Note that the remaining callbacks are not affected as they have no relation to windows, mainly error callback and connection-disconection callbacks (for monitors, etc)

### Hints and Attributes
Hint and attribute values are checked at compile time. For example, `glfwSetWindowAttrib(my_window, GLFW_RESIZABLE, GLFW_TRUE)` becomes `my_window.set<vkfw::Attribute::eResizable>(true)` (or `vkfw::set<vkfw::Attribute::eResizable>(my_window, true)` if enhanced more is disabled).
You no longer need to double check whether attribute can even be set: SFINAE garanties that there will be no `set` overload for, say, `vkfw::Attribute::eTransparentFramebuffer`.
Same with hints, they can be either set in GLFW-style, using `vkfw::windowHint<...>(...)` (and `vkfw::initHint<...>(...)`) function template, or by passing a `vkfw::WindowHints` object to `vkfw::createWindow(...)` (and a `vkfw::InitHints` object to `vkfw::init(...)`).
In enhanced mode, the last optional parameter of `vkfw::createWindow(..., bool reset_hints = true)` decides whether to return currently set hint values to default before applying passed `vkfw::WindowHints` object.

## Configuration Options

### `VKFW_DISABLE_ENHANCED_MODE`
When this is defined before including `vkfw.hpp`, you essentially disable all enhanced functionality. 

All you then get is improved compile time error detection, via scoped enums and bitmasks, as well as a compile time checked attribute/hint getters/setters.

### `VKFW_NO_EXCEPTIONS`
When a `vkfw` function returns an error value code, an exception is thrown unless this preprocessor definition is defined before including `vkfw.hpp`.

### `VKFW_NO_SMART_HANDLE`
The `UniqueHandle` helper class and all the unique handle types and functions returning them are not compiled if this precompiler definition is defined.

### `VKFW_NO_STD_FUNCTION_CALLBACKS`
Disables c++ callbacks based on `std::function`. Define this if you cannot afford an extra function call per event for extra usability. Note, that original callbacks do not use `enum class`es and it's your responcibility to cast the values correctly inside the callback itself. Or you can just use original preprocessor definitions.

### `VKFW_NO_NODISCARD_WARNINGS`
With C++17, most `vkfw`-functions returning something are declared with the `[[nodiscard]]` attribute. The attribute can be removed by defining this before including `vkfw.hpp`.

### `VKFW_NO_INCLUDE_VULKAN` and `VKFW_INCLUDE_GL`
VKFW includes `vulkan.h` by default (same as GLFW with `GLFW_INCLUDE_VULKAN` defined) - this preprocessor definition prevents it (resulting in same behavior as GLFW with `GLFW_INCLUDE_NONE` defined). If you need GLFW to include OpenGL header, you **also** need to define `VKFW_INCLUDE_GL` (default GLFW behavior).

### `VKFW_NO_INCLUDE_VULKAN_HPP`
VKFW includes `vulkan.hpp` by default. This preprocessor definition allows to disable the inclusion.
When it is not defined, some of the vulkan.hpp helpers are used (like `UniqueHandle`), otherwise an alternatives are declared.

### `VKFW_NO_LEADING_e_IN_ENUMS`
Removes leading `e` from enum values, for example `vkfw::Key::eA` becomes `vkfw::Key::A` and `vkfw::Key::e1` becomes `vkfw::Key::_1`.

### `VKFW_NAMESPACE`
By default, the namespace used with `vkfw.hpp` is `vkfw`. By defining `VKFW_HPP_NAMESPACE` before including `vkfw.hpp`, you can adjust this.

### `VKFW_NO_STRUCT_CONSTRUCTORS`
In order to support designated initializers (c++20 feature) a struct must not have constructors, so this preprocessor definition just removes them outright. For example:
```c++
vkfw::WindowHints hints {
    .clientAPI = vkfw::ClientAPI::eOpenGL,
    .contextVersionMajor = 4u,
    .contextVersionMinor = 1u
};
```

### `VKFW_NO_SPACESHIP_OPERATOR`
If for some reason you prefer not to have a spaceship operator used even if your compiler supports it, you can define this option to fall back on conventional comparison operators.

### `VKFW_NO_STRING_VIEW`
Define this if you prefer `char const *` to `std::string_view` even if your compiler supports it.

### `VKFW_NO_SPAN`
Define this if you prefer c style arrays / `std::vector`s to `std::span` even if your compiler supports it.

### `VKFW_INLINE`
This preprocessor definition is set to be the compiler-dependent attribute used to mark functions as inline. If your compiler happens to need some different attribute, you can set this define accordingly before including `vkfw.hpp`.

### `VKFW_HPP_ASSERT`
Define this one if you need an alternative assertion, by default `<cassert>` is used.
Mainly, this allow to introduce your own function with the same interface as `assert` to be used instead.

### `VKFW_HPP_ASSERT_ON_RESULT`
Allows to replace an assertion call used to check success codes if exceptions are disabled. By default `VKFW_HPP_ASSERT` is used.

## See Also
- Original [GLFW C API](https://www.glfw.org)
- [Vulkan-Hpp](https://github.com/KhronosGroup/Vulkan-Hpp) - similar bindings for Khronos Vulkan API
- [VKMA](https://github.com/Cvelth/vkma) - similar bindings for GPUOpen VulkanMemoryAllocator.

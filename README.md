# VKFW: C++ Bindings for GLFW
The goal of VKFW is to provide header only C++ bindings for the [GLFW C API](https://github.com/glfw/glfw) to improve the developers GLFW experience without introducing CPU runtime cost. It adds features like type safety for enums and bitfields, STL container support and exceptions.

The bindings (and even the structure of this file) are heavily inspired by [Vulkan-Hpp](https://github.com/KhronosGroup/Vulkan-Hpp) and are designed with similar file structure, code style, etc. In other words, VKFW is intended to be used in projects than already take advantage of Vulkan-Hpp.

## Getting Started
Just `#include <vkfw/vkfw.hpp>` and you're ready to use the C++ bindings.

But don't forget than you still need to make sure than `GLFW/glfw3.h` (and `GLFW/glfw3native.h`) can be included and that the project is linked against `glfw3`.

### Minimum Requirements
VKFW requires a C++11 capable compiler to compile. The following compilers are expected to work:
- Visual Studio >= 2015
- GCC >= 4.8.2 (earlier version might work, but are untested)
- Clang >= 3.3

## Usage
### namespace `vkfw`
To avoid name collisions with the GLFW C API the C++ bindings reside in the `vkfw` namespace. The following rules apply to the new naming

- All functions, enums, handles, and structs have the `glfw`/`GLFW` prefix removed. In addition to this the first letter of functions is lower case, and the first letter of structs is upper case
    - `glfwInit` can be accessed as `vkfw::init`
    - `GLFWwindow` can be accessed as `vkfw::Window`
- Enums are mapped to scoped enums to provide compile time type safety. The names have been changed to 'e' + CamelCase with `GLFW_` prefix removed.
    - `GLFW_KEY_C` is now `vkfw::Key::eC`
    - `GLFW_JOYSTICK_2` is now `vkfw::Joystick::e2`
    - `GLFW_ARROW_CURSOR` is now `vkfw::Cursor::eArrow`

In some cases it might be necessary to move `vkfw` to a custom namespace. This can be achieved by defining `VKFW_HPP_NAMESPACE` before including `vkfw`.

### Handles
VKFW declares a class for all handles to ensure full type safety and to add support for member functions on handles. A member function has been added to a handle class for each function which accepts the corresoinding handle as first parameter. Instead of `glfwSetWindowTitle(&window, title)` one can write
- `window.setTitle(title)`
- `window.setWindowTitle(title)`
- `vkfw::setWindowTitle(window, title)`

### Return values, Error Codes & Exceptions
By default VKFW has exceptions enabled. This means than VKFW checks both the return value of the function and an error code returned by `glfwGetError()` (or equivalent `vkfw::getError()`). If it indicates a failure a `std::runtime_error` will be thrown.

[comment]: # (If exception handling is disabled by defining `VKFW_HPP_NO_EXCEPTIONS` the type of `vkfw::ResultValue<SomeType>::type` is a struct holding a `vkfw::Result` and a `SomeType`. This struct supports unpacking the return values by using `std::tie`.)

### C++17: `[[nodiscard]]`
With C++17 and above, some functions are attributed with `[[nodiscard]]`, resulting in a warning if you don't use the return value in any way. You can switch those warnings off by defining `VKFW_HPP_NO_NODISCARD_WARNINGS`.

### UniqueHandle for automatic resource management
VKFW provides a `vkfw::UniqueHandle<Type, Deleter>` interface. For each GLFW handle type `vkfw::Type` there is a unique handle `vkfw::UniqueType` which will delete the underlying GLFW resource upon destruction, e.g. `vkfw::UniqueWindow` is the unique handle for `vkfw::Window`.

For each function which constructs a GLFW handle of type `vkfw::Type` VKFW provides a second version which returns a `vkfw::UniqueType`. E.g. for `vkfw::createWindow(...)` there is `vkfw::createWindowUnique(...)`.

[comment]: # (Note that using vk::UniqueHandle comes at a cost since most deleters have to store the vk::AllocationCallbacks and parent handle used for construction because they are required for automatic destruction.)

[comment]: # (Custom assertions???)

[comment]: # (Type Traits???)

## Configuration Options

[comment]: # (`VKFW_HPP_ASSERT`)
[comment]: # (`VKFW_HPP_ASSERT_ON_RESULT`)
[comment]: # (`VKFW_HPP_DEFAULT_DISPATCHER`)
[comment]: # (`VKFW_HPP_DEFAULT_DISPATCHER_TYPE`)
[comment]: # (`VKFW_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE`)

### `VKFW_HPP_DISABLE_ENHANCED_MODE`
When this is defined before including `vkfw.hpp`, you essentially disable all enhanced functionality. 

[comment]: # (All you then get is improved compile time error detection, via scoped enums, usage of the helper class vk::Flags for bitmasks, wrapper structs for all vulkan structs providing default initialization, and the helper class vk::StructureChain for compile-time construction of structure chains.)

[comment]: # (`VKFW_HPP_DISPATCH_LOADER_DYNAMIC`)
[comment]: # (`VKFW_HPP_ENABLE_DYNAMIC_LOADER_TOOL`)

### `VKFW_HPP_INLINE`
This is set to be the compiler-dependent attribute used to mark functions as inline. If your compiler happens to need some different attribute, you can set this define accordingly before including `vkfw.hpp`.

### `VKFW_HPP_NAMESPACE`
By default, the namespace used with `vkfw.hpp` is `vkfw`. By defining `VKFW_HPP_NAMESPACE` before including `vkfw.hpp`, you can adjust this.

### `VKFW_HPP_NO_EXCEPTIONS`
When a `vkfw` function returns an error value code, an exception is thrown unless `VKFW_HPP_NO_EXCEPTIONS` is defined before including `vkfw.hpp`.

### `VKFW_HPP_NO_NODISCARD_WARNINGS`
With C++17, all `vkfw`-functions returning something are declared with the attribute `[[nodiscard]]`. This can be removed by defining `VKFW_HPP_NO_NODISCARD_WARNINGS` before including `vkfw.hpp`.

### `VKFW_HPP_NO_SMART_HANDLE`
By defining `VKFW_HPP_NO_SMART_HANDLE` before including `vkfw.hpp`, the helper class `UniqueHandle` and all the unique handle types are not available.

[comment]: # (`VKFW_HPP_NO_SPACESHIP_OPERATOR`)
[comment]: # (`VKFW_HPP_TYPESAFE_CONVERSION`)

## License
Copyright 2020 Cvelth.

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at

> http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
module;

// Because declaring modules (specifically the `export module $NAME`
// declaration) in headers is not allowed, the header inclusion logic has to be
// duplicated.
//
// To enable that, _nothing_ is included by the header if
// `VKFW_MODULE_IMPLEMENTATION` macro is defined.
#define VKFW_MODULE_IMPLEMENTATION

#ifndef VKFW_INCLUDE_GL
  #define GLFW_INCLUDE_NONE
#endif
#ifndef VKFW_NO_INCLUDE_VULKAN
  #define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

#ifndef VKFW_NO_INCLUDE_VULKAN_HPP
  #if defined(VKFW_NO_STRUCT_CONSTRUCTORS) && !defined(VULKAN_HPP_NO_STRUCT_CONSTRUCTORS)
    #define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS VKFW_NO_STRUCT_CONSTRUCTORS
  #endif
  #if defined(VKFW_NO_EXCEPTIONS) && !defined(VULKAN_HPP_NO_EXCEPTIONS)
    #define VULKAN_HPP_NO_EXCEPTIONS VKFW_NO_EXCEPTIONS
  #endif
  #if defined(VKFW_NO_NODISCARD_WARNINGS) && !defined(VULKAN_HPP_NO_NODISCARD_WARNINGS)
    #define VULKAN_HPP_NO_NODISCARD_WARNINGS VKFW_NO_NODISCARD_WARNINGS
  #endif
  #if defined(VKFW_ASSERT) && !defined(VULKAN_HPP_ASSERT)
    #define VULKAN_HPP_ASSERT VKFW_ASSERT
  #endif
  #if defined(VKFW_ASSERT_ON_RESULT) && !defined(VULKAN_HPP_ASSERT_ON_RESULT)
    #define VULKAN_HPP_ASSERT_ON_RESULT VKFW_ASSERT_ON_RESULT
  #endif
  #if defined(VKFW_DISABLE_ENHANCED_MODE) && !defined(VULKAN_HPP_DISABLE_ENHANCED_MODE)
    #define VULKAN_HPP_DISABLE_ENHANCED_MODE VKFW_DISABLE_ENHANCED_MODE
  #endif
  #if defined(VKFW_INLINE) && !defined(VULKAN_HPP_INLINE)
    #define VULKAN_HPP_INLINE VKFW_INLINE
  #endif
  #if defined(VKFW_NO_SMART_HANDLE) && !defined(VULKAN_HPP_NO_SMART_HANDLE)
    #define VULKAN_HPP_NO_SMART_HANDLE VKFW_NO_SMART_HANDLE
  #endif
  #ifdef VKFW_ENABLE_VULKAN_HPP_MODULE
    #include <vulkan/vulkan_hpp_macros.hpp>
  #else
    #include <vulkan/vulkan.hpp>
  #endif
#endif

#if 20 <= VKFW_CPP_VERSION && defined(__has_include) && __has_include(<version> )
  #include <version>
#endif
#if !defined(VKFW_NO_STRING_VIEW) && 17 <= VKFW_CPP_VERSION
  #define VKFW_HAS_STRING_VIEW
  #ifndef VKFW_ENABLE_STD_MODULE
    #include <string_view>
  #endif
#endif
#if !defined(VKFW_NO_SPAN) && 20 <= VKFW_CPP_VERSION && defined(__cpp_lib_span)                    \
  && defined(__has_include) && 202002L <= __cpp_lib_span && __has_include(<span> )
  #define VKFW_HAS_SPAN
  #ifndef VKFW_ENABLE_STD_MODULE
    #include <span>
  #endif
#endif
#if !defined(VKFW_NO_SPACESHIP_OPERATOR) && 20 <= VKFW_CPP_VERSION                                 \
  && defined(__cpp_impl_three_way_comparison) && defined(__has_include)                            \
  && 201711 <= __cpp_impl_three_way_comparison && __has_include(<compare> )
  #define VKFW_HAS_SPACESHIP_OPERATOR
  #ifndef VKFW_ENABLE_STD_MODULE
    #include <compare>
  #endif
#endif

#ifndef VKFW_ENABLE_STD_MODULE
  #include <cstdint>
  #include <string>
  #include <system_error>
  #include <tuple>
  #include <vector>
#endif

#if defined(VULKAN_HPP_NO_SMART_HANDLE) && !defined(VKFW_NO_SMART_HANDLE)                          \
  && !defined(VKFW_NO_INCLUDE_VULKAN_HPP)
  #pragma message(                                                                                 \
    "warning: VKFW_NO_SMART_HANDLE will be defined as vkfw requires Vulkan-HPP handles when "      \
    "VKFW_NO_INCLUDE_VULKAN_HPP isn't defined. You can silence this warning by defining "          \
    "VKFW_NO_SMART_HANDLE or VKFW_NO_INCLUDE_VULKAN_HPP before including <vkfw/vkfw.hpp>")
  #define VKFW_NO_SMART_HANDLE
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  #ifndef VKFW_NO_SMART_HANDLE
    #define VKFW_NO_SMART_HANDLE
  #endif
#elif !defined(VKFW_ENABLE_STD_MODULE)
  #include <algorithm>
  #include <chrono>
  #include <iterator>
  #include <memory>
#endif

#if !defined(VKFW_NO_STD_FUNCTION_CALLBACKS) && !defined(VKFW_ENABLE_STD_MODULE)
  #include <functional>
#endif

#ifndef VKFW_ASSERT
  #include <cassert>
  #define VKFW_ASSERT assert
#endif

export module vkfw;

#ifdef VKFW_ENABLE_VULKAN_HPP_MODULE
import vulkan_hpp;
#endif

#ifdef VKFW_ENABLE_STD_MODULE
  #ifdef VULKAN_HPP_STD_MODULE
import VULKAN_HPP_STD_MODULE
  #else
// use std.compat for maximum compatibility
import std.compat;
  #endif
#endif

#include "vkfw/vkfw.hpp"

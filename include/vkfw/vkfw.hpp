#pragma once
// Copyright (c) 2020 Cvelth.
//
// SPDX-License-Identifier: Apache-2.0
//

#ifdef _MSVC_LANG
  #define VKFW_CPLUSPLUS _MSVC_LANG
#else
  #define VKFW_CPLUSPLUS __cplusplus
#endif

#if 201703L < VKFW_CPLUSPLUS
  #define VKFW_CPP_VERSION 20
#elif 201402L < VKFW_CPLUSPLUS
  #define VKFW_CPP_VERSION 17
#elif 201103L < VKFW_CPLUSPLUS
  #define VKFW_CPP_VERSION 14
#elif 199711L < VKFW_CPLUSPLUS
  #define VKFW_CPP_VERSION 11
#else
  #error "vkfw.hpp needs at least c++ standard version 11"
#endif

#if 20 <= VKFW_CPP_VERSION && defined(__has_include) && __has_include(<version> )
  #include <version>
#endif
#if !defined(VKFW_NO_STRING_VIEW) && 17 <= VKFW_CPP_VERSION
  #include <string_view>
  #define VKFW_HAS_STRING_VIEW
#endif
#if !defined(VKFW_NO_SPAN) && 20 <= VKFW_CPP_VERSION && defined(__cpp_lib_span)                    \
  && defined(__has_include) && 202002L <= __cpp_lib_span && __has_include(<span> )
  #include <span>
  #define VKFW_HAS_SPAN
#endif
#if !defined(VKFW_NO_SPACESHIP_OPERATOR) && 20 <= VKFW_CPP_VERSION                                 \
  && defined(__cpp_impl_three_way_comparison) && defined(__has_include)                            \
  && 201711 <= __cpp_impl_three_way_comparison && __has_include(<compare> )
  #define VKFW_HAS_SPACESHIP_OPERATOR
  #include <compare>
#endif

#include <cstdint>
#include <string>
#include <system_error>
#include <tuple>
#include <vector>

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
  #if defined(VKFW_HPP_INLINE) && !defined(VULKAN_HPP_INLINE)
    #define VULKAN_HPP_INLINE VKFW_HPP_INLINE
  #endif
  #if defined(VKFW_NO_SMART_HANDLE) && !defined(VULKAN_HPP_NO_SMART_HANDLE)
    #define VULKAN_HPP_NO_SMART_HANDLE VKFW_NO_SMART_HANDLE
  #endif
  #include <vulkan/vulkan.hpp>
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  #ifndef VKFW_NO_SMART_HANDLE
    #define VKFW_NO_SMART_HANDLE
  #endif
#else
  #include <algorithm>
  #include <chrono>
  #include <iterator>
  #include <memory>
#endif

#ifndef VKFW_NO_STD_FUNCTION_CALLBACKS
  #include <functional>
#endif

#ifndef VKFW_ASSERT
  #include <cassert>
  #define VKFW_ASSERT assert
#endif

#ifndef VKFW_ASSERT_ON_RESULT
  #define VKFW_ASSERT_ON_RESULT VKFW_ASSERT
#endif

#define VKFW_VERSION_MAJOR             0
#define VKFW_VERSION_MINOR             1
#define VKFW_VERSION_PATCH             0
#define VKFW_TARGET_GLFW_VERSION_MAJOR 3
#define VKFW_TARGET_GLFW_VERSION_MINOR 3

static_assert(GLFW_VERSION_MAJOR == VKFW_TARGET_GLFW_VERSION_MAJOR
                && GLFW_VERSION_MINOR == VKFW_TARGET_GLFW_VERSION_MINOR,
              "\"glfw3.h\" version is not compatible with the \"vkfw.hpp\" version!");

#ifndef VKFW_INLINE
  #ifdef __clang__
    #if __has_attribute(always_inline)
      #define VKFW_INLINE __attribute__((always_inline)) __inline__
    #else
      #define VKFW_INLINE inline
    #endif
  #elif defined(__GNUC__)
    #define VKFW_INLINE __attribute__((always_inline)) __inline__
  #elif defined(_MSC_VER)
    #define VKFW_INLINE inline
  #else
    #define VKFW_INLINE inline
  #endif
#endif

#ifdef __cpp_constexpr
  #define VKFW_CONSTEXPR constexpr
  #if __cpp_constexpr >= 201304
    #define VKFW_CONSTEXPR_14 constexpr
  #else
    #define VKFW_CONSTEXPR_14
  #endif
  #define VKFW_CONST_OR_CONSTEXPR constexpr
#else
  #define VKFW_CONSTEXPR
  #define VKFW_CONSTEXPR_14
  #define VKFW_CONST_OR_CONSTEXPR const
#endif

#ifndef VKFW_NOEXCEPT
  #if defined(_MSC_VER) && (_MSC_VER <= 1800)
    #define VKFW_NOEXCEPT
  #else
    #define VKFW_NOEXCEPT     noexcept
    #define VKFW_HAS_NOEXCEPT 1
  #endif
#endif

#if 14 <= VKFW_CPP_VERSION
  #define VKFW_DEPRECATED(msg) [[deprecated(msg)]]
#else
  #define VKFW_DEPRECATED(msg)
#endif

#if (17 <= VKFW_CPP_VERSION) && !defined(VKFW_NO_NODISCARD_WARNINGS)
  #define VKFW_NODISCARD [[nodiscard]]
  #ifdef VKFW_NO_EXCEPTIONS
    #define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS [[nodiscard]]
  #else
    #define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS
  #endif
#else
  #define VKFW_NODISCARD
  #define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS
#endif

#ifndef VKFW_NAMESPACE
  #define VKFW_NAMESPACE vkfw
#endif

#define VKFW_STRINGIFY2(text) #text
#define VKFW_STRINGIFY(text)  VKFW_STRINGIFY2(text)
#define VKFW_NAMESPACE_STRING VKFW_STRINGIFY(VKFW_NAMESPACE)

#ifdef VKFW_NO_LEADING_e_IN_ENUMS
  #define VKFW_ENUMERATOR(name)            name
  #define VKFW_ENUMERATOR2(name_1, name_2) name_2
#else
  #define VKFW_ENUMERATOR(name)            e##name
  #define VKFW_ENUMERATOR2(name_1, name_2) e##name_1
#endif

namespace VKFW_NAMESPACE {
  enum Boolean { VKFW_ENUMERATOR(True) = GLFW_TRUE, VKFW_ENUMERATOR(False) = GLFW_FALSE };
  enum class KeyAction {
    VKFW_ENUMERATOR(Release) = GLFW_RELEASE,
    VKFW_ENUMERATOR(Press) = GLFW_PRESS,
    VKFW_ENUMERATOR(Repeat) = GLFW_REPEAT
  };
  enum class MouseButtonAction {
    VKFW_ENUMERATOR(Release) = GLFW_RELEASE,
    VKFW_ENUMERATOR(Press) = GLFW_PRESS
  };
  enum class JoystickHatState {
    VKFW_ENUMERATOR(Centered) = GLFW_HAT_CENTERED,
    VKFW_ENUMERATOR(Up) = GLFW_HAT_UP,
    VKFW_ENUMERATOR(Right) = GLFW_HAT_RIGHT,
    VKFW_ENUMERATOR(Down) = GLFW_HAT_DOWN,
    VKFW_ENUMERATOR(Left) = GLFW_HAT_LEFT,
    VKFW_ENUMERATOR(Right_Up) = GLFW_HAT_RIGHT_UP,
    VKFW_ENUMERATOR(Right_Down) = GLFW_HAT_RIGHT_DOWN,
    VKFW_ENUMERATOR(Left_Up) = GLFW_HAT_LEFT_UP,
    VKFW_ENUMERATOR(Left_Down) = GLFW_HAT_LEFT_DOWN
  };
  enum class Key {
    /* The unknown Key */
    VKFW_ENUMERATOR(Unknown) = GLFW_KEY_UNKNOWN,

    /* Printable Keys */
    VKFW_ENUMERATOR(Space) = GLFW_KEY_SPACE,
    VKFW_ENUMERATOR(Apostrophe) = GLFW_KEY_APOSTROPHE, /* ' */
    VKFW_ENUMERATOR(Comma) = GLFW_KEY_COMMA,           /* , */
    VKFW_ENUMERATOR(Minus) = GLFW_KEY_MINUS,           /* - */
    VKFW_ENUMERATOR(Period) = GLFW_KEY_PERIOD,         /* . */
    VKFW_ENUMERATOR(Slash) = GLFW_KEY_SLASH,           /* / */
    VKFW_ENUMERATOR2(0, _0) = GLFW_KEY_0,
    VKFW_ENUMERATOR2(1, _1) = GLFW_KEY_1,
    VKFW_ENUMERATOR2(2, _2) = GLFW_KEY_2,
    VKFW_ENUMERATOR2(3, _3) = GLFW_KEY_3,
    VKFW_ENUMERATOR2(4, _4) = GLFW_KEY_4,
    VKFW_ENUMERATOR2(5, _5) = GLFW_KEY_5,
    VKFW_ENUMERATOR2(6, _6) = GLFW_KEY_6,
    VKFW_ENUMERATOR2(7, _7) = GLFW_KEY_7,
    VKFW_ENUMERATOR2(8, _8) = GLFW_KEY_8,
    VKFW_ENUMERATOR2(9, _9) = GLFW_KEY_9,
    VKFW_ENUMERATOR(Semicolon) = GLFW_KEY_SEMICOLON, /* ; */
    VKFW_ENUMERATOR(Equal) = GLFW_KEY_EQUAL,         /* = */
    VKFW_ENUMERATOR(A) = GLFW_KEY_A,
    VKFW_ENUMERATOR(B) = GLFW_KEY_B,
    VKFW_ENUMERATOR(C) = GLFW_KEY_C,
    VKFW_ENUMERATOR(D) = GLFW_KEY_D,
    VKFW_ENUMERATOR(E) = GLFW_KEY_E,
    VKFW_ENUMERATOR(F) = GLFW_KEY_F,
    VKFW_ENUMERATOR(G) = GLFW_KEY_G,
    VKFW_ENUMERATOR(H) = GLFW_KEY_H,
    VKFW_ENUMERATOR(I) = GLFW_KEY_I,
    VKFW_ENUMERATOR(J) = GLFW_KEY_J,
    VKFW_ENUMERATOR(K) = GLFW_KEY_K,
    VKFW_ENUMERATOR(L) = GLFW_KEY_L,
    VKFW_ENUMERATOR(M) = GLFW_KEY_M,
    VKFW_ENUMERATOR(N) = GLFW_KEY_N,
    VKFW_ENUMERATOR(O) = GLFW_KEY_O,
    VKFW_ENUMERATOR(P) = GLFW_KEY_P,
    VKFW_ENUMERATOR(Q) = GLFW_KEY_Q,
    VKFW_ENUMERATOR(R) = GLFW_KEY_R,
    VKFW_ENUMERATOR(S) = GLFW_KEY_S,
    VKFW_ENUMERATOR(T) = GLFW_KEY_T,
    VKFW_ENUMERATOR(U) = GLFW_KEY_U,
    VKFW_ENUMERATOR(V) = GLFW_KEY_V,
    VKFW_ENUMERATOR(W) = GLFW_KEY_W,
    VKFW_ENUMERATOR(X) = GLFW_KEY_X,
    VKFW_ENUMERATOR(Y) = GLFW_KEY_Y,
    VKFW_ENUMERATOR(Z) = GLFW_KEY_Z,
    VKFW_ENUMERATOR(LeftBracket) = GLFW_KEY_LEFT_BRACKET,   /* [ */
    VKFW_ENUMERATOR(Backslash) = GLFW_KEY_BACKSLASH,        /* \ */
    VKFW_ENUMERATOR(RightBracket) = GLFW_KEY_RIGHT_BRACKET, /* ] */
    VKFW_ENUMERATOR(GraveAccent) = GLFW_KEY_GRAVE_ACCENT,   /* ` */
    VKFW_ENUMERATOR(World1) = GLFW_KEY_WORLD_1,             /* non-US #1 */
    VKFW_ENUMERATOR(World2) = GLFW_KEY_WORLD_2,             /* non-US #2 */

    /* Function Keys */
    VKFW_ENUMERATOR(Escape) = GLFW_KEY_ESCAPE,
    VKFW_ENUMERATOR(Enter) = GLFW_KEY_ENTER,
    VKFW_ENUMERATOR(Tab) = GLFW_KEY_TAB,
    VKFW_ENUMERATOR(Backspace) = GLFW_KEY_BACKSPACE,
    VKFW_ENUMERATOR(Insert) = GLFW_KEY_INSERT,
    VKFW_ENUMERATOR(Delete) = GLFW_KEY_DELETE,
    VKFW_ENUMERATOR(Right) = GLFW_KEY_RIGHT,
    VKFW_ENUMERATOR(Left) = GLFW_KEY_LEFT,
    VKFW_ENUMERATOR(Down) = GLFW_KEY_DOWN,
    VKFW_ENUMERATOR(Up) = GLFW_KEY_UP,
    VKFW_ENUMERATOR(PageUp) = GLFW_KEY_PAGE_UP,
    VKFW_ENUMERATOR(PageDown) = GLFW_KEY_PAGE_DOWN,
    VKFW_ENUMERATOR(Home) = GLFW_KEY_HOME,
    VKFW_ENUMERATOR(End) = GLFW_KEY_END,
    VKFW_ENUMERATOR(CapsLock) = GLFW_KEY_CAPS_LOCK,
    VKFW_ENUMERATOR(ScrollLock) = GLFW_KEY_SCROLL_LOCK,
    VKFW_ENUMERATOR(NumLock) = GLFW_KEY_NUM_LOCK,
    VKFW_ENUMERATOR(PrintScreen) = GLFW_KEY_PRINT_SCREEN,
    VKFW_ENUMERATOR(Pause) = GLFW_KEY_PAUSE,
    VKFW_ENUMERATOR(F1) = GLFW_KEY_F1,
    VKFW_ENUMERATOR(F2) = GLFW_KEY_F2,
    VKFW_ENUMERATOR(F3) = GLFW_KEY_F3,
    VKFW_ENUMERATOR(F4) = GLFW_KEY_F4,
    VKFW_ENUMERATOR(F5) = GLFW_KEY_F5,
    VKFW_ENUMERATOR(F6) = GLFW_KEY_F6,
    VKFW_ENUMERATOR(F7) = GLFW_KEY_F7,
    VKFW_ENUMERATOR(F8) = GLFW_KEY_F8,
    VKFW_ENUMERATOR(F9) = GLFW_KEY_F9,
    VKFW_ENUMERATOR(F10) = GLFW_KEY_F10,
    VKFW_ENUMERATOR(F11) = GLFW_KEY_F11,
    VKFW_ENUMERATOR(F12) = GLFW_KEY_F12,
    VKFW_ENUMERATOR(F13) = GLFW_KEY_F13,
    VKFW_ENUMERATOR(F14) = GLFW_KEY_F14,
    VKFW_ENUMERATOR(F15) = GLFW_KEY_F15,
    VKFW_ENUMERATOR(F16) = GLFW_KEY_F16,
    VKFW_ENUMERATOR(F17) = GLFW_KEY_F17,
    VKFW_ENUMERATOR(F18) = GLFW_KEY_F18,
    VKFW_ENUMERATOR(F19) = GLFW_KEY_F19,
    VKFW_ENUMERATOR(F20) = GLFW_KEY_F20,
    VKFW_ENUMERATOR(F21) = GLFW_KEY_F21,
    VKFW_ENUMERATOR(F22) = GLFW_KEY_F22,
    VKFW_ENUMERATOR(F23) = GLFW_KEY_F23,
    VKFW_ENUMERATOR(F24) = GLFW_KEY_F24,
    VKFW_ENUMERATOR(F25) = GLFW_KEY_F25,
    VKFW_ENUMERATOR(KeyPad_0) = GLFW_KEY_KP_0,
    VKFW_ENUMERATOR(KeyPad_1) = GLFW_KEY_KP_1,
    VKFW_ENUMERATOR(KeyPad_2) = GLFW_KEY_KP_2,
    VKFW_ENUMERATOR(KeyPad_3) = GLFW_KEY_KP_3,
    VKFW_ENUMERATOR(KeyPad_4) = GLFW_KEY_KP_4,
    VKFW_ENUMERATOR(KeyPad_5) = GLFW_KEY_KP_5,
    VKFW_ENUMERATOR(KeyPad_6) = GLFW_KEY_KP_6,
    VKFW_ENUMERATOR(KeyPad_7) = GLFW_KEY_KP_7,
    VKFW_ENUMERATOR(KeyPad_8) = GLFW_KEY_KP_8,
    VKFW_ENUMERATOR(KeyPad_9) = GLFW_KEY_KP_9,
    VKFW_ENUMERATOR(KeyPad_Decimal) = GLFW_KEY_KP_DECIMAL,
    VKFW_ENUMERATOR(KeyPad_Divide) = GLFW_KEY_KP_DIVIDE,
    VKFW_ENUMERATOR(KeyPad_Multiply) = GLFW_KEY_KP_MULTIPLY,
    VKFW_ENUMERATOR(KeyPad_Subtract) = GLFW_KEY_KP_SUBTRACT,
    VKFW_ENUMERATOR(KeyPad_Add) = GLFW_KEY_KP_ADD,
    VKFW_ENUMERATOR(KeyPad_Enter) = GLFW_KEY_KP_ENTER,
    VKFW_ENUMERATOR(KeyPad_Equal) = GLFW_KEY_KP_EQUAL,
    VKFW_ENUMERATOR(LeftShift) = GLFW_KEY_LEFT_SHIFT,
    VKFW_ENUMERATOR(LeftControl) = GLFW_KEY_LEFT_CONTROL,
    VKFW_ENUMERATOR(LeftAlt) = GLFW_KEY_LEFT_ALT,
    VKFW_ENUMERATOR(LeftSuper) = GLFW_KEY_LEFT_SUPER,
    VKFW_ENUMERATOR(RightShift) = GLFW_KEY_RIGHT_SHIFT,
    VKFW_ENUMERATOR(RightControl) = GLFW_KEY_RIGHT_CONTROL,
    VKFW_ENUMERATOR(RightAlt) = GLFW_KEY_RIGHT_ALT,
    VKFW_ENUMERATOR(RightSuper) = GLFW_KEY_RIGHT_SUPER,
    VKFW_ENUMERATOR(Menu) = GLFW_KEY_MENU,

    VKFW_ENUMERATOR(LAST) = GLFW_KEY_LAST
  };
  enum class MouseButton {
    VKFW_ENUMERATOR2(1, _1) = GLFW_MOUSE_BUTTON_1,
    VKFW_ENUMERATOR2(2, _2) = GLFW_MOUSE_BUTTON_2,
    VKFW_ENUMERATOR2(3, _3) = GLFW_MOUSE_BUTTON_3,
    VKFW_ENUMERATOR2(4, _4) = GLFW_MOUSE_BUTTON_4,
    VKFW_ENUMERATOR2(5, _5) = GLFW_MOUSE_BUTTON_5,
    VKFW_ENUMERATOR2(6, _6) = GLFW_MOUSE_BUTTON_6,
    VKFW_ENUMERATOR2(7, _7) = GLFW_MOUSE_BUTTON_7,
    VKFW_ENUMERATOR2(8, _8) = GLFW_MOUSE_BUTTON_8,

    VKFW_ENUMERATOR(Left) = GLFW_MOUSE_BUTTON_LEFT,
    VKFW_ENUMERATOR(Right) = GLFW_MOUSE_BUTTON_RIGHT,
    VKFW_ENUMERATOR(Middle) = GLFW_MOUSE_BUTTON_MIDDLE,

    VKFW_ENUMERATOR(LAST) = GLFW_MOUSE_BUTTON_LAST
  };
  enum class Joystick {
    VKFW_ENUMERATOR2(1, _1) = GLFW_JOYSTICK_1,
    VKFW_ENUMERATOR2(2, _2) = GLFW_JOYSTICK_2,
    VKFW_ENUMERATOR2(3, _3) = GLFW_JOYSTICK_3,
    VKFW_ENUMERATOR2(4, _4) = GLFW_JOYSTICK_4,
    VKFW_ENUMERATOR2(5, _5) = GLFW_JOYSTICK_5,
    VKFW_ENUMERATOR2(6, _6) = GLFW_JOYSTICK_6,
    VKFW_ENUMERATOR2(7, _7) = GLFW_JOYSTICK_7,
    VKFW_ENUMERATOR2(8, _8) = GLFW_JOYSTICK_8,
    VKFW_ENUMERATOR2(9, _9) = GLFW_JOYSTICK_9,
    VKFW_ENUMERATOR2(10, _10) = GLFW_JOYSTICK_10,
    VKFW_ENUMERATOR2(11, _11) = GLFW_JOYSTICK_11,
    VKFW_ENUMERATOR2(12, _12) = GLFW_JOYSTICK_12,
    VKFW_ENUMERATOR2(13, _13) = GLFW_JOYSTICK_13,
    VKFW_ENUMERATOR2(14, _14) = GLFW_JOYSTICK_14,
    VKFW_ENUMERATOR2(15, _15) = GLFW_JOYSTICK_15,
    VKFW_ENUMERATOR2(16, _16) = GLFW_JOYSTICK_16,

    VKFW_ENUMERATOR(LAST) = GLFW_JOYSTICK_LAST
  };
  enum class GamepadButton {
    VKFW_ENUMERATOR(A) = GLFW_GAMEPAD_BUTTON_A,
    VKFW_ENUMERATOR(B) = GLFW_GAMEPAD_BUTTON_B,
    VKFW_ENUMERATOR(X) = GLFW_GAMEPAD_BUTTON_X,
    VKFW_ENUMERATOR(Y) = GLFW_GAMEPAD_BUTTON_Y,
    VKFW_ENUMERATOR(LeftBumper) = GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
    VKFW_ENUMERATOR(RightBumper) = GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
    VKFW_ENUMERATOR(Back) = GLFW_GAMEPAD_BUTTON_BACK,
    VKFW_ENUMERATOR(Start) = GLFW_GAMEPAD_BUTTON_START,
    VKFW_ENUMERATOR(Guide) = GLFW_GAMEPAD_BUTTON_GUIDE,
    VKFW_ENUMERATOR(LeftThumb) = GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
    VKFW_ENUMERATOR(RightThumb) = GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
    VKFW_ENUMERATOR(DpadUp) = GLFW_GAMEPAD_BUTTON_DPAD_UP,
    VKFW_ENUMERATOR(DpadRight) = GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
    VKFW_ENUMERATOR(DpadDown) = GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
    VKFW_ENUMERATOR(DpadLeft) = GLFW_GAMEPAD_BUTTON_DPAD_LEFT,

    VKFW_ENUMERATOR(Cross) = GLFW_GAMEPAD_BUTTON_CROSS,
    VKFW_ENUMERATOR(Circle) = GLFW_GAMEPAD_BUTTON_CIRCLE,
    VKFW_ENUMERATOR(Square) = GLFW_GAMEPAD_BUTTON_SQUARE,
    VKFW_ENUMERATOR(Triangle) = GLFW_GAMEPAD_BUTTON_TRIANGLE,

    VKFW_ENUMERATOR(LAST) = GLFW_GAMEPAD_BUTTON_LAST
  };
  enum class GamepadAxis {
    VKFW_ENUMERATOR(LeftX) = GLFW_GAMEPAD_AXIS_LEFT_X,
    VKFW_ENUMERATOR(LeftY) = GLFW_GAMEPAD_AXIS_LEFT_Y,
    VKFW_ENUMERATOR(RightX) = GLFW_GAMEPAD_AXIS_RIGHT_X,
    VKFW_ENUMERATOR(RightY) = GLFW_GAMEPAD_AXIS_RIGHT_Y,
    VKFW_ENUMERATOR(LeftTrigger) = GLFW_GAMEPAD_AXIS_LEFT_TRIGGER,
    VKFW_ENUMERATOR(RightTrigger) = GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER,

    VKFW_ENUMERATOR(LAST) = GLFW_GAMEPAD_AXIS_LAST
  };
  enum class Result {
    VKFW_ENUMERATOR(Success) = GLFW_NO_ERROR,
    VKFW_ENUMERATOR(NotInitialized) = GLFW_NOT_INITIALIZED,
    VKFW_ENUMERATOR(NoCurrentContext) = GLFW_NO_CURRENT_CONTEXT,
    VKFW_ENUMERATOR(InvalidEnum) = GLFW_INVALID_ENUM,
    VKFW_ENUMERATOR(InvalidValue) = GLFW_INVALID_VALUE,
    VKFW_ENUMERATOR(OutOfMemory) = GLFW_OUT_OF_MEMORY,
    VKFW_ENUMERATOR(ApiUnavailable) = GLFW_API_UNAVAILABLE,
    VKFW_ENUMERATOR(VersionUnavailable) = GLFW_VERSION_UNAVAILABLE,
    VKFW_ENUMERATOR(PlatformError) = GLFW_PLATFORM_ERROR,
    VKFW_ENUMERATOR(FormatUnavailable) = GLFW_FORMAT_UNAVAILABLE,
    VKFW_ENUMERATOR(NoWindowContext) = GLFW_NO_WINDOW_CONTEXT
  };
  VKFW_INLINE VKFW_CONSTEXPR bool check(Result result) {
    return result == Result::VKFW_ENUMERATOR(Success);
  }
  enum class InitializationHint {
    VKFW_ENUMERATOR(JoystickHatButtons) = GLFW_JOYSTICK_HAT_BUTTONS,
    VKFW_ENUMERATOR(CocoaChdirResources) = GLFW_COCOA_CHDIR_RESOURCES, // MacOS specific
    VKFW_ENUMERATOR(CocoaMenubar) = GLFW_COCOA_MENUBAR                 // MacOS specific
  };
  enum class WindowHint {

    // Window Hints
    VKFW_ENUMERATOR(Focused) = GLFW_FOCUSED,
    VKFW_ENUMERATOR(Resizable) = GLFW_RESIZABLE,
    VKFW_ENUMERATOR(Visible) = GLFW_VISIBLE,
    VKFW_ENUMERATOR(Decorated) = GLFW_DECORATED,
    VKFW_ENUMERATOR(AutoIconify) = GLFW_AUTO_ICONIFY,
    VKFW_ENUMERATOR(Floating) = GLFW_FLOATING,
    VKFW_ENUMERATOR(Maximized) = GLFW_MAXIMIZED,
    VKFW_ENUMERATOR(CenterCursor) = GLFW_CENTER_CURSOR,
    VKFW_ENUMERATOR(TransparentFramebuffer) = GLFW_TRANSPARENT_FRAMEBUFFER,
    VKFW_ENUMERATOR(FocusOnShow) = GLFW_FOCUS_ON_SHOW,

    // Framebuffer Hints
    VKFW_ENUMERATOR(RedBits) = GLFW_RED_BITS,
    VKFW_ENUMERATOR(GreenBits) = GLFW_GREEN_BITS,
    VKFW_ENUMERATOR(BlueBits) = GLFW_BLUE_BITS,
    VKFW_ENUMERATOR(AlphaBits) = GLFW_ALPHA_BITS,
    VKFW_ENUMERATOR(DepthBits) = GLFW_DEPTH_BITS,
    VKFW_ENUMERATOR(StencilBits) = GLFW_STENCIL_BITS,
    VKFW_ENUMERATOR(AccumulationRedBits) = GLFW_ACCUM_RED_BITS,
    VKFW_ENUMERATOR(AccumulationGreenBits) = GLFW_ACCUM_GREEN_BITS,
    VKFW_ENUMERATOR(AccumulationBlueBits) = GLFW_ACCUM_BLUE_BITS,
    VKFW_ENUMERATOR(AccumulationAlphaBits) = GLFW_ACCUM_ALPHA_BITS,
    VKFW_ENUMERATOR(AuxiliaryBuffers) = GLFW_AUX_BUFFERS,
    VKFW_ENUMERATOR(StereoscopicRendering) = GLFW_STEREO,
    VKFW_ENUMERATOR(Samples) = GLFW_SAMPLES,
    VKFW_ENUMERATOR(SRGBCapable) = GLFW_SRGB_CAPABLE,
    VKFW_ENUMERATOR(RefreshRate) = GLFW_REFRESH_RATE,

    VKFW_ENUMERATOR(ScaleToMonitor) = GLFW_SCALE_TO_MONITOR,

    // Context client API Hints
    VKFW_ENUMERATOR(DoubleBuffer) = GLFW_DOUBLEBUFFER,
    VKFW_ENUMERATOR(ClientAPI) = GLFW_CLIENT_API,
    VKFW_ENUMERATOR(ContextVersionMajor) = GLFW_CONTEXT_VERSION_MAJOR,
    VKFW_ENUMERATOR(ContextVersionMinor) = GLFW_CONTEXT_VERSION_MINOR,
    // VKFW_ENUMERATOR(ContextRevision) = GLFW_CONTEXT_REVISION,
    VKFW_ENUMERATOR(ContextRobustness) = GLFW_CONTEXT_ROBUSTNESS,
    VKFW_ENUMERATOR(OpenGLForwardCompatibility) = GLFW_OPENGL_FORWARD_COMPAT,
    VKFW_ENUMERATOR(OpenGLDebugContext) = GLFW_OPENGL_DEBUG_CONTEXT,
    VKFW_ENUMERATOR(OpenGLProfile) = GLFW_OPENGL_PROFILE,
    VKFW_ENUMERATOR(ContextReleaseBehavior) = GLFW_CONTEXT_RELEASE_BEHAVIOR,
    VKFW_ENUMERATOR(ContextNoError) = GLFW_CONTEXT_NO_ERROR,
    VKFW_ENUMERATOR(ContextCreationAPI) = GLFW_CONTEXT_CREATION_API,

    // MacOS specific Hints
    VKFW_ENUMERATOR(CocoaRetinaFramebuffer) = GLFW_COCOA_RETINA_FRAMEBUFFER,
    VKFW_ENUMERATOR(CocoaFrameName) = GLFW_COCOA_FRAME_NAME,
    VKFW_ENUMERATOR(CocoaGraphicsSwitching) = GLFW_COCOA_GRAPHICS_SWITCHING,

    // X11 specific Hints
    VKFW_ENUMERATOR(X11ClassName) = GLFW_X11_CLASS_NAME,
    VKFW_ENUMERATOR(X11InstanceName) = GLFW_X11_INSTANCE_NAME,
  };
  enum class Attribute {
    // Window Attributes
    VKFW_ENUMERATOR(Focused) = GLFW_FOCUSED,
    VKFW_ENUMERATOR(Iconified) = GLFW_ICONIFIED,
    VKFW_ENUMERATOR(Resizable) = GLFW_RESIZABLE,
    VKFW_ENUMERATOR(Visible) = GLFW_VISIBLE,
    VKFW_ENUMERATOR(Decorated) = GLFW_DECORATED,
    VKFW_ENUMERATOR(AutoIconify) = GLFW_AUTO_ICONIFY,
    VKFW_ENUMERATOR(Floating) = GLFW_FLOATING,
    VKFW_ENUMERATOR(Maximized) = GLFW_MAXIMIZED,
    VKFW_ENUMERATOR(TransparentFramebuffer) = GLFW_TRANSPARENT_FRAMEBUFFER,
    VKFW_ENUMERATOR(Hovered) = GLFW_HOVERED,
    VKFW_ENUMERATOR(FocusOnShow) = GLFW_FOCUS_ON_SHOW,

    // Context client API Attributes
    VKFW_ENUMERATOR(ClientAPI) = GLFW_CLIENT_API,
    VKFW_ENUMERATOR(ContextVersionMajor) = GLFW_CONTEXT_VERSION_MAJOR,
    VKFW_ENUMERATOR(ContextVersionMinor) = GLFW_CONTEXT_VERSION_MINOR,
    VKFW_ENUMERATOR(ContextRevision) = GLFW_CONTEXT_REVISION,
    VKFW_ENUMERATOR(ContextRobustness) = GLFW_CONTEXT_ROBUSTNESS,
    VKFW_ENUMERATOR(OpenGLForwardCompatibility) = GLFW_OPENGL_FORWARD_COMPAT,
    VKFW_ENUMERATOR(OpenGLDebugContext) = GLFW_OPENGL_DEBUG_CONTEXT,
    VKFW_ENUMERATOR(OpenGLProfile) = GLFW_OPENGL_PROFILE,
    VKFW_ENUMERATOR(ContextReleaseBehavior) = GLFW_CONTEXT_RELEASE_BEHAVIOR,
    VKFW_ENUMERATOR(ContextNoError) = GLFW_CONTEXT_NO_ERROR,
    VKFW_ENUMERATOR(ContextCreationAPI) = GLFW_CONTEXT_CREATION_API,
  };
  using WindowAttribute = Attribute;

  enum class ClientAPI {
    VKFW_ENUMERATOR(None) = GLFW_NO_API,
    VKFW_ENUMERATOR(OpenGL) = GLFW_OPENGL_API,
    VKFW_ENUMERATOR(OpenGL_ES) = GLFW_OPENGL_ES_API
  };
  enum class ContextRobustness {
    VKFW_ENUMERATOR(None) = GLFW_NO_ROBUSTNESS,
    VKFW_ENUMERATOR(NoResetNotification) = GLFW_NO_RESET_NOTIFICATION,
    VKFW_ENUMERATOR(LoseContextOnReset) = GLFW_LOSE_CONTEXT_ON_RESET
  };
  enum class OpenGLProfile {
    VKFW_ENUMERATOR(Any) = GLFW_OPENGL_ANY_PROFILE,
    VKFW_ENUMERATOR(Core) = GLFW_OPENGL_CORE_PROFILE,
    VKFW_ENUMERATOR(Compatibility) = GLFW_OPENGL_COMPAT_PROFILE
  };
  enum class InputMode {
    VKFW_ENUMERATOR(Cursor) = GLFW_CURSOR,
    VKFW_ENUMERATOR(StickyKeys) = GLFW_STICKY_KEYS,
    VKFW_ENUMERATOR(StickyMouseButtons) = GLFW_STICKY_MOUSE_BUTTONS,
    VKFW_ENUMERATOR(LockKeyModifiers) = GLFW_LOCK_KEY_MODS,
    VKFW_ENUMERATOR(RawMouseMotion) = GLFW_RAW_MOUSE_MOTION
  };
  enum class CursorMode {
    VKFW_ENUMERATOR(Normal) = GLFW_CURSOR_NORMAL,
    VKFW_ENUMERATOR(Hidden) = GLFW_CURSOR_HIDDEN,
    VKFW_ENUMERATOR(Disabled) = GLFW_CURSOR_DISABLED
  };
  enum class ContextReleaseBehavior {
    VKFW_ENUMERATOR(Any) = GLFW_ANY_RELEASE_BEHAVIOR,
    VKFW_ENUMERATOR(Flush) = GLFW_RELEASE_BEHAVIOR_FLUSH,
    VKFW_ENUMERATOR(None) = GLFW_RELEASE_BEHAVIOR_NONE
  };
  enum class ContextCreationAPI {
    VKFW_ENUMERATOR(Native) = GLFW_NATIVE_CONTEXT_API,
    VKFW_ENUMERATOR(EGL) = GLFW_EGL_CONTEXT_API,
    VKFW_ENUMERATOR(OSMESA) = GLFW_OSMESA_CONTEXT_API
  };
  enum class CursorShape {
    VKFW_ENUMERATOR(Arrow) = GLFW_ARROW_CURSOR,
    VKFW_ENUMERATOR(IBeam) = GLFW_IBEAM_CURSOR,
    VKFW_ENUMERATOR(Crosshair) = GLFW_CROSSHAIR_CURSOR,
    VKFW_ENUMERATOR(Hand) = GLFW_HAND_CURSOR,
    VKFW_ENUMERATOR(HResize) = GLFW_HRESIZE_CURSOR,
    VKFW_ENUMERATOR(VResize) = GLFW_VRESIZE_CURSOR
  };
  enum class Status {
    VKFW_ENUMERATOR(Connected) = GLFW_CONNECTED,
    VKFW_ENUMERATOR(Disconnected) = GLFW_DISCONNECTED
  };
  enum DontCare : unsigned {
    DontCare = unsigned(GLFW_DONT_CARE)
#ifndef VKFW_NO_LEADING_e_IN_ENUMS
      ,
    eDontCare = unsigned(GLFW_DONT_CARE)
#endif
  };

  enum class ModifierKeyBits {
    VKFW_ENUMERATOR(Shift) = GLFW_MOD_SHIFT,
    VKFW_ENUMERATOR(Control) = GLFW_MOD_CONTROL,
    VKFW_ENUMERATOR(Alt) = GLFW_MOD_ALT,
    VKFW_ENUMERATOR(Super) = GLFW_MOD_SUPER,
    VKFW_ENUMERATOR(CapsLock) = GLFW_MOD_CAPS_LOCK,
    VKFW_ENUMERATOR(NumLock) = GLFW_MOD_NUM_LOCK
  };
  class ModifierKeyFlags {
  public:
    using MaskType = typename std::underlying_type<ModifierKeyBits>::type;
    enum class traits : MaskType {
      allFlags = MaskType(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(Shift))
               | MaskType(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(Control))
               | MaskType(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(Alt))
               | MaskType(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(Super))
               | MaskType(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(CapsLock))
               | MaskType(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(NumLock))
    };

    VKFW_CONSTEXPR ModifierKeyFlags() VKFW_NOEXCEPT : m_mask(0) {}
    VKFW_CONSTEXPR ModifierKeyFlags(ModifierKeyBits bit) VKFW_NOEXCEPT
      : m_mask(static_cast<MaskType>(bit)) {}
    VKFW_CONSTEXPR ModifierKeyFlags(ModifierKeyFlags const &rhs) VKFW_NOEXCEPT
      : m_mask(rhs.m_mask) {}
    VKFW_CONSTEXPR explicit ModifierKeyFlags(MaskType flags) VKFW_NOEXCEPT : m_mask(flags) {}

#ifdef VKFW_HAS_SPACESHIP_OPERATOR
    auto operator<=>(ModifierKeyFlags const &) const = default;
#else
    VKFW_CONSTEXPR bool operator<(ModifierKeyFlags const &rhs) const VKFW_NOEXCEPT {
      return m_mask < rhs.m_mask;
    }
    VKFW_CONSTEXPR bool operator<=(ModifierKeyFlags const &rhs) const VKFW_NOEXCEPT {
      return m_mask <= rhs.m_mask;
    }
    VKFW_CONSTEXPR bool operator>(ModifierKeyFlags const &rhs) const VKFW_NOEXCEPT {
      return m_mask > rhs.m_mask;
    }
    VKFW_CONSTEXPR bool operator>=(ModifierKeyFlags const &rhs) const VKFW_NOEXCEPT {
      return m_mask >= rhs.m_mask;
    }
    VKFW_CONSTEXPR bool operator==(ModifierKeyFlags const &rhs) const VKFW_NOEXCEPT {
      return m_mask == rhs.m_mask;
    }
    VKFW_CONSTEXPR bool operator!=(ModifierKeyFlags const &rhs) const VKFW_NOEXCEPT {
      return m_mask != rhs.m_mask;
    }
#endif
    VKFW_CONSTEXPR bool operator!() const VKFW_NOEXCEPT { return !m_mask; }
    VKFW_CONSTEXPR ModifierKeyFlags operator&(ModifierKeyFlags const &rhs) const VKFW_NOEXCEPT {
      return ModifierKeyFlags(m_mask & rhs.m_mask);
    }
    VKFW_CONSTEXPR ModifierKeyFlags operator|(ModifierKeyFlags const &rhs) const VKFW_NOEXCEPT {
      return ModifierKeyFlags(m_mask | rhs.m_mask);
    }
    VKFW_CONSTEXPR ModifierKeyFlags operator^(ModifierKeyFlags const &rhs) const VKFW_NOEXCEPT {
      return ModifierKeyFlags(m_mask ^ rhs.m_mask);
    }
    VKFW_CONSTEXPR ModifierKeyFlags operator~() const VKFW_NOEXCEPT {
      return ModifierKeyFlags(m_mask ^ static_cast<MaskType>(traits::allFlags));
    }

    VKFW_CONSTEXPR_14 ModifierKeyFlags &operator=(ModifierKeyFlags const &rhs) VKFW_NOEXCEPT {
      m_mask = rhs.m_mask;
      return *this;
    }
    VKFW_CONSTEXPR_14 ModifierKeyFlags &operator|=(ModifierKeyFlags const &rhs) VKFW_NOEXCEPT {
      m_mask |= rhs.m_mask;
      return *this;
    }
    VKFW_CONSTEXPR_14 ModifierKeyFlags &operator&=(ModifierKeyFlags const &rhs) VKFW_NOEXCEPT {
      m_mask &= rhs.m_mask;
      return *this;
    }
    VKFW_CONSTEXPR_14 ModifierKeyFlags &operator^=(ModifierKeyFlags const &rhs) VKFW_NOEXCEPT {
      m_mask ^= rhs.m_mask;
      return *this;
    }

    explicit VKFW_CONSTEXPR operator bool() const VKFW_NOEXCEPT { return !!m_mask; }
    explicit VKFW_CONSTEXPR operator MaskType() const VKFW_NOEXCEPT { return m_mask; }

  private:
    MaskType m_mask;
  };
#if !defined(VKFW_HAS_SPACESHIP_OPERATOR)
  template <typename BitType>
  VKFW_CONSTEXPR bool operator<(BitType bit, ModifierKeyFlags const &flags) VKFW_NOEXCEPT {
    return flags > bit;
  }
  template <typename BitType>
  VKFW_CONSTEXPR bool operator<=(BitType bit, ModifierKeyFlags const &flags) VKFW_NOEXCEPT {
    return flags >= bit;
  }
  template <typename BitType>
  VKFW_CONSTEXPR bool operator>(BitType bit, ModifierKeyFlags const &flags) VKFW_NOEXCEPT {
    return flags < bit;
  }
  template <typename BitType>
  VKFW_CONSTEXPR bool operator>=(BitType bit, ModifierKeyFlags const &flags) VKFW_NOEXCEPT {
    return flags <= bit;
  }
  template <typename BitType>
  VKFW_CONSTEXPR bool operator==(BitType bit, ModifierKeyFlags const &flags) VKFW_NOEXCEPT {
    return flags == bit;
  }
  template <typename BitType>
  VKFW_CONSTEXPR bool operator!=(BitType bit, ModifierKeyFlags const &flags) VKFW_NOEXCEPT {
    return flags != bit;
  }
#endif
  VKFW_CONSTEXPR ModifierKeyFlags operator&(ModifierKeyBits bit,
                                            ModifierKeyFlags const &flags) VKFW_NOEXCEPT {
    return flags & bit;
  }
  VKFW_CONSTEXPR ModifierKeyFlags operator|(ModifierKeyBits bit,
                                            ModifierKeyFlags const &flags) VKFW_NOEXCEPT {
    return flags | bit;
  }
  VKFW_CONSTEXPR ModifierKeyFlags operator^(ModifierKeyBits bit,
                                            ModifierKeyFlags const &flags) VKFW_NOEXCEPT {
    return flags ^ bit;
  }
  VKFW_INLINE VKFW_CONSTEXPR ModifierKeyFlags operator|(ModifierKeyBits bit0,
                                                        ModifierKeyBits bit1) VKFW_NOEXCEPT {
    return ModifierKeyFlags(bit0) | bit1;
  }
  VKFW_INLINE VKFW_CONSTEXPR ModifierKeyFlags operator&(ModifierKeyBits bit0,
                                                        ModifierKeyBits bit1) VKFW_NOEXCEPT {
    return ModifierKeyFlags(bit0) & bit1;
  }
  VKFW_INLINE VKFW_CONSTEXPR ModifierKeyFlags operator^(ModifierKeyBits bit0,
                                                        ModifierKeyBits bit1) VKFW_NOEXCEPT {
    return ModifierKeyFlags(bit0) ^ bit1;
  }
  VKFW_INLINE VKFW_CONSTEXPR ModifierKeyFlags operator~(ModifierKeyBits bits) VKFW_NOEXCEPT {
    return ~(ModifierKeyFlags(bits));
  }

  VKFW_INLINE std::string to_string(Boolean value) {
    switch (value) {
    case Boolean::VKFW_ENUMERATOR(True): return "True";
    case Boolean::VKFW_ENUMERATOR(False): return "False";
    default: return "invalid";
    }
  }
  VKFW_INLINE std::string to_string(KeyAction value) {
    switch (value) {
    case KeyAction::VKFW_ENUMERATOR(Release): return "Release";
    case KeyAction::VKFW_ENUMERATOR(Press): return "Press";
    case KeyAction::VKFW_ENUMERATOR(Repeat): return "Repeat";
    default: return "invalid";
    }
  }
  VKFW_INLINE std::string to_string(MouseButtonAction value) {
    switch (value) {
    case MouseButtonAction::VKFW_ENUMERATOR(Release): return "Release";
    case MouseButtonAction::VKFW_ENUMERATOR(Press): return "Press";
    default: return "invalid";
    }
  }
  VKFW_INLINE std::string to_string(JoystickHatState value) {
    switch (value) {
    case JoystickHatState::VKFW_ENUMERATOR(Centered): return "Centered";
    case JoystickHatState::VKFW_ENUMERATOR(Up): return "Up";
    case JoystickHatState::VKFW_ENUMERATOR(Right): return "Right";
    case JoystickHatState::VKFW_ENUMERATOR(Down): return "Down";
    case JoystickHatState::VKFW_ENUMERATOR(Left): return "Left";
    case JoystickHatState::VKFW_ENUMERATOR(Right_Up): return "Right Up";
    case JoystickHatState::VKFW_ENUMERATOR(Right_Down): return "Right Down";
    case JoystickHatState::VKFW_ENUMERATOR(Left_Up): return "Left Up";
    case JoystickHatState::VKFW_ENUMERATOR(Left_Down): return "Left Down";
    default: return "invalid";
    }
  }
  VKFW_INLINE std::string to_string(Key value) {
    switch (value) {
    case Key::VKFW_ENUMERATOR(Unknown): return "Unknown";

    /*
     * Printable Keys
     */
    case Key::VKFW_ENUMERATOR(Space): return "Space";
    case Key::VKFW_ENUMERATOR(Apostrophe): return "Apostrophe";
    case Key::VKFW_ENUMERATOR(Comma): return "Comma";
    case Key::VKFW_ENUMERATOR(Minus): return "Minus";
    case Key::VKFW_ENUMERATOR(Period): return "Period";
    case Key::VKFW_ENUMERATOR(Slash): return "Slash";
    case Key::VKFW_ENUMERATOR2(0, _0): return "0";
    case Key::VKFW_ENUMERATOR2(1, _1): return "1";
    case Key::VKFW_ENUMERATOR2(2, _2): return "2";
    case Key::VKFW_ENUMERATOR2(3, _3): return "3";
    case Key::VKFW_ENUMERATOR2(4, _4): return "4";
    case Key::VKFW_ENUMERATOR2(5, _5): return "5";
    case Key::VKFW_ENUMERATOR2(6, _6): return "6";
    case Key::VKFW_ENUMERATOR2(7, _7): return "7";
    case Key::VKFW_ENUMERATOR2(8, _8): return "8";
    case Key::VKFW_ENUMERATOR2(9, _9): return "9";
    case Key::VKFW_ENUMERATOR(Semicolon): return "Semicolon";
    case Key::VKFW_ENUMERATOR(Equal): return "Equal";
    case Key::VKFW_ENUMERATOR(A): return "A";
    case Key::VKFW_ENUMERATOR(B): return "B";
    case Key::VKFW_ENUMERATOR(C): return "C";
    case Key::VKFW_ENUMERATOR(D): return "D";
    case Key::VKFW_ENUMERATOR(E): return "E";
    case Key::VKFW_ENUMERATOR(F): return "F";
    case Key::VKFW_ENUMERATOR(G): return "G";
    case Key::VKFW_ENUMERATOR(H): return "H";
    case Key::VKFW_ENUMERATOR(I): return "I";
    case Key::VKFW_ENUMERATOR(J): return "J";
    case Key::VKFW_ENUMERATOR(K): return "K";
    case Key::VKFW_ENUMERATOR(L): return "L";
    case Key::VKFW_ENUMERATOR(M): return "M";
    case Key::VKFW_ENUMERATOR(N): return "N";
    case Key::VKFW_ENUMERATOR(O): return "O";
    case Key::VKFW_ENUMERATOR(P): return "P";
    case Key::VKFW_ENUMERATOR(Q): return "Q";
    case Key::VKFW_ENUMERATOR(R): return "R";
    case Key::VKFW_ENUMERATOR(S): return "S";
    case Key::VKFW_ENUMERATOR(T): return "T";
    case Key::VKFW_ENUMERATOR(U): return "U";
    case Key::VKFW_ENUMERATOR(V): return "V";
    case Key::VKFW_ENUMERATOR(W): return "W";
    case Key::VKFW_ENUMERATOR(X): return "X";
    case Key::VKFW_ENUMERATOR(Y): return "Y";
    case Key::VKFW_ENUMERATOR(Z): return "Z";
    case Key::VKFW_ENUMERATOR(LeftBracket): return "LeftBracket";
    case Key::VKFW_ENUMERATOR(Backslash): return "Backslash";
    case Key::VKFW_ENUMERATOR(RightBracket): return "RightBracket";
    case Key::VKFW_ENUMERATOR(GraveAccent): return "GraveAccent";
    case Key::VKFW_ENUMERATOR(World1): return "World1";
    case Key::VKFW_ENUMERATOR(World2): return "World2";

    /*
     * Function Keys
     */
    case Key::VKFW_ENUMERATOR(Escape): return "Escape";
    case Key::VKFW_ENUMERATOR(Enter): return "Enter";
    case Key::VKFW_ENUMERATOR(Tab): return "Tab";
    case Key::VKFW_ENUMERATOR(Backspace): return "Backspace";
    case Key::VKFW_ENUMERATOR(Insert): return "Insert";
    case Key::VKFW_ENUMERATOR(Delete): return "Delete";
    case Key::VKFW_ENUMERATOR(Right): return "Right";
    case Key::VKFW_ENUMERATOR(Left): return "Left";
    case Key::VKFW_ENUMERATOR(Down): return "Down";
    case Key::VKFW_ENUMERATOR(Up): return "Up";
    case Key::VKFW_ENUMERATOR(PageUp): return "PageUp";
    case Key::VKFW_ENUMERATOR(PageDown): return "PageDown";
    case Key::VKFW_ENUMERATOR(Home): return "Home";
    case Key::VKFW_ENUMERATOR(End): return "End";
    case Key::VKFW_ENUMERATOR(CapsLock): return "CapsLock";
    case Key::VKFW_ENUMERATOR(ScrollLock): return "ScrollLock";
    case Key::VKFW_ENUMERATOR(NumLock): return "NumLock";
    case Key::VKFW_ENUMERATOR(PrintScreen): return "PrintScreen";
    case Key::VKFW_ENUMERATOR(Pause): return "Pause";
    case Key::VKFW_ENUMERATOR(F1): return "F1";
    case Key::VKFW_ENUMERATOR(F2): return "F2";
    case Key::VKFW_ENUMERATOR(F3): return "F3";
    case Key::VKFW_ENUMERATOR(F4): return "F4";
    case Key::VKFW_ENUMERATOR(F5): return "F5";
    case Key::VKFW_ENUMERATOR(F6): return "F6";
    case Key::VKFW_ENUMERATOR(F7): return "F7";
    case Key::VKFW_ENUMERATOR(F8): return "F8";
    case Key::VKFW_ENUMERATOR(F9): return "F9";
    case Key::VKFW_ENUMERATOR(F10): return "F10";
    case Key::VKFW_ENUMERATOR(F11): return "F11";
    case Key::VKFW_ENUMERATOR(F12): return "F12";
    case Key::VKFW_ENUMERATOR(F13): return "F13";
    case Key::VKFW_ENUMERATOR(F14): return "F14";
    case Key::VKFW_ENUMERATOR(F15): return "F15";
    case Key::VKFW_ENUMERATOR(F16): return "F16";
    case Key::VKFW_ENUMERATOR(F17): return "F17";
    case Key::VKFW_ENUMERATOR(F18): return "F18";
    case Key::VKFW_ENUMERATOR(F19): return "F19";
    case Key::VKFW_ENUMERATOR(F20): return "F20";
    case Key::VKFW_ENUMERATOR(F21): return "F21";
    case Key::VKFW_ENUMERATOR(F22): return "F22";
    case Key::VKFW_ENUMERATOR(F23): return "F23";
    case Key::VKFW_ENUMERATOR(F24): return "F24";
    case Key::VKFW_ENUMERATOR(F25): return "F25";
    case Key::VKFW_ENUMERATOR(KeyPad_0): return "KeyPad 0";
    case Key::VKFW_ENUMERATOR(KeyPad_1): return "KeyPad 1";
    case Key::VKFW_ENUMERATOR(KeyPad_2): return "KeyPad 2";
    case Key::VKFW_ENUMERATOR(KeyPad_3): return "KeyPad 3";
    case Key::VKFW_ENUMERATOR(KeyPad_4): return "KeyPad 4";
    case Key::VKFW_ENUMERATOR(KeyPad_5): return "KeyPad 5";
    case Key::VKFW_ENUMERATOR(KeyPad_6): return "KeyPad 6";
    case Key::VKFW_ENUMERATOR(KeyPad_7): return "KeyPad 7";
    case Key::VKFW_ENUMERATOR(KeyPad_8): return "KeyPad 8";
    case Key::VKFW_ENUMERATOR(KeyPad_9): return "KeyPad 9";
    case Key::VKFW_ENUMERATOR(KeyPad_Decimal): return "KeyPad Decimal";
    case Key::VKFW_ENUMERATOR(KeyPad_Divide): return "KeyPad Divide";
    case Key::VKFW_ENUMERATOR(KeyPad_Multiply): return "KeyPad Multiply";
    case Key::VKFW_ENUMERATOR(KeyPad_Subtract): return "KeyPad Subtract";
    case Key::VKFW_ENUMERATOR(KeyPad_Add): return "KeyPad Add";
    case Key::VKFW_ENUMERATOR(KeyPad_Enter): return "KeyPad Enter";
    case Key::VKFW_ENUMERATOR(KeyPad_Equal): return "KeyPad Equal";
    case Key::VKFW_ENUMERATOR(LeftShift): return "LeftShift";
    case Key::VKFW_ENUMERATOR(LeftControl): return "LeftControl";
    case Key::VKFW_ENUMERATOR(LeftAlt): return "LeftAlt";
    case Key::VKFW_ENUMERATOR(LeftSuper): return "LeftSuper";
    case Key::VKFW_ENUMERATOR(RightShift): return "RightShift";
    case Key::VKFW_ENUMERATOR(RightControl): return "RightControl";
    case Key::VKFW_ENUMERATOR(RightAlt): return "RightAlt";
    case Key::VKFW_ENUMERATOR(RightSuper): return "RightSuper";
    case Key::VKFW_ENUMERATOR(Menu): return "Menu";
    default: return "invalid";
    }
  }
  VKFW_INLINE std::string to_string(MouseButton value) {
    switch (value) {
    case MouseButton::VKFW_ENUMERATOR2(1, _1): return "1 (left)";
    case MouseButton::VKFW_ENUMERATOR2(2, _2): return "2 (right)";
    case MouseButton::VKFW_ENUMERATOR2(3, _3): return "3 (middle)";
    case MouseButton::VKFW_ENUMERATOR2(4, _4): return "4";
    case MouseButton::VKFW_ENUMERATOR2(5, _5): return "5";
    case MouseButton::VKFW_ENUMERATOR2(6, _6): return "6";
    case MouseButton::VKFW_ENUMERATOR2(7, _7): return "7";
    case MouseButton::VKFW_ENUMERATOR2(8, _8): return "8";
    default: return "invalid";
    }
  }
  VKFW_INLINE std::string to_string(Joystick value) {
    switch (value) {
    case Joystick::VKFW_ENUMERATOR2(1, _1): return "1";
    case Joystick::VKFW_ENUMERATOR2(2, _2): return "2";
    case Joystick::VKFW_ENUMERATOR2(3, _3): return "3";
    case Joystick::VKFW_ENUMERATOR2(4, _4): return "4";
    case Joystick::VKFW_ENUMERATOR2(5, _5): return "5";
    case Joystick::VKFW_ENUMERATOR2(6, _6): return "6";
    case Joystick::VKFW_ENUMERATOR2(7, _7): return "7";
    case Joystick::VKFW_ENUMERATOR2(8, _8): return "8";
    case Joystick::VKFW_ENUMERATOR2(9, _9): return "9";
    case Joystick::VKFW_ENUMERATOR2(10, _10): return "10";
    case Joystick::VKFW_ENUMERATOR2(11, _11): return "11";
    case Joystick::VKFW_ENUMERATOR2(12, _12): return "12";
    case Joystick::VKFW_ENUMERATOR2(13, _13): return "13";
    case Joystick::VKFW_ENUMERATOR2(14, _14): return "14";
    case Joystick::VKFW_ENUMERATOR2(15, _15): return "15";
    case Joystick::VKFW_ENUMERATOR2(16, _16): return "16";
    default: return "invalid";
    }
  }
  VKFW_INLINE std::string to_string(GamepadButton value) {
    switch (value) {
    case GamepadButton::VKFW_ENUMERATOR(A): return "A (Cross)";
    case GamepadButton::VKFW_ENUMERATOR(B): return "B (Circle)";
    case GamepadButton::VKFW_ENUMERATOR(X): return "X (Square)";
    case GamepadButton::VKFW_ENUMERATOR(Y): return "Y (Triangle)";
    case GamepadButton::VKFW_ENUMERATOR(LeftBumper): return "Left Bumper";
    case GamepadButton::VKFW_ENUMERATOR(RightBumper): return "Right Bumper";
    case GamepadButton::VKFW_ENUMERATOR(Back): return "Back";
    case GamepadButton::VKFW_ENUMERATOR(Start): return "Start";
    case GamepadButton::VKFW_ENUMERATOR(Guide): return "Guide";
    case GamepadButton::VKFW_ENUMERATOR(LeftThumb): return "Left Thumb";
    case GamepadButton::VKFW_ENUMERATOR(RightThumb): return "Right Thumb";
    case GamepadButton::VKFW_ENUMERATOR(DpadUp): return "Dpad Up";
    case GamepadButton::VKFW_ENUMERATOR(DpadRight): return "Dpad Right";
    case GamepadButton::VKFW_ENUMERATOR(DpadDown): return "Dpad Down";
    case GamepadButton::VKFW_ENUMERATOR(DpadLeft): return "Dpad Left";
    default: return "invalid";
    }
  }
  VKFW_INLINE std::string to_string(GamepadAxis value) {
    switch (value) {
    case GamepadAxis::VKFW_ENUMERATOR(LeftX): return "Left X";
    case GamepadAxis::VKFW_ENUMERATOR(LeftY): return "Left Y";
    case GamepadAxis::VKFW_ENUMERATOR(RightX): return "Right X";
    case GamepadAxis::VKFW_ENUMERATOR(RightY): return "Right Y";
    case GamepadAxis::VKFW_ENUMERATOR(LeftTrigger): return "Left Trigger";
    case GamepadAxis::VKFW_ENUMERATOR(RightTrigger): return "Right Trigger";
    default: return "invalid";
    }
  }
  VKFW_INLINE std::string to_string(Result value) {
    switch (value) {
    case Result::VKFW_ENUMERATOR(Success): return "No error has occurred";
    case Result::VKFW_ENUMERATOR(NotInitialized): return "GLFW has not been initialized";
    case Result::VKFW_ENUMERATOR(NoCurrentContext): return "No context is current for this thread";
    case Result::VKFW_ENUMERATOR(InvalidEnum):
      return "One of the arguments to the function was an invalid enum value";
    case Result::VKFW_ENUMERATOR(InvalidValue):
      return "One of the arguments to the function was an invalid value";
    case Result::VKFW_ENUMERATOR(OutOfMemory): return "A memory allocation failed";
    case Result::VKFW_ENUMERATOR(ApiUnavailable):
      return "GLFW could not find support for the requested API on the system";
    case Result::VKFW_ENUMERATOR(VersionUnavailable):
      return "The requested OpenGL or OpenGL ES version is not available";
    case Result::VKFW_ENUMERATOR(PlatformError):
      return "A platform-specific error occurred that does not match "
             "any of the more specific categories";
    case Result::VKFW_ENUMERATOR(FormatUnavailable):
      return "The requested format is not supported or available";
    case Result::VKFW_ENUMERATOR(NoWindowContext):
      return "The specified window does not have an OpenGL or OpenGL ES context";
    default: return "invalid";
    }
  }

  VKFW_INLINE std::string to_string(ModifierKeyFlags value) {
    if (!value)
      return "{}";
    std::string output;

    if (value & ModifierKeyBits::VKFW_ENUMERATOR(CapsLock))
      output += "CapsLock | ";
    if (value & ModifierKeyBits::VKFW_ENUMERATOR(NumLock))
      output += "NumLock | ";

    if (value & ModifierKeyBits::VKFW_ENUMERATOR(Control))
      output += "Control + ";
    if (value & ModifierKeyBits::VKFW_ENUMERATOR(Alt))
      output += "Alt + ";
    if (value & ModifierKeyBits::VKFW_ENUMERATOR(Super))
      output += "Super + ";

    return "{ " + output.substr(0, output.size() - 3) + " }";
  }

#ifndef VKFW_NO_ENHANCED_MODE
  template <InitializationHint hint> struct InitializationHintTraits;
  template <>
  struct InitializationHintTraits<InitializationHint::VKFW_ENUMERATOR(JoystickHatButtons)>
    : std::true_type {
    using type = bool;
  };
  template <>
  struct InitializationHintTraits<InitializationHint::VKFW_ENUMERATOR(CocoaChdirResources)>
    : std::true_type {
    using type = bool;
  };
  template <>
  struct InitializationHintTraits<InitializationHint::VKFW_ENUMERATOR(CocoaMenubar)>
    : std::true_type {
    using type = bool;
  };

  template <WindowHint hint> struct WindowHintTraits;
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(Focused)> { using type = bool; };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(Resizable)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(Visible)> { using type = bool; };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(Decorated)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(AutoIconify)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(Floating)> { using type = bool; };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(Maximized)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(CenterCursor)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(TransparentFramebuffer)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(FocusOnShow)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(RedBits)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(GreenBits)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(BlueBits)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(AlphaBits)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(DepthBits)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(StencilBits)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(AccumulationRedBits)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(AccumulationGreenBits)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(AccumulationBlueBits)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(AccumulationAlphaBits)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(AuxiliaryBuffers)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(StereoscopicRendering)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(Samples)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(SRGBCapable)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(RefreshRate)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(ScaleToMonitor)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(DoubleBuffer)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(ClientAPI)> {
    using type = ClientAPI;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(ContextVersionMajor)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(ContextVersionMinor)> {
    using type = unsigned;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(ContextRobustness)> {
    using type = ContextRobustness;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(OpenGLForwardCompatibility)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(OpenGLDebugContext)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(OpenGLProfile)> {
    using type = OpenGLProfile;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(ContextReleaseBehavior)> {
    using type = ContextReleaseBehavior;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(ContextNoError)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(ContextCreationAPI)> {
    using type = ContextCreationAPI;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(CocoaRetinaFramebuffer)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(CocoaFrameName)> {
  #ifdef VKFW_HAS_STRING_VIEW
    using type = std::string_view;
  #else
    using type = char const *;
  #endif
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(CocoaGraphicsSwitching)> {
    using type = bool;
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(X11ClassName)> {
  #ifdef VKFW_HAS_STRING_VIEW
    using type = std::string_view;
  #else
    using type = char const *;
  #endif
  };
  template <> struct WindowHintTraits<WindowHint::VKFW_ENUMERATOR(X11InstanceName)> {
  #ifdef VKFW_HAS_STRING_VIEW
    using type = std::string_view;
  #else
    using type = char const *;
  #endif
  };

  template <Attribute attribute> struct AttributeTraits;
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(Focused)> : std::false_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(Iconified)> : std::false_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(Resizable)> : std::true_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(Visible)> : std::false_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(Decorated)> : std::true_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(AutoIconify)> : std::true_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(Floating)> : std::true_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(Maximized)> : std::false_type {
    using type = bool;
  };
  template <>
  struct AttributeTraits<Attribute::VKFW_ENUMERATOR(TransparentFramebuffer)> : std::false_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(Hovered)> : std::false_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(FocusOnShow)> : std::true_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(ClientAPI)> : std::false_type {
    using type = ClientAPI;
  };
  template <>
  struct AttributeTraits<Attribute::VKFW_ENUMERATOR(ContextVersionMajor)> : std::false_type {
    using type = size_t;
  };
  template <>
  struct AttributeTraits<Attribute::VKFW_ENUMERATOR(ContextVersionMinor)> : std::false_type {
    using type = size_t;
  };
  template <>
  struct AttributeTraits<Attribute::VKFW_ENUMERATOR(ContextRevision)> : std::false_type {
    using type = size_t;
  };
  template <>
  struct AttributeTraits<Attribute::VKFW_ENUMERATOR(ContextRobustness)> : std::false_type {
    using type = ContextRobustness;
  };
  template <>
  struct AttributeTraits<Attribute::VKFW_ENUMERATOR(OpenGLForwardCompatibility)> : std::false_type {
    using type = bool;
  };
  template <>
  struct AttributeTraits<Attribute::VKFW_ENUMERATOR(OpenGLDebugContext)> : std::false_type {
    using type = bool;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(OpenGLProfile)> : std::false_type {
    using type = OpenGLProfile;
  };
  template <>
  struct AttributeTraits<Attribute::VKFW_ENUMERATOR(ContextReleaseBehavior)> : std::false_type {
    using type = ContextReleaseBehavior;
  };
  template <> struct AttributeTraits<Attribute::VKFW_ENUMERATOR(ContextNoError)> : std::false_type {
    using type = bool;
  };
  template <>
  struct AttributeTraits<Attribute::VKFW_ENUMERATOR(ContextCreationAPI)> : std::false_type {
    using type = ContextCreationAPI;
  };

  template <InputMode mode> struct InputModeTraits;
  template <> struct InputModeTraits<InputMode::VKFW_ENUMERATOR(Cursor)> {
    using type = CursorMode;
  };
  template <> struct InputModeTraits<InputMode::VKFW_ENUMERATOR(StickyKeys)> { using type = bool; };
  template <> struct InputModeTraits<InputMode::VKFW_ENUMERATOR(StickyMouseButtons)> {
    using type = bool;
  };
  template <> struct InputModeTraits<InputMode::VKFW_ENUMERATOR(LockKeyModifiers)> {
    using type = bool;
  };
  template <> struct InputModeTraits<InputMode::VKFW_ENUMERATOR(RawMouseMotion)> {
    using type = bool;
  };
#endif
} // namespace VKFW_NAMESPACE

namespace VKFW_NAMESPACE {
#ifndef VKFW_NO_SMART_HANDLE
  #ifndef VKFW_NO_INCLUDE_VULKAN_HPP
  template <typename Type>
  using UniqueHandleTraits
    = VULKAN_HPP_NAMESPACE::UniqueHandleTraits<Type, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE>;
  template <typename Type>
  using UniqueHandle = VULKAN_HPP_NAMESPACE::UniqueHandle<Type, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE>;
  #else
  template <typename Type> class UniqueHandleTraits;
  template <typename Type> class UniqueHandle : public UniqueHandleTraits<Type>::deleter {
  private:
    using Deleter = typename UniqueHandleTraits<Type>::deleter;

  public:
    using element_type = Type;

    UniqueHandle() : Deleter(), m_value() {}
    explicit UniqueHandle(Type const &value, Deleter const &deleter = Deleter()) VKFW_NOEXCEPT
      : Deleter(deleter),
        m_value(value) {}
    UniqueHandle(UniqueHandle const &) = delete;
    UniqueHandle(UniqueHandle &&other) VKFW_NOEXCEPT
      : Deleter(std::move(static_cast<Deleter &>(other))),
        m_value(other.release()) {}
    ~UniqueHandle() VKFW_NOEXCEPT {
      if (m_value)
        this->destroy(m_value);
    }

    UniqueHandle &operator=(UniqueHandle const &) = delete;
    UniqueHandle &operator=(UniqueHandle &&other) VKFW_NOEXCEPT {
      reset(other.release());
      *static_cast<Deleter *>(this) = std::move(static_cast<Deleter &>(other));
      return *this;
    }

    explicit operator bool() const VKFW_NOEXCEPT { return m_value.operator bool(); }
    Type const *operator->() const VKFW_NOEXCEPT { return &m_value; }
    Type *operator->() VKFW_NOEXCEPT { return &m_value; }
    Type const &operator*() const VKFW_NOEXCEPT { return m_value; }
    Type &operator*() VKFW_NOEXCEPT { return m_value; }
    const Type &get() const VKFW_NOEXCEPT { return m_value; }
    Type &get() VKFW_NOEXCEPT { return m_value; }
    void reset(Type const &value = Type()) VKFW_NOEXCEPT {
      if (m_value != value) {
        if (m_value)
          this->destroy(m_value);
        m_value = value;
      }
    }
    Type release() VKFW_NOEXCEPT {
      Type value = m_value;
      m_value = nullptr;
      return value;
    }
    void swap(UniqueHandle<Type> &rhs) VKFW_NOEXCEPT {
      std::swap(m_value, rhs.m_value);
      std::swap(static_cast<Deleter &>(*this), static_cast<Deleter &>(rhs));
    }

  private:
    Type m_value;
  };
  #endif
#endif
} // namespace VKFW_NAMESPACE

#ifndef VKFW_NO_EXCEPTIONS
namespace std {
  template <> struct is_error_code_enum<VKFW_NAMESPACE::Result> : public true_type {};
} // namespace std
#endif

namespace VKFW_NAMESPACE {
#ifndef VKFW_NO_EXCEPTIONS
  class ErrorCategoryImpl : public std::error_category {
  public:
    virtual char const *name() const VKFW_NOEXCEPT override {
      return VKFW_NAMESPACE_STRING "::Result";
    }
    virtual std::string message(int ev) const override {
      return to_string(static_cast<Result>(ev));
    }
  };
  class Error {
  public:
    Error() VKFW_NOEXCEPT = default;
    Error(const Error &) VKFW_NOEXCEPT = default;
    virtual ~Error() VKFW_NOEXCEPT = default;

    virtual char const *what() const VKFW_NOEXCEPT = 0;
  };
  class SystemError : public Error, public std::system_error {
  public:
    SystemError(std::error_code ec) : Error(), std::system_error(ec) {}
    SystemError(std::error_code ec, std::string const &what)
      : Error(), std::system_error(ec, what) {}
    SystemError(std::error_code ec, char const *what) : Error(), std::system_error(ec, what) {}
    SystemError(int ev, std::error_category const &ecat) : Error(), std::system_error(ev, ecat) {}
    SystemError(int ev, std::error_category const &ecat, std::string const &what)
      : Error(), std::system_error(ev, ecat, what) {}
    SystemError(int ev, std::error_category const &ecat, char const *what)
      : Error(), std::system_error(ev, ecat, what) {}

    virtual char const *what() const VKFW_NOEXCEPT { return std::system_error::what(); }
  };
  VKFW_INLINE const std::error_category &errorCategory() VKFW_NOEXCEPT {
    static ErrorCategoryImpl instance;
    return instance;
  }
  VKFW_INLINE std::error_code make_error_code(Result e) VKFW_NOEXCEPT {
    return std::error_code(static_cast<int>(e), errorCategory());
  }
  VKFW_INLINE std::error_condition make_error_condition(Result e) VKFW_NOEXCEPT {
    return std::error_condition(static_cast<int>(e), errorCategory());
  }
  class NotInitializedError : public SystemError {
  public:
    NotInitializedError(std::string const &message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(NotInitialized)), message) {}
    NotInitializedError(char const *message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(NotInitialized)), message) {}
  };
  class NoCurrentContextError : public SystemError {
  public:
    NoCurrentContextError(std::string const &message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(NoCurrentContext)), message) {}
    NoCurrentContextError(char const *message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(NoCurrentContext)), message) {}
  };
  class InvalidEnumError : public SystemError {
  public:
    InvalidEnumError(std::string const &message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(InvalidEnum)), message) {}
    InvalidEnumError(char const *message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(InvalidEnum)), message) {}
  };
  class InvalidValueError : public SystemError {
  public:
    InvalidValueError(std::string const &message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(InvalidValue)), message) {}
    InvalidValueError(char const *message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(InvalidValue)), message) {}
  };
  class OutOfMemoryError : public SystemError {
  public:
    OutOfMemoryError(std::string const &message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(OutOfMemory)), message) {}
    OutOfMemoryError(char const *message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(OutOfMemory)), message) {}
  };
  class ApiUnavailableError : public SystemError {
  public:
    ApiUnavailableError(std::string const &message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(ApiUnavailable)), message) {}
    ApiUnavailableError(char const *message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(ApiUnavailable)), message) {}
  };
  class VersionUnavailableError : public SystemError {
  public:
    VersionUnavailableError(std::string const &message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(VersionUnavailable)), message) {}
    VersionUnavailableError(char const *message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(VersionUnavailable)), message) {}
  };
  class PlatformError : public SystemError {
  public:
    PlatformError(std::string const &message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(PlatformError)), message) {}
    PlatformError(char const *message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(PlatformError)), message) {}
  };
  class FormatUnavailableError : public SystemError {
  public:
    FormatUnavailableError(std::string const &message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(FormatUnavailable)), message) {}
    FormatUnavailableError(char const *message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(FormatUnavailable)), message) {}
  };
  class NoWindowContextError : public SystemError {
  public:
    NoWindowContextError(std::string const &message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(NoWindowContext)), message) {}
    NoWindowContextError(char const *message)
      : SystemError(make_error_code(Result::VKFW_ENUMERATOR(NoWindowContext)), message) {}
  };

  [[noreturn]] static void throwResultException(Result result, char const *message) {
    switch (result) {
    // case Result::VKFW_ENUMERATOR(Success): break;
    case Result::VKFW_ENUMERATOR(NotInitialized): throw NotInitializedError(message);
    case Result::VKFW_ENUMERATOR(NoCurrentContext): throw NoCurrentContextError(message);
    case Result::VKFW_ENUMERATOR(InvalidEnum): throw InvalidEnumError(message);
    case Result::VKFW_ENUMERATOR(InvalidValue): throw InvalidValueError(message);
    case Result::VKFW_ENUMERATOR(OutOfMemory): throw OutOfMemoryError(message);
    case Result::VKFW_ENUMERATOR(ApiUnavailable): throw ApiUnavailableError(message);
    case Result::VKFW_ENUMERATOR(VersionUnavailable): throw VersionUnavailableError(message);
    case Result::VKFW_ENUMERATOR(PlatformError): throw PlatformError(message);
    case Result::VKFW_ENUMERATOR(FormatUnavailable): throw FormatUnavailableError(message);
    case Result::VKFW_ENUMERATOR(NoWindowContext): throw NoWindowContextError(message);
    default: throw SystemError(make_error_code(result));
    }
  }
#endif

  template <typename T> struct ResultValue {
#ifdef VKFW_HAS_NOEXCEPT
    ResultValue(Result r, T &&v) VKFW_NOEXCEPT(VKFW_NOEXCEPT(T(std::move(v))))
#else
    ResultValue(Result r, T &&v)
#endif
      : result(r), value(std::move(v)) {
    }

    Result result;
    T value;

    operator std::tuple<Result &, T &>() VKFW_NOEXCEPT {
      return std::tuple<Result &, T &>(result, value);
    }
  };

#ifndef VKFW_NO_SMART_HANDLE
  template <typename Type> struct ResultValue<UniqueHandle<Type>> {
  #ifdef VKFW_HAS_NOEXCEPT
    ResultValue(Result r, UniqueHandle<Type> &&v) VKFW_NOEXCEPT
  #else
    ResultValue(Result r, UniqueHandle<Type> &&v)
  #endif
      : result(r),
        value(std::move(v)) {
    }

    std::tuple<Result, UniqueHandle<Type>> asTuple() {
      return std::make_tuple(result, std::move(value));
    }

    Result result;
    UniqueHandle<Type> value;
  };
#endif

  template <typename T> struct ResultValueType {
#ifdef VKFW_NO_EXCEPTIONS
    typedef ResultValue<T> type;
#else
    typedef T type;
#endif
  };
  template <> struct ResultValueType<void> {
#ifdef VKFW_NO_EXCEPTIONS
    typedef Result type;
#else
    typedef void type;
#endif
  };

  template <typename T> VKFW_INLINE void ignore(T const &) VKFW_NOEXCEPT {}
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  createResultValue(Result result, char const *message) {
#ifdef VKFW_NO_EXCEPTIONS
    ignore(message);
    VKFW_ASSERT_ON_RESULT(result == Result::VKFW_ENUMERATOR(Success));
    return result;
#else
    if (!check(result))
      throwResultException(result, message);
#endif
  }
  template <typename T>
  VKFW_INLINE typename ResultValueType<T>::type createResultValue(Result result, T &data,
                                                                  char const *message) {
#ifdef VKFW_NO_EXCEPTIONS
    ignore(message);
    VKFW_ASSERT_ON_RESULT(result == Result::VKFW_ENUMERATOR(Success));
    return ResultValue<T>(result, std::move(data));
#else
    if (!check(result))
      throwResultException(result, message);
    return std::move(data);
#endif
  }
#ifndef VKFW_NO_SMART_HANDLE
  template <typename T>
  VKFW_INLINE typename ResultValueType<UniqueHandle<T>>::type
  createResultValueUnique(Result result, T &data, char const *message) {
  #ifdef VKFW_NO_EXCEPTIONS
    ignore(message);
    VKFW_ASSERT_ON_RESULT(result == Result::VKFW_ENUMERATOR(Success));
    return ResultValue<UniqueHandle<T>>(result, UniqueHandle<T>(data));
  #else
    if (!check(result))
      throwResultException(result, message);
    return UniqueHandle<T>(data);
  #endif
  }
#endif
#ifndef VKFW_NO_SMART_HANDLE
  template <typename T> struct CustomDestroy {
    void destroy(T &) { static_assert("Cannot delete an object without a specified deleter."); }
  };
#endif
#ifndef VKFW_NO_STD_FUNCTION_CALLBACKS
  struct DynamicCallbackStorage;
#endif

  struct Nullopt {};
  VKFW_CONSTEXPR Nullopt nullopt = {};
  template <typename T> class Optional {
  public:
    using value_type = T;

    VKFW_INLINE VKFW_CONSTEXPR Optional() : m_has_value(false) {}
    VKFW_INLINE VKFW_CONSTEXPR Optional(Nullopt) : m_has_value(false) {}
    VKFW_INLINE VKFW_CONSTEXPR Optional(value_type const &value)
      : m_has_value(true), m_value(value) {}
    VKFW_INLINE VKFW_CONSTEXPR Optional(value_type &&value)
      : m_has_value(true), m_value(std::move(value)) {}
    template <typename convertible_value_type,
              typename = typename std::enable_if<
                std::is_convertible<convertible_value_type, value_type>::value>::type>
    VKFW_INLINE VKFW_CONSTEXPR Optional(convertible_value_type const &value)
      : m_has_value(true), m_value(value_type{ value }) {}
    template <typename convertible_value_type,
              typename = typename std::enable_if<
                std::is_convertible<convertible_value_type, value_type>::value>::type>
    VKFW_INLINE VKFW_CONSTEXPR Optional(convertible_value_type &&value)
      : m_has_value(true), m_value(value_type{ std::move(value) }) {}
    template <class U>
    VKFW_INLINE VKFW_CONSTEXPR Optional(Optional<U> const &another)
      : m_has_value(another.m_has_value), m_value(another.m_value) {}
    template <class U>
    VKFW_INLINE VKFW_CONSTEXPR Optional(Optional<U> &&another)
      : m_has_value(another.m_has_value), m_value(std::move(another.m_value)) {}
    VKFW_INLINE VKFW_CONSTEXPR Optional &operator=(Nullopt) {
      m_has_value = false;
      return *this;
    }
    template <class U>
    VKFW_INLINE VKFW_CONSTEXPR_14 Optional &operator=(Optional<U> const &another) {
      m_has_value = another.m_has_value;
      m_value = another.m_value;
      return *this;
    }
    template <class U> VKFW_INLINE VKFW_CONSTEXPR_14 Optional &operator=(Optional<U> &&another) {
      m_has_value = another.m_has_value;
      m_value = std::move(another.m_value);
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR bool has_value() const { return m_has_value; }
    VKFW_INLINE VKFW_CONSTEXPR_14 value_type const &value() const {
      assert(m_has_value);
      return m_value;
    }

  private:
    bool m_has_value;
    T m_value;
  };

#ifndef VKFW_DISABLE_ENHANCED_MODE
  class Instance {
  public:
    using CType = void;
    VKFW_INLINE VKFW_CONSTEXPR Instance() : m_state(false) {}
    VKFW_INLINE VKFW_CONSTEXPR Instance(std::nullptr_t) VKFW_NOEXCEPT : m_state(false) {}
    VKFW_INLINE VKFW_CONSTEXPR Instance(bool state) VKFW_NOEXCEPT : m_state(state) {}
    VKFW_INLINE VKFW_CONSTEXPR Instance(Instance const &another) VKFW_NOEXCEPT
      : m_state(another.m_state) {}
    VKFW_INLINE VKFW_CONSTEXPR_14 Instance(Instance &&another) VKFW_NOEXCEPT
      : m_state(another.m_state) {
      another.m_state = false;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Instance operator=(Instance const &another) VKFW_NOEXCEPT {
      m_state = another.m_state;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Instance operator=(Instance &&another) VKFW_NOEXCEPT {
      m_state = another.m_state;
      another.m_state = false;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Instance &operator=(bool state) VKFW_NOEXCEPT {
      m_state = state;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Instance &operator=(std::nullptr_t) VKFW_NOEXCEPT {
      m_state = false;
      return *this;
    }
    VKFW_INLINE explicit operator bool() const VKFW_NOEXCEPT { return m_state; }
    VKFW_INLINE bool operator!() const VKFW_NOEXCEPT { return !m_state; }
  #if defined(VKFW_HAS_SPACESHIP_OPERATOR)
    auto operator<=>(Instance const &) const = default;
  #else
    bool operator==(Instance const &another) const VKFW_NOEXCEPT {
      return m_state == another.m_state;
    }
    bool operator!=(Instance const &another) const VKFW_NOEXCEPT { return !operator==(another); }
  #endif
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type destroy();

  private:
    bool m_state;
  };

  class Monitor {
  public:
    using CType = GLFWmonitor;

  public:
    VKFW_INLINE VKFW_CONSTEXPR Monitor() VKFW_NOEXCEPT : m_monitor(nullptr) {}
    VKFW_INLINE VKFW_CONSTEXPR Monitor(std::nullptr_t) VKFW_NOEXCEPT : m_monitor(nullptr) {}
    VKFW_INLINE VKFW_CONSTEXPR Monitor(GLFWmonitor *monitor) VKFW_NOEXCEPT : m_monitor(monitor) {}
    VKFW_INLINE VKFW_CONSTEXPR Monitor(Monitor const &another) VKFW_NOEXCEPT
      : m_monitor(another.m_monitor) {}
    VKFW_INLINE VKFW_CONSTEXPR_14 Monitor(Monitor &&another) VKFW_NOEXCEPT
      : m_monitor(another.m_monitor) {
      another.m_monitor = nullptr;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Monitor operator=(Monitor const &another) VKFW_NOEXCEPT {
      m_monitor = another.m_monitor;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Monitor operator=(Monitor &&another) VKFW_NOEXCEPT {
      m_monitor = another.m_monitor;
      another.m_monitor = nullptr;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Monitor &operator=(GLFWmonitor *monitor) VKFW_NOEXCEPT {
      m_monitor = monitor;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Monitor &operator=(std::nullptr_t) VKFW_NOEXCEPT {
      m_monitor = nullptr;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR operator GLFWmonitor *() const VKFW_NOEXCEPT { return m_monitor; }
    VKFW_INLINE VKFW_CONSTEXPR explicit operator bool() const VKFW_NOEXCEPT {
      return m_monitor != nullptr;
    }
    VKFW_INLINE VKFW_CONSTEXPR bool operator!() const VKFW_NOEXCEPT { return m_monitor == nullptr; }
  #if defined(VKFW_HAS_SPACESHIP_OPERATOR)
    auto operator<=>(Monitor const &) const = default;
  #else
    bool operator==(Monitor const &another) const VKFW_NOEXCEPT {
      return m_monitor == another.m_monitor;
    }
    bool operator!=(Monitor const &another) const VKFW_NOEXCEPT { return !operator==(another); }
  #endif

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type getPos(int *xpos,
                                                                                  int *ypos) const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<int, int>>::type getPos() const;
    VKFW_NODISCARD typename ResultValueType<int>::type getPosX() const;
    VKFW_NODISCARD typename ResultValueType<int>::type getPosY() const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    getWorkarea(int *xpos, int *ypos, size_t *width, size_t *height) const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<int, int, size_t, size_t>>::type
    getWorkarea() const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<int, int>>::type getWorkareaPos() const;
    VKFW_NODISCARD typename ResultValueType<int>::type getWorkareaPosX() const;
    VKFW_NODISCARD typename ResultValueType<int>::type getWorkareaPosY() const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<size_t, size_t>>::type
    getWorkareaSize() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getWorkareaWidth() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getWorkareaHeight() const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    getPhysicalSize(size_t *widthMM, size_t *heightMM) const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<size_t, size_t>>::type
    getPhysicalSize() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getPhysicalWidth() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getPhysicalHeight() const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    getContentScale(float *xscale, float *yscale) const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<float, float>>::type getContentScale() const;
    VKFW_NODISCARD typename ResultValueType<float>::type getContentScaleX() const;
    VKFW_NODISCARD typename ResultValueType<float>::type getContentScaleY() const;

  #ifdef VKFW_HAS_STRING_VIEW
    VKFW_NODISCARD typename ResultValueType<std::string_view>::type getName() const;
  #else
    VKFW_NODISCARD typename ResultValueType<char const *>::type getName() const;
  #endif

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setUserPointer(void *pointer) const;
    VKFW_NODISCARD typename ResultValueType<void *>::type getUserPointer() const;

    VKFW_NODISCARD typename ResultValueType<GLFWvidmode const *>::type getVideoMode() const;
  #ifdef VKFW_HAS_SPAN
    VKFW_NODISCARD typename ResultValueType<std::span<GLFWvidmode const>>::type
    getVideoModes() const;
  #else
    VKFW_NODISCARD typename ResultValueType<std::vector<GLFWvidmode>>::type getVideoModes() const;
  #endif

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setGamma(float gamma) const;
    VKFW_NODISCARD typename ResultValueType<GLFWgammaramp const *>::type getGammaRamp() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setGammaRamp(GLFWgammaramp const *ramp) const;

  private:
    GLFWmonitor *m_monitor;
  };

  class Cursor {
  public:
    using CType = GLFWcursor;

  public:
    VKFW_INLINE VKFW_CONSTEXPR Cursor() VKFW_NOEXCEPT : m_cursor(nullptr) {}
    VKFW_INLINE VKFW_CONSTEXPR Cursor(std::nullptr_t) VKFW_NOEXCEPT : m_cursor(nullptr) {}
    VKFW_INLINE VKFW_CONSTEXPR Cursor(GLFWcursor *cursor) VKFW_NOEXCEPT : m_cursor(cursor) {}
    VKFW_INLINE VKFW_CONSTEXPR Cursor(Cursor const &another) VKFW_NOEXCEPT
      : m_cursor(another.m_cursor) {}
    VKFW_INLINE VKFW_CONSTEXPR_14 Cursor(Cursor &&another) VKFW_NOEXCEPT
      : m_cursor(another.m_cursor) {
      another.m_cursor = nullptr;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Cursor operator=(Cursor const &another) VKFW_NOEXCEPT {
      m_cursor = another.m_cursor;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Cursor operator=(Cursor &&another) VKFW_NOEXCEPT {
      m_cursor = another.m_cursor;
      another.m_cursor = nullptr;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Cursor &operator=(GLFWcursor *cursor) VKFW_NOEXCEPT {
      m_cursor = cursor;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Cursor &operator=(std::nullptr_t) VKFW_NOEXCEPT {
      m_cursor = nullptr;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR operator GLFWcursor *() const VKFW_NOEXCEPT { return m_cursor; }
    VKFW_INLINE VKFW_CONSTEXPR explicit operator bool() const VKFW_NOEXCEPT {
      return m_cursor != nullptr;
    }
    VKFW_INLINE VKFW_CONSTEXPR bool operator!() const VKFW_NOEXCEPT { return m_cursor == nullptr; }
  #if defined(VKFW_HAS_SPACESHIP_OPERATOR)
    auto operator<=>(Cursor const &) const = default;
  #else
    bool operator==(Cursor const &another) const VKFW_NOEXCEPT {
      return m_cursor == another.m_cursor;
    }
    bool operator!=(Cursor const &another) const VKFW_NOEXCEPT { return !operator==(another); }
  #endif
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type destroy();

  private:
    GLFWcursor *m_cursor;
  };

  using Image = GLFWimage;

  class Window {
  public:
    using CType = GLFWwindow;

  public:
    VKFW_INLINE VKFW_CONSTEXPR Window() VKFW_NOEXCEPT : m_window(nullptr) {}
    VKFW_INLINE VKFW_CONSTEXPR Window(std::nullptr_t) VKFW_NOEXCEPT : m_window(nullptr) {}
    VKFW_INLINE VKFW_CONSTEXPR Window(GLFWwindow *window) VKFW_NOEXCEPT : m_window(window) {}
    VKFW_INLINE VKFW_CONSTEXPR Window(Window const &another) VKFW_NOEXCEPT
      : m_window(another.m_window) {}
    VKFW_INLINE VKFW_CONSTEXPR_14 Window(Window &&another) VKFW_NOEXCEPT
      : m_window(another.m_window) {
      another.m_window = nullptr;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Window operator=(Window const &another) VKFW_NOEXCEPT {
      m_window = another.m_window;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Window operator=(Window &&another) VKFW_NOEXCEPT {
      m_window = another.m_window;
      another.m_window = nullptr;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Window &operator=(GLFWwindow *window) VKFW_NOEXCEPT {
      m_window = window;
      return *this;
    }
    VKFW_INLINE VKFW_CONSTEXPR_14 Window &operator=(std::nullptr_t) VKFW_NOEXCEPT {
      m_window = nullptr;
      return *this;
    }

    VKFW_INLINE VKFW_CONSTEXPR operator GLFWwindow *() const VKFW_NOEXCEPT { return m_window; }
    VKFW_INLINE VKFW_CONSTEXPR explicit operator bool() const VKFW_NOEXCEPT {
      return m_window != nullptr;
    }
    VKFW_INLINE VKFW_CONSTEXPR bool operator!() const VKFW_NOEXCEPT { return m_window == nullptr; }
  #if defined(VKFW_HAS_SPACESHIP_OPERATOR)
    auto operator<=>(Window const &) const = default;
  #else
    bool operator==(Window const &another) const VKFW_NOEXCEPT {
      return m_window == another.m_window;
    }
    bool operator!=(Window const &another) const VKFW_NOEXCEPT { return !operator==(another); }
  #endif
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type destroy();

    VKFW_NODISCARD typename ResultValueType<bool>::type shouldClose() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setShouldClose(bool value) const;

  #ifdef VKFW_HAS_STRING_VIEW
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setTitle(std::string_view title) const;
  #else
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setTitle(char const *title) const;
  #endif

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type getPos(int *xpos,
                                                                                  int *ypos) const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<int, int>>::type getPos() const;
    VKFW_NODISCARD typename ResultValueType<int>::type getPosX() const;
    VKFW_NODISCARD typename ResultValueType<int>::type getPosY() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type setPos(int xpos,
                                                                                  int ypos) const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setPos(std::tuple<int, int> pos) const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    getSize(size_t *width, size_t *height) const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<size_t, size_t>>::type getSize() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getWidth() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getHeight() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setSize(size_t width, size_t height) const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setSize(std::tuple<size_t, size_t> size) const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setSizeLimits(size_t minimum_width, size_t minimum_height, size_t maximum_width,
                  size_t maximum_height) const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type setSizeLimits(
      std::tuple<size_t, size_t> minimum_size, std::tuple<size_t, size_t> maximum_size) const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setSizeLimits(std::tuple<size_t, size_t, size_t, size_t> limits) const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setAspectRatio(size_t numerator, size_t denominator) const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    getFramebufferSize(size_t *width, size_t *height) const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<size_t, size_t>>::type
    getFramebufferSize() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getFramebufferWidth() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getFramebufferHeight() const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    getFrameSize(size_t *left, size_t *top, size_t *right, size_t *bottom) const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<size_t, size_t, size_t, size_t>>::type
    getFrameSize() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getLeftFrameSize() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getTopFrameSize() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getRightFrameSize() const;
    VKFW_NODISCARD typename ResultValueType<size_t>::type getBottomFrameSize() const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    getContentScale(float *xscale, float *yscale) const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<float, float>>::type getContentScale() const;
    VKFW_NODISCARD typename ResultValueType<float>::type getContentScaleX() const;
    VKFW_NODISCARD typename ResultValueType<float>::type getContentScaleY() const;

    VKFW_NODISCARD typename ResultValueType<float>::type getOpacity() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setOpacity(float opacity) const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type iconify() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type restore() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type maximize() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type show() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type hide() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type focus() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type requestAttention() const;
    VKFW_NODISCARD typename ResultValueType<Monitor>::type getMonitor() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setMonitor(Monitor const &monitor, int xpos, int ypos, size_t width, size_t height,
               size_t refreshRate = 0) const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setMonitor(Monitor const &monitor, std::tuple<int, int> pos, std::tuple<size_t, size_t> size,
               size_t refreshRate = 0) const;

  #ifdef VKFW_HAS_SPAN
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setIcon(std::span<vkfw::Image> images) const;
  #endif
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setIcon(std::vector<vkfw::Image> images) const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setIcon(size_t image_count, vkfw::Image *images) const;

    template <Attribute attribute>
    VKFW_NODISCARD typename ResultValueType<typename AttributeTraits<attribute>::type>::type
    get() const;

    template <Attribute attribute,
              typename = typename std::enable_if<AttributeTraits<attribute>::value>::type>
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    set(typename AttributeTraits<attribute>::type const &new_value) const;

    template <InputMode mode>
    VKFW_NODISCARD typename ResultValueType<typename InputModeTraits<mode>::type>::type get() const;

    template <InputMode mode>
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    set(typename InputModeTraits<mode>::type const &new_value) const;

  #ifdef VKFW_NO_STD_FUNCTION_CALLBACKS
    VKFW_INLINE GLFWwindowposfun setPosCallback(GLFWwindowposfun callback) const {
      return glfwSetWindowPosCallback(m_window, callback);
    }
    VKFW_INLINE GLFWwindowsizefun setSizeCallback(GLFWwindowsizefun callback) const {
      return glfwSetWindowSizeCallback(m_window, callback);
    }
    VKFW_INLINE GLFWwindowclosefun setCloseCallback(GLFWwindowclosefun callback) const {
      return glfwSetWindowCloseCallback(m_window, callback);
    }
    VKFW_INLINE GLFWwindowrefreshfun setRefreshCallback(GLFWwindowrefreshfun callback) const {
      return glfwSetWindowRefreshCallback(m_window, callback);
    }
    VKFW_INLINE GLFWwindowfocusfun setFocusCallback(GLFWwindowfocusfun callback) const {
      return glfwSetWindowFocusCallback(m_window, callback);
    }
    VKFW_INLINE GLFWwindowiconifyfun setIconifyCallback(GLFWwindowiconifyfun callback) const {
      return glfwSetWindowIconifyCallback(m_window, callback);
    }
    VKFW_INLINE GLFWwindowmaximizefun setMaximizeCallback(GLFWwindowmaximizefun callback) const {
      return glfwSetWindowMaximizeCallback(m_window, callback);
    }
    VKFW_INLINE GLFWframebuffersizefun
    setFramebufferSizeCallback(GLFWframebuffersizefun callback) const {
      return glfwSetFramebufferSizeCallback(m_window, callback);
    }
    VKFW_INLINE GLFWwindowcontentscalefun
    setContentScaleCallback(GLFWwindowcontentscalefun callback) const {
      return glfwSetWindowContentScaleCallback(m_window, callback);
    }
    VKFW_INLINE GLFWkeyfun setKeyCallback(GLFWkeyfun callback) const {
      return glfwSetKeyCallback(m_window, callback);
    }
    VKFW_INLINE GLFWcharfun setCharCallback(GLFWcharfun callback) const {
      return glfwSetCharCallback(m_window, callback);
    }
    VKFW_INLINE GLFWcharmodsfun setCharModsCallback(GLFWcharmodsfun callback) const {
      return glfwSetCharModsCallback(m_window, callback);
    }
    VKFW_INLINE GLFWmousebuttonfun setMouseButtonCallback(GLFWmousebuttonfun callback) const {
      return glfwSetMouseButtonCallback(m_window, callback);
    }
    VKFW_INLINE GLFWcursorposfun setCursorPosCallback(GLFWcursorposfun callback) const {
      return glfwSetCursorPosCallback(m_window, callback);
    }
    VKFW_INLINE GLFWcursorenterfun setCursorEnterCallback(GLFWcursorenterfun callback) const {
      return glfwSetCursorEnterCallback(m_window, callback);
    }
    VKFW_INLINE GLFWscrollfun setScrollCallback(GLFWscrollfun callback) const {
      return glfwSetScrollCallback(m_window, callback);
    }
    VKFW_INLINE GLFWdropfun setDropCallback(GLFWdropfun callback) const {
      return glfwSetDropCallback(m_window, callback);
    }
  #else
    VKFW_NODISCARD VKFW_INLINE DynamicCallbackStorage *callbacks() const {
      return reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(m_window));
    }
  #endif
    VKFW_NODISCARD typename ResultValueType<void *>::type getUserPointer() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setUserPointer(void *pointer) const;

    VKFW_NODISCARD typename ResultValueType<bool>::type getKey(Key key) const;
    VKFW_NODISCARD typename ResultValueType<bool>::type getMouseButton(MouseButton button) const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    getCursorPos(double *xpos, double *ypos) const;
    VKFW_NODISCARD typename ResultValueType<std::tuple<double, double>>::type getCursorPos() const;
    VKFW_NODISCARD typename ResultValueType<double>::type getCursorPosX() const;
    VKFW_NODISCARD typename ResultValueType<double>::type getCursorPosY() const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setCursorPos(double xpos, double ypos) const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    setCursor(Cursor const &cursor) const;

    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
    makeContextCurrent() const;
    VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type swapBuffers() const;

  private:
    GLFWwindow *m_window;
  };
#endif

  VKFW_INLINE Result getError(char const **description = nullptr) {
    return static_cast<Result>(glfwGetError(description));
  }
  VKFW_INLINE GLFWerrorfun setErrorCallback(GLFWerrorfun callback) {
    return glfwSetErrorCallback(callback);
  }

  template <InitializationHint hint>
  VKFW_INLINE Result initHint(typename InitializationHintTraits<hint>::type value) {
    glfwInitHint(static_cast<int>(hint), static_cast<int>(value));
    return getError();
  }
#ifndef VKFW_DISABLE_ENHANCED_MODE
  template <InitializationHint hint>
  class OptionalInitializationHint
    : public Optional<typename InitializationHintTraits<hint>::type> {
  public:
    using Optional<typename InitializationHintTraits<hint>::type>::Optional;
  };
  struct InitHints {
  #ifndef VKFW_NO_STRUCT_CONSTRUCTORS
  public:
    VKFW_CONSTEXPR InitHints(
      OptionalInitializationHint<InitializationHint::VKFW_ENUMERATOR(JoystickHatButtons)>
        joystickHatButtons_
      = nullopt,
      OptionalInitializationHint<InitializationHint::VKFW_ENUMERATOR(CocoaChdirResources)>
        cocoaChdirResources_
      = nullopt,
      OptionalInitializationHint<InitializationHint::VKFW_ENUMERATOR(CocoaMenubar)> cocoaMenubar_
      = nullopt) VKFW_NOEXCEPT : joystickHatButtons(joystickHatButtons_),
                                 cocoaChdirResources(cocoaChdirResources_),
                                 cocoaMenubar(cocoaMenubar_) {}
  #endif
  public:
    OptionalInitializationHint<InitializationHint::VKFW_ENUMERATOR(JoystickHatButtons)>
      joystickHatButtons = nullopt;
    OptionalInitializationHint<InitializationHint::VKFW_ENUMERATOR(CocoaChdirResources)>
      cocoaChdirResources = nullopt;
    OptionalInitializationHint<InitializationHint::VKFW_ENUMERATOR(CocoaMenubar)> cocoaMenubar
      = nullopt;
  };
  template <InitializationHint hint>
  VKFW_INLINE Result setInitHint(OptionalInitializationHint<hint> optional_hint) {
    if (optional_hint.has_value())
      return initHint<hint>(optional_hint.value());
    else
      return initHint<hint>(InitializationHintTraits<hint>::value);
  }
  VKFW_INLINE Result setInitHints(InitHints hints) {
    Result result = Result::VKFW_ENUMERATOR(Success);
    if (!check(result = setInitHint(hints.joystickHatButtons)))
      return result;
    if (!check(result = setInitHint(hints.cocoaChdirResources)))
      return result;
    if (!check(result = setInitHint(hints.cocoaMenubar)))
      return result;
    return result;
  }
#endif

  VKFW_INLINE Result defaultWindowHints() {
    glfwDefaultWindowHints();
    return getError();
  }
  template <WindowHint hint>
  VKFW_INLINE Result windowHint(typename WindowHintTraits<hint>::type value) {
    glfwWindowHint(static_cast<int>(hint), static_cast<int>(value));
    return getError();
  }
#ifndef VKFW_DISABLE_ENHANCED_MODE
  template <WindowHint hint>
  class OptionalWindowHint : public Optional<typename WindowHintTraits<hint>::type> {
  public:
    using Optional<typename WindowHintTraits<hint>::type>::Optional;
  };
  struct WindowHints {
  #ifndef VKFW_NO_STRUCT_CONSTRUCTORS
  public:
    #if HAS_STRING_VIEW
    VKFW_CONSTEXPR
    #else
    VKFW_INLINE
    #endif
    WindowHints(
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Resizable)> resizable_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Visible)> visible_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Decorated)> decorated_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Focused)> focused_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AutoIconify)> autoIconify_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Floating)> floating_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Maximized)> maximized_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(CenterCursor)> centerCursor_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(TransparentFramebuffer)>
        transparentFramebuffer_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(FocusOnShow)> focusOnShow_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ScaleToMonitor)> scaleToMonitor_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(RedBits)> redBits_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(GreenBits)> greenBits_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(BlueBits)> blueBits_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AlphaBits)> alphaBits_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(DepthBits)> depthBits_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(StencilBits)> stencilBits_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationRedBits)> accumulationRedBits_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationGreenBits)> accumulationGreenBits_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationBlueBits)> accumulationBlueBits_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationAlphaBits)> accumulationAlphaBits_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AuxiliaryBuffers)> auxiliaryBuffers_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Samples)> samples_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(RefreshRate)> refreshRate_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(StereoscopicRendering)> stereo_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(SRGBCapable)> srgbCapable_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(DoubleBuffer)> doubleBuffer_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ClientAPI)> clientAPI_
      = ClientAPI::VKFW_ENUMERATOR(None),
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextCreationAPI)> contextCreationAPI_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextVersionMajor)> contextVersionMajor_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextVersionMinor)> contextVersionMinor_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextRobustness)> contextRobustness_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextReleaseBehavior)>
        contextReleaseBehavior_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextNoError)> contextNoError_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(OpenGLForwardCompatibility)>
        openGLForwardCompatibility_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(OpenGLDebugContext)> openGLDebugContext_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(OpenGLProfile)> openGLProfile_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaRetinaFramebuffer)>
        cocoaRetinaFramebuffer_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaFrameName)> cocoaFrameName_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaGraphicsSwitching)>
        cocoaGraphicsSwitching_
      = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(X11ClassName)> x11ClassName_ = nullopt,
      OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(X11InstanceName)> x11InstanceName_ = nullopt)
      VKFW_NOEXCEPT : resizable(resizable_),
                      visible(visible_),
                      decorated(decorated_),
                      focused(focused_),
                      autoIconify(autoIconify_),
                      floating(floating_),
                      maximized(maximized_),
                      centerCursor(centerCursor_),
                      transparentFramebuffer(transparentFramebuffer_),
                      focusOnShow(focusOnShow_),
                      scaleToMonitor(scaleToMonitor_),
                      redBits(redBits_),
                      greenBits(greenBits_),
                      blueBits(blueBits_),
                      alphaBits(alphaBits_),
                      depthBits(depthBits_),
                      stencilBits(stencilBits_),
                      accumulationRedBits(accumulationRedBits_),
                      accumulationGreenBits(accumulationGreenBits_),
                      accumulationBlueBits(accumulationBlueBits_),
                      accumulationAlphaBits(accumulationAlphaBits_),
                      auxiliaryBuffers(auxiliaryBuffers_),
                      samples(samples_),
                      refreshRate(refreshRate_),
                      stereo(stereo_),
                      srgbCapable(srgbCapable_),
                      doubleBuffer(doubleBuffer_),
                      clientAPI(clientAPI_),
                      contextCreationAPI(contextCreationAPI_),
                      contextVersionMajor(contextVersionMajor_),
                      contextVersionMinor(contextVersionMinor_),
                      contextRobustness(contextRobustness_),
                      contextReleaseBehavior(contextReleaseBehavior_),
                      contextNoError(contextNoError_),
                      openGLForwardCompatibility(openGLForwardCompatibility_),
                      openGLDebugContext(openGLDebugContext_),
                      openGLProfile(openGLProfile_),
                      cocoaRetinaFramebuffer(cocoaRetinaFramebuffer_),
                      cocoaFrameName(cocoaFrameName_),
                      cocoaGraphicsSwitching(cocoaGraphicsSwitching_),
                      x11ClassName(x11ClassName_),
                      x11InstanceName(x11InstanceName_) {}
  #endif
  public:
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Resizable)> resizable = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Visible)> visible = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Decorated)> decorated = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Focused)> focused = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AutoIconify)> autoIconify = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Floating)> floating = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Maximized)> maximized = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(CenterCursor)> centerCursor = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(TransparentFramebuffer)> transparentFramebuffer
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(FocusOnShow)> focusOnShow = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ScaleToMonitor)> scaleToMonitor = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(RedBits)> redBits = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(GreenBits)> greenBits = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(BlueBits)> blueBits = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AlphaBits)> alphaBits = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(DepthBits)> depthBits = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(StencilBits)> stencilBits = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationRedBits)> accumulationRedBits
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationGreenBits)> accumulationGreenBits
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationBlueBits)> accumulationBlueBits
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationAlphaBits)> accumulationAlphaBits
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(AuxiliaryBuffers)> auxiliaryBuffers = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(Samples)> samples = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(RefreshRate)> refreshRate = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(StereoscopicRendering)> stereo = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(SRGBCapable)> srgbCapable = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(DoubleBuffer)> doubleBuffer = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ClientAPI)> clientAPI
      = ClientAPI::VKFW_ENUMERATOR(None);
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextCreationAPI)> contextCreationAPI
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextVersionMajor)> contextVersionMajor
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextVersionMinor)> contextVersionMinor
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextRobustness)> contextRobustness = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextReleaseBehavior)> contextReleaseBehavior
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(ContextNoError)> contextNoError = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(OpenGLForwardCompatibility)>
      openGLForwardCompatibility = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(OpenGLDebugContext)> openGLDebugContext
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(OpenGLProfile)> openGLProfile = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaRetinaFramebuffer)> cocoaRetinaFramebuffer
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaFrameName)> cocoaFrameName = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaGraphicsSwitching)> cocoaGraphicsSwitching
      = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(X11ClassName)> x11ClassName = nullopt;
    OptionalWindowHint<WindowHint::VKFW_ENUMERATOR(X11InstanceName)> x11InstanceName = nullopt;
  };
  template <WindowHint hint> Result setWindowHint(OptionalWindowHint<hint> optional_hint) {
    if (optional_hint.has_value())
      return windowHint<hint>(optional_hint.value());
    else
      return Result::VKFW_ENUMERATOR(Success);
  }
  VKFW_INLINE Result setWindowHints(WindowHints const &hints) {
    Result result = Result::VKFW_ENUMERATOR(Success);
    if (!check(result = setWindowHint(hints.resizable)))
      return result;
    if (!check(result = setWindowHint(hints.visible)))
      return result;
    if (!check(result = setWindowHint(hints.decorated)))
      return result;
    if (!check(result = setWindowHint(hints.focused)))
      return result;
    if (!check(result = setWindowHint(hints.autoIconify)))
      return result;
    if (!check(result = setWindowHint(hints.floating)))
      return result;
    if (!check(result = setWindowHint(hints.maximized)))
      return result;
    if (!check(result = setWindowHint(hints.centerCursor)))
      return result;
    if (!check(result = setWindowHint(hints.transparentFramebuffer)))
      return result;
    if (!check(result = setWindowHint(hints.focusOnShow)))
      return result;
    if (!check(result = setWindowHint(hints.scaleToMonitor)))
      return result;
    if (!check(result = setWindowHint(hints.redBits)))
      return result;
    if (!check(result = setWindowHint(hints.greenBits)))
      return result;
    if (!check(result = setWindowHint(hints.blueBits)))
      return result;
    if (!check(result = setWindowHint(hints.alphaBits)))
      return result;
    if (!check(result = setWindowHint(hints.depthBits)))
      return result;
    if (!check(result = setWindowHint(hints.stencilBits)))
      return result;
    if (!check(result = setWindowHint(hints.accumulationRedBits)))
      return result;
    if (!check(result = setWindowHint(hints.accumulationGreenBits)))
      return result;
    if (!check(result = setWindowHint(hints.accumulationBlueBits)))
      return result;
    if (!check(result = setWindowHint(hints.accumulationAlphaBits)))
      return result;
    if (!check(result = setWindowHint(hints.auxiliaryBuffers)))
      return result;
    if (!check(result = setWindowHint(hints.samples)))
      return result;
    if (!check(result = setWindowHint(hints.refreshRate)))
      return result;
    if (!check(result = setWindowHint(hints.stereo)))
      return result;
    if (!check(result = setWindowHint(hints.srgbCapable)))
      return result;
    if (!check(result = setWindowHint(hints.doubleBuffer)))
      return result;
    if (!check(result = setWindowHint(hints.clientAPI)))
      return result;
    if (!check(result = setWindowHint(hints.contextCreationAPI)))
      return result;
    if (!check(result = setWindowHint(hints.contextVersionMajor)))
      return result;
    if (!check(result = setWindowHint(hints.contextVersionMinor)))
      return result;
    if (!check(result = setWindowHint(hints.contextRobustness)))
      return result;
    if (!check(result = setWindowHint(hints.contextReleaseBehavior)))
      return result;
    if (!check(result = setWindowHint(hints.contextNoError)))
      return result;
    if (!check(result = setWindowHint(hints.openGLForwardCompatibility)))
      return result;
    if (!check(result = setWindowHint(hints.openGLDebugContext)))
      return result;
    if (!check(result = setWindowHint(hints.openGLProfile)))
      return result;
    if (!check(result = setWindowHint(hints.cocoaRetinaFramebuffer)))
      return result;
    if (!check(result = setWindowHint(hints.cocoaFrameName)))
      return result;
    if (!check(result = setWindowHint(hints.cocoaGraphicsSwitching)))
      return result;
    if (!check(result = setWindowHint(hints.x11ClassName)))
      return result;
    if (!check(result = setWindowHint(hints.x11InstanceName)))
      return result;
    return result;
  }
#endif

  template <InitializationHint hint>
  VKFW_INLINE Result set(typename InitializationHintTraits<hint>::type value) {
    return initHint<hint>(std::move(value));
  }
  template <WindowHint hint> VKFW_INLINE Result set(typename WindowHintTraits<hint>::type value) {
    return windowHint<hint>(std::move(value));
  }

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_NODISCARD Result init();
  VKFW_NODISCARD Result terminate();
#else
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type init(InitHints hints = {});
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type terminate();
  #ifndef VKFW_NO_SMART_HANDLE
  using UniqueInstance = UniqueHandle<Instance>;
  VKFW_NODISCARD typename ResultValueType<UniqueInstance>::type initUnique(InitHints hints = {});
  #endif
#endif

  struct Version {
    size_t major, minor, revision;
  };
  VKFW_INLINE Version getVersion() {
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    return Version{ static_cast<size_t>(major), static_cast<size_t>(minor),
                    static_cast<size_t>(revision) };
  }

#ifdef VKFW_HAS_STRING_VIEW
  VKFW_INLINE std::string_view getVersionString() {
#else
  VKFW_INLINE char const *getVersionString() {
#endif
    return glfwGetVersionString();
  }

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_NODISCARD GLFWmonitor *getPrimaryMonitor();
  #ifdef VKFW_HAS_SPAN
  VKFW_NODISCARD std::span<GLFWmonitor *> getMonitors();
  #else
  VKFW_NODISCARD GLFWmonitor **getMonitors(size_t *count);
  #endif
#else
  VKFW_NODISCARD typename ResultValueType<Monitor>::type getPrimaryMonitor();
  VKFW_NODISCARD typename ResultValueType<std::vector<Monitor>>::type getMonitors();
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  void getMonitorPos(GLFWmonitor *monitor, int *xpos, int *ypos);
  void getMonitorWorkarea(GLFWmonitor *monitor, int *xpos, int *ypos, size_t *width,
                          size_t *height);
  void getMonitorPhysicalSize(GLFWmonitor *monitor, size_t *widthMM, size_t *heightMM);
  void getMonitorContentScale(GLFWmonitor *monitor, float *xscale, float *yscale);

  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD std::string_view getMonitorName();
  #else
  VKFW_NODISCARD char const *getMonitorName();
  #endif

  void setMonitorUserPointer(GLFWmonitor *monitor, void *pointer);
  VKFW_NODISCARD void *getMonitorUserPointer(GLFWmonitor *monitor);

  VKFW_NODISCARD GLFWvidmode const *getVideoMode(GLFWmonitor *monitor);
  #ifdef VKFW_HAS_SPAN
  VKFW_NODISCARD std::span<GLFWvidmode const> getVideoModes(GLFWmonitor *monitor);
  #else
  VKFW_NODISCARD GLFWvidmode const *getVideoModes(GLFWmonitor *monitor, size_t *count);
  #endif

  void setGamma(GLFWmonitor *monitor, float gamma);
  VKFW_NODISCARD GLFWgammaramp const *getGammaRamp(GLFWmonitor *monitor);
  void setGammaRamp(GLFWmonitor *monitor, GLFWgammaramp const *ramp);
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_NODISCARD GLFWwindow *createWindow(size_t width, size_t height, char const *title,
                                          GLFWmonitor *monitor = nullptr,
                                          GLFWwindow *share = nullptr);
  VKFW_NODISCARD Result destroyWindow(GLFWwindow *window);
#else
  VKFW_NODISCARD typename ResultValueType<Window>::type
  createWindow(size_t width, size_t height, char const *title, WindowHints hints = WindowHints{},
               Monitor monitor = nullptr, Window share = nullptr, bool reset_hints = true);
  #ifndef VKFW_NO_SMART_HANDLE
  using UniqueWindow = UniqueHandle<Window>;
  VKFW_NODISCARD typename ResultValueType<UniqueWindow>::type createWindowUnique(
    size_t width, size_t height, char const *title, WindowHints const &hints = WindowHints{},
    Monitor monitor = nullptr, Window share = nullptr, bool reset_hints = true);
  #endif
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  bool windowShouldClose(GLFWwindow *window);
  void setWindowShouldClose(GLFWwindow *window, bool value);

  #ifdef VKFW_HAS_STRING_VIEW
  void setWindowTitle(GLFWwindow *window, std::string_view title);
  #else
  void setWindowTitle(GLFWwindow *window, char const *title);
  #endif

  void getWindowPos(GLFWwindow *window, int *xpos, int *ypos);
  void setWindowPos(GLFWwindow *window, int xpos, int ypos);
  void getWindowSize(GLFWwindow *window, size_t *width, size_t *height);
  void setWindowSizeLimits(GLFWwindow *window, size_t minimum_width, size_t minimum_height,
                           size_t maximum_width, size_t maximum_height);
  void setWindowAspectRatio(GLFWwindow *window, size_t numerator, size_t denominator);
  void setWindowSize(GLFWwindow *window, size_t width, size_t height);
  void getFramebufferSize(GLFWwindow *window, size_t *width, size_t *height);
  void getWindowFrameSize(GLFWwindow *window, size_t *left, size_t *top, size_t *right,
                          size_t *bottom);
  void getWindowContentScale(GLFWwindow *window, float *xscale, float *yscale);
  float getWindowOpacity(GLFWwindow *window);
  void setWindowOpacity(GLFWwindow *window, float opacity);
  void iconifyWindow(GLFWwindow *window);
  void restoreWindow(GLFWwindow *window);
  void maximizeWindow(GLFWwindow *window);
  void showWindow(GLFWwindow *window);
  void hideWindow(GLFWwindow *window);
  void focusWindow(GLFWwindow *window);
  void requestWindowAttention(GLFWwindow *window);
  GLFWmonitor *getWindowMonitor(GLFWwindow *window);
  void setWindowMonitor(GLFWwindow *window, GLFWmonitor *monitor, int xpos, int ypos, size_t width,
                        size_t height, size_t refreshRate);

  #ifdef VKFW_HAS_SPAN
  void setWindowIcon(std::span<vkfw::Image> images);
  #endif
  void setWindowIcon(GLFWwindow *window, std::vector<vkfw::Image> images);
  void setWindowIcon(GLFWwindow *window, int count, vkfw::Image const *images);

  template <Attribute attribute>
  VKFW_NODISCARD typename ResultValueType<typename AttributeTraits<attribute>::type>::type
  getWindowAttribute(GLFWwindow *window);
  template <Attribute attribute,
            typename = typename std::enable_if<AttributeTraits<attribute>::value>::type>
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type setWindowAttribute(
    GLFWwindow *window, typename AttributeTraits<attribute>::type const &new_value);

  template <Attribute attribute>
  VKFW_NODISCARD VKFW_INLINE
    typename ResultValueType<typename AttributeTraits<attribute>::type>::type
    get(GLFWwindow *window) {
    return getWindowAttribute<attribute>(window);
  }
  template <Attribute attribute,
            typename = typename std::enable_if<AttributeTraits<attribute>::value>::type>
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  set(GLFWwindow *window, typename AttributeTraits<attribute>::type const &new_value) {
    return setWindowAttribute<attribute>(window, new_value);
  }

  template <InputMode mode>
  VKFW_NODISCARD typename ResultValueType<typename InputModeTraits<mode>::type>::type
  getInputMode(GLFWwindow *window);
  template <InputMode mode>
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
  setInputMode(GLFWwindow *window, typename InputModeTraits<mode>::type const &new_value);

  template <InputMode mode>
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<typename InputModeTraits<mode>::type>::type
  get(GLFWwindow *window) {
    return getInputMode<mode>(window);
  }
  template <InputMode mode>
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  set(GLFWwindow *window, typename InputModeTraits<mode>::type const &new_value) {
    return setInputMode<mode>(window, new_value);
  }

  #ifdef VKFW_NO_STD_FUNCTION_CALLBACKS
  VKFW_INLINE GLFWwindowposfun setWindowPosCallback(GLFWwindow *window, GLFWwindowposfun callback) {
    return glfwSetWindowPosCallback(window, callback);
  }
  VKFW_INLINE GLFWwindowsizefun setWindowSizeCallback(GLFWwindow *window,
                                                      GLFWwindowsizefun callback) {
    return glfwSetWindowSizeCallback(window, callback);
  }
  VKFW_INLINE GLFWwindowclosefun setWindowCloseCallback(GLFWwindow *window,
                                                        GLFWwindowclosefun callback) {
    return glfwSetWindowCloseCallback(window, callback);
  }
  VKFW_INLINE GLFWwindowrefreshfun setWindowRefreshCallback(GLFWwindow *window,
                                                            GLFWwindowrefreshfun callback) {
    return glfwSetWindowRefreshCallback(window, callback);
  }
  VKFW_INLINE GLFWwindowfocusfun setWindowFocusCallback(GLFWwindow *window,
                                                        GLFWwindowfocusfun callback) {
    return glfwSetWindowFocusCallback(window, callback);
  }
  VKFW_INLINE GLFWwindowiconifyfun setWindowIconifyCallback(GLFWwindow *window,
                                                            GLFWwindowiconifyfun callback) {
    return glfwSetWindowIconifyCallback(window, callback);
  }
  VKFW_INLINE GLFWwindowmaximizefun setWindowMaximizeCallback(GLFWwindow *window,
                                                              GLFWwindowmaximizefun callback) {
    return glfwSetWindowMaximizeCallback(window, callback);
  }
  VKFW_INLINE GLFWframebuffersizefun setFramebufferSizeCallback(GLFWwindow *window,
                                                                GLFWframebuffersizefun callback) {
    return glfwSetFramebufferSizeCallback(window, callback);
  }
  VKFW_INLINE GLFWwindowcontentscalefun
  setWindowContentScaleCallback(GLFWwindow *window, GLFWwindowcontentscalefun callback) {
    return glfwSetWindowContentScaleCallback(window, callback);
  }
  VKFW_INLINE GLFWkeyfun setKeyCallback(GLFWwindow *window, GLFWkeyfun callback) {
    return glfwSetKeyCallback(window, callback);
  }
  VKFW_INLINE GLFWcharfun setCharCallback(GLFWwindow *window, GLFWcharfun callback) {
    return glfwSetCharCallback(window, callback);
  }
  VKFW_INLINE GLFWcharmodsfun setCharModsCallback(GLFWwindow *window, GLFWcharmodsfun callback) {
    return glfwSetCharModsCallback(window, callback);
  }
  VKFW_INLINE GLFWmousebuttonfun setMouseButtonCallback(GLFWwindow *window,
                                                        GLFWmousebuttonfun callback) {
    return glfwSetMouseButtonCallback(window, callback);
  }
  VKFW_INLINE GLFWcursorposfun setCursorPosCallback(GLFWwindow *window, GLFWcursorposfun callback) {
    return glfwSetCursorPosCallback(window, callback);
  }
  VKFW_INLINE GLFWcursorenterfun setCursorEnterCallback(GLFWwindow *window,
                                                        GLFWcursorenterfun callback) {
    return glfwSetCursorEnterCallback(window, callback);
  }
  VKFW_INLINE GLFWscrollfun setScrollCallback(GLFWwindow *window, GLFWscrollfun callback) {
    return glfwSetScrollCallback(window, callback);
  }
  VKFW_INLINE GLFWdropfun setDropCallback(GLFWwindow *window, GLFWdropfun callback) {
    return glfwSetDropCallback(window, callback);
  }
  #else
  VKFW_NODISCARD VKFW_INLINE DynamicCallbackStorage *accessWindowCallbacks(GLFWwindow *window) {
    return reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
  }
  #endif
  VKFW_NODISCARD typename ResultValueType<void *>::type getWindowUserPointer(GLFWwindow *window);
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
  setWindowUserPointer(GLFWwindow *window, void *pointer);

  VKFW_NODISCARD bool getKey(GLFWwindow *window, Key key);
  VKFW_NODISCARD bool getMouseButton(GLFWwindow *window, MouseButton button);
  void getCursorPos(GLFWwindow *window, double *xpos, double *ypos);
  void setCursorPos(GLFWwindow *window, double xpos, double ypos);
  void setCursor(GLFWwindow *window, GLFWcursor *cursor);
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  void pollEvents();
  void waitEvents();
  void waitEventsTimeout(double timeout);
  void postEmptyEvent();

  void makeContextCurrent(GLFWwindow *window);
  VKFW_NODISCARD GLFWwindow *getCurrentContext();
  void swapBuffers(GLFWwindow *window);
  void swapInterval(int interval);

  VKFW_NODISCARD bool rawMouseMotionSupported();

  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD std::string_view getKeyName(Key key, int scancode = 0);
  #else
  VKFW_NODISCARD char const *getKeyName(Key key, int scancode = 0);
  #endif
  VKFW_NODISCARD int getKeyScancode(Key key);
#else
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type pollEvents();
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type waitEvents();
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
  waitEventsTimeout(double timeout);
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
  waitEventsTimeout(std::chrono::duration<double> timeout);
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type postEmptyEvent();

  VKFW_NODISCARD typename ResultValueType<Window>::type getCurrentContext();
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type swapInterval(int interval);

  VKFW_NODISCARD typename ResultValueType<bool>::type rawMouseMotionSupported();

  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD typename ResultValueType<std::string_view>::type getKeyName(Key key,
                                                                             int32_t scancode = 0);
  #else
  VKFW_NODISCARD typename ResultValueType<char const *>::type getKeyName(Key key,
                                                                         int32_t scancode = 0);
  #endif
  VKFW_NODISCARD typename ResultValueType<int>::type getKeyScancode(Key key);
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_NODISCARD GLFWcursor *createCursor(vkfw::Image const *image, int xhot, int yhot);
  VKFW_NODISCARD GLFWcursor *createStandardCursor(CursorShape shape);
  VKFW_NODISCARD Result destroyCursor(GLFWcursor *cursor);
#else
  VKFW_NODISCARD typename ResultValueType<Cursor>::type createCursor(vkfw::Image const &image,
                                                                     int xhot, int yhot);
  VKFW_NODISCARD typename ResultValueType<Cursor>::type createStandardCursor(CursorShape shape);
  #ifndef VKFW_NO_SMART_HANDLE
  using UniqueCursor = UniqueHandle<Cursor>;
  VKFW_NODISCARD typename ResultValueType<UniqueCursor>::type
  createCursorUnique(vkfw::Image const &image, int xhot, int yhot);
  VKFW_NODISCARD typename ResultValueType<UniqueCursor>::type
  createStandardCursorUnique(CursorShape shape);
  #endif
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  #ifdef VKFW_HAS_STRING_VIEW
  void setClipboardString(std::string_view string);
  std::string_view getClipboardString();
  #else
  void setClipboardString(char const *string);
  char const *getClipboardString();
  #endif

  double getTime();
  void setTime(double time);
  uint64_t getTimerValue();
  uint64_t getTimerFrequency();
#else
  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
  setClipboardString(std::string_view string);
  VKFW_NODISCARD typename ResultValueType<std::string_view>::type getClipboardString();
  #else
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
  setClipboardString(char const *string);
  VKFW_NODISCARD typename ResultValueType<char const *>::type getClipboardString();
  #endif

  VKFW_NODISCARD typename ResultValueType<double>::type getTime();
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type setTime(double time);
  VKFW_NODISCARD typename ResultValueType<uint64_t>::type getTimerValue();
  VKFW_NODISCARD typename ResultValueType<uint64_t>::type getTimerFrequency();
#endif

  VKFW_NODISCARD VKFW_INLINE bool joystickPresent(Joystick jid) {
    return static_cast<bool>(glfwJoystickPresent(static_cast<int>(jid)));
  }
  VKFW_NODISCARD VKFW_INLINE float const *getJoystickAxes(Joystick jid, int *count) {
    return glfwGetJoystickAxes(static_cast<int>(jid), count);
  }
  VKFW_NODISCARD VKFW_INLINE const unsigned char *getJoystickButtons(Joystick jid, int *count) {
    return glfwGetJoystickButtons(static_cast<int>(jid), count);
  }
  VKFW_NODISCARD VKFW_INLINE const unsigned char *getJoystickHats(Joystick jid, int *count) {
    return glfwGetJoystickHats(static_cast<int>(jid), count);
  }
#ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD VKFW_INLINE std::string_view getJoystickName(Joystick jid) {
    return glfwGetJoystickName(static_cast<int>(jid));
  }
  VKFW_NODISCARD VKFW_INLINE std::string_view getJoystickGUID(Joystick jid) {
    return glfwGetJoystickGUID(static_cast<int>(jid));
  }
#else
  VKFW_NODISCARD VKFW_INLINE char const *getJoystickName(Joystick jid) {
    return glfwGetJoystickName(static_cast<int>(jid));
  }
  VKFW_NODISCARD VKFW_INLINE char const *getJoystickGUID(Joystick jid) {
    return glfwGetJoystickGUID(static_cast<int>(jid));
  }
#endif
  VKFW_INLINE void getJoystickUserPointer(Joystick jid, void *pointer) {
    glfwSetJoystickUserPointer(static_cast<int>(jid), pointer);
  }
  VKFW_NODISCARD VKFW_INLINE void *getJoystickUserPointer(Joystick jid) {
    return glfwGetJoystickUserPointer(static_cast<int>(jid));
  }
  VKFW_NODISCARD VKFW_INLINE bool joystickIsGamepad(Joystick jid) {
    return static_cast<bool>(glfwJoystickIsGamepad(static_cast<int>(jid)));
  }
  VKFW_INLINE GLFWjoystickfun setJoystickCallback(GLFWjoystickfun callback) {
    return glfwSetJoystickCallback(callback);
  }
#ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD VKFW_INLINE bool updateGamepadMappings(std::string_view string) {
    return static_cast<bool>(glfwUpdateGamepadMappings(string.data()));
  }
#endif
  VKFW_NODISCARD VKFW_INLINE bool updateGamepadMappings(char const *string) {
    return static_cast<bool>(glfwUpdateGamepadMappings(string));
  }
#ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD VKFW_INLINE char const *getGamepadName(Joystick jid) {
    return glfwGetGamepadName(static_cast<int>(jid));
  }
#else
  VKFW_NODISCARD VKFW_INLINE char const *getGamepadName(Joystick jid) {
    return glfwGetGamepadName(static_cast<int>(jid));
  }
#endif
  VKFW_NODISCARD VKFW_INLINE bool getGamepadState(Joystick jid, GLFWgamepadstate *state) {
    return static_cast<bool>(glfwGetGamepadState(static_cast<int>(jid), state));
  }

  VKFW_NODISCARD VKFW_INLINE bool extensionSupported(char const *extension) {
    return static_cast<bool>(glfwExtensionSupported(extension));
  }
  VKFW_NODISCARD VKFW_INLINE GLFWglproc getProcAddress(char const *procname) {
    return glfwGetProcAddress(procname);
  }
  VKFW_NODISCARD VKFW_INLINE bool vulkanSupported() { return glfwVulkanSupported(); }

#ifdef VKFW_HAS_SPAN
  VKFW_NODISCARD VKFW_INLINE std::span<char const *> getRequiredInstanceExtensions() {
    uint32_t count;
    auto pointer = glfwGetRequiredInstanceExtensions(&count);
    return std::span<char const *>(pointer, count);
  }
#endif
  VKFW_NODISCARD VKFW_INLINE char const **getRequiredInstanceExtensions(uint32_t *count) {
    return glfwGetRequiredInstanceExtensions(count);
  }
#ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD VKFW_INLINE GLFWvkproc getInstanceProcAddress(VkInstance instance,
                                                               std::string_view procname) {
    return glfwGetInstanceProcAddress(instance, procname.data());
  }
#endif
  VKFW_NODISCARD VKFW_INLINE GLFWvkproc getInstanceProcAddress(VkInstance instance,
                                                               char const *procname) {
    return glfwGetInstanceProcAddress(instance, procname);
  }
  VKFW_NODISCARD VKFW_INLINE bool getPhysicalDevicePresentationSupport(VkInstance instance,
                                                                       VkPhysicalDevice device,
                                                                       uint32_t queuefamily) {
    return static_cast<bool>(
      glfwGetPhysicalDevicePresentationSupport(instance, device, queuefamily));
  }
#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_INLINE VkResult createWindowSurface(VkInstance instance, GLFWwindow *window,
                                           VkAllocationCallbacks const *allocator,
                                           VkSurfaceKHR *surface) {
    return glfwCreateWindowSurface(instance, window, allocator, surface);
  }
#else
  #ifndef VKFW_NO_INCLUDE_VULKAN_HPP
  VKFW_NODISCARD VKFW_INLINE vk::SurfaceKHR
  createWindowSurface(vk::Instance const &instance, Window const &window,
                      VkAllocationCallbacks const *allocator = nullptr) {
    VkSurfaceKHR output;
    glfwCreateWindowSurface(instance, window, allocator, &output);
    return output;
  }
    #ifndef VKFW_NO_SMART_HANDLE
  VKFW_NODISCARD VKFW_INLINE vk::UniqueSurfaceKHR
  createWindowSurfaceUnique(vk::Instance const &instance, Window const &window,
                            VkAllocationCallbacks const *allocator = nullptr) {
    VkSurfaceKHR output;
    glfwCreateWindowSurface(instance, window, allocator, &output);

    vk::ObjectDestroy<vk::Instance, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE> deleter(instance, nullptr);
    return vk::UniqueSurfaceKHR(output, deleter);
  }
    #endif
  #endif
#endif
} // namespace VKFW_NAMESPACE

#ifndef VKFW_NO_STD_FUNCTION_CALLBACKS
namespace VKFW_NAMESPACE {
  struct DynamicCallbackStorage {
  #ifdef VKFW_DISABLE_ENHANCED_MODE
    friend void *VKFW_NAMESPACE::getWindowUserPointer(GLFWwindow *window);
    friend void VKFW_NAMESPACE::setWindowUserPointer(GLFWwindow *window, void *pointer);
    using window_type = GLFWwindow *;
  #else
    friend class Window;
    using window_type = Window const &;
  #endif
  private:
    void *user_ptr = nullptr;

  public:
    std::function<void(window_type, int, int)> on_window_move;
    std::function<void(window_type, size_t, size_t)> on_window_resize;
    std::function<void(window_type)> on_window_close;
    std::function<void(window_type)> on_window_refresh;
    std::function<void(window_type, bool)> on_window_focus;
    std::function<void(window_type, bool)> on_window_iconify;
    std::function<void(window_type, bool)> on_window_maximize;
    std::function<void(window_type, size_t, size_t)> on_framebuffer_resize;
    std::function<void(window_type, float, float)> on_window_content_scale_change;
    std::function<void(window_type, MouseButton, MouseButtonAction, ModifierKeyFlags)>
      on_mouse_button;
    std::function<void(window_type, double, double)> on_cursor_move;
    std::function<void(window_type, bool)> on_cursor_enter;
    std::function<void(window_type, double, double)> on_scroll;
    std::function<void(window_type, Key, int32_t, KeyAction, ModifierKeyFlags)> on_key;
    std::function<void(window_type, uint32_t)> on_character;
  #ifdef VKFW_HAS_STRING_VIEW
    std::function<void(window_type, std::vector<std::string_view>)> on_drop;
  #else
    std::function<void(window_type, std::vector<char const *>)> on_drop;
  #endif
  };
} // namespace VKFW_NAMESPACE
#endif

#ifndef VKFW_NO_SMART_HANDLE
template <> struct VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Instance> {
  VKFW_INLINE void destroy(Instance &instance) { static_cast<void>(instance.destroy()); }
};
  #ifndef VKFW_NO_INCLUDE_VULKAN_HPP
template <>
class VULKAN_HPP_NAMESPACE::UniqueHandleTraits<VKFW_NAMESPACE::Instance,
                                               VULKAN_HPP_DEFAULT_DISPATCHER_TYPE> {
  #else
template <> class VKFW_NAMESPACE::UniqueHandleTraits<VKFW_NAMESPACE::Instance> {
  #endif
public:
  using deleter = VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Instance>;
};

template <> struct VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Window> {
  VKFW_INLINE void destroy(Window &window) { static_cast<void>(window.destroy()); }
};
  #ifndef VKFW_NO_INCLUDE_VULKAN_HPP
template <>
class VULKAN_HPP_NAMESPACE::UniqueHandleTraits<VKFW_NAMESPACE::Window,
                                               VULKAN_HPP_DEFAULT_DISPATCHER_TYPE> {
  #else
template <> class VKFW_NAMESPACE::UniqueHandleTraits<VKFW_NAMESPACE::Window> {
  #endif
public:
  using deleter = VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Window>;
};

template <> struct VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Cursor> {
  VKFW_INLINE void destroy(Cursor &cursor) { static_cast<void>(cursor.destroy()); }
};
  #ifndef VKFW_NO_INCLUDE_VULKAN_HPP
template <>
class VULKAN_HPP_NAMESPACE::UniqueHandleTraits<VKFW_NAMESPACE::Cursor,
                                               VULKAN_HPP_DEFAULT_DISPATCHER_TYPE> {
  #else
template <> class VKFW_NAMESPACE::UniqueHandleTraits<VKFW_NAMESPACE::Cursor> {
  #endif
public:
  using deleter = VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Cursor>;
};
#endif

namespace VKFW_NAMESPACE {
#ifndef VKFW_DISABLE_ENHANCED_MODE
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Instance::destroy() {
    if (m_state) {
      glfwTerminate();
      m_state = false;
      return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Instance::destroy");
    } else
      return createResultValue(Result::VKFW_ENUMERATOR(Success),
                               VKFW_NAMESPACE_STRING "::Instance::destroy");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::destroy() {
    if (m_window) {
  #ifndef VKFW_NO_STD_FUNCTION_CALLBACKS
      auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(m_window));
      if (ptr)
        delete ptr;
  #endif
      glfwDestroyWindow(m_window);
      m_window = nullptr;
      return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::destroy");
    } else
      return createResultValue(Result::VKFW_ENUMERATOR(Success),
                               VKFW_NAMESPACE_STRING "::Window::destroy");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Cursor::destroy() {
    glfwDestroyCursor(m_cursor);
    m_cursor = nullptr;
    return createResultValue(Result::VKFW_ENUMERATOR(Success),
                             VKFW_NAMESPACE_STRING "::Cursor::destroy");
  }
#endif

#ifdef VKFW_HAS_STRING_VIEW
  template <>
  VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(CocoaFrameName)>(
    typename WindowHintTraits<WindowHint::VKFW_ENUMERATOR(CocoaFrameName)>::type value) {
    glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(CocoaFrameName)),
                         value.data());
    return getError();
  }
#else
  template <>
  VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(CocoaFrameName)>(
    typename WindowHintTraits<WindowHint::VKFW_ENUMERATOR(CocoaFrameName)>::type value) {
    glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(CocoaFrameName)), value);
    return getError();
  }
#endif
#ifdef VKFW_HAS_STRING_VIEW
  template <>
  VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(X11ClassName)>(
    typename WindowHintTraits<WindowHint::VKFW_ENUMERATOR(X11ClassName)>::type value) {
    glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(X11ClassName)), value.data());
    return getError();
  }
#else
  template <>
  VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(X11ClassName)>(
    typename WindowHintTraits<WindowHint::VKFW_ENUMERATOR(X11ClassName)>::type value) {
    glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(X11ClassName)), value);
    return getError();
  }
#endif
#ifdef VKFW_HAS_STRING_VIEW
  template <>
  VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(X11InstanceName)>(
    typename WindowHintTraits<WindowHint::VKFW_ENUMERATOR(X11InstanceName)>::type value) {
    glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(X11InstanceName)),
                         value.data());
    return getError();
  }
#else
  template <>
  VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(X11InstanceName)>(
    typename WindowHintTraits<WindowHint::VKFW_ENUMERATOR(X11InstanceName)>::type value) {
    glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(X11InstanceName)), value);
    return getError();
  }
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_NODISCARD VKFW_INLINE Result init() {
    if (glfwInit())
      return Result::VKFW_ENUMERATOR(Success);
    else
      return getError();
  }
  VKFW_NODISCARD VKFW_INLINE Result terminate() {
    glfwTerminate();
    return getError();
  }
#else
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  init(InitHints hints) {
    Result result = setInitHints(hints);
    if (!check(result))
      return createResultValue(result, VKFW_NAMESPACE_STRING "::init");

    if (glfwInit())
      return createResultValue(Result::VKFW_ENUMERATOR(Success), VKFW_NAMESPACE_STRING "::init");
    else
      return createResultValue(getError(), VKFW_NAMESPACE_STRING "::init");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type terminate() {
    glfwTerminate();
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::terminate");
  }
  #ifndef VKFW_NO_SMART_HANDLE
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<VKFW_NAMESPACE::UniqueInstance>::type
  initUnique(InitHints hints) {
    Instance instance;

    Result result = setInitHints(hints);
    if (!check(result))
      return createResultValueUnique(result, instance, VKFW_NAMESPACE_STRING "::initUnique");

    if (glfwInit()) {
      instance = true;
      return createResultValueUnique(Result::VKFW_ENUMERATOR(Success), instance,
                                     VKFW_NAMESPACE_STRING "::initUnique");
    } else
      return createResultValueUnique(getError(), instance, VKFW_NAMESPACE_STRING "::initUnique");
  }
  #endif
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_NODISCARD VKFW_INLINE GLFWmonitor *getPrimaryMonitor() { return glfwGetPrimaryMonitor(); }
  #ifdef VKFW_HAS_SPAN
  VKFW_NODISCARD VKFW_INLINE std::span<GLFWmonitor *> getMonitors() {
    int tmp_count;
    auto **output = glfwGetMonitors(&tmp_count);
    return std::span<GLFWmonitor *>(output, static_cast<size_t>(tmp_count > 0 ? tmp_count : 0));
  }
  #else
  VKFW_NODISCARD VKFW_INLINE GLFWmonitor **getMonitors(size_t *count) {
    int tmp_count;
    auto **output = glfwGetMonitors(&tmp_count);
    *count = static_cast<size_t>(tmp_count > 0 ? tmp_count : 0);
    return output;
  }
  #endif
#else
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<Monitor>::type getPrimaryMonitor() {
    Monitor monitor = glfwGetPrimaryMonitor();
    return createResultValue(getError(), monitor, VKFW_NAMESPACE_STRING "::getPrimaryMonitor");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::vector<Monitor>>::type getMonitors() {
    std::vector<Monitor> output;

    int count;
    auto ptr = glfwGetMonitors(&count);
    Result result = getError();
    if (check(result)) {
      output.reserve(static_cast<size_t>(count));
      std::transform(ptr, ptr + count, std::back_inserter(output),
                     [](GLFWmonitor *monitor) { return Monitor(monitor); });
      VKFW_ASSERT(output.size() == static_cast<size_t>(count));
    }
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::getMonitors");
  }
#endif
  VKFW_INLINE GLFWmonitorfun setMonitorCallback(GLFWmonitorfun const &callback) {
    return glfwSetMonitorCallback(callback);
  }

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_INLINE void getMonitorPos(GLFWmonitor *monitor, int *xpos, int *ypos) {
    glfwGetMonitorPos(monitor, xpos, ypos);
  }
  VKFW_INLINE void getMonitorWorkarea(GLFWmonitor *monitor, int *xpos, int *ypos, size_t *width,
                                      size_t *height) {
    int temp_width, temp_height;
    glfwGetMonitorWorkarea(monitor, xpos, ypos, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      *width = temp_width;
      *height = temp_height;
    } else {
      *width = 0u;
      *height = 0u;
    }
  }
  VKFW_INLINE void getMonitorPhysicalSize(GLFWmonitor *monitor, size_t *widthMM, size_t *heightMM) {
    int temp_width, temp_height;
    glfwGetMonitorPhysicalSize(monitor, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      *widthMM = temp_width;
      *heightMM = temp_height;
    } else {
      *widthMM = 0u;
      *heightMM = 0u;
    }
  }
  VKFW_INLINE void getMonitorContentScale(GLFWmonitor *monitor, float *xscale, float *yscale) {
    glfwGetMonitorContentScale(monitor, xscale, yscale);
  }
  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD VKFW_INLINE std::string_view getMonitorName(GLFWmonitor *monitor) {
  #else
  VKFW_NODISCARD VKFW_INLINE char const *getMonitorName(GLFWmonitor *monitor) {
  #endif
    return glfwGetMonitorName(monitor);
  }

  VKFW_INLINE void setMonitorUserPointer(GLFWmonitor *monitor, void *pointer) {
    glfwSetMonitorUserPointer(monitor, pointer);
  }
  VKFW_NODISCARD VKFW_INLINE void *getMonitorUserPointer(GLFWmonitor *monitor) {
    return glfwGetMonitorUserPointer(monitor);
  }

  VKFW_NODISCARD VKFW_INLINE GLFWvidmode const *getVideoMode(GLFWmonitor *monitor) {
    return glfwGetVideoMode(monitor);
  }
  #ifdef VKFW_HAS_SPAN
  VKFW_NODISCARD VKFW_INLINE std::span<GLFWvidmode const> getVideoModes(GLFWmonitor *monitor) {
    int count;
    GLFWvidmode const *pointer = glfwGetVideoModes(monitor, &count);
    return std::span<GLFWvidmode const>(pointer, static_cast<size_t>(count));
  }
  #else
  VKFW_NODISCARD VKFW_INLINE GLFWvidmode const *getVideoModes(GLFWmonitor *monitor, size_t *count) {
    int temp_count;
    GLFWvidmode const *pointer = glfwGetVideoModes(monitor, &temp_count);
    if (temp_count > 0)
      *count = temp_count;
    else
      *count = 0u;
    return pointer;
  }
  #endif

  VKFW_INLINE void setGamma(GLFWmonitor *monitor, float gamma) { glfwSetGamma(monitor, gamma); }
  VKFW_NODISCARD VKFW_INLINE GLFWgammaramp const *getGammaRamp(GLFWmonitor *monitor) {
    return glfwGetGammaRamp(monitor);
  }
  VKFW_INLINE void setGammaRamp(GLFWmonitor *monitor, GLFWgammaramp const *ramp) {
    glfwSetGammaRamp(monitor, ramp);
  }
#else
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Monitor::getPos(int *xpos, int *ypos) const {
    glfwGetMonitorPos(m_monitor, xpos, ypos);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Monitor::getPos");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<int, int>>::type
  Monitor::getPos() const {
    std::tuple<int, int> output;
    glfwGetMonitorPos(m_monitor, &std::get<0>(output), &std::get<1>(output));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Monitor::getPos");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type Monitor::getPosX() const {
    int output;
    glfwGetMonitorPos(m_monitor, &output, nullptr);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Monitor::getPosX");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type Monitor::getPosY() const {
    int output;
    glfwGetMonitorPos(m_monitor, nullptr, &output);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Monitor::getPosY");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Monitor::getWorkarea(int *xpos, int *ypos, size_t *width, size_t *height) const {
    int temp_width, temp_height;
    glfwGetMonitorWorkarea(m_monitor, xpos, ypos, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      *width = temp_width;
      *height = temp_height;
    } else {
      *width = 0u;
      *height = 0u;
    }
    return createResultValue(result, VKFW_NAMESPACE_STRING "::Monitor::getWorkarea");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<int, int, size_t, size_t>>::type
  Monitor::getWorkarea() const {
    std::tuple<int, int, size_t, size_t> output;
    int temp_width, temp_height;
    glfwGetMonitorWorkarea(m_monitor, &std::get<0>(output), &std::get<1>(output), &temp_width,
                           &temp_height);
    Result result = getError();
    if (check(result)) {
      std::get<2>(output) = temp_width;
      std::get<3>(output) = temp_height;
    } else {
      std::get<2>(output) = 0u;
      std::get<3>(output) = 0u;
    }
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Monitor::getWorkarea");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<int, int>>::type
  Monitor::getWorkareaPos() const {
    std::tuple<int, int> output;
    glfwGetMonitorWorkarea(m_monitor, &std::get<0>(output), &std::get<1>(output), nullptr, nullptr);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Monitor::getWorkareaPos");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type Monitor::getWorkareaPosX() const {
    int output;
    glfwGetMonitorWorkarea(m_monitor, &output, nullptr, nullptr, nullptr);
    return createResultValue(getError(), output,
                             VKFW_NAMESPACE_STRING "::Monitor::getWorkareaPosX");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type Monitor::getWorkareaPosY() const {
    int output;
    glfwGetMonitorWorkarea(m_monitor, nullptr, &output, nullptr, nullptr);
    return createResultValue(getError(), output,
                             VKFW_NAMESPACE_STRING "::Monitor::getWorkareaPosY");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<size_t, size_t>>::type
  Monitor::getWorkareaSize() const {
    std::tuple<size_t, size_t> output;
    int temp_width, temp_height;
    glfwGetMonitorWorkarea(m_monitor, nullptr, nullptr, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      std::get<0>(output) = temp_width;
      std::get<1>(output) = temp_height;
    } else {
      std::get<0>(output) = 0u;
      std::get<1>(output) = 0u;
    }
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Monitor::getWorkareaSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type
  Monitor::getWorkareaWidth() const {
    size_t output;
    int temp;
    glfwGetMonitorWorkarea(m_monitor, nullptr, nullptr, &temp, nullptr);
    Result result = getError();
    if (check(result))
      output = static_cast<size_t>(temp);
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Monitor::getWorkareaWidth");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type
  Monitor::getWorkareaHeight() const {
    size_t output;
    int temp;
    glfwGetMonitorWorkarea(m_monitor, nullptr, nullptr, nullptr, &temp);
    Result result = getError();
    if (check(result))
      output = static_cast<size_t>(temp);
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Monitor::getWorkareaHeight");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Monitor::getPhysicalSize(size_t *widthMM, size_t *heightMM) const {
    int temp_width, temp_height;
    glfwGetMonitorPhysicalSize(m_monitor, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      *widthMM = temp_width;
      *heightMM = temp_height;
    } else {
      *widthMM = 0u;
      *heightMM = 0u;
    }
    return createResultValue(result, VKFW_NAMESPACE_STRING "::Monitor::getPhysicalSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<size_t, size_t>>::type
  Monitor::getPhysicalSize() const {
    std::tuple<size_t, size_t> output;
    int temp_width, temp_height;
    glfwGetMonitorPhysicalSize(m_monitor, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      std::get<0>(output) = temp_width;
      std::get<1>(output) = temp_height;
    } else {
      std::get<0>(output) = 0u;
      std::get<1>(output) = 0u;
    }
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Monitor::getPhysicalSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type
  Monitor::getPhysicalWidth() const {
    size_t output;
    int temp;
    glfwGetMonitorPhysicalSize(m_monitor, &temp, nullptr);
    Result result = getError();
    if (check(result))
      output = static_cast<size_t>(temp);
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Monitor::getPhysicalWidth");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type
  Monitor::getPhysicalHeight() const {
    size_t output;
    int temp;
    glfwGetMonitorPhysicalSize(m_monitor, nullptr, &temp);
    Result result = getError();
    if (check(result))
      output = static_cast<size_t>(temp);
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Monitor::getPhysicalHeight");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Monitor::getContentScale(float *xscale, float *yscale) const {
    glfwGetMonitorContentScale(m_monitor, xscale, yscale);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Monitor::getContentScale");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<float, float>>::type
  Monitor::getContentScale() const {
    std::tuple<float, float> output;
    glfwGetMonitorContentScale(m_monitor, &std::get<0>(output), &std::get<1>(output));
    return createResultValue(getError(), output,
                             VKFW_NAMESPACE_STRING "::Monitor::getContentScale");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<float>::type
  Monitor::getContentScaleX() const {
    float output;
    glfwGetMonitorContentScale(m_monitor, &output, nullptr);
    return createResultValue(getError(), output,
                             VKFW_NAMESPACE_STRING "::Monitor::getContentScaleX");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<float>::type
  Monitor::getContentScaleY() const {
    float output;
    glfwGetMonitorContentScale(m_monitor, nullptr, &output);
    return createResultValue(getError(), output,
                             VKFW_NAMESPACE_STRING "::Monitor::getContentScaleY");
  }

  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::string_view>::type
  Monitor::getName() const {
    char const *tmp = glfwGetMonitorName(m_monitor);
    std::string_view output;
    if (tmp)
      output = tmp;
  #else
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<char const *>::type Monitor::getName() const {
    char const *output = glfwGetMonitorName(m_monitor);
  #endif
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Monitor::getName");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Monitor::setUserPointer(void *pointer) const {
    glfwSetMonitorUserPointer(m_monitor, pointer);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Monitor::setUserPointer");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<void *>::type
  Monitor::getUserPointer() const {
    void *output = glfwGetMonitorUserPointer(m_monitor);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Monitor::getUserPointer");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<GLFWvidmode const *>::type
  Monitor::getVideoMode() const {
    GLFWvidmode const *output = glfwGetVideoMode(m_monitor);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Monitor::getVideoMode");
  }
  #ifdef VKFW_HAS_SPAN
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::span<GLFWvidmode const>>::type
  Monitor::getVideoModes() const {
    int count;
    GLFWvidmode const *pointer = glfwGetVideoModes(m_monitor, &count);
    std::span<GLFWvidmode const> output(pointer, static_cast<size_t>(count));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Monitor::getVideoModes");
  }
  #else
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::vector<GLFWvidmode>>::type
  Monitor::getVideoModes() const {
    int count;
    GLFWvidmode const *pointer = glfwGetVideoModes(m_monitor, &count);
    std::vector<GLFWvidmode> output(pointer, pointer + static_cast<size_t>(count));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Monitor::getVideoModes");
  }
  #endif
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Monitor::setGamma(float gamma) const {
    glfwSetGamma(m_monitor, gamma);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Monitor::setGamma");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<GLFWgammaramp const *>::type
  Monitor::getGammaRamp() const {
    auto *output = glfwGetGammaRamp(m_monitor);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Monitor::getGammaRamp");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Monitor::setGammaRamp(GLFWgammaramp const *ramp) const {
    glfwSetGammaRamp(m_monitor, ramp);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Monitor::setGammaRamp");
  }
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_NODISCARD VKFW_INLINE GLFWwindow *createWindow(size_t width, size_t height,
                                                      char const *title, GLFWmonitor *monitor,
                                                      GLFWwindow *share) {
    return glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title, monitor,
                            share);
  }
  VKFW_NODISCARD VKFW_INLINE Result destroyWindow(GLFWwindow *window) {
    glfwDestroyWindow(window);
    return getError();
  }
#else
  #ifndef VKFW_NO_STD_FUNCTION_CALLBACKS
  VKFW_INLINE void setup_DynamicCallbackStorage(GLFWwindow *window_ptr) {
    if (window_ptr) {
      glfwSetWindowUserPointer(window_ptr, new DynamicCallbackStorage{});
      glfwSetWindowPosCallback(window_ptr, [](GLFWwindow *window, int xpos, int ypos) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_window_move)
          ptr->on_window_move(window, xpos, ypos);
      });
      glfwSetWindowSizeCallback(window_ptr, [](GLFWwindow *window, int width, int height) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_window_resize)
          ptr->on_window_resize(window, static_cast<size_t>(width), static_cast<size_t>(height));
      });
      glfwSetWindowCloseCallback(window_ptr, [](GLFWwindow *window) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_window_close)
          ptr->on_window_close(window);
      });
      glfwSetWindowRefreshCallback(window_ptr, [](GLFWwindow *window) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_window_refresh)
          ptr->on_window_refresh(window);
      });
      glfwSetWindowFocusCallback(window_ptr, [](GLFWwindow *window, int focused) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_window_focus)
          ptr->on_window_focus(window, static_cast<bool>(focused));
      });
      glfwSetWindowIconifyCallback(window_ptr, [](GLFWwindow *window, int iconified) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_window_iconify)
          ptr->on_window_iconify(window, static_cast<bool>(iconified));
      });
      glfwSetWindowMaximizeCallback(window_ptr, [](GLFWwindow *window, int maximized) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_window_maximize)
          ptr->on_window_maximize(window, static_cast<bool>(maximized));
      });
      glfwSetFramebufferSizeCallback(window_ptr, [](GLFWwindow *window, int width, int height) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_framebuffer_resize)
          ptr->on_framebuffer_resize(window, static_cast<size_t>(width),
                                     static_cast<size_t>(height));
      });
      glfwSetWindowContentScaleCallback(window_ptr, [](GLFWwindow *window, float xscale,
                                                       float yscale) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_window_content_scale_change)
          ptr->on_window_content_scale_change(window, xscale, yscale);
      });
      glfwSetMouseButtonCallback(window_ptr, [](GLFWwindow *window, int button, int action,
                                                int mods) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_mouse_button)
          ptr->on_mouse_button(window, static_cast<MouseButton>(button),
                               static_cast<MouseButtonAction>(action),
                               static_cast<ModifierKeyFlags>(mods));
      });
      glfwSetCursorPosCallback(window_ptr, [](GLFWwindow *window, double xpos, double ypos) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_cursor_move)
          ptr->on_cursor_move(window, xpos, ypos);
      });
      glfwSetCursorEnterCallback(window_ptr, [](GLFWwindow *window, int entered) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_cursor_enter)
          ptr->on_cursor_enter(window, static_cast<bool>(entered));
      });
      glfwSetScrollCallback(window_ptr, [](GLFWwindow *window, double xoffset, double yoffset) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_scroll)
          ptr->on_scroll(window, xoffset, yoffset);
      });
      glfwSetKeyCallback(window_ptr, [](GLFWwindow *window, int key, int scancode, int action,
                                        int mods) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_key)
          ptr->on_key(window, static_cast<Key>(key), scancode, static_cast<KeyAction>(action),
                      static_cast<ModifierKeyFlags>(mods));
      });
      glfwSetCharCallback(window_ptr, [](GLFWwindow *window, unsigned int codepoint) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_character)
          ptr->on_character(window, codepoint);
      });
      glfwSetDropCallback(window_ptr, [](GLFWwindow *window, int path_count, char const *paths[]) {
        auto *ptr = reinterpret_cast<DynamicCallbackStorage *>(glfwGetWindowUserPointer(window));
        if (ptr && ptr->on_drop) {
    #ifdef VKFW_HAS_STRING_VIEW
          std::vector<std::string_view> output;
          output.reserve(path_count);
          std::transform(paths, paths + path_count, std::back_inserter(output),
                         [](char const *path) { return std::string_view{ path }; });
          ptr->on_drop(window, std::move(output));
    #else
					ptr->on_drop(window, std::vector<char const *>(paths, paths + path_count));
    #endif
        }
      });
    }
  }
  #endif
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<Window>::type
  createWindow(size_t width, size_t height, char const *title, WindowHints hints, Monitor monitor,
               Window share, bool reset_hints) {
    Window output;
    if (reset_hints) {
      Result result = defaultWindowHints();
      if (!check(result))
        return createResultValue(result, output, VKFW_NAMESPACE_STRING "::defaultWindowHints");
    }
    Result result = setWindowHints(std::move(hints));
    if (!check(result))
      return createResultValue(result, output, VKFW_NAMESPACE_STRING "::setWindowHints");

    output = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title, monitor,
                              share);
  #ifndef VKFW_NO_STD_FUNCTION_CALLBACKS
    setup_DynamicCallbackStorage(output);
  #endif
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::createWindow");
  }
  #ifndef VKFW_NO_SMART_HANDLE
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<UniqueWindow>::type
  createWindowUnique(size_t width, size_t height, char const *title, WindowHints const &hints,
                     Monitor monitor, Window share, bool reset_hints) {
    Window output;
    if (reset_hints) {
      Result result = defaultWindowHints();
      if (!check(result))
        return createResultValueUnique(result, output,
                                       VKFW_NAMESPACE_STRING "::defaultWindowHints");
    }
    Result result = setWindowHints(hints);
    if (!check(result))
      return createResultValueUnique(result, output, VKFW_NAMESPACE_STRING "::setWindowHints");

    output = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title, monitor,
                              share);
    #ifndef VKFW_NO_STD_FUNCTION_CALLBACKS
    setup_DynamicCallbackStorage(output);
    #endif
    return createResultValueUnique(getError(), output,
                                   VKFW_NAMESPACE_STRING "::createWindowUnique");
  }
  #endif
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_NODISCARD VKFW_INLINE bool windowShouldClose(GLFWwindow *window) {
    return static_cast<bool>(glfwWindowShouldClose(window));
  }
  VKFW_INLINE void setWindowShouldClose(GLFWwindow *window, bool value) {
    glfwSetWindowShouldClose(window, static_cast<int>(value));
  }

  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_INLINE void setWindowTitle(GLFWwindow *window, std::string_view title) {
    glfwSetWindowTitle(window, title.data());
  }
  #else
  VKFW_INLINE void setWindowTitle(GLFWwindow *window, char const *title) {
    glfwSetWindowTitle(window, title);
  }
  #endif

  VKFW_INLINE void getWindowPos(GLFWwindow *window, int *xpos, int *ypos) {
    glfwGetWindowPos(window, xpos, ypos);
  }
  VKFW_INLINE void setWindowPos(GLFWwindow *window, int xpos, int ypos) {
    glfwSetWindowPos(window, xpos, ypos);
  }
  VKFW_INLINE void getWindowSize(GLFWwindow *window, size_t *width, size_t *height) {
    int temp_width, temp_height;
    glfwGetWindowSize(window, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      *width = temp_width;
      *height = temp_height;
    } else {
      *width = 0u;
      *height = 0u;
    }
  }
  VKFW_INLINE void setWindowSizeLimits(GLFWwindow *window, size_t minimum_width,
                                       size_t minimum_height, size_t maximum_width,
                                       size_t maximum_height) {
    glfwSetWindowSizeLimits(window, static_cast<int>(minimum_width),
                            static_cast<int>(minimum_height), static_cast<int>(maximum_width),
                            static_cast<int>(maximum_height));
  }
  VKFW_INLINE void setWindowAspectRatio(GLFWwindow *window, size_t numerator, size_t denominator) {
    glfwSetWindowAspectRatio(window, static_cast<int>(numerator), static_cast<int>(denominator));
  }
  VKFW_INLINE void setWindowSize(GLFWwindow *window, size_t width, size_t height) {
    glfwSetWindowSize(window, static_cast<int>(width), static_cast<int>(height));
  }
  VKFW_INLINE void getFramebufferSize(GLFWwindow *window, size_t *width, size_t *height) {
    int temp_width, temp_height;
    glfwGetFramebufferSize(window, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      *width = temp_width;
      *height = temp_height;
    } else {
      *width = 0u;
      *height = 0u;
    }
  }
  VKFW_INLINE void getWindowFrameSize(GLFWwindow *window, size_t *left, size_t *top, size_t *right,
                                      size_t *bottom) {
    int temp_left, temp_top, temp_right, temp_bottom;
    glfwGetWindowFrameSize(window, &temp_left, &temp_top, &temp_right, &temp_bottom);
    Result result = getError();
    if (check(result)) {
      *left = temp_left;
      *top = temp_top;
      *right = temp_right;
      *bottom = temp_bottom;
    } else {
      *left = 0u;
      *top = 0u;
      *right = 0u;
      *bottom = 0u;
    }
  }
  VKFW_INLINE void getWindowContentScale(GLFWwindow *window, float *xscale, float *yscale) {
    glfwGetWindowContentScale(window, xscale, yscale);
  }
  VKFW_NODISCARD VKFW_INLINE float getWindowOpacity(GLFWwindow *window) {
    return glfwGetWindowOpacity(window);
  }
  VKFW_INLINE void setWindowOpacity(GLFWwindow *window, float opacity) {
    glfwSetWindowOpacity(window, opacity);
  }
  VKFW_INLINE void iconifyWindow(GLFWwindow *window) { glfwIconifyWindow(window); }
  VKFW_INLINE void restoreWindow(GLFWwindow *window) { glfwRestoreWindow(window); }
  VKFW_INLINE void maximizeWindow(GLFWwindow *window) { glfwMaximizeWindow(window); }
  VKFW_INLINE void showWindow(GLFWwindow *window) { glfwShowWindow(window); }
  VKFW_INLINE void hideWindow(GLFWwindow *window) { glfwHideWindow(window); }
  VKFW_INLINE void focusWindow(GLFWwindow *window) { glfwFocusWindow(window); }
  VKFW_INLINE void requestWindowAttention(GLFWwindow *window) {
    glfwRequestWindowAttention(window);
  }
  VKFW_NODISCARD VKFW_INLINE GLFWmonitor *getWindowMonitor(GLFWwindow *window) {
    return glfwGetWindowMonitor(window);
  }
  VKFW_INLINE void setWindowMonitor(GLFWwindow *window, GLFWmonitor *monitor, int xpos, int ypos,
                                    size_t width, size_t height, size_t refreshRate) {
    glfwSetWindowMonitor(window, monitor, xpos, ypos, static_cast<int>(width),
                         static_cast<int>(height), static_cast<int>(refreshRate));
  }

  #ifdef VKFW_HAS_SPAN
  VKFW_INLINE void setWindowIcon(GLFWwindow *window, std::span<vkfw::Image> images) {
    glfwSetWindowIcon(window, static_cast<int>(images.size()), images.data());
  }
  #endif
  VKFW_INLINE void setWindowIcon(GLFWwindow *window, std::vector<vkfw::Image> images) {
    glfwSetWindowIcon(window, static_cast<int>(images.size()), images.data());
  }
  VKFW_INLINE void setWindowIcon(GLFWwindow *window, int image_count, vkfw::Image const *images) {
    glfwSetWindowIcon(window, static_cast<int>(image_count), images);
  }

  template <Attribute attribute>
  VKFW_NODISCARD VKFW_INLINE
    typename ResultValueType<typename AttributeTraits<attribute>::type>::type
    getWindowAttribute(GLFWwindow *window) {
    auto output = static_cast<typename AttributeTraits<attribute>::type>(
      glfwGetWindowAttrib(window, static_cast<int>(attribute)));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::getWindowAttribute");
  }
  template <Attribute attribute, typename>
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  setWindowAttribute(GLFWwindow *window,
                     typename AttributeTraits<attribute>::type const &new_value) {
    glfwSetWindowAttrib(window, static_cast<int>(attribute), static_cast<int>(new_value));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::setWindowAttribute");
  }

  VKFW_NODISCARD VKFW_INLINE void *getWindowUserPointer(GLFWwindow *window) {
  #ifdef VKFW_NO_STD_FUNCTION_CALLBACKS
    return glfwGetWindowUserPointer(window);
  #else
    return accessWindowCallbacks(window)->user_ptr;
  #endif
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  setWindowUserPointer(GLFWwindow *window, void *pointer) {
  #ifdef VKFW_NO_STD_FUNCTION_CALLBACKS
    glfwSetWindowUserPointer(m_window, ptr);
  #else
    accessWindowCallbacks(window)->user_ptr = pointer;
  #endif
  }

  VKFW_NODISCARD VKFW_INLINE bool getKey(GLFWwindow *window, Key key) {
    return glfwGetKey(window, static_cast<int>(key))
        == static_cast<int>(KeyAction::VKFW_ENUMERATOR(Press));
  }
  VKFW_NODISCARD VKFW_INLINE bool getMouseButton(GLFWwindow *window, MouseButton button) {
    return glfwGetKey(window, static_cast<int>(button))
        == static_cast<int>(MouseButtonAction::VKFW_ENUMERATOR(Press));
  }
  VKFW_INLINE void getCursorPos(GLFWwindow *window, double *xpos, double *ypos) {
    glfwGetCursorPos(window, xpos, ypos);
  }
  VKFW_INLINE void setCursorPos(GLFWwindow *window, double xpos, double ypos) {
    glfwSetCursorPos(window, xpos, ypos);
  }

  VKFW_INLINE void setCursor(GLFWwindow *window, GLFWcursor *cursor) {
    glfwSetCursor(window, cursor);
  }
#else
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<bool>::type Window::shouldClose() const {
    auto output = static_cast<bool>(glfwWindowShouldClose(m_window));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::shouldClose");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setShouldClose(bool value) const {
    glfwSetWindowShouldClose(m_window, value);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setShouldClose");
  }

  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setTitle(std::string_view title) const {
    glfwSetWindowTitle(m_window, title.data());
  #else
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setTitle(char const *title) const {
    glfwSetWindowTitle(m_window, title);
  #endif
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setTitle");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::getPos(int *xpos, int *ypos) const {
    glfwGetWindowPos(m_window, xpos, ypos);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::getPos");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<int, int>>::type
  Window::getPos() const {
    std::tuple<int, int> output;
    glfwGetWindowPos(m_window, &std::get<0>(output), &std::get<1>(output));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getPos");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type Window::getPosX() const {
    int output;
    glfwGetWindowPos(m_window, &output, nullptr);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getPosX");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type Window::getPosY() const {
    int output;
    glfwGetWindowPos(m_window, nullptr, &output);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getPosY");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setPos(int xpos, int ypos) const {
    glfwSetWindowPos(m_window, xpos, ypos);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setPos");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setPos(std::tuple<int, int> pos) const {
    glfwSetWindowPos(m_window, std::get<0>(pos), std::get<1>(pos));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setPos");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::getSize(size_t *width, size_t *height) const {
    int temp_width, temp_height;
    glfwGetWindowSize(m_window, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      *width = temp_width;
      *height = temp_height;
    } else {
      *width = 0u;
      *height = 0u;
    }
    return createResultValue(result, VKFW_NAMESPACE_STRING "::Window::getSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<size_t, size_t>>::type
  Window::getSize() const {
    std::tuple<size_t, size_t> output;
    int temp_width, temp_height;
    glfwGetWindowSize(m_window, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      std::get<0>(output) = temp_width;
      std::get<1>(output) = temp_height;
    } else {
      std::get<0>(output) = 0u;
      std::get<1>(output) = 0u;
    }
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Window::getSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type Window::getWidth() const {
    size_t output;
    int temp;
    glfwGetWindowSize(m_window, &temp, nullptr);
    Result result = getError();
    if (check(result))
      output = static_cast<size_t>(temp);
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Window::getWidth");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type Window::getHeight() const {
    size_t output;
    int temp;
    glfwGetWindowSize(m_window, nullptr, &temp);
    Result result = getError();
    if (check(result))
      output = static_cast<size_t>(temp);
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Window::getHeight");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setSize(size_t width, size_t height) const {
    glfwSetWindowSize(m_window, static_cast<int>(width), static_cast<int>(height));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setSize");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setSize(std::tuple<size_t, size_t> size) const {
    glfwSetWindowSize(m_window, static_cast<int>(std::get<0>(size)),
                      static_cast<int>(std::get<1>(size)));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setSize");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setSizeLimits(size_t minimum_width, size_t minimum_height, size_t maximum_width,
                        size_t maximum_height) const {
    glfwSetWindowSizeLimits(m_window, static_cast<int>(minimum_width),
                            static_cast<int>(minimum_height), static_cast<int>(maximum_width),
                            static_cast<int>(maximum_height));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setSizeLimits");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setSizeLimits(std::tuple<size_t, size_t> minimum_size,
                        std::tuple<size_t, size_t> maximum_size) const {
    glfwSetWindowSizeLimits(m_window, static_cast<int>(std::get<0>(minimum_size)),
                            static_cast<int>(std::get<1>(minimum_size)),
                            static_cast<int>(std::get<0>(maximum_size)),
                            static_cast<int>(std::get<1>(maximum_size)));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setSizeLimits");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setSizeLimits(std::tuple<size_t, size_t, size_t, size_t> limits) const {
    glfwSetWindowSizeLimits(m_window, static_cast<int>(std::get<0>(limits)),
                            static_cast<int>(std::get<1>(limits)),
                            static_cast<int>(std::get<2>(limits)),
                            static_cast<int>(std::get<3>(limits)));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setSizeLimits");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setAspectRatio(size_t numerator, size_t denominator) const {
    glfwSetWindowAspectRatio(m_window, static_cast<int>(numerator), static_cast<int>(denominator));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setAspectRatio");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::getFramebufferSize(size_t *width, size_t *height) const {
    int temp_width, temp_height;
    glfwGetFramebufferSize(m_window, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      *width = temp_width;
      *height = temp_height;
    } else {
      *width = 0u;
      *height = 0u;
    }
    return createResultValue(result, VKFW_NAMESPACE_STRING "::Window::getFramebufferSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<size_t, size_t>>::type
  Window::getFramebufferSize() const {
    std::tuple<size_t, size_t> output;
    int temp_width, temp_height;
    glfwGetFramebufferSize(m_window, &temp_width, &temp_height);
    Result result = getError();
    if (check(result)) {
      std::get<0>(output) = temp_width;
      std::get<1>(output) = temp_height;
    } else {
      std::get<0>(output) = 0u;
      std::get<1>(output) = 0u;
    }
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Window::getFramebufferSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type
  Window::getFramebufferWidth() const {
    size_t output;
    int temp;
    glfwGetFramebufferSize(m_window, &temp, nullptr);
    Result result = getError();
    if (check(result))
      output = static_cast<size_t>(temp);
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Window::getFramebufferWidth");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type
  Window::getFramebufferHeight() const {
    size_t output;
    int temp;
    glfwGetFramebufferSize(m_window, nullptr, &temp);
    Result result = getError();
    if (check(result))
      output = static_cast<size_t>(temp);
    else
      output = 0u;
    return createResultValue(result, output,
                             VKFW_NAMESPACE_STRING "::Window::getFramebufferHeight");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::getFrameSize(size_t *left, size_t *top, size_t *right, size_t *bottom) const {
    int temp_left, temp_top, temp_right, temp_bottom;
    glfwGetWindowFrameSize(m_window, &temp_left, &temp_top, &temp_right, &temp_bottom);
    Result result = getError();
    if (check(result)) {
      *left = temp_left;
      *top = temp_top;
      *right = temp_right;
      *bottom = temp_bottom;
    } else {
      *left = 0u;
      *top = 0u;
      *right = 0u;
      *bottom = 0u;
    }
    return createResultValue(result, VKFW_NAMESPACE_STRING "::Window::getFrameSize");
  }
  VKFW_NODISCARD VKFW_INLINE
    typename ResultValueType<std::tuple<size_t, size_t, size_t, size_t>>::type
    Window::getFrameSize() const {
    std::tuple<size_t, size_t, size_t, size_t> output;
    int temp_left, temp_top, temp_right, temp_bottom;
    glfwGetWindowFrameSize(m_window, &temp_left, &temp_top, &temp_right, &temp_bottom);
    Result result = getError();
    if (check(result)) {
      std::get<0>(output) = temp_left;
      std::get<1>(output) = temp_top;
      std::get<2>(output) = temp_right;
      std::get<3>(output) = temp_bottom;
    } else {
      std::get<0>(output) = 0u;
      std::get<1>(output) = 0u;
      std::get<2>(output) = 0u;
      std::get<3>(output) = 0u;
    }
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Window::getFrameSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type
  Window::getLeftFrameSize() const {
    size_t output;
    int temp;
    glfwGetWindowFrameSize(m_window, &temp, nullptr, nullptr, nullptr);
    Result result = getError();
    if (check(result))
      output = temp;
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Window::getLeftFrameSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type
  Window::getTopFrameSize() const {
    size_t output;
    int temp;
    glfwGetWindowFrameSize(m_window, nullptr, &temp, nullptr, nullptr);
    Result result = getError();
    if (check(result))
      output = temp;
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Window::getTopFrameSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type
  Window::getRightFrameSize() const {
    size_t output;
    int temp;
    glfwGetWindowFrameSize(m_window, nullptr, nullptr, &temp, nullptr);
    Result result = getError();
    if (check(result))
      output = temp;
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Window::getRightFrameSize");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<size_t>::type
  Window::getBottomFrameSize() const {
    size_t output;
    int temp;
    glfwGetWindowFrameSize(m_window, nullptr, nullptr, nullptr, &temp);
    Result result = getError();
    if (check(result))
      output = temp;
    else
      output = 0u;
    return createResultValue(result, output, VKFW_NAMESPACE_STRING "::Window::getBottomFrameSize");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::getContentScale(float *xscale, float *yscale) const {
    glfwGetWindowContentScale(m_window, xscale, yscale);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::getContentScale");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<float, float>>::type
  Window::getContentScale() const {
    std::tuple<float, float> output;
    glfwGetWindowContentScale(m_window, &std::get<0>(output), &std::get<1>(output));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getContentScale");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<float>::type
  Window::getContentScaleX() const {
    float output;
    glfwGetWindowContentScale(m_window, &output, nullptr);
    return createResultValue(getError(), output,
                             VKFW_NAMESPACE_STRING "::Window::getContentScaleX");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<float>::type
  Window::getContentScaleY() const {
    float output;
    glfwGetWindowContentScale(m_window, nullptr, &output);
    return createResultValue(getError(), output,
                             VKFW_NAMESPACE_STRING "::Window::getContentScaleY");
  }

  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<float>::type Window::getOpacity() const {
    auto output = glfwGetWindowOpacity(m_window);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getOpacity");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setOpacity(float opacity) const {
    glfwSetWindowOpacity(m_window, opacity);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setOpacity");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::iconify() const {
    glfwIconifyWindow(m_window);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::iconify");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::restore() const {
    glfwRestoreWindow(m_window);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::restore");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::maximize() const {
    glfwMaximizeWindow(m_window);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::maximize");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::show() const {
    glfwShowWindow(m_window);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::show");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::hide() const {
    glfwHideWindow(m_window);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::hide");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::focus() const {
    glfwFocusWindow(m_window);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::focus");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::requestAttention() const {
    glfwRequestWindowAttention(m_window);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::requestAttention");
  }

  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<Monitor>::type Window::getMonitor() const {
    Monitor output = glfwGetWindowMonitor(m_window);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getMonitor");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setMonitor(Monitor const &monitor, int xpos, int ypos, size_t width, size_t height,
                     size_t refreshRate) const {
    glfwSetWindowMonitor(m_window, monitor, xpos, ypos, static_cast<int>(width),
                         static_cast<int>(height), static_cast<int>(refreshRate));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setMonitor");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setMonitor(Monitor const &monitor, std::tuple<int, int> pos,
                     std::tuple<size_t, size_t> size, size_t refreshRate) const {
    glfwSetWindowMonitor(m_window, monitor, std::get<0>(pos), std::get<1>(pos),
                         static_cast<int>(std::get<0>(size)), static_cast<int>(std::get<1>(size)),
                         static_cast<int>(refreshRate));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setMonitor");
  }

  template <Attribute attribute>
  VKFW_NODISCARD VKFW_INLINE
    typename ResultValueType<typename AttributeTraits<attribute>::type>::type
    Window::get() const {
    auto output = static_cast<typename AttributeTraits<attribute>::type>(
      glfwGetWindowAttrib(m_window, static_cast<int>(attribute)));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::get");
  }
  template <Attribute attribute, typename>
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::set(typename AttributeTraits<attribute>::type const &new_value) const {
    glfwSetWindowAttrib(m_window, static_cast<int>(attribute), static_cast<int>(new_value));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::set");
  }

  template <InputMode mode>
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<typename InputModeTraits<mode>::type>::type
  Window::get() const {
    auto output = static_cast<typename InputModeTraits<mode>::type>(
      glfwGetInputMode(m_window, static_cast<int>(mode)));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::get");
  }

  template <InputMode mode>
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::set(typename InputModeTraits<mode>::type const &new_value) const {
    glfwSetInputMode(m_window, static_cast<int>(mode), static_cast<int>(new_value));
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::set");
  }

  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<void *>::type Window::getUserPointer() const {
  #ifdef VKFW_NO_STD_FUNCTION_CALLBACKS
    auto *output = glfwGetWindowUserPointer(m_window);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getUserPointer");
  #else
    auto *output = callbacks()->user_ptr;
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getUserPointer");
  #endif
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setUserPointer(void *pointer) const {
  #ifdef VKFW_NO_STD_FUNCTION_CALLBACKS
    glfwSetWindowUserPointer(m_window, pointer);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setUserPointer");
  #else
    callbacks()->user_ptr = pointer;
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setUserPointer");
  #endif
  }

  #ifdef VKFW_HAS_SPAN
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setIcon(std::span<vkfw::Image> images) const {
    glfwSetWindowIcon(m_window, static_cast<int>(images.size()), images.data());
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setIcon");
  }
  #endif
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setIcon(std::vector<vkfw::Image> images) const {
    glfwSetWindowIcon(m_window, static_cast<int>(images.size()), images.data());
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setIcon");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setIcon(size_t image_count, vkfw::Image *images) const {
    glfwSetWindowIcon(m_window, static_cast<int>(image_count), images);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setIcon");
  }

  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<bool>::type Window::getKey(Key key) const {
    bool output = glfwGetKey(m_window, static_cast<int>(key))
               == static_cast<int>(KeyAction::VKFW_ENUMERATOR(Press));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getKey");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<bool>::type
  Window::getMouseButton(MouseButton button) const {
    bool output = glfwGetMouseButton(m_window, static_cast<int>(button))
               == static_cast<int>(MouseButtonAction::VKFW_ENUMERATOR(Press));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getMouseButton");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::getCursorPos(double *xpos, double *ypos) const {
    glfwGetCursorPos(m_window, xpos, ypos);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::getCursorPos");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<double, double>>::type
  Window::getCursorPos() const {
    std::tuple<double, double> output;
    glfwGetCursorPos(m_window, &std::get<0>(output), &std::get<1>(output));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getCursorPos");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<double>::type Window::getCursorPosX() const {
    double output;
    glfwGetCursorPos(m_window, &output, nullptr);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getCursorPosX");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<double>::type Window::getCursorPosY() const {
    double output;
    glfwGetCursorPos(m_window, nullptr, &output);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::Window::getCursorPosY");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setCursorPos(double xpos, double ypos) const {
    glfwSetCursorPos(m_window, xpos, ypos);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setCursorPos");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::setCursor(Cursor const &cursor) const {
    glfwSetCursor(m_window, cursor);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::setCursorPos");
  }

  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::makeContextCurrent() const {
    glfwMakeContextCurrent(m_window);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::makeContextCurrent");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  Window::swapBuffers() const {
    glfwSwapBuffers(m_window);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::Window::swapBuffers");
  }
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_INLINE void pollEvents() { glfwPollEvents(); }
  VKFW_INLINE void waitEvents() { glfwWaitEvents(); }
  VKFW_INLINE void waitEventsTimeout(double timeout) { glfwWaitEventsTimeout(timeout); }
  VKFW_INLINE void postEmptyEvent() { glfwPostEmptyEvent(); }

  VKFW_INLINE void makeContextCurrent(GLFWwindow *window) { glfwMakeContextCurrent(window); }
  VKFW_NODISCARD VKFW_INLINE GLFWwindow *getCurrentContext() { return glfwGetCurrentContext(); }
  VKFW_INLINE void swapBuffers(GLFWwindow *window) { glfwSwapBuffers(window); }
  VKFW_INLINE void swapInterval(int interval) { glfwSwapInterval(interval); }

  VKFW_NODISCARD VKFW_INLINE bool rawMouseMotionSupported() {
    return static_cast<bool>(glfwRawMouseMotionSupported());
  }

  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD VKFW_INLINE std::string_view getKeyName(Key key, int scancode) {
    char const *tmp = glfwGetKeyName(static_cast<int>(key), scancode);
    return tmp ? std::string_view(tmp) : std::string_view();
  }
  #else
  VKFW_NODISCARD VKFW_INLINE char const *getKeyName(Key key, int scancode) {
    return glfwGetKeyName(static_cast<int>(key), scancode);
  }
  #endif
  VKFW_NODISCARD VKFW_INLINE int getKeyScancode(Key key) {
    return glfwGetKeyScancode(static_cast<int>(key));
  }
#else
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type pollEvents() {
    glfwPollEvents();
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::pollEvents");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type waitEvents() {
    glfwWaitEvents();
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::waitEvents");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  waitEventsTimeout(double timeout) {
    glfwWaitEventsTimeout(timeout);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::waitEventsTimeout");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  waitEventsTimeout(std::chrono::duration<double> timeout) {
    glfwWaitEventsTimeout(timeout.count());
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::waitEventsTimeout");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  postEmptyEvent() {
    glfwPostEmptyEvent();
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::postEmptyEvent");
  }

  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<Window>::type getCurrentContext() {
    Window output = glfwGetCurrentContext();
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::getCurrentContext");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  swapInterval(int interval) {
    glfwSwapInterval(interval);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::swapInterval");
  }

  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<bool>::type rawMouseMotionSupported() {
    bool output = static_cast<bool>(glfwRawMouseMotionSupported());
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::rawMouseMotionSupported");
  }

  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::string_view>::type
  getKeyName(Key key, int32_t scancode) {
    char const *tmp = glfwGetKeyName(static_cast<int>(key), static_cast<int>(scancode));
    std::string_view output;
    if (tmp)
      output = tmp;
  #else
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<char const *>::type
  getKeyName(Key key, int32_t scancode) {
    char const *output = glfwGetKeyName(static_cast<int>(key), static_cast<int>(scancode));
  #endif
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::rawMouseMotionSupported");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type getKeyScancode(Key key) {
    int32_t output = static_cast<int32_t>(glfwGetKeyScancode(static_cast<int>(key)));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::rawMouseMotionSupported");
  }
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  VKFW_NODISCARD VKFW_INLINE GLFWcursor *createCursor(vkfw::Image const *image, int xhot,
                                                      int yhot) {
    return glfwCreateCursor(image, xhot, yhot);
  }
  VKFW_NODISCARD VKFW_INLINE GLFWcursor *createStandardCursor(CursorShape shape) {
    return glfwCreateStandardCursor(static_cast<int>(shape));
  }
  VKFW_NODISCARD VKFW_INLINE Result destroyCursor(GLFWcursor *cursor) {
    glfwDestroyCursor(cursor);
    return getError();
  }
#else
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<Cursor>::type
  createCursor(vkfw::Image const &image, int xhot, int yhot) {
    Cursor output = glfwCreateCursor(&image, xhot, yhot);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::createCursor");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<Cursor>::type
  createStandardCursor(CursorShape shape) {
    Cursor output = glfwCreateStandardCursor(static_cast<int>(shape));
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::createStandardCursor");
  }
  #ifndef VKFW_NO_SMART_HANDLE
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<UniqueCursor>::type
  createCursorUnique(vkfw::Image const &image, int xhot, int yhot) {
    Cursor output = glfwCreateCursor(&image, xhot, yhot);
    return createResultValueUnique(getError(), output,
                                   VKFW_NAMESPACE_STRING "::createCursorUnique");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<UniqueCursor>::type
  createStandardCursorUnique(CursorShape shape) {
    Cursor output = glfwCreateStandardCursor(static_cast<int>(shape));
    return createResultValueUnique(getError(), output,
                                   VKFW_NAMESPACE_STRING "::createStandardCursorUnique");
  }
  #endif
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_INLINE void setClipboardString(std::string_view string) {
    glfwSetClipboardString(nullptr, string.data());
  }
  VKFW_INLINE std::string_view getClipboardString() {
    char const *tmp = glfwGetClipboardString(nullptr);
    return tmp ? std::string_view(tmp) : std::string_view();
  }
  #else
  VKFW_INLINE void setClipboardString(char const *string) {
    glfwSetClipboardString(nullptr, string);
  }
  VKFW_INLINE char const *getClipboardString() { return glfwGetClipboardString(nullptr); }
  #endif

  VKFW_INLINE double getTime() { return glfwGetTime(); }
  VKFW_INLINE void setTime(double time) { glfwSetTime(time); }
  VKFW_INLINE uint64_t getTimerValue() { return glfwGetTimerValue(); }
  VKFW_INLINE uint64_t getTimerFrequency() { return glfwGetTimerFrequency(); }
#else
  #ifdef VKFW_HAS_STRING_VIEW
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  setClipboardString(std::string_view string) {
    glfwSetClipboardString(nullptr, string.data());
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::setClipboardString");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::string_view>::type getClipboardString() {
    char const *tmp = glfwGetClipboardString(nullptr);
    std::string_view output;
    if (tmp)
      output = tmp;
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::getClipboardString");
  }
  #else
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  setClipboardString(char const *string) {
    glfwSetClipboardString(nullptr, string);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::setClipboardString");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<char const *>::type getClipboardString() {
    char const *output = glfwGetClipboardString(nullptr);
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::getClipboardString");
  }
  #endif

  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<double>::type getTime() {
    double output = glfwGetTime();
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::getTime");
  }
  VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
  setTime(double time) {
    glfwSetTime(time);
    return createResultValue(getError(), VKFW_NAMESPACE_STRING "::setTime");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<uint64_t>::type getTimerValue() {
    uint64_t output = glfwGetTimerValue();
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::getTimerValue");
  }
  VKFW_NODISCARD VKFW_INLINE typename ResultValueType<uint64_t>::type getTimerFrequency() {
    uint64_t output = glfwGetTimerFrequency();
    return createResultValue(getError(), output, VKFW_NAMESPACE_STRING "::getTimerFrequency");
  }
#endif
} // namespace VKFW_NAMESPACE

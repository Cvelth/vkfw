#pragma once
// Copyright (c) 2020 Cvelth.
//
// SPDX-License-Identifier: Apache-2.0
//

#ifdef _MSVC_LANG
# define VKFW_CPLUSPLUS _MSVC_LANG
#else
# define VKFW_CPLUSPLUS __cplusplus
#endif

#if 201703L < VKFW_CPLUSPLUS
# define VKFW_CPP_VERSION 20
#elif 201402L < VKFW_CPLUSPLUS
# define VKFW_CPP_VERSION 17
#elif 201103L < VKFW_CPLUSPLUS
# define VKFW_CPP_VERSION 14
#elif 199711L < VKFW_CPLUSPLUS
# define VKFW_CPP_VERSION 11
#else
# error "vkfw.hpp needs at least c++ standard version 11"
#endif

#ifndef VKFW_INCLUDE_GL
# define GLFW_INCLUDE_NONE
#endif
#ifndef VKFW_NO_INCLUDE_VULKAN
# define GLFW_INCLUDE_VULKAN
#endif

#if defined(VKFW_NO_STRUCT_CONSTRUCTORS) && !defined(VULKAN_HPP_NO_STRUCT_CONSTRUCTORS)
# define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS VKFW_NO_STRUCT_CONSTRUCTORS
#endif
#if defined(VKFW_NO_EXCEPTIONS) && !defined(VULKAN_HPP_NO_EXCEPTIONS)
# define VULKAN_HPP_NO_EXCEPTIONS VKFW_NO_EXCEPTIONS
#endif
#if defined(VKFW_NO_NODISCARD_WARNINGS) && !defined(VULKAN_HPP_NO_NODISCARD_WARNINGS)
# define VULKAN_HPP_NO_NODISCARD_WARNINGS VKFW_NO_NODISCARD_WARNINGS
#endif
#if defined(VKFW_ASSERT) && !defined(VULKAN_HPP_ASSERT)
# define VULKAN_HPP_ASSERT VKFW_ASSERT
#endif
#if defined(VKFW_ASSERT_ON_RESULT) && !defined(VULKAN_HPP_ASSERT_ON_RESULT)
# define VULKAN_HPP_ASSERT_ON_RESULT VKFW_ASSERT_ON_RESULT
#endif
#if defined(VKFW_DISABLE_ENHANCED_MODE) && !defined(VULKAN_HPP_DISABLE_ENHANCED_MODE)
# define VULKAN_HPP_DISABLE_ENHANCED_MODE VKFW_DISABLE_ENHANCED_MODE
#endif
#if defined(VKFW_HPP_INLINE) && !defined(VULKAN_HPP_INLINE)
# define VULKAN_HPP_INLINE VKFW_HPP_INLINE
#endif
#if defined(VKFW_NO_SMART_HANDLE) && !defined(VULKAN_HPP_NO_SMART_HANDLE)
# define VULKAN_HPP_NO_SMART_HANDLE VKFW_NO_SMART_HANDLE
#endif

// Standard library includes go here!
#include <string>
#include <system_error>
#include <tuple>

#include <GLFW/glfw3.h>
//#ifndef VKFW_NO_INCLUDE_VULKAN_HPP
# include <vulkan/vulkan.hpp>
//#endif

#if 20 <= VKFW_CPP_VERSION && defined(__has_include) && __has_include( <version> )
# include <version>
#endif

#if 17 <= VKFW_CPP_VERSION
# include <string_view>
# define VKFW_HAS_STRING_VIEW
#endif
#if 20 <= VKFW_CPP_VERSION && defined(__cpp_lib_span) && defined(__has_include) && 202002L <= __cpp_lib_span && __has_include( <span> )
# include <span>
# define VKFW_HAS_SPAN
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
# ifndef VKFW_NO_SMART_HANDLE
#   define VKFW_NO_SMART_HANDLE
# endif
#else
# include <algorithm>
# include <iterator>
# include <memory>
# include <vector>
#endif

#ifndef VKFW_ASSERT
# include <cassert>
# define VKFW_ASSERT assert
#endif

#ifndef VKFW_ASSERT_ON_RESULT
# define VKFW_ASSERT_ON_RESULT VKFW_ASSERT
#endif

#define VKFW_VERSION_MAJOR 0
#define VKFW_VERSION_MINOR 3
#define VKFW_VERSION_PATCH 0
static_assert(GLFW_VERSION_MAJOR == 3
			  && GLFW_VERSION_MINOR == 3
			  && GLFW_VERSION_REVISION == 2
			  , "\"glfw3.h\" version is not compatible with the \"vkfw.hpp\" version!");

#ifndef VKFW_INLINE
# ifdef __clang__
#   if __has_attribute(always_inline)
#     define VKFW_INLINE __attribute__((always_inline)) __inline__
#   else
#     define VKFW_INLINE inline
#   endif
# elifdef __GNUC__
#   define VKFW_INLINE __attribute__((always_inline)) __inline__
# elifdef _MSC_VER
#   define VKFW_INLINE inline
# else
#   define VKFW_INLINE inline
# endif
#endif

//#ifdef VKFW_TYPESAFE_CONVERSION
//# define VKFW_TYPESAFE_EXPLICIT
//#else
//# define VKFW_TYPESAFE_EXPLICIT explicit
//#endif

#ifdef __cpp_constexpr
# define VKFW_CONSTEXPR constexpr
# if __cpp_constexpr >= 201304
#   define VKFW_CONSTEXPR_14 constexpr
# else
#   define VKFW_CONSTEXPR_14
# endif
# define VKFW_CONST_OR_CONSTEXPR constexpr
#else
# define VKFW_CONSTEXPR
# define VKFW_CONSTEXPR_14
# define VKFW_CONST_OR_CONSTEXPR const
#endif

#ifndef VKFW_NOEXCEPT
# if defined(_MSC_VER) && (_MSC_VER <= 1800)
#   define VKFW_NOEXCEPT
# else
#   define VKFW_NOEXCEPT noexcept
#   define VKFW_HAS_NOEXCEPT 1
# endif
#endif

#if 14 <= VKFW_CPP_VERSION
# define VKFW_DEPRECATED( msg ) [[deprecated( msg )]]
#else
# define VKFW_DEPRECATED( msg )
#endif

#if ( 17 <= VKFW_CPP_VERSION ) && !defined( VKFW_NO_NODISCARD_WARNINGS )
# define VKFW_NODISCARD [[nodiscard]]
# ifdef VKFW_NO_EXCEPTIONS
#   define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS [[nodiscard]]
# else
#   define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS
# endif
#else
# define VKFW_NODISCARD
# define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS
#endif

#ifndef VKFW_NAMESPACE
#define VKFW_NAMESPACE vkfw
#endif

#define VKFW_STRINGIFY2(text) #text
#define VKFW_STRINGIFY(text) VKFW_STRINGIFY2(text)
#define VKFW_NAMESPACE_STRING VKFW_STRINGIFY(VKFW_NAMESPACE)

#ifdef VKFW_NO_LEADING_e_IN_ENUMS
# define VKFW_ENUMERATOR(name) name
# define VKFW_ENUMERATOR2(name_1, name_2) name_2
#else
# define VKFW_ENUMERATOR(name) e ## name
# define VKFW_ENUMERATOR2(name_1, name_2) e ## name_1
#endif

#if defined(VULKAN_HPP_HAS_SPACESHIP_OPERATOR) && !defined(VKFW_HAS_SPACESHIP_OPERATOR)
# define VKFW_HAS_SPACESHIP_OPERATOR VULKAN_HPP_HAS_SPACESHIP_OPERATOR
#endif

namespace VKFW_NAMESPACE {
	template <typename BitType> using Flags
		= VULKAN_HPP_NAMESPACE::Flags<BitType>;
	template <typename FlagBitsType> using FlagTraits
		= VULKAN_HPP_NAMESPACE::FlagTraits<FlagBitsType>;

	enum class Boolean {
		VKFW_ENUMERATOR(True) = GLFW_TRUE,
		VKFW_ENUMERATOR(False) = GLFW_FALSE
	};
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
		VKFW_ENUMERATOR(Apostrophe) = GLFW_KEY_APOSTROPHE,		/* ' */
		VKFW_ENUMERATOR(Comma) = GLFW_KEY_COMMA,				/* , */
		VKFW_ENUMERATOR(Minus) = GLFW_KEY_MINUS,				/* - */
		VKFW_ENUMERATOR(Period) = GLFW_KEY_PERIOD,				/* . */
		VKFW_ENUMERATOR(Slash) = GLFW_KEY_SLASH,				/* / */
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
		VKFW_ENUMERATOR(Semicolon) = GLFW_KEY_SEMICOLON,		/* ; */
		VKFW_ENUMERATOR(Equal) = GLFW_KEY_EQUAL,				/* = */
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
		VKFW_ENUMERATOR(LeftBracket) = GLFW_KEY_LEFT_BRACKET,	/* [ */
		VKFW_ENUMERATOR(Backslash) = GLFW_KEY_BACKSLASH,		/* \ */
		VKFW_ENUMERATOR(RightBracket) = GLFW_KEY_RIGHT_BRACKET,	/* ] */
		VKFW_ENUMERATOR(GraveAccent) = GLFW_KEY_GRAVE_ACCENT,	/* ` */
		VKFW_ENUMERATOR(World1) = GLFW_KEY_WORLD_1,				/* non-US #1 */
		VKFW_ENUMERATOR(World2) = GLFW_KEY_WORLD_2,				/* non-US #2 */

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
	VKFW_INLINE VKFW_CONSTEXPR bool check(Result result) { return result == Result::VKFW_ENUMERATOR(Success); }
	enum class InitializationHint {
		VKFW_ENUMERATOR(JoystickHatButtons) = GLFW_JOYSTICK_HAT_BUTTONS,
		VKFW_ENUMERATOR(CocoaChdirResources) = GLFW_COCOA_CHDIR_RESOURCES, // MacOS specific
		VKFW_ENUMERATOR(CocoaMenubar) = GLFW_COCOA_MENUBAR // MacOS specific
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
		//VKFW_ENUMERATOR(ContextRevision) = GLFW_CONTEXT_REVISION,
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
		VKFW_ENUMERATOR(DoubleBuffer) = GLFW_DOUBLEBUFFER,
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
	enum class Unknown {
		VKFW_ENUMERATOR(Cursor) = GLFW_CURSOR,
		VKFW_ENUMERATOR(StickyKeys) = GLFW_STICKY_KEYS,
		VKFW_ENUMERATOR(StickyMouseButtons) = GLFW_STICKY_MOUSE_BUTTONS,
		VKFW_ENUMERATOR(LockKeyModifiers) = GLFW_LOCK_KEY_MODS,
		VKFW_ENUMERATOR(RawMouseMotion) = GLFW_RAW_MOUSE_MOTION
	};
	enum class CursorVisibility {
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
		, eDontCare = unsigned(GLFW_DONT_CARE)
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
	using ModifierKeyFlags = Flags<ModifierKeyBits>;
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

				/* Printable Keys */
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

				/* Function Keys */
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
			case MouseButton::VKFW_ENUMERATOR2(1, _1):	return "1 (left)";
			case MouseButton::VKFW_ENUMERATOR2(2, _2):return "2 (right)";
			case MouseButton::VKFW_ENUMERATOR2(3, _3):return "3 (middle)";
			case MouseButton::VKFW_ENUMERATOR2(4, _4):return "4";
			case MouseButton::VKFW_ENUMERATOR2(5, _5):return "5";
			case MouseButton::VKFW_ENUMERATOR2(6, _6):	return "6";
			case MouseButton::VKFW_ENUMERATOR2(7, _7):	return "7";
			case MouseButton::VKFW_ENUMERATOR2(8, _8):	return "8";
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
			case Result::VKFW_ENUMERATOR(NoCurrentContext):
				return "No context is current for this thread";
			case Result::VKFW_ENUMERATOR(InvalidEnum):
				return "One of the arguments to the function was an invalid enum value";
			case Result::VKFW_ENUMERATOR(InvalidValue):
				return "One of the arguments to the function was an invalid value";
			case Result::VKFW_ENUMERATOR(OutOfMemory):
				return "A memory allocation failed";
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
		if (!value) return "{}";
		std::string output;

		if (value & ModifierKeyBits::VKFW_ENUMERATOR(CapsLock)) output += "CapsLock | ";
		if (value & ModifierKeyBits::VKFW_ENUMERATOR(NumLock)) output += "NumLock | ";

		if (value & ModifierKeyBits::VKFW_ENUMERATOR(Control)) output += "Control + ";
		if (value & ModifierKeyBits::VKFW_ENUMERATOR(Alt)) output += "Alt + ";
		if (value & ModifierKeyBits::VKFW_ENUMERATOR(Super)) output += "Super + ";

		return "{ " + output.substr(0, output.size() - 3) + " }";
	}
}

namespace VKFW_NAMESPACE {
#ifndef VKFW_NO_SMART_HANDLE
	template <typename Type> using UniqueHandleTraits
		= VULKAN_HPP_NAMESPACE::UniqueHandleTraits<Type, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE>;
	template <typename Type> using UniqueHandle
		= VULKAN_HPP_NAMESPACE::UniqueHandle<Type, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE>;
#endif
	//template <typename Type> struct isHandleType {
	//	static VKFW_CONST_OR_CONSTEXPR bool value = false;
	//};
}

#ifndef VKFW_NO_EXCEPTIONS
namespace std {
	template <>
	struct is_error_code_enum<VKFW_NAMESPACE::Result> : public true_type {};
}
#endif

namespace VKFW_NAMESPACE {
#ifndef VKFW_NO_EXCEPTIONS
	class ErrorCategoryImpl : public std::error_category {
	public:
		virtual char const *name() const VKFW_NOEXCEPT override {
			return VKFW_NAMESPACE_STRING"::Result";
		}
		virtual std::string message(int ev) const override { return to_string(static_cast<Result>(ev)); }
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
		SystemError(std::error_code ec)
			: Error(), std::system_error(ec) {}
		SystemError(std::error_code ec, std::string const &what)
			: Error(), std::system_error(ec, what) {}
		SystemError(std::error_code ec, char const *what)
			: Error(), std::system_error(ec, what) {}
		SystemError(int ev, std::error_category const &ecat)
			: Error(), std::system_error(ev, ecat) {}
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
			: result(r), value(std::move(v)) {}

		Result result;
		T value;

		operator std::tuple<Result &, T &>() VKFW_NOEXCEPT {
			return std::tuple<Result &, T &>(result, value);
		}
	};

#ifndef VKFW_NO_SMART_HANDLE
	template <typename Type> struct ResultValue<UniqueHandle<Type>> {
# ifdef VKFW_HAS_NOEXCEPT
		ResultValue(Result r, UniqueHandle<Type> &&v) VKFW_NOEXCEPT
# else
		ResultValue(Result r, UniqueHandle<Type> &&v)
# endif
			: result(r), value(std::move(v)) {}

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
		if (!check(result)) throwResultException(result, message);
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
		if (!check(result)) throwResultException(result, message);
		return std::move(data);
#endif
	}
#ifndef VKFW_NO_SMART_HANDLE
	template <typename T>
	VKFW_INLINE typename ResultValueType<UniqueHandle<T>>::type
		createResultValueUnique(Result result, T &data, char const *message) {
# ifdef VKFW_NO_EXCEPTIONS
		ignore(message);
		VKFW_ASSERT_ON_RESULT(result == Result::VKFW_ENUMERATOR(Success));
		return ResultValue<UniqueHandle<T>>(result, UniqueHandle<T>(data));
# else
		if (!check(result)) throwResultException(result, message);
		return UniqueHandle<T>(data);
# endif
	}
#endif
#ifndef VKFW_NO_SMART_HANDLE
	template<typename T>
	struct CustomDestroy {
		void destroy(T &t) { static_assert("Cannot delete an object without a specified deleter."); }
	};
#endif

	struct Nullopt {};
	VKFW_CONSTEXPR Nullopt nullopt = {};
	template <typename T>
	class Optional {
	public:
		using value_type = T;

		VKFW_INLINE VKFW_CONSTEXPR Optional() : m_has_value(false) {}
		VKFW_INLINE VKFW_CONSTEXPR Optional(Nullopt) : m_has_value(false) {}
		VKFW_INLINE VKFW_CONSTEXPR Optional(value_type const &t) : m_has_value(true), m_value(t) {}
		VKFW_INLINE VKFW_CONSTEXPR Optional(value_type &&t) : m_has_value(true), m_value(std::move(t)) {}
		template <typename convertible_value_type,
			typename = typename std::enable_if<std::is_convertible<convertible_value_type, value_type>::value>::type
		> VKFW_INLINE VKFW_CONSTEXPR Optional(convertible_value_type const &t) : m_has_value(true), m_value(value_type{ t }) {}
		template <typename convertible_value_type,
			typename = typename std::enable_if<std::is_convertible<convertible_value_type, value_type>::value>::type
		> VKFW_INLINE VKFW_CONSTEXPR Optional(convertible_value_type &&t) : m_has_value(true), m_value(value_type{ std::move(t) }) {}
		template<class U> VKFW_INLINE VKFW_CONSTEXPR Optional(Optional<U> const &another)
			: m_has_value(another.m_has_value), m_value(another.m_value) {}
		template<class U> VKFW_INLINE VKFW_CONSTEXPR Optional(Optional<U> &&another)
			: m_has_value(another.m_has_value), m_value(std::move(another.m_value)) {}
		VKFW_INLINE VKFW_CONSTEXPR Optional &operator=(Nullopt) { m_has_value = false; return *this; }
		template<class U> VKFW_INLINE VKFW_CONSTEXPR_14 Optional &operator=(Optional<U> const &another) {
			m_has_value = another.m_has_value;
			m_value = another.m_value;
			return *this;
		}
		template<class U> VKFW_INLINE VKFW_CONSTEXPR_14 Optional &operator=(Optional<U> &&another) {
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
		VKFW_INLINE VKFW_CONSTEXPR Instance(Instance const &another) VKFW_NOEXCEPT : m_state(another.m_state) {}
		VKFW_INLINE VKFW_CONSTEXPR_14 Instance(Instance &&another) VKFW_NOEXCEPT : m_state(another.m_state) { another.m_state = false; }
		VKFW_INLINE VKFW_CONSTEXPR_14 Instance operator=(Instance const &another) VKFW_NOEXCEPT {
			m_state = another.m_state; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Instance operator=(Instance &&another) VKFW_NOEXCEPT {
			m_state = another.m_state; another.m_state = false; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Instance &operator=(bool state) VKFW_NOEXCEPT {
			m_state = state; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Instance &operator=(std::nullptr_t) VKFW_NOEXCEPT {
			m_state = false; return *this;
		}
		VKFW_INLINE explicit operator bool() const VKFW_NOEXCEPT { return m_state; }
		VKFW_INLINE bool operator!() const VKFW_NOEXCEPT { return !m_state; }
# if defined(VKFW_HAS_SPACESHIP_OPERATOR)
		auto operator<=>(Instance const &) const = default;
# else
		bool operator==(Instance const &another) const VKFW_NOEXCEPT { return m_state == another.m_state; }
		bool operator!=(Instance const &another) const VKFW_NOEXCEPT { return !operator==(another); }
# endif
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
			: m_monitor(another.m_monitor) { another.m_monitor = nullptr; }
		VKFW_INLINE VKFW_CONSTEXPR_14 Monitor operator=(Monitor const &another) VKFW_NOEXCEPT {
			m_monitor = another.m_monitor; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Monitor operator=(Monitor &&another) VKFW_NOEXCEPT {
			m_monitor = another.m_monitor; another.m_monitor = nullptr; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Monitor &operator=(GLFWmonitor *monitor) VKFW_NOEXCEPT {
			m_monitor = monitor; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Monitor &operator=(std::nullptr_t) VKFW_NOEXCEPT {
			m_monitor = nullptr; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR operator GLFWmonitor *() const VKFW_NOEXCEPT { return m_monitor; }
		VKFW_INLINE VKFW_CONSTEXPR explicit operator bool() const VULKAN_HPP_NOEXCEPT { return m_monitor != nullptr; }
		VKFW_INLINE VKFW_CONSTEXPR bool operator!() const VULKAN_HPP_NOEXCEPT { return m_monitor == nullptr; }
# if defined(VKFW_HAS_SPACESHIP_OPERATOR)
		auto operator<=>(Monitor const &) const = default;
# else
		bool operator==(Monitor const &another) const VKFW_NOEXCEPT { return m_monitor == another.m_monitor; }
		bool operator!=(Monitor const &another) const VKFW_NOEXCEPT { return !operator==(another); }
# endif

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type getPos(int *xpos, int *ypos) const;
		VKFW_NODISCARD typename ResultValueType<std::tuple<int, int>>::type getPos() const;
		VKFW_NODISCARD typename ResultValueType<int>::type getPosX() const;
		VKFW_NODISCARD typename ResultValueType<int>::type getPosY() const;

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			getWorkarea(int *xpos, int *ypos, size_t *width, size_t *height) const;
		VKFW_NODISCARD typename ResultValueType<std::tuple<int, int, size_t, size_t>>::type getWorkarea() const;
		VKFW_NODISCARD typename ResultValueType<std::tuple<int, int>>::type getWorkareaPos() const;
		VKFW_NODISCARD typename ResultValueType<int>::type getWorkareaPosX() const;
		VKFW_NODISCARD typename ResultValueType<int>::type getWorkareaPosY() const;
		VKFW_NODISCARD typename ResultValueType<std::tuple<size_t, size_t>>::type getWorkareaSize() const;
		VKFW_NODISCARD typename ResultValueType<size_t>::type getWorkareaWidth() const;
		VKFW_NODISCARD typename ResultValueType<size_t>::type getWorkareaHeight() const;

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			getPhysicalSize(size_t *widthMM, size_t *heightMM) const;
		VKFW_NODISCARD typename ResultValueType<std::tuple<size_t, size_t>>::type getPhysicalSize() const;
		VKFW_NODISCARD typename ResultValueType<size_t>::type getPhysicalWidth() const;
		VKFW_NODISCARD typename ResultValueType<size_t>::type getPhysicalHeight() const;

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			getContentScale(float *xscale, float *yscale) const;
		VKFW_NODISCARD typename ResultValueType<std::tuple<float, float>>::type getContentScale() const;
		VKFW_NODISCARD typename ResultValueType<float>::type getContentScaleX() const;
		VKFW_NODISCARD typename ResultValueType<float>::type getContentScaleY() const;

# ifdef VKFW_HAS_STRING_VIEW
		VKFW_NODISCARD typename ResultValueType<std::string_view>::type getName() const;
# else
		VKFW_NODISCARD typename ResultValueType<char const *>::type getName() const;
# endif

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setUserPointer(void *pointer) const;
		VKFW_NODISCARD typename ResultValueType<void *>::type getUserPointer() const;

		VKFW_NODISCARD typename ResultValueType<GLFWvidmode const *>::type getVideoMode() const;
# ifdef VKFW_HAS_SPAN
		VKFW_NODISCARD typename ResultValueType<std::span<GLFWvidmode const>>::type getVideoModes() const;
# else
		VKFW_NODISCARD typename ResultValueType<std::vector<GLFWvidmode>>::type getVideoModes() const;
# endif

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type setGamma(float gamma) const;
		VKFW_NODISCARD typename ResultValueType<GLFWgammaramp const *>::type getGammaRamp() const;
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setGammaRamp(GLFWgammaramp const *ramp) const;

	private:
		GLFWmonitor *m_monitor;
	};

	class Window {
	public:
		using CType = GLFWwindow;
	public:
		VKFW_INLINE VKFW_CONSTEXPR Window() VKFW_NOEXCEPT : m_window(nullptr) {}
		VKFW_INLINE VKFW_CONSTEXPR Window(std::nullptr_t) VKFW_NOEXCEPT : m_window(nullptr) {}
		VKFW_INLINE VKFW_CONSTEXPR Window(GLFWwindow *window) VKFW_NOEXCEPT : m_window(window) {}
		VKFW_INLINE VKFW_CONSTEXPR Window(Window const &another) VKFW_NOEXCEPT : m_window(another.m_window) {}
		VKFW_INLINE VKFW_CONSTEXPR_14 Window(Window &&another) VKFW_NOEXCEPT : m_window(another.m_window) { another.m_window = nullptr; }
		VKFW_INLINE VKFW_CONSTEXPR_14 Window operator=(Window const &another) VKFW_NOEXCEPT {
			m_window = another.m_window; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Window operator=(Window &&another) VKFW_NOEXCEPT {
			m_window = another.m_window; another.m_window = nullptr; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Window &operator=(GLFWwindow *window) VKFW_NOEXCEPT {
			m_window = window; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Window &operator=(std::nullptr_t) VKFW_NOEXCEPT {
			m_window = nullptr; return *this;
		}

		VKFW_INLINE VKFW_CONSTEXPR operator GLFWwindow *() const VKFW_NOEXCEPT { return m_window; }
		VKFW_INLINE VKFW_CONSTEXPR explicit operator bool() const VULKAN_HPP_NOEXCEPT { return m_window != nullptr; }
		VKFW_INLINE VKFW_CONSTEXPR bool operator!() const VULKAN_HPP_NOEXCEPT { return m_window == nullptr; }
# if defined(VKFW_HAS_SPACESHIP_OPERATOR)
		auto operator<=>(Window const &) const = default;
# else
		bool operator==(Window const &another) const VKFW_NOEXCEPT { return m_window == another.m_window; }
		bool operator!=(Window const &another) const VKFW_NOEXCEPT { return !operator==(another); }
# endif
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type destroy();

		VKFW_NODISCARD typename ResultValueType<bool>::type shouldClose() const;
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setShouldClose(bool value) const;

# ifdef VKFW_HAS_STRING_VIEW
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setTitle(std::string_view title) const;
# else
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setTitle(char const *title) const;
# endif

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			getPos(int *xpos, int *ypos) const;
		VKFW_NODISCARD typename ResultValueType<std::tuple<int, int>>::type getPos() const;
		VKFW_NODISCARD typename ResultValueType<int>::type getPosX() const;
		VKFW_NODISCARD typename ResultValueType<int>::type getPosY() const;
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setPos(int xpos, int ypos) const;
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setPos(std::tuple<int, int> pos) const;

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			getSize(size_t *width, size_t *height) const;
		VKFW_NODISCARD typename ResultValueType<std::tuple<size_t, size_t>>::type getSize() const;
		VKFW_NODISCARD typename ResultValueType<size_t>::type getWidth() const;
		VKFW_NODISCARD typename ResultValueType<size_t>::type getHeight() const;
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setSize(size_t width, size_t height);
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setSize(std::tuple<size_t, size_t> size);

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setSizeLimits(size_t minimum_width, size_t minimum_height,
						  size_t maximum_width, size_t maximum_height);
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setSizeLimits(std::tuple<size_t, size_t> minimum_size,
						  std::tuple<size_t, size_t> maximum_size);
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setSizeLimits(std::tuple<size_t, size_t, size_t, size_t> limits);
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			setAspectRatio(size_t numerator, size_t denominator);

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			getFramebufferSize(size_t *width, size_t *height) const;
		VKFW_NODISCARD typename ResultValueType<std::tuple<size_t, size_t>>::type 
			getFramebufferSize() const;
		VKFW_NODISCARD typename ResultValueType<size_t>::type getFramebufferWidth() const;
		VKFW_NODISCARD typename ResultValueType<size_t>::type getFramebufferHeight() const;

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
			getFrameSize(size_t *left, size_t *top,
						 size_t *right, size_t *bottom);
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
			setOpacity(float opacity);

		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type iconify();
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type restore();
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type maximize();
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type show();
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type hide();
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type focus();
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type requestAttention();
		VKFW_NODISCARD typename ResultValueType<Monitor>::type getMonitor();
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type 
			setMonitor(Monitor const &monitor, int xpos, int ypos,
					   size_t width, size_t height, size_t refreshRate);
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type 
			setMonitor(Monitor const &monitor, std::tuple<int, int> pos,
					   std::tuple<size_t, size_t> size, size_t refreshRate);

	private:
		GLFWwindow *m_window;
	};

	class Cursor {
	public:
		using CType = GLFWcursor;
	public:
		VKFW_INLINE VKFW_CONSTEXPR Cursor() VKFW_NOEXCEPT : m_cursor(nullptr) {}
		VKFW_INLINE VKFW_CONSTEXPR Cursor(std::nullptr_t) VKFW_NOEXCEPT : m_cursor(nullptr) {}
		VKFW_INLINE VKFW_CONSTEXPR Cursor(GLFWcursor *cursor) VKFW_NOEXCEPT : m_cursor(cursor) {}
		VKFW_INLINE VKFW_CONSTEXPR Cursor(Cursor const &another) VKFW_NOEXCEPT : m_cursor(another.m_cursor) {}
		VKFW_INLINE VKFW_CONSTEXPR_14 Cursor(Cursor &&another) VKFW_NOEXCEPT : m_cursor(another.m_cursor) { another.m_cursor = nullptr; }
		VKFW_INLINE VKFW_CONSTEXPR_14 Cursor operator=(Cursor const &another) VKFW_NOEXCEPT {
			m_cursor = another.m_cursor; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Cursor operator=(Cursor &&another) VKFW_NOEXCEPT {
			m_cursor = another.m_cursor; another.m_cursor = nullptr; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Cursor &operator=(GLFWcursor *cursor) VKFW_NOEXCEPT {
			m_cursor = cursor; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR_14 Cursor &operator=(std::nullptr_t) VKFW_NOEXCEPT {
			m_cursor = nullptr; return *this;
		}
		VKFW_INLINE VKFW_CONSTEXPR operator GLFWcursor *() const VKFW_NOEXCEPT { return m_cursor; }
		VKFW_INLINE VKFW_CONSTEXPR explicit operator bool() const VULKAN_HPP_NOEXCEPT { return m_cursor != nullptr; }
		VKFW_INLINE VKFW_CONSTEXPR bool operator!() const VULKAN_HPP_NOEXCEPT { return m_cursor == nullptr; }
# if defined(VKFW_HAS_SPACESHIP_OPERATOR)
		auto operator<=>(Cursor const &) const = default;
# else
		bool operator==(Cursor const &another) const VKFW_NOEXCEPT { return m_cursor == another.m_cursor; }
		bool operator!=(Cursor const &another) const VKFW_NOEXCEPT { return !operator==(another); }
# endif
		VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type destroy();

		// Member functions go here.

	private:
		GLFWcursor *m_cursor;
	};
#endif

	VKFW_INLINE Result getError(char const **description = nullptr) {
		return static_cast<Result>(glfwGetError(description));
	}
	VKFW_INLINE GLFWerrorfun setErrorCallback(GLFWerrorfun callback) {
		return glfwSetErrorCallback(callback);
	}

	template <InitializationHint hint_name, typename hint_type>
	Result initHint(hint_type const &value);
#ifndef VKFW_DISABLE_ENHANCED_MODE
	template <typename Type> using HintType = Optional<Type>;
	template <typename Type, InitializationHint hint> class InitializationHintType : public HintType<Type> {
	public: using HintType<Type>::HintType;
	};
	template <InitializationHint hint> using BooleanInitializationHint = InitializationHintType<bool, hint>;
	struct InitHints {
# ifndef VKFW_NO_STRUCT_CONSTRUCTORS
	public:
		VKFW_CONSTEXPR InitHints(
			BooleanInitializationHint<InitializationHint::VKFW_ENUMERATOR(JoystickHatButtons)> joystickHatButtons_ = nullopt,
			BooleanInitializationHint<InitializationHint::VKFW_ENUMERATOR(CocoaChdirResources)> cocoaChdirResources_ = nullopt,
			BooleanInitializationHint<InitializationHint::VKFW_ENUMERATOR(CocoaMenubar)> cocoaMenubar_ = nullopt
		) VKFW_NOEXCEPT
			: joystickHatButtons(joystickHatButtons_)
			, cocoaChdirResources(cocoaChdirResources_)
			, cocoaMenubar(cocoaMenubar_) {}
# endif
	public:
		BooleanInitializationHint<InitializationHint::VKFW_ENUMERATOR(JoystickHatButtons)>
			joystickHatButtons = nullopt;
		BooleanInitializationHint<InitializationHint::VKFW_ENUMERATOR(CocoaChdirResources)>
			cocoaChdirResources = nullopt;
		BooleanInitializationHint<InitializationHint::VKFW_ENUMERATOR(CocoaMenubar)>
			cocoaMenubar = nullopt;
};
	template<typename Type, InitializationHint hint_name>
	Result setInitHint(InitializationHintType<Type, hint_name> const &hint) {
		if (hint.has_value())
			initHint<hint_name>(hint.value());
		else
			initHint<hint_name>(true);
		return getError();
	}
	VKFW_INLINE Result setInitHints(InitHints hints) {
		Result result = Result::VKFW_ENUMERATOR(Success);
		if (!check(result = setInitHint(hints.joystickHatButtons))) return result;
		if (!check(result = setInitHint(hints.cocoaChdirResources))) return result;
		if (!check(result = setInitHint(hints.cocoaMenubar))) return result;
		return result;
	}
#endif

	VKFW_INLINE Result defaultWindowHints() {
		glfwDefaultWindowHints();
		return getError();
	}
	template <WindowHint hint_name, typename hint_type>
	Result windowHint(hint_type const &value);
#ifndef VKFW_DISABLE_ENHANCED_MODE
	template <typename Type, WindowHint hint> class WindowHintType : public HintType<Type> {
	public: using HintType<Type>::HintType;
	};
	template <WindowHint hint> using BooleanWindowHint = WindowHintType<bool, hint>;
	template <WindowHint hint> using UnsignedWindowHint = WindowHintType<unsigned, hint>;
# ifdef VKFW_HAS_STRING_VIEW
	template <WindowHint hint> using StringWindowHint = WindowHintType<std::string_view, hint>;
# else
	template <WindowHint hint> using StringWindowHint = WindowHintType<std::string, hint>;
# endif

	struct WindowHints {
# ifndef VKFW_NO_STRUCT_CONSTRUCTORS
	public:
#if HAS_STRING_VIEW
		VKFW_CONSTEXPR
#else
		VKFW_INLINE
#endif
		WindowHints (
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Resizable)> resizable_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Visible)> visible_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Decorated)> decorated_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Focused)> focused_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(AutoIconify)> autoIconify_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Floating)> floating_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Maximized)> maximized_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(CenterCursor)> centerCursor_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(TransparentFramebuffer)> transparentFramebuffer_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(FocusOnShow)> focusOnShow_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(ScaleToMonitor)> scaleToMonitor_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(RedBits)> redBits_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(GreenBits)> greenBits_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(BlueBits)> blueBits_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AlphaBits)> alphaBits_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(DepthBits)> depthBits_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(StencilBits)> stencilBits_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationRedBits)> accumulationRedBits_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationGreenBits)> accumulationGreenBits_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationBlueBits)> accumulationBlueBits_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationAlphaBits)> accumulationAlphaBits_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AuxiliaryBuffers)> auxiliaryBuffers_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(Samples)> samples_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(RefreshRate)> refreshRate_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(StereoscopicRendering)> stereo_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(SRGBCapable)> srgbCapable_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(DoubleBuffer)> doubleBuffer_ = nullopt,
			WindowHintType<ClientAPI, WindowHint::VKFW_ENUMERATOR(ClientAPI)> clientAPI_ = ClientAPI::VKFW_ENUMERATOR(None),
			WindowHintType<ContextCreationAPI, WindowHint::VKFW_ENUMERATOR(ContextCreationAPI)> contextAPI_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(ContextVersionMajor)> contextVersionMajor_ = nullopt,
			UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(ContextVersionMinor)> contextVersionMinor_ = nullopt,
			WindowHintType<ContextRobustness, WindowHint::VKFW_ENUMERATOR(ContextRobustness)> contextRobustness_ = nullopt,
			WindowHintType<ContextReleaseBehavior, WindowHint::VKFW_ENUMERATOR(ContextReleaseBehavior)> contextReleaseBehavior_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(ContextNoError)> contextNoError_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(OpenGLForwardCompatibility)> openGLForwardCompatibility_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(OpenGLDebugContext)> openGLDebugContext_ = nullopt,
			WindowHintType<OpenGLProfile, WindowHint::VKFW_ENUMERATOR(OpenGLProfile)> openGLProfile_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaRetinaFramebuffer)> cocoaRetinaFramebuffer_ = nullopt,
			StringWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaFrameName)> cocoaFrameName_ = nullopt,
			BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaGraphicsSwitching)> cocoaGraphicsSwitching_ = nullopt,
			StringWindowHint<WindowHint::VKFW_ENUMERATOR(X11ClassName)> x11ClassName_ = nullopt,
			StringWindowHint<WindowHint::VKFW_ENUMERATOR(X11InstanceName)> x11InstanceName_ = nullopt
		) VKFW_NOEXCEPT
			: resizable(resizable_)
			, visible(visible_)
			, decorated(decorated_)
			, focused(focused_)
			, autoIconify(autoIconify_)
			, floating(floating_)
			, maximized(maximized_)
			, centerCursor(centerCursor_)
			, transparentFramebuffer(transparentFramebuffer_)
			, focusOnShow(focusOnShow_)
			, scaleToMonitor(scaleToMonitor_)
			, redBits(redBits_)
			, greenBits(greenBits_)
			, blueBits(blueBits_)
			, alphaBits(alphaBits_)
			, depthBits(depthBits_)
			, stencilBits(stencilBits_)
			, accumulationRedBits(accumulationRedBits_)
			, accumulationGreenBits(accumulationGreenBits_)
			, accumulationBlueBits(accumulationBlueBits_)
			, accumulationAlphaBits(accumulationAlphaBits_)
			, auxiliaryBuffers(auxiliaryBuffers_)
			, samples(samples_)
			, refreshRate(refreshRate_)
			, stereo(stereo_)
			, srgbCapable(srgbCapable_)
			, doubleBuffer(doubleBuffer_)
			, clientAPI(clientAPI_)
			, contextAPI(contextAPI_)
			, contextVersionMajor(contextVersionMajor_)
			, contextVersionMinor(contextVersionMinor_)
			, contextRobustness(contextRobustness_)
			, contextReleaseBehavior(contextReleaseBehavior_)
			, contextNoError(contextNoError_)
			, openGLForwardCompatibility(openGLForwardCompatibility_)
			, openGLDebugContext(openGLDebugContext_)
			, openGLProfile(openGLProfile_)
			, cocoaRetinaFramebuffer(cocoaRetinaFramebuffer_)
			, cocoaFrameName(cocoaFrameName_)
			, cocoaGraphicsSwitching(cocoaGraphicsSwitching_)
			, x11ClassName(x11ClassName_)
			, x11InstanceName(x11InstanceName_) {}
# endif
	public:
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Resizable)>
			resizable = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Visible)>
			visible = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Decorated)>
			decorated = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Focused)>
			focused = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(AutoIconify)>
			autoIconify = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Floating)>
			floating = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(Maximized)>
			maximized = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(CenterCursor)>
			centerCursor = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(TransparentFramebuffer)>
			transparentFramebuffer = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(FocusOnShow)>
			focusOnShow = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(ScaleToMonitor)>
			scaleToMonitor = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(RedBits)>
			redBits = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(GreenBits)>
			greenBits = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(BlueBits)>
			blueBits = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AlphaBits)>
			alphaBits = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(DepthBits)>
			depthBits = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(StencilBits)>
			stencilBits = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationRedBits)>
			accumulationRedBits = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationGreenBits)>
			accumulationGreenBits = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationBlueBits)>
			accumulationBlueBits = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AccumulationAlphaBits)>
			accumulationAlphaBits = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(AuxiliaryBuffers)>
			auxiliaryBuffers = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(Samples)>
			samples = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(RefreshRate)>
			refreshRate = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(StereoscopicRendering)>
			stereo = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(SRGBCapable)>
			srgbCapable = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(DoubleBuffer)>
			doubleBuffer = nullopt;
		WindowHintType<ClientAPI, WindowHint::VKFW_ENUMERATOR(ClientAPI)>
			clientAPI = ClientAPI::VKFW_ENUMERATOR(None);
		WindowHintType<ContextCreationAPI, WindowHint::VKFW_ENUMERATOR(ContextCreationAPI)>
			contextAPI = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(ContextVersionMajor)>
			contextVersionMajor = nullopt;
		UnsignedWindowHint<WindowHint::VKFW_ENUMERATOR(ContextVersionMinor)>
			contextVersionMinor = nullopt;
		WindowHintType<ContextRobustness, WindowHint::VKFW_ENUMERATOR(ContextRobustness)>
			contextRobustness = nullopt;
		WindowHintType<ContextReleaseBehavior, WindowHint::VKFW_ENUMERATOR(ContextReleaseBehavior)>
			contextReleaseBehavior = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(ContextNoError)>
			contextNoError = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(OpenGLForwardCompatibility)>
			openGLForwardCompatibility = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(OpenGLDebugContext)>
			openGLDebugContext = nullopt;
		WindowHintType<OpenGLProfile, WindowHint::VKFW_ENUMERATOR(OpenGLProfile)>
			openGLProfile = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaRetinaFramebuffer)>
			cocoaRetinaFramebuffer = nullopt;
		StringWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaFrameName)>
			cocoaFrameName = nullopt;
		BooleanWindowHint<WindowHint::VKFW_ENUMERATOR(CocoaGraphicsSwitching)>
			cocoaGraphicsSwitching = nullopt;
		StringWindowHint<WindowHint::VKFW_ENUMERATOR(X11ClassName)>
			x11ClassName = nullopt;
		StringWindowHint<WindowHint::VKFW_ENUMERATOR(X11InstanceName)>
			x11InstanceName = nullopt;
	};
	template<typename Type, WindowHint hint_name>
	Result setWindowHint(WindowHintType<Type, hint_name> const &hint) {
		if (hint.has_value()) {
			windowHint<hint_name>(hint.value());
			return getError();
		} else
			return Result::VKFW_ENUMERATOR(Success);
	}
	VKFW_INLINE Result setWindowHints(WindowHints hints) {
		Result result = Result::VKFW_ENUMERATOR(Success);
		if (!check(result = setWindowHint(hints.resizable))) return result;
		if (!check(result = setWindowHint(hints.visible))) return result;
		if (!check(result = setWindowHint(hints.decorated))) return result;
		if (!check(result = setWindowHint(hints.focused))) return result;
		if (!check(result = setWindowHint(hints.autoIconify))) return result;
		if (!check(result = setWindowHint(hints.floating))) return result;
		if (!check(result = setWindowHint(hints.maximized))) return result;
		if (!check(result = setWindowHint(hints.centerCursor))) return result;
		if (!check(result = setWindowHint(hints.transparentFramebuffer))) return result;
		if (!check(result = setWindowHint(hints.focusOnShow))) return result;
		if (!check(result = setWindowHint(hints.scaleToMonitor))) return result;
		if (!check(result = setWindowHint(hints.redBits))) return result;
		if (!check(result = setWindowHint(hints.greenBits))) return result;
		if (!check(result = setWindowHint(hints.blueBits))) return result;
		if (!check(result = setWindowHint(hints.alphaBits))) return result;
		if (!check(result = setWindowHint(hints.depthBits))) return result;
		if (!check(result = setWindowHint(hints.stencilBits))) return result;
		if (!check(result = setWindowHint(hints.accumulationRedBits))) return result;
		if (!check(result = setWindowHint(hints.accumulationGreenBits))) return result;
		if (!check(result = setWindowHint(hints.accumulationBlueBits))) return result;
		if (!check(result = setWindowHint(hints.accumulationAlphaBits))) return result;
		if (!check(result = setWindowHint(hints.auxiliaryBuffers))) return result;
		if (!check(result = setWindowHint(hints.samples))) return result;
		if (!check(result = setWindowHint(hints.refreshRate))) return result;
		if (!check(result = setWindowHint(hints.stereo))) return result;
		if (!check(result = setWindowHint(hints.srgbCapable))) return result;
		if (!check(result = setWindowHint(hints.doubleBuffer))) return result;
		if (!check(result = setWindowHint(hints.clientAPI))) return result;
		if (!check(result = setWindowHint(hints.contextAPI))) return result;
		if (!check(result = setWindowHint(hints.contextVersionMajor))) return result;
		if (!check(result = setWindowHint(hints.contextVersionMinor))) return result;
		if (!check(result = setWindowHint(hints.contextRobustness))) return result;
		if (!check(result = setWindowHint(hints.contextReleaseBehavior))) return result;
		if (!check(result = setWindowHint(hints.contextNoError))) return result;
		if (!check(result = setWindowHint(hints.openGLForwardCompatibility))) return result;
		if (!check(result = setWindowHint(hints.openGLDebugContext))) return result;
		if (!check(result = setWindowHint(hints.openGLProfile))) return result;
		if (!check(result = setWindowHint(hints.cocoaRetinaFramebuffer))) return result;
		if (!check(result = setWindowHint(hints.cocoaFrameName))) return result;
		if (!check(result = setWindowHint(hints.cocoaGraphicsSwitching))) return result;
		if (!check(result = setWindowHint(hints.x11ClassName))) return result;
		if (!check(result = setWindowHint(hints.x11InstanceName))) return result;
		return result;
	}
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
	VKFW_NODISCARD Result init();
	VKFW_NODISCARD Result terminate();
#else
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
		init(InitHints hints = {});
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS typename ResultValueType<void>::type
		terminate();
# ifndef VKFW_NO_SMART_HANDLE
	using UniqueInstance = UniqueHandle<Instance>;
	VKFW_NODISCARD typename ResultValueType<UniqueInstance>::type
		initUnique(InitHints hints = {});
# endif
#endif

	struct Version {
		size_t major, minor, revision;
	};
	VKFW_INLINE Version getVersion() {
		int major, minor, revision;
		glfwGetVersion(&major, &minor, &revision);
		return Version{
			static_cast<size_t>(major),
			static_cast<size_t>(minor),
			static_cast<size_t>(revision)
		};
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
# ifdef VKFW_HAS_SPAN
	VKFW_NODISCARD std::span<GLFWmonitor *> getMonitors();
# else
	VKFW_NODISCARD GLFWmonitor **getMonitors(size_t *count);
# endif
#else
	VKFW_NODISCARD typename ResultValueType<Monitor>::type getPrimaryMonitor();
	VKFW_NODISCARD typename ResultValueType<std::vector<Monitor>>::type getMonitors();
#endif
	VKFW_NODISCARD GLFWmonitorfun setMonitorCallback(GLFWmonitorfun const &callback);

#ifdef VKFW_DISABLE_ENHANCED_MODE
	void getMonitorPos(GLFWmonitor *monitor, int *xpos, int *ypos);
	void getMonitorWorkarea(GLFWmonitor *monitor, int *xpos, int *ypos,
							size_t *width, size_t *height);
	void getMonitorPhysicalSize(GLFWmonitor *monitor,
								size_t *widthMM, size_t *heightMM);
	void getMonitorContentScale(GLFWmonitor *monitor,
								float *xscale, float *yscale);

# ifdef VKFW_HAS_STRING_VIEW
	VKFW_NODISCARD std::string_view getMonitorName();
# else
	VKFW_NODISCARD char const *getMonitorName();
# endif

	void setMonitorUserPointer(GLFWmonitor *monitor, void *pointer);
	VKFW_NODISCARD void *getMonitorUserPointer(GLFWmonitor *monitor);

	VKFW_NODISCARD GLFWvidmode const *getVideoMode(GLFWmonitor *monitor);
# ifdef VKFW_HAS_SPAN
	VKFW_NODISCARD std::span<GLFWvidmode const> getVideoModes(GLFWmonitor *monitor);
# else
	VKFW_NODISCARD GLFWvidmode const *getVideoModes(GLFWmonitor *monitor, size_t *count);
# endif

	void setGamma(GLFWmonitor *monitor, float gamma);
	VKFW_NODISCARD GLFWgammaramp const *getGammaRamp(GLFWmonitor *monitor);
	void setGammaRamp(GLFWmonitor *monitor, GLFWgammaramp const *ramp);
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
	VKFW_NODISCARD GLFWwindow *createWindow(size_t width, size_t height, char const *title,
											GLFWmonitor *monitor = nullptr, GLFWwindow *share = nullptr);
	VKFW_NODISCARD Result destroyWindow(GLFWwindow *window);
#else
	VKFW_NODISCARD typename ResultValueType<Window>::type
		createWindow(size_t width, size_t height, char const *title,
					 WindowHints hints = WindowHints{},
					 Monitor monitor = nullptr, Window share = nullptr,
					 bool reset_hints = true);
# ifndef VKFW_NO_SMART_HANDLE
	using UniqueWindow = UniqueHandle<Window>;
	VKFW_NODISCARD typename ResultValueType<UniqueWindow>::type
		createWindowUnique(size_t width, size_t height, char const *title,
						   WindowHints hints = WindowHints{},
						   Monitor monitor = nullptr, Window share = nullptr,
						   bool reset_hints = true);
# endif
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
	bool windowShouldClose(GLFWwindow *window);
	void setWindowShouldClose(GLFWwindow *window, bool value);

# ifdef VKFW_HAS_STRING_VIEW
	void setWindowTitle(GLFWwindow *window, std::string_view title);
# else
	void setWindowTitle(GLFWwindow *window, char const *title);
# endif

	void getWindowPos(GLFWwindow *window, int *xpos, int *ypos);
	void setWindowPos(GLFWwindow *window, int xpos, int ypos);
	void getWindowSize(GLFWwindow *window, size_t *width, size_t *height);
	void setWindowSizeLimits(GLFWwindow *window, size_t minimum_width, size_t minimum_height,
							 size_t maximum_width, size_t maximum_height);
	void setWindowAspectRatio(GLFWwindow *window, size_t numerator, size_t denominator);
	void setWindowSize(GLFWwindow *window, size_t width, size_t height);
	void getFramebufferSize(GLFWwindow *window, size_t *width, size_t *height);
	void getWindowFrameSize(GLFWwindow *window, size_t *left, size_t *top,
							size_t *right, size_t *bottom);
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
	void setWindowMonitor(GLFWwindow *window, GLFWmonitor *monitor, int xpos, int ypos,
						  size_t width, size_t height, size_t refreshRate);
#endif

	// To be implemented
	// void glfwSetWindowIcon(GLFWwindow *window, int count, GLFWimage const *images);
	// int glfwGetWindowAttrib(GLFWwindow *window, int attrib);
	// void glfwSetWindowAttrib(GLFWwindow *window, int attrib, int value);
	// void glfwSetWindowUserPointer(GLFWwindow *window, void *pointer);
	// void *glfwGetWindowUserPointer(GLFWwindow *window);
	// GLFWwindowposfun glfwSetWindowPosCallback(GLFWwindow *window, GLFWwindowposfun callback);
	// GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindow *window, GLFWwindowsizefun callback);
	// GLFWwindowclosefun glfwSetWindowCloseCallback(GLFWwindow *window, GLFWwindowclosefun callback);
	// GLFWwindowrefreshfun glfwSetWindowRefreshCallback(GLFWwindow *window, GLFWwindowrefreshfun callback);
	// GLFWwindowfocusfun glfwSetWindowFocusCallback(GLFWwindow *window, GLFWwindowfocusfun callback);
	// GLFWwindowiconifyfun glfwSetWindowIconifyCallback(GLFWwindow *window, GLFWwindowiconifyfun callback);
	// GLFWwindowmaximizefun glfwSetWindowMaximizeCallback(GLFWwindow *window, GLFWwindowmaximizefun callback);
	// GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWwindow *window, GLFWframebuffersizefun callback);
	// GLFWwindowcontentscalefun glfwSetWindowContentScaleCallback(GLFWwindow *window, GLFWwindowcontentscalefun callback);
	// void glfwPollEvents(void);
	// void glfwWaitEvents(void);
	// void glfwWaitEventsTimeout(double timeout);
	// void glfwPostEmptyEvent(void);
	// int glfwGetInputMode(GLFWwindow *window, int mode);
	// void glfwSetInputMode(GLFWwindow *window, int mode, int value);
	// int glfwRawMouseMotionSupported(void);
	// char const *glfwGetKeyName(int key, int scancode);
	// int glfwGetKeyScancode(int key);
	// int glfwGetKey(GLFWwindow *window, int key);
	// int glfwGetMouseButton(GLFWwindow *window, int button);
	// void glfwGetCursorPos(GLFWwindow *window, double *xpos, double *ypos);
	// void glfwSetCursorPos(GLFWwindow *window, double xpos, double ypos);
	// GLFWcursor *glfwCreateCursor(GLFWimage const *image, int xhot, int yhot);
	// GLFWcursor *glfwCreateStandardCursor(int shape);
	// void glfwDestroyCursor(GLFWcursor *cursor);
	// void glfwSetCursor(GLFWwindow *window, GLFWcursor *cursor);
	// GLFWkeyfun glfwSetKeyCallback(GLFWwindow *window, GLFWkeyfun callback);
	// GLFWcharfun glfwSetCharCallback(GLFWwindow *window, GLFWcharfun callback);
	// GLFWcharmodsfun glfwSetCharModsCallback(GLFWwindow *window, GLFWcharmodsfun callback);
	// GLFWmousebuttonfun glfwSetMouseButtonCallback(GLFWwindow *window, GLFWmousebuttonfun callback);
	// GLFWcursorposfun glfwSetCursorPosCallback(GLFWwindow *window, GLFWcursorposfun callback);
	// GLFWcursorenterfun glfwSetCursorEnterCallback(GLFWwindow *window, GLFWcursorenterfun callback);
	// GLFWscrollfun glfwSetScrollCallback(GLFWwindow *window, GLFWscrollfun callback);
	// GLFWdropfun glfwSetDropCallback(GLFWwindow *window, GLFWdropfun callback);

	// To be implemented
	// int glfwJoystickPresent(int jid);
	// float const *glfwGetJoystickAxes(int jid, int *count);
	// const unsigned char *glfwGetJoystickButtons(int jid, int *count);
	// const unsigned char *glfwGetJoystickHats(int jid, int *count);
	// char const *glfwGetJoystickName(int jid);
	// char const *glfwGetJoystickGUID(int jid);
	// void glfwSetJoystickUserPointer(int jid, void *pointer);
	// void *glfwGetJoystickUserPointer(int jid);
	// int glfwJoystickIsGamepad(int jid);
	// GLFWjoystickfun glfwSetJoystickCallback(GLFWjoystickfun callback);
	// int glfwUpdateGamepadMappings(char const *string);
	// char const *glfwGetGamepadName(int jid);
	// int glfwGetGamepadState(int jid, GLFWgamepadstate *state);
	// void glfwSetClipboardString(GLFWwindow *window, char const *string);
	// char const *glfwGetClipboardString(GLFWwindow *window);
	// double glfwGetTime(void);
	// void glfwSetTime(double time);
	// uint64_t glfwGetTimerValue(void);
	// uint64_t glfwGetTimerFrequency(void);
	// void glfwMakeContextCurrent(GLFWwindow *window);
	// GLFWwindow *glfwGetCurrentContext(void);
	// void glfwSwapBuffers(GLFWwindow *window);
	// void glfwSwapInterval(int interval);
	// int glfwExtensionSupported(char const *extension);
	// GLFWglproc glfwGetProcAddress(char const *procname);
	// int glfwVulkanSupported(void);
	// char const **glfwGetRequiredInstanceExtensions(uint32_t *count);

	// To be implemented
	// GLFWvkproc glfwGetInstanceProcAddress(VkInstance instance, char const *procname);
	// int glfwGetPhysicalDevicePresentationSupport(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily);
	// VkResult glfwCreateWindowSurface(VkInstance instance, GLFWwindow *window, VkAllocationCallbacks const *allocator, VkSurfaceKHR *surface);
}

template <> struct VULKAN_HPP_NAMESPACE::FlagTraits<VKFW_NAMESPACE::ModifierKeyBits> {
	enum : VkFlags {
		allFlags = VkFlags(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(Shift))
		| VkFlags(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(Control))
		| VkFlags(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(Alt))
		| VkFlags(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(Super))
		| VkFlags(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(CapsLock))
		| VkFlags(VKFW_NAMESPACE::ModifierKeyBits::VKFW_ENUMERATOR(NumLock))
	};
};
#ifndef VKFW_NO_SMART_HANDLE
template<> struct VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Instance> {
	VKFW_INLINE void destroy(Instance &instance) { static_cast<void>(instance.destroy()); }
};
template<> class VULKAN_HPP_NAMESPACE::UniqueHandleTraits<VKFW_NAMESPACE::Instance, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE> {
public:
	using deleter = VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Instance>;
};

template<> struct VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Window> {
	VKFW_INLINE void destroy(Window &window) { static_cast<void>(window.destroy()); }
};
template<> class VULKAN_HPP_NAMESPACE::UniqueHandleTraits<VKFW_NAMESPACE::Window, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE> {
public:
	using deleter = VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Window>;
};

template<> struct VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Cursor> {
	VKFW_INLINE void destroy(Cursor &cursor) { static_cast<void>(cursor.destroy()); }
};
template<> class VULKAN_HPP_NAMESPACE::UniqueHandleTraits<VKFW_NAMESPACE::Cursor, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE> {
public:
	using deleter = VKFW_NAMESPACE::CustomDestroy<VKFW_NAMESPACE::Cursor>;
};
#endif

namespace VKFW_NAMESPACE {
#ifndef VKFW_DISABLE_ENHANCED_MODE
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type Instance::destroy() {
		if (m_state) {
			glfwTerminate();
			m_state = false;
			return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Instance::destroy");
		} else
			return createResultValue(Result::VKFW_ENUMERATOR(Success), VKFW_NAMESPACE_STRING"::Instance::destroy");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type Window::destroy() {
		if (m_window) {
			glfwDestroyWindow(m_window);
			m_window = nullptr;
			return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::destroy");
		} else
			return createResultValue(Result::VKFW_ENUMERATOR(Success), VKFW_NAMESPACE_STRING"::Window::destroy");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type Cursor::destroy() {
		// Empty for now!!
		return createResultValue(Result::VKFW_ENUMERATOR(Success), VKFW_NAMESPACE_STRING"::Cursor::destroy");
	}
#endif

	template<> VKFW_INLINE Result initHint<InitializationHint::VKFW_ENUMERATOR(JoystickHatButtons), Boolean>(Boolean const &value) {
		glfwInitHint(static_cast<int>(InitializationHint::VKFW_ENUMERATOR(JoystickHatButtons)),
					 static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result initHint<InitializationHint::VKFW_ENUMERATOR(JoystickHatButtons), bool>(bool const &value) {
		glfwInitHint(static_cast<int>(InitializationHint::VKFW_ENUMERATOR(JoystickHatButtons)),
					 static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result initHint<InitializationHint::VKFW_ENUMERATOR(CocoaChdirResources), Boolean>(Boolean const &value) {
		glfwInitHint(static_cast<int>(InitializationHint::VKFW_ENUMERATOR(CocoaChdirResources)),
					 static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result initHint<InitializationHint::VKFW_ENUMERATOR(CocoaChdirResources), bool>(bool const &value) {
		glfwInitHint(static_cast<int>(InitializationHint::VKFW_ENUMERATOR(CocoaChdirResources)),
					 static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result initHint<InitializationHint::VKFW_ENUMERATOR(CocoaMenubar), Boolean>(Boolean const &value) {
		glfwInitHint(static_cast<int>(InitializationHint::VKFW_ENUMERATOR(CocoaMenubar)),
					 static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result initHint<InitializationHint::VKFW_ENUMERATOR(CocoaMenubar), bool>(bool const &value) {
		glfwInitHint(static_cast<int>(InitializationHint::VKFW_ENUMERATOR(CocoaMenubar)),
					 static_cast<int>(value));
		return getError();
	}

	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Resizable), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Resizable)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Resizable), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Resizable)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Visible), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Visible)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Visible), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Visible)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Decorated), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Decorated)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Decorated), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Decorated)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Focused), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Focused)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Focused), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Focused)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(AutoIconify), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(AutoIconify)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(AutoIconify), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(AutoIconify)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Floating), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Floating)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Floating), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Floating)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Maximized), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Maximized)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Maximized), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Maximized)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(CenterCursor), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(CenterCursor)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(CenterCursor), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(CenterCursor)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(TransparentFramebuffer), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(TransparentFramebuffer)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(TransparentFramebuffer), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(TransparentFramebuffer)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(FocusOnShow), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(FocusOnShow)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(FocusOnShow), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(FocusOnShow)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(ScaleToMonitor), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(ScaleToMonitor)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(ScaleToMonitor), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(ScaleToMonitor)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(RedBits), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(RedBits)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(GreenBits), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(GreenBits)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(BlueBits), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(BlueBits)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(AlphaBits), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(AlphaBits)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(DepthBits), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(DepthBits)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(StencilBits), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(StencilBits)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(AccumulationRedBits), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(AccumulationRedBits)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(AccumulationGreenBits), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(AccumulationGreenBits)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(AccumulationBlueBits), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(AccumulationBlueBits)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(AccumulationAlphaBits), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(AccumulationAlphaBits)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(AuxiliaryBuffers), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(AuxiliaryBuffers)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(Samples), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(Samples)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(RefreshRate), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(RefreshRate)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(StereoscopicRendering), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(StereoscopicRendering)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(StereoscopicRendering), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(StereoscopicRendering)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(SRGBCapable), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(SRGBCapable)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(SRGBCapable), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(SRGBCapable)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(DoubleBuffer), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(DoubleBuffer)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(DoubleBuffer), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(DoubleBuffer)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(ClientAPI), ClientAPI>(ClientAPI const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(ClientAPI)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(ContextCreationAPI), ContextCreationAPI>(ContextCreationAPI const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(ContextCreationAPI)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(ContextVersionMajor), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(ContextVersionMajor)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(ContextVersionMinor), unsigned>(unsigned const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(ContextVersionMinor)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(ContextRobustness), ContextRobustness>(ContextRobustness const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(ContextRobustness)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(ContextReleaseBehavior), ContextReleaseBehavior>(ContextReleaseBehavior const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(ContextReleaseBehavior)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(ContextNoError), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(ContextNoError)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(ContextNoError), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(ContextNoError)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(OpenGLForwardCompatibility), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(OpenGLForwardCompatibility)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(OpenGLForwardCompatibility), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(OpenGLForwardCompatibility)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(OpenGLDebugContext), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(OpenGLDebugContext)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(OpenGLDebugContext), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(OpenGLDebugContext)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(OpenGLProfile), OpenGLProfile>(OpenGLProfile const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(OpenGLProfile)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(CocoaRetinaFramebuffer), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(CocoaRetinaFramebuffer)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(CocoaRetinaFramebuffer), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(CocoaRetinaFramebuffer)),
					   static_cast<int>(value));
		return getError();
	}
#ifdef VKFW_HAS_STRING_VIEW
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(CocoaFrameName), std::string_view>(std::string_view const &value) {
		glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(CocoaFrameName)),
							 value.data());
		return getError();
	}
#else
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(CocoaFrameName), std::string>(std::string const &value) {
		glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(CocoaFrameName)),
							 value.c_str());
		return getError();
	}
#endif
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(CocoaGraphicsSwitching), Boolean>(Boolean const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(CocoaGraphicsSwitching)),
					   static_cast<int>(value));
		return getError();
	}
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(CocoaGraphicsSwitching), bool>(bool const &value) {
		glfwWindowHint(static_cast<int>(WindowHint::VKFW_ENUMERATOR(CocoaGraphicsSwitching)),
					   static_cast<int>(value));
		return getError();
	}
#ifdef VKFW_HAS_STRING_VIEW
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(X11ClassName), std::string_view>(std::string_view const &value) {
		glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(X11ClassName)),
							 value.data());
		return getError();
	}
#else
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(X11ClassName), std::string>(std::string const &value) {
		glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(X11ClassName)),
							 value.c_str());
		return getError();
	}
#endif
#ifdef VKFW_HAS_STRING_VIEW
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(X11InstanceName), std::string_view>(std::string_view const &value) {
		glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(X11InstanceName)),
							 value.data());
		return getError();
	}
#else
	template<> VKFW_INLINE Result windowHint<WindowHint::VKFW_ENUMERATOR(X11InstanceName), std::string>(std::string const &value) {
		glfwWindowHintString(static_cast<int>(WindowHint::VKFW_ENUMERATOR(X11InstanceName)),
							 value.c_str());
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
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type init(InitHints hints) {
		Result result = setInitHints(hints);
		if (!check(result)) return createResultValue(result, VKFW_NAMESPACE_STRING"::init");

		if (glfwInit())
			return createResultValue(Result::VKFW_ENUMERATOR(Success), VKFW_NAMESPACE_STRING"::init");
		else
			return createResultValue(getError(), VKFW_NAMESPACE_STRING"::init");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type terminate() {
		glfwTerminate();
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::terminate");
	}
# ifndef VKFW_NO_SMART_HANDLE
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<VKFW_NAMESPACE::UniqueInstance>::type
		initUnique(InitHints hints) {
		Instance instance;

		Result result = setInitHints(hints);
		if (!check(result)) return createResultValueUnique(result, instance,
														   VKFW_NAMESPACE_STRING"::initUnique");

		if (glfwInit()) {
			instance = true;
			return createResultValueUnique(Result::VKFW_ENUMERATOR(Success), instance,
										   VKFW_NAMESPACE_STRING"::initUnique");
		} else
			return createResultValueUnique(getError(), instance,
										   VKFW_NAMESPACE_STRING"::initUnique");
	}
# endif
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
	VKFW_NODISCARD VKFW_INLINE GLFWmonitor *getPrimaryMonitor() { return glfwGetPrimaryMonitor(); }
# ifdef VKFW_HAS_SPAN
	VKFW_NODISCARD VKFW_INLINE std::span<GLFWmonitor *> getMonitors() {
		int tmp_count;
		auto **output = glfwGetMonitors(&tmp_count);
		return std::span<GLFWmonitor *>(output, static_cast<size_t>(tmp_count > 0 ? tmp_count : 0));
	}
# else
	VKFW_NODISCARD VKFW_INLINE GLFWmonitor **getMonitors(size_t *count) {
		int tmp_count;
		auto **output = glfwGetMonitors(&tmp_count);
		*count = static_cast<size_t>(tmp_count > 0 ? tmp_count : 0);
		return output;
	}
# endif
#else
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<Monitor>::type getPrimaryMonitor() {
		Monitor monitor = glfwGetPrimaryMonitor();
		return createResultValue(getError(), monitor, VKFW_NAMESPACE_STRING"::getPrimaryMonitor");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::getMonitors");
	}
#endif
	VKFW_NODISCARD VKFW_INLINE GLFWmonitorfun setMonitorCallback(GLFWmonitorfun const &callback) {
		return glfwSetMonitorCallback(callback);
	}

#ifdef VKFW_DISABLE_ENHANCED_MODE
	VKFW_INLINE void getMonitorPos(GLFWmonitor *monitor, int *xpos, int *ypos) {
		glfwGetMonitorPos(monitor, xpos, ypos);
	}
	VKFW_INLINE void getMonitorWorkarea(GLFWmonitor *monitor, int *xpos, int *ypos,
										size_t *width, size_t *height) {
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
	VKFW_INLINE void getMonitorPhysicalSize(GLFWmonitor *monitor,
											size_t *widthMM, size_t *heightMM) {
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
	VKFW_INLINE void getMonitorContentScale(GLFWmonitor *monitor,
											float *xscale, float *yscale) {
		glfwGetMonitorContentScale(monitor, xscale, yscale);
	}
# ifdef VKFW_HAS_STRING_VIEW
	VKFW_NODISCARD VKFW_INLINE std::string_view getMonitorName(GLFWmonitor *monitor) {
# else
	VKFW_NODISCARD VKFW_INLINE char const *getMonitorName(GLFWmonitor *monitor) {
# endif
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
# ifdef VKFW_HAS_SPAN
	VKFW_NODISCARD VKFW_INLINE std::span<GLFWvidmode const> getVideoModes(GLFWmonitor *monitor) {
		int count;
		GLFWvidmode const *pointer = glfwGetVideoModes(monitor, &count);
		return std::span<GLFWvidmode const>(pointer, static_cast<size_t>(count));
	}
# else
	VKFW_NODISCARD VKFW_INLINE GLFWvidmode const *getVideoModes(GLFWmonitor *monitor, size_t *count) {
		int temp_count;
		GLFWvidmode const *pointer = glfwGetVideoModes(monitor, &temp_count);
		if (temp_count > 0)
			*count = temp_count;
		else
			*count = 0u;
		return pointer;
	}
# endif

	VKFW_INLINE void setGamma(GLFWmonitor *monitor, float gamma) {
		glfwSetGamma(monitor, gamma);
	}
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
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Monitor::getPos");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<int, int>>::type 
	Monitor::getPos() const {
		std::tuple<int, int> output;
		glfwGetMonitorPos(m_monitor, &std::get<0>(output), &std::get<1>(output));
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getPos");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type 
	Monitor::getPosX() const {
		int output;
		glfwGetMonitorPos(m_monitor, &output, nullptr);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getPosX");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type 
	Monitor::getPosY() const {
		int output;
		glfwGetMonitorPos(m_monitor, nullptr, &output);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getPosY");
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
		return createResultValue(result, VKFW_NAMESPACE_STRING"::Monitor::getWorkarea");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<int, int, size_t, size_t>>::type
	Monitor::getWorkarea() const {
		std::tuple<int, int, size_t, size_t> output;
		int temp_width, temp_height;
		glfwGetMonitorWorkarea(m_monitor, &std::get<0>(output), &std::get<1>(output),
							   &temp_width, &temp_height);
		Result result = getError();
		if (check(result)) {
			std::get<2>(output) = temp_width;
			std::get<3>(output) = temp_height;
		} else {
			std::get<2>(output) = 0u;
			std::get<3>(output) = 0u;
		}
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Monitor::getWorkarea");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<int, int>>::type
	Monitor::getWorkareaPos() const {
		std::tuple<int, int> output;
		glfwGetMonitorWorkarea(m_monitor, &std::get<0>(output), &std::get<1>(output), nullptr, nullptr);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getWorkareaPos");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type 
	Monitor::getWorkareaPosX() const {
		int output;
		glfwGetMonitorWorkarea(m_monitor, &output, nullptr, nullptr, nullptr);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getWorkareaPosX");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type 
	Monitor::getWorkareaPosY() const {
		int output;
		glfwGetMonitorWorkarea(m_monitor, nullptr, &output, nullptr, nullptr);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getWorkareaPosY");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Monitor::getWorkareaSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Monitor::getWorkareaWidth");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Monitor::getWorkareaHeight");
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
		return createResultValue(result, VKFW_NAMESPACE_STRING"::Monitor::getPhysicalSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Monitor::getPhysicalSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Monitor::getPhysicalWidth");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Monitor::getPhysicalHeight");
	}

	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Monitor::getContentScale(float *xscale, float *yscale) const {
		glfwGetMonitorContentScale(m_monitor, xscale, yscale);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Monitor::getContentScale");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<float, float>>::type
	Monitor::getContentScale() const {
		std::tuple<float, float> output;
		glfwGetMonitorContentScale(m_monitor, &std::get<0>(output), &std::get<1>(output));
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getContentScale");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<float>::type 
	Monitor::getContentScaleX() const {
		float output;
		glfwGetMonitorContentScale(m_monitor, &output, nullptr);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getContentScaleX");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<float>::type 
	Monitor::getContentScaleY() const {
		float output;
		glfwGetMonitorContentScale(m_monitor, nullptr, &output);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getContentScaleY");
	}

# ifdef VKFW_HAS_STRING_VIEW
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::string_view>::type 
	Monitor::getName() const {
		std::string_view output = glfwGetMonitorName(m_monitor);
# else
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<char const *>::type 
	Monitor::getName() const {
		char const *output = glfwGetMonitorName(m_monitor);
# endif
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getName");
	}

	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Monitor::setUserPointer(void *pointer) const {
		glfwSetMonitorUserPointer(m_monitor, pointer);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Monitor::setUserPointer");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<void *>::type 
	Monitor::getUserPointer() const {
		void *output = glfwGetMonitorUserPointer(m_monitor);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getUserPointer");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<GLFWvidmode const *>::type 
	Monitor::getVideoMode() const {
		GLFWvidmode const *output = glfwGetVideoMode(m_monitor);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getVideoMode");
	}
# ifdef VKFW_HAS_SPAN
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::span<GLFWvidmode const>>::type
	Monitor::getVideoModes() const {
		int count;
		GLFWvidmode const *pointer = glfwGetVideoModes(m_monitor, &count);
		std::span<GLFWvidmode const> output(pointer, static_cast<size_t>(count));
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getVideoModes");
	}
# else
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::vector<GLFWvidmode>>::type
	Monitor::getVideoModes() const {
		int count;
		GLFWvidmode const *pointer = glfwGetVideoModes(m_monitor, &count);
		std::vector<GLFWvidmode> output(pointer, pointer + static_cast<size_t>(count));
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getVideoModes");
	}
# endif
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Monitor::setGamma(float gamma) const {
		glfwSetGamma(m_monitor, gamma);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Monitor::setGamma");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<GLFWgammaramp const *>::type
	Monitor::getGammaRamp() const {
		auto *output = glfwGetGammaRamp(m_monitor);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Monitor::getGammaRamp");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Monitor::setGammaRamp(GLFWgammaramp const *ramp) const {
		glfwSetGammaRamp(m_monitor, ramp);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Monitor::setGammaRamp");
	}
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
	VKFW_NODISCARD VKFW_INLINE GLFWwindow *createWindow(size_t width, size_t height, char const *title,
														GLFWmonitor *monitor, GLFWwindow *share) {
		return glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title, monitor, share);
	}
	VKFW_NODISCARD VKFW_INLINE Result destroyWindow(GLFWwindow *window) {
		glfwDestroyWindow(window);
		return getError();
	}
#else
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<Window>::type
	createWindow(size_t width, size_t height, char const *title, WindowHints hints,
				 Monitor monitor, Window share, bool reset_hints) {
		if (reset_hints)
			defaultWindowHints();
		setWindowHints(std::move(hints));

		Window window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
										 title, monitor, share);
		return createResultValue(getError(), window, VKFW_NAMESPACE_STRING"::createWindow");
	}
# ifndef VKFW_NO_SMART_HANDLE
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<UniqueWindow>::type
	createWindowUnique(size_t width, size_t height, char const *title, WindowHints hints,
					   Monitor monitor, Window share, bool reset_hints) {
		if (reset_hints)
			defaultWindowHints();
		setWindowHints(std::move(hints));

		Window window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
										 title, monitor, share);
		return createResultValueUnique(getError(), window, VKFW_NAMESPACE_STRING"::createWindowUnique");
	}
# endif
#endif

#ifdef VKFW_DISABLE_ENHANCED_MODE
	VKFW_NODISCARD VKFW_INLINE bool windowShouldClose(GLFWwindow *window) {
		return static_cast<bool>(glfwWindowShouldClose(window));
	}
	VKFW_INLINE void setWindowShouldClose(GLFWwindow *window, bool value) {
		glfwSetWindowShouldClose(window, static_cast<int>(value));
	}

# ifdef VKFW_HAS_STRING_VIEW
	VKFW_INLINE void setWindowTitle(GLFWwindow *window, std::string_view title) {
		glfwSetWindowTitle(window, title.data());
	}
# else
	VKFW_INLINE void setWindowTitle(GLFWwindow *window, char const *title) {
		glfwSetWindowTitle(window, title);
	}
# endif

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
	VKFW_INLINE void setWindowSizeLimits(GLFWwindow *window,
										 size_t minimum_width, size_t minimum_height,
										 size_t maximum_width, size_t maximum_height) {
		glfwSetWindowSizeLimits(window,
								static_cast<int>(minimum_width),
								static_cast<int>(minimum_height),
								static_cast<int>(maximum_width),
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
	VKFW_INLINE void getWindowFrameSize(GLFWwindow *window,
										size_t *left, size_t *top,
										size_t *right, size_t *bottom) {
		int temp_left, temp_top, temp_right, temp_bottom;
		glfwGetWindowFrameSize(window, 
							   &temp_left, &temp_top, 
							   &temp_right, &temp_bottom);
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
	VKFW_INLINE void iconifyWindow(GLFWwindow *window) {
		glfwIconifyWindow(window);
	}
	VKFW_INLINE void restoreWindow(GLFWwindow *window) {
		glfwRestoreWindow(window);
	}
	VKFW_INLINE void maximizeWindow(GLFWwindow *window) {
		glfwMaximizeWindow(window);
	}
	VKFW_INLINE void showWindow(GLFWwindow *window) {
		glfwShowWindow(window);
	}
	VKFW_INLINE void hideWindow(GLFWwindow *window) {
		glfwHideWindow(window);
	}
	VKFW_INLINE void focusWindow(GLFWwindow *window) {
		glfwFocusWindow(window);
	}
	VKFW_INLINE void requestWindowAttention(GLFWwindow *window) {
		glfwRequestWindowAttention(window);
	}
	VKFW_NODISCARD VKFW_INLINE GLFWmonitor *getWindowMonitor(GLFWwindow *window) {
		return glfwGetWindowMonitor(window);
	}
	VKFW_INLINE void setWindowMonitor(GLFWwindow *window, GLFWmonitor *monitor, 
									  int xpos, int ypos, size_t width, size_t height, 
									  size_t refreshRate) {
		glfwSetWindowMonitor(window, monitor, xpos, ypos,
							 static_cast<int>(width), static_cast<int>(height),
							 static_cast<int>(refreshRate));
	}
#else
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<bool>::type Window::shouldClose() const {
		auto output = static_cast<bool>(glfwWindowShouldClose(m_window));
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Window::shouldClose");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setShouldClose(bool value) const {
		glfwSetWindowShouldClose(m_window, value);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setShouldClose");
	}

# ifdef VKFW_HAS_STRING_VIEW
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setTitle(std::string_view title) const {
		glfwSetWindowTitle(m_window, title.data());
# else
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setTitle(char const *title) const {
		glfwSetWindowTitle(m_window, title);
# endif
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setTitle");
	}

	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::getPos(int *xpos, int *ypos) const {
		glfwGetWindowPos(m_window, xpos, ypos);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::getPos");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<int, int>>::type 
	Window::getPos() const {
		std::tuple<int, int> output;
		glfwGetWindowPos(m_window, &std::get<0>(output), &std::get<1>(output));
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Window::getPos");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type 
	Window::getPosX() const {
		int output;
		glfwGetWindowPos(m_window, &output, nullptr);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Window::getPosX");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<int>::type 
	Window::getPosY() const {
		int output;
		glfwGetWindowPos(m_window, nullptr, &output);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Window::getPosY");
	}

	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setPos(int xpos, int ypos) const {
		glfwSetWindowPos(m_window, xpos, ypos);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setPos");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setPos(std::tuple<int, int> pos) const {
		glfwSetWindowPos(m_window, std::get<0>(pos), std::get<1>(pos));
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setPos");
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
		return createResultValue(result, VKFW_NAMESPACE_STRING"::Window::getSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getWidth");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getHeight");
	}

	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setSize(size_t width, size_t height) {
		glfwSetWindowSize(m_window, static_cast<int>(width), static_cast<int>(height));
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setSize");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setSize(std::tuple<size_t, size_t> size) {
		glfwSetWindowSize(m_window, 
						  static_cast<int>(std::get<0>(size)), 
						  static_cast<int>(std::get<1>(size)));
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setSize");
	}

	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setSizeLimits(size_t minimum_width, size_t minimum_height,
						  size_t maximum_width, size_t maximum_height) {
		glfwSetWindowSizeLimits(m_window,
								static_cast<int>(minimum_width),
								static_cast<int>(minimum_height),
								static_cast<int>(maximum_width),
								static_cast<int>(maximum_height));
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setSizeLimits");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setSizeLimits(std::tuple<size_t, size_t> minimum_size,
						  std::tuple<size_t, size_t> maximum_size) {
		glfwSetWindowSizeLimits(m_window,
								static_cast<int>(std::get<0>(minimum_size)),
								static_cast<int>(std::get<1>(minimum_size)),
								static_cast<int>(std::get<0>(maximum_size)),
								static_cast<int>(std::get<1>(maximum_size)));
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setSizeLimits");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setSizeLimits(std::tuple<size_t, size_t, size_t, size_t> limits) {
		glfwSetWindowSizeLimits(m_window,
								static_cast<int>(std::get<0>(limits)),
								static_cast<int>(std::get<1>(limits)),
								static_cast<int>(std::get<2>(limits)),
								static_cast<int>(std::get<3>(limits)));
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setSizeLimits");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setAspectRatio(size_t numerator, size_t denominator) {
		glfwSetWindowAspectRatio(m_window, 
								 static_cast<int>(numerator),
								 static_cast<int>(denominator));
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setAspectRatio");
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
		return createResultValue(result, VKFW_NAMESPACE_STRING"::Window::getFramebufferSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getFramebufferSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getFramebufferWidth");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getFramebufferHeight");
	}

	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::getFrameSize(size_t *left, size_t *top,
						 size_t *right, size_t *bottom) {
		int temp_left, temp_top, temp_right, temp_bottom;
		glfwGetWindowFrameSize(m_window, 
							   &temp_left, &temp_top, 
							   &temp_right, &temp_bottom);
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
		return createResultValue(result, VKFW_NAMESPACE_STRING"::Window::getFrameSize");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<size_t, size_t, size_t, size_t>>::type
	Window::getFrameSize() const {
		std::tuple<size_t, size_t, size_t, size_t> output;
		int temp_left, temp_top, temp_right, temp_bottom;
		glfwGetWindowFrameSize(m_window,
							   &temp_left, &temp_top,
							   &temp_right, &temp_bottom);
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getFrameSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getLeftFrameSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getTopFrameSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getRightFrameSize");
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
		return createResultValue(result, output, VKFW_NAMESPACE_STRING"::Window::getBottomFrameSize");
	}
	
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::getContentScale(float *xscale, float *yscale) const {
		glfwGetWindowContentScale(m_window, xscale, yscale);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::getContentScale");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<std::tuple<float, float>>::type
	Window::getContentScale() const {
		std::tuple<float, float> output;
		glfwGetWindowContentScale(m_window, &std::get<0>(output), &std::get<1>(output));
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Window::getContentScale");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<float>::type 
	Window::getContentScaleX() const {
		float output;
		glfwGetWindowContentScale(m_window, &output, nullptr);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Window::getContentScaleX");
	}
	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<float>::type 
	Window::getContentScaleY() const {
		float output;
		glfwGetWindowContentScale(m_window, nullptr, &output);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Window::getContentScaleY");
	}

	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<float>::type Window::getOpacity() const {
		auto output = glfwGetWindowOpacity(m_window);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Window::getOpacity");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setOpacity(float opacity) {
		glfwSetWindowOpacity(m_window, opacity);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setOpacity");
	}

	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type Window::iconify() {
		glfwIconifyWindow(m_window);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::iconify");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type Window::restore() {
		glfwRestoreWindow(m_window);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::restore");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type Window::maximize() {
		glfwMaximizeWindow(m_window);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::maximize");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type Window::show() {
		glfwShowWindow(m_window);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::show");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type Window::hide() {
		glfwHideWindow(m_window);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::hide");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type Window::focus() {
		glfwFocusWindow(m_window);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::focus");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type Window::requestAttention() {
		glfwRequestWindowAttention(m_window);
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::requestAttention");
	}

	VKFW_NODISCARD VKFW_INLINE typename ResultValueType<Monitor>::type Window::getMonitor() {
		Monitor output = glfwGetWindowMonitor(m_window);
		return createResultValue(getError(), output, VKFW_NAMESPACE_STRING"::Window::getMonitor");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setMonitor(Monitor const &monitor, int xpos, int ypos,
					   size_t width, size_t height, size_t refreshRate) {
		glfwSetWindowMonitor(m_window, monitor, xpos, ypos,
							 static_cast<int>(width), static_cast<int>(height),
							 static_cast<int>(refreshRate));
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setMonitor");
	}
	VKFW_NODISCARD_WHEN_NO_EXCEPTIONS VKFW_INLINE typename ResultValueType<void>::type
	Window::setMonitor(Monitor const &monitor, std::tuple<int, int> pos,
					   std::tuple<size_t, size_t> size, size_t refreshRate) {
		glfwSetWindowMonitor(m_window, monitor, std::get<0>(pos), std::get<1>(pos),
							 static_cast<int>(std::get<0>(size)), static_cast<int>(std::get<1>(size)),
							 static_cast<int>(refreshRate));
		return createResultValue(getError(), VKFW_NAMESPACE_STRING"::Window::setMonitor");
	}
#endif
}
#pragma once
// Copyright (c) 2020 Cvelth.
//
// SPDX-License-Identifier: Apache-2.0
//

#if defined(_MSVC_LANG)
#  define VKFW_CPLUSPLUS _MSVC_LANG
#else
#  define VKFW_CPLUSPLUS __cplusplus
#endif

#if 201703L < VKFW_CPLUSPLUS
#  define VKFW_CPP_VERSION 20
#elif 201402L < VKFW_CPLUSPLUS
#  define VKFW_CPP_VERSION 17
#elif 201103L < VKFW_CPLUSPLUS
#  define VKFW_CPP_VERSION 14
#elif 199711L < VKFW_CPLUSPLUS
#  define VKFW_CPP_VERSION 11
#else
#  error "vkfw.hpp needs at least c++ standard version 11"
#endif

// Standard library includes go here!
#include <string>

#if 17 <= VULKAN_HPP_CPP_VERSION
#  include <string_view>
#endif

#if !defined(VKFW_INCLUDE_GL)
#  define GLFW_INCLUDE_NONE
#endif
#if !defined(VKFW_NO_INCLUDE_VULKAN)
#  define GLFW_INCLUDE_VULKAN
#endif

#include <GLFW/glfw3.h>
//#if !defined(VKFW_NO_INCLUDE_VULKAN_HPP)
#  include <vulkan/vulkan.hpp>
//#endif

#if defined(VKFW_DISABLE_ENHANCED_MODE)
#  if !defined(VKFW_NO_SMART_HANDLE)
#    define VKFW_NO_SMART_HANDLE
#  endif
#else
#  include <memory>
#  include <vector>
#endif

#if !defined(VKFW_ASSERT)
#  include <cassert>
#  define VKFW_ASSERT assert
#endif

#if !defined(VKFW_ASSERT_ON_RESULT)
# define VKFW_ASSERT_ON_RESULT VKFW_ASSERT
#endif

#define VKFW_VERSION_MAJOR 0
#define VKFW_VERSION_MINOR 3
#define VKFW_VERSION_PATCH 0
static_assert(GLFW_VERSION_MAJOR == 3
			  && GLFW_VERSION_MINOR == 3
			  && GLFW_VERSION_REVISION == 2
			  , "\"glfw3.h\" version is not compatible with the \"vkfw.hpp\" version!");

#if !defined(VKFW_INLINE)
#  if defined(__clang__)
#    if __has_attribute(always_inline)
#      define VKFW_INLINE __attribute__((always_inline)) __inline__
#    else
#      define VKFW_INLINE inline
#    endif
#  elif defined(__GNUC__)
#    define VKFW_INLINE __attribute__((always_inline)) __inline__
#  elif defined(_MSC_VER)
#    define VKFW_INLINE inline
#  else
#    define VKFW_INLINE inline
#  endif
#endif

#if defined(VKFW_TYPESAFE_CONVERSION)
#  define VKFW_TYPESAFE_EXPLICIT
#else
#  define VKFW_TYPESAFE_EXPLICIT explicit
#endif

#if defined(__cpp_constexpr)
#  define VKFW_CONSTEXPR constexpr
#  if __cpp_constexpr >= 201304
#    define VKFW_CONSTEXPR_14  constexpr
#  else
#    define VKFW_CONSTEXPR_14
#  endif
#  define VKFW_CONST_OR_CONSTEXPR  constexpr
#else
#  define VKFW_CONSTEXPR
#  define VKFW_CONSTEXPR_14
#  define VKFW_CONST_OR_CONSTEXPR  const
#endif

#if !defined(VKFW_NOEXCEPT)
#  if defined(_MSC_VER) && (_MSC_VER <= 1800)
#    define VKFW_NOEXCEPT
#  else
#    define VKFW_NOEXCEPT noexcept
#    define VKFW_HAS_NOEXCEPT 1
#  endif
#endif

#if 14 <= VKFW_CPP_VERSION
#  define VKFW_DEPRECATED( msg ) [[deprecated( msg )]]
#else
#  define VKFW_DEPRECATED( msg )
#endif

#if ( 17 <= VKFW_CPP_VERSION ) && !defined( VKFW_NO_NODISCARD_WARNINGS )
#  define VKFW_NODISCARD [[nodiscard]]
#  if defined(VKFW_NO_EXCEPTIONS)
#    define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS [[nodiscard]]
#  else
#    define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS
#  endif
#else
#  define VKFW_NODISCARD
#  define VKFW_NODISCARD_WHEN_NO_EXCEPTIONS
#endif

#if !defined(VKFW_NAMESPACE)
#define VKFW_NAMESPACE vkfw
#endif

#define VKFW_STRINGIFY2(text) #text
#define VKFW_STRINGIFY(text) VKFW_STRINGIFY2(text)
#define VKFW_NAMESPACE_STRING VKFW_STRINGIFY(VKFW_NAMESPACE)

#if !(defined(VKFW_CHAR_T) && defined(VKFW_CHAR_LITERAL))
#  if defined(VKFW_USE_CHAR8_T) && defined(__cpp_char8_t) && defined(__cpp_lib_char8_t)
#    define VKFW_CHAR_T char8_t
#    define VKFW_CHAR_LITERAL u8""
#  elif defined(VKFW_USE_CHAR16_T)
#    define VKFW_CHAR_T char16_t
#    define VKFW_CHAR_LITERAL u""
#  elif defined(VKFW_USE_CHAR32_T)
#    define VKFW_CHAR_T char32_t
#    define VKFW_CHAR_LITERAL U""
#  elif defined(VKFW_USE_WCHAR_T)
#    define VKFW_CHAR_T wchar_t
#    define VKFW_CHAR_LITERAL L""
#  else
#    define VKFW_CHAR_T char
#    define VKFW_CHAR_LITERAL
#  endif
#endif

#define VKFW_STRING_T std::basic_string<VKFW_CHAR_T>
#if 17 <= VKFW_CPP_VERSION
#  define VKFW_STRING_VIEW_T std::basic_string_view<VKFW_CHAR_T>
#endif

#if defined(VKFW_NO_LEADING_e_IN_ENUMS)
#  define VKFW_ENUMERATOR(name) name
#  define VKFW_ENUMERATOR2(name_1, name_2) name_2
#else
#  define VKFW_ENUMERATOR(name) e ## name
#  define VKFW_ENUMERATOR2(name_1, name_2) e ## name_1
#endif

namespace VKFW_NAMESPACE {
	template <typename RefType> using Optional
		= VULKAN_HPP_NAMESPACE::Optional<RefType>;
	template <typename BitType> using Flags
		= VULKAN_HPP_NAMESPACE::Flags<BitType>;
	template <typename FlagBitsType> using FlagTraits
		= VULKAN_HPP_NAMESPACE::FlagTraits<FlagBitsType>;

#if !defined(VKFW_NO_SMART_HANDLE)
	template <typename Type> using UniqueHandleTraits
		= VULKAN_HPP_NAMESPACE::UniqueHandleTraits<Type, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE>;
	template <typename Type> using UniqueHandle
		= VULKAN_HPP_NAMESPACE::UniqueHandle<Type, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE>;
#endif

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
	enum class Error {
		VKFW_ENUMERATOR(None) = GLFW_NO_ERROR,
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

	enum class ModifierKeyBits {
		VKFW_ENUMERATOR(Shift) = GLFW_MOD_SHIFT,
		VKFW_ENUMERATOR(Control) = GLFW_MOD_CONTROL,
		VKFW_ENUMERATOR(Alt) = GLFW_MOD_ALT,
		VKFW_ENUMERATOR(Super) = GLFW_MOD_SUPER,
		VKFW_ENUMERATOR(CapsLock) = GLFW_MOD_CAPS_LOCK,
		VKFW_ENUMERATOR(NumLock) = GLFW_MOD_NUM_LOCK
	};
	using ModifierKeyFlags = Flags<ModifierKeyBits>;
	VKFW_INLINE VKFW_CONSTEXPR ModifierKeyFlags operator|(ModifierKeyBits bit0, ModifierKeyBits bit1) VKFW_NOEXCEPT {
		return ModifierKeyFlags(bit0) | bit1;
	}
	VKFW_INLINE VKFW_CONSTEXPR ModifierKeyFlags operator&(ModifierKeyBits bit0, ModifierKeyBits bit1) VKFW_NOEXCEPT {
		return ModifierKeyFlags(bit0) & bit1;
	}
	VKFW_INLINE VKFW_CONSTEXPR ModifierKeyFlags operator^(ModifierKeyBits bit0, ModifierKeyBits bit1) VKFW_NOEXCEPT {
		return ModifierKeyFlags(bit0) ^ bit1;
	}
	VKFW_INLINE VKFW_CONSTEXPR ModifierKeyFlags operator~(ModifierKeyBits bits) VKFW_NOEXCEPT {
		return ~(ModifierKeyFlags(bits));
	}

	VKFW_INLINE VKFW_STRING_T to_string(Boolean value) {
		switch (value) {
			case Boolean::VKFW_ENUMERATOR(True): return VKFW_CHAR_LITERAL"True";
			case Boolean::VKFW_ENUMERATOR(False): return VKFW_CHAR_LITERAL"False";
			default: return VKFW_CHAR_LITERAL"invalid";
		}
	}
	VKFW_INLINE VKFW_STRING_T to_string(KeyAction value) {
		switch (value) {
			case KeyAction::VKFW_ENUMERATOR(Release): return VKFW_CHAR_LITERAL"Release";
			case KeyAction::VKFW_ENUMERATOR(Press): return VKFW_CHAR_LITERAL"Press";
			case KeyAction::VKFW_ENUMERATOR(Repeat): return VKFW_CHAR_LITERAL"Repeat";
			default: return VKFW_CHAR_LITERAL"invalid";
		}
	}
	VKFW_INLINE VKFW_STRING_T to_string(MouseButtonAction value) {
		switch (value) {
			case MouseButtonAction::VKFW_ENUMERATOR(Release): return VKFW_CHAR_LITERAL"Release";
			case MouseButtonAction::VKFW_ENUMERATOR(Press): return VKFW_CHAR_LITERAL"Press";
			default: return VKFW_CHAR_LITERAL"invalid";
		}
	}
	VKFW_INLINE VKFW_STRING_T to_string(JoystickHatState value) {
		switch (value) {
			case JoystickHatState::VKFW_ENUMERATOR(Centered): return VKFW_CHAR_LITERAL"Centered";
			case JoystickHatState::VKFW_ENUMERATOR(Up): return VKFW_CHAR_LITERAL"Up";
			case JoystickHatState::VKFW_ENUMERATOR(Right): return VKFW_CHAR_LITERAL"Right";
			case JoystickHatState::VKFW_ENUMERATOR(Down): return VKFW_CHAR_LITERAL"Down";
			case JoystickHatState::VKFW_ENUMERATOR(Left): return VKFW_CHAR_LITERAL"Left";
			case JoystickHatState::VKFW_ENUMERATOR(Right_Up): return VKFW_CHAR_LITERAL"Right Up";
			case JoystickHatState::VKFW_ENUMERATOR(Right_Down): return VKFW_CHAR_LITERAL"Right Down";
			case JoystickHatState::VKFW_ENUMERATOR(Left_Up): return VKFW_CHAR_LITERAL"Left Up";
			case JoystickHatState::VKFW_ENUMERATOR(Left_Down): return VKFW_CHAR_LITERAL"Left Down";
			default: return VKFW_CHAR_LITERAL"invalid";
		}
	}
	VKFW_INLINE VKFW_STRING_T to_string(Key value) {
		switch (value) {
			case Key::VKFW_ENUMERATOR(Unknown): return VKFW_CHAR_LITERAL"Unknown";

				/* Printable Keys */
			case Key::VKFW_ENUMERATOR(Space): return VKFW_CHAR_LITERAL"Space";
			case Key::VKFW_ENUMERATOR(Apostrophe): return VKFW_CHAR_LITERAL"Apostrophe";
			case Key::VKFW_ENUMERATOR(Comma): return VKFW_CHAR_LITERAL"Comma";
			case Key::VKFW_ENUMERATOR(Minus): return VKFW_CHAR_LITERAL"Minus";
			case Key::VKFW_ENUMERATOR(Period): return VKFW_CHAR_LITERAL"Period";
			case Key::VKFW_ENUMERATOR(Slash): return VKFW_CHAR_LITERAL"Slash";
			case Key::VKFW_ENUMERATOR2(0, _0): return VKFW_CHAR_LITERAL"0";
			case Key::VKFW_ENUMERATOR2(1, _1): return VKFW_CHAR_LITERAL"1";
			case Key::VKFW_ENUMERATOR2(2, _2): return VKFW_CHAR_LITERAL"2";
			case Key::VKFW_ENUMERATOR2(3, _3): return VKFW_CHAR_LITERAL"3";
			case Key::VKFW_ENUMERATOR2(4, _4): return VKFW_CHAR_LITERAL"4";
			case Key::VKFW_ENUMERATOR2(5, _5): return VKFW_CHAR_LITERAL"5";
			case Key::VKFW_ENUMERATOR2(6, _6): return VKFW_CHAR_LITERAL"6";
			case Key::VKFW_ENUMERATOR2(7, _7): return VKFW_CHAR_LITERAL"7";
			case Key::VKFW_ENUMERATOR2(8, _8): return VKFW_CHAR_LITERAL"8";
			case Key::VKFW_ENUMERATOR2(9, _9): return VKFW_CHAR_LITERAL"9";
			case Key::VKFW_ENUMERATOR(Semicolon): return VKFW_CHAR_LITERAL"Semicolon";
			case Key::VKFW_ENUMERATOR(Equal): return VKFW_CHAR_LITERAL"Equal";
			case Key::VKFW_ENUMERATOR(A): return VKFW_CHAR_LITERAL"A";
			case Key::VKFW_ENUMERATOR(B): return VKFW_CHAR_LITERAL"B";
			case Key::VKFW_ENUMERATOR(C): return VKFW_CHAR_LITERAL"C";
			case Key::VKFW_ENUMERATOR(D): return VKFW_CHAR_LITERAL"D";
			case Key::VKFW_ENUMERATOR(E): return VKFW_CHAR_LITERAL"E";
			case Key::VKFW_ENUMERATOR(F): return VKFW_CHAR_LITERAL"F";
			case Key::VKFW_ENUMERATOR(G): return VKFW_CHAR_LITERAL"G";
			case Key::VKFW_ENUMERATOR(H): return VKFW_CHAR_LITERAL"H";
			case Key::VKFW_ENUMERATOR(I): return VKFW_CHAR_LITERAL"I";
			case Key::VKFW_ENUMERATOR(J): return VKFW_CHAR_LITERAL"J";
			case Key::VKFW_ENUMERATOR(K): return VKFW_CHAR_LITERAL"K";
			case Key::VKFW_ENUMERATOR(L): return VKFW_CHAR_LITERAL"L";
			case Key::VKFW_ENUMERATOR(M): return VKFW_CHAR_LITERAL"M";
			case Key::VKFW_ENUMERATOR(N): return VKFW_CHAR_LITERAL"N";
			case Key::VKFW_ENUMERATOR(O): return VKFW_CHAR_LITERAL"O";
			case Key::VKFW_ENUMERATOR(P): return VKFW_CHAR_LITERAL"P";
			case Key::VKFW_ENUMERATOR(Q): return VKFW_CHAR_LITERAL"Q";
			case Key::VKFW_ENUMERATOR(R): return VKFW_CHAR_LITERAL"R";
			case Key::VKFW_ENUMERATOR(S): return VKFW_CHAR_LITERAL"S";
			case Key::VKFW_ENUMERATOR(T): return VKFW_CHAR_LITERAL"T";
			case Key::VKFW_ENUMERATOR(U): return VKFW_CHAR_LITERAL"U";
			case Key::VKFW_ENUMERATOR(V): return VKFW_CHAR_LITERAL"V";
			case Key::VKFW_ENUMERATOR(W): return VKFW_CHAR_LITERAL"W";
			case Key::VKFW_ENUMERATOR(X): return VKFW_CHAR_LITERAL"X";
			case Key::VKFW_ENUMERATOR(Y): return VKFW_CHAR_LITERAL"Y";
			case Key::VKFW_ENUMERATOR(Z): return VKFW_CHAR_LITERAL"Z";
			case Key::VKFW_ENUMERATOR(LeftBracket): return VKFW_CHAR_LITERAL"LeftBracket";
			case Key::VKFW_ENUMERATOR(Backslash): return VKFW_CHAR_LITERAL"Backslash";
			case Key::VKFW_ENUMERATOR(RightBracket): return VKFW_CHAR_LITERAL"RightBracket";
			case Key::VKFW_ENUMERATOR(GraveAccent): return VKFW_CHAR_LITERAL"GraveAccent";
			case Key::VKFW_ENUMERATOR(World1): return VKFW_CHAR_LITERAL"World1";
			case Key::VKFW_ENUMERATOR(World2): return VKFW_CHAR_LITERAL"World2";

				/* Function Keys */
			case Key::VKFW_ENUMERATOR(Escape): return VKFW_CHAR_LITERAL"Escape";
			case Key::VKFW_ENUMERATOR(Enter): return VKFW_CHAR_LITERAL"Enter";
			case Key::VKFW_ENUMERATOR(Tab): return VKFW_CHAR_LITERAL"Tab";
			case Key::VKFW_ENUMERATOR(Backspace): return VKFW_CHAR_LITERAL"Backspace";
			case Key::VKFW_ENUMERATOR(Insert): return VKFW_CHAR_LITERAL"Insert";
			case Key::VKFW_ENUMERATOR(Delete): return VKFW_CHAR_LITERAL"Delete";
			case Key::VKFW_ENUMERATOR(Right): return VKFW_CHAR_LITERAL"Right";
			case Key::VKFW_ENUMERATOR(Left): return VKFW_CHAR_LITERAL"Left";
			case Key::VKFW_ENUMERATOR(Down): return VKFW_CHAR_LITERAL"Down";
			case Key::VKFW_ENUMERATOR(Up): return VKFW_CHAR_LITERAL"Up";
			case Key::VKFW_ENUMERATOR(PageUp): return VKFW_CHAR_LITERAL"PageUp";
			case Key::VKFW_ENUMERATOR(PageDown): return VKFW_CHAR_LITERAL"PageDown";
			case Key::VKFW_ENUMERATOR(Home): return VKFW_CHAR_LITERAL"Home";
			case Key::VKFW_ENUMERATOR(End): return VKFW_CHAR_LITERAL"End";
			case Key::VKFW_ENUMERATOR(CapsLock): return VKFW_CHAR_LITERAL"CapsLock";
			case Key::VKFW_ENUMERATOR(ScrollLock): return VKFW_CHAR_LITERAL"ScrollLock";
			case Key::VKFW_ENUMERATOR(NumLock): return VKFW_CHAR_LITERAL"NumLock";
			case Key::VKFW_ENUMERATOR(PrintScreen): return VKFW_CHAR_LITERAL"PrintScreen";
			case Key::VKFW_ENUMERATOR(Pause): return VKFW_CHAR_LITERAL"Pause";
			case Key::VKFW_ENUMERATOR(F1): return VKFW_CHAR_LITERAL"F1";
			case Key::VKFW_ENUMERATOR(F2): return VKFW_CHAR_LITERAL"F2";
			case Key::VKFW_ENUMERATOR(F3): return VKFW_CHAR_LITERAL"F3";
			case Key::VKFW_ENUMERATOR(F4): return VKFW_CHAR_LITERAL"F4";
			case Key::VKFW_ENUMERATOR(F5): return VKFW_CHAR_LITERAL"F5";
			case Key::VKFW_ENUMERATOR(F6): return VKFW_CHAR_LITERAL"F6";
			case Key::VKFW_ENUMERATOR(F7): return VKFW_CHAR_LITERAL"F7";
			case Key::VKFW_ENUMERATOR(F8): return VKFW_CHAR_LITERAL"F8";
			case Key::VKFW_ENUMERATOR(F9): return VKFW_CHAR_LITERAL"F9";
			case Key::VKFW_ENUMERATOR(F10): return VKFW_CHAR_LITERAL"F10";
			case Key::VKFW_ENUMERATOR(F11): return VKFW_CHAR_LITERAL"F11";
			case Key::VKFW_ENUMERATOR(F12): return VKFW_CHAR_LITERAL"F12";
			case Key::VKFW_ENUMERATOR(F13): return VKFW_CHAR_LITERAL"F13";
			case Key::VKFW_ENUMERATOR(F14): return VKFW_CHAR_LITERAL"F14";
			case Key::VKFW_ENUMERATOR(F15): return VKFW_CHAR_LITERAL"F15";
			case Key::VKFW_ENUMERATOR(F16): return VKFW_CHAR_LITERAL"F16";
			case Key::VKFW_ENUMERATOR(F17): return VKFW_CHAR_LITERAL"F17";
			case Key::VKFW_ENUMERATOR(F18): return VKFW_CHAR_LITERAL"F18";
			case Key::VKFW_ENUMERATOR(F19): return VKFW_CHAR_LITERAL"F19";
			case Key::VKFW_ENUMERATOR(F20): return VKFW_CHAR_LITERAL"F20";
			case Key::VKFW_ENUMERATOR(F21): return VKFW_CHAR_LITERAL"F21";
			case Key::VKFW_ENUMERATOR(F22): return VKFW_CHAR_LITERAL"F22";
			case Key::VKFW_ENUMERATOR(F23): return VKFW_CHAR_LITERAL"F23";
			case Key::VKFW_ENUMERATOR(F24): return VKFW_CHAR_LITERAL"F24";
			case Key::VKFW_ENUMERATOR(F25): return VKFW_CHAR_LITERAL"F25";
			case Key::VKFW_ENUMERATOR(KeyPad_0): return VKFW_CHAR_LITERAL"KeyPad 0";
			case Key::VKFW_ENUMERATOR(KeyPad_1): return VKFW_CHAR_LITERAL"KeyPad 1";
			case Key::VKFW_ENUMERATOR(KeyPad_2): return VKFW_CHAR_LITERAL"KeyPad 2";
			case Key::VKFW_ENUMERATOR(KeyPad_3): return VKFW_CHAR_LITERAL"KeyPad 3";
			case Key::VKFW_ENUMERATOR(KeyPad_4): return VKFW_CHAR_LITERAL"KeyPad 4";
			case Key::VKFW_ENUMERATOR(KeyPad_5): return VKFW_CHAR_LITERAL"KeyPad 5";
			case Key::VKFW_ENUMERATOR(KeyPad_6): return VKFW_CHAR_LITERAL"KeyPad 6";
			case Key::VKFW_ENUMERATOR(KeyPad_7): return VKFW_CHAR_LITERAL"KeyPad 7";
			case Key::VKFW_ENUMERATOR(KeyPad_8): return VKFW_CHAR_LITERAL"KeyPad 8";
			case Key::VKFW_ENUMERATOR(KeyPad_9): return VKFW_CHAR_LITERAL"KeyPad 9";
			case Key::VKFW_ENUMERATOR(KeyPad_Decimal): return VKFW_CHAR_LITERAL"KeyPad Decimal";
			case Key::VKFW_ENUMERATOR(KeyPad_Divide): return VKFW_CHAR_LITERAL"KeyPad Divide";
			case Key::VKFW_ENUMERATOR(KeyPad_Multiply): return VKFW_CHAR_LITERAL"KeyPad Multiply";
			case Key::VKFW_ENUMERATOR(KeyPad_Subtract): return VKFW_CHAR_LITERAL"KeyPad Subtract";
			case Key::VKFW_ENUMERATOR(KeyPad_Add): return VKFW_CHAR_LITERAL"KeyPad Add";
			case Key::VKFW_ENUMERATOR(KeyPad_Enter): return VKFW_CHAR_LITERAL"KeyPad Enter";
			case Key::VKFW_ENUMERATOR(KeyPad_Equal): return VKFW_CHAR_LITERAL"KeyPad Equal";
			case Key::VKFW_ENUMERATOR(LeftShift): return VKFW_CHAR_LITERAL"LeftShift";
			case Key::VKFW_ENUMERATOR(LeftControl): return VKFW_CHAR_LITERAL"LeftControl";
			case Key::VKFW_ENUMERATOR(LeftAlt): return VKFW_CHAR_LITERAL"LeftAlt";
			case Key::VKFW_ENUMERATOR(LeftSuper): return VKFW_CHAR_LITERAL"LeftSuper";
			case Key::VKFW_ENUMERATOR(RightShift): return VKFW_CHAR_LITERAL"RightShift";
			case Key::VKFW_ENUMERATOR(RightControl): return VKFW_CHAR_LITERAL"RightControl";
			case Key::VKFW_ENUMERATOR(RightAlt): return VKFW_CHAR_LITERAL"RightAlt";
			case Key::VKFW_ENUMERATOR(RightSuper): return VKFW_CHAR_LITERAL"RightSuper";
			case Key::VKFW_ENUMERATOR(Menu): return VKFW_CHAR_LITERAL"Menu";
			default: return VKFW_CHAR_LITERAL"invalid";
		}
	}
	VKFW_INLINE VKFW_STRING_T to_string(MouseButton value) {
		switch (value) {
			case MouseButton::VKFW_ENUMERATOR2(1, _1):	return VKFW_CHAR_LITERAL"1 (left)";
			case MouseButton::VKFW_ENUMERATOR2(2, _2):return VKFW_CHAR_LITERAL"2 (right)";
			case MouseButton::VKFW_ENUMERATOR2(3, _3):return VKFW_CHAR_LITERAL"3 (middle)";
			case MouseButton::VKFW_ENUMERATOR2(4, _4):return VKFW_CHAR_LITERAL"4";
			case MouseButton::VKFW_ENUMERATOR2(5, _5):return VKFW_CHAR_LITERAL"5";
			case MouseButton::VKFW_ENUMERATOR2(6, _6):	return VKFW_CHAR_LITERAL"6";
			case MouseButton::VKFW_ENUMERATOR2(7, _7):	return VKFW_CHAR_LITERAL"7";
			case MouseButton::VKFW_ENUMERATOR2(8, _8):	return VKFW_CHAR_LITERAL"8";
			default: return VKFW_CHAR_LITERAL"invalid";
		}
	}
	VKFW_INLINE VKFW_STRING_T to_string(Joystick value) {
		switch (value) {
			case Joystick::VKFW_ENUMERATOR2(1, _1): return VKFW_CHAR_LITERAL"1";
			case Joystick::VKFW_ENUMERATOR2(2, _2): return VKFW_CHAR_LITERAL"2";
			case Joystick::VKFW_ENUMERATOR2(3, _3): return VKFW_CHAR_LITERAL"3";
			case Joystick::VKFW_ENUMERATOR2(4, _4): return VKFW_CHAR_LITERAL"4";
			case Joystick::VKFW_ENUMERATOR2(5, _5): return VKFW_CHAR_LITERAL"5";
			case Joystick::VKFW_ENUMERATOR2(6, _6): return VKFW_CHAR_LITERAL"6";
			case Joystick::VKFW_ENUMERATOR2(7, _7): return VKFW_CHAR_LITERAL"7";
			case Joystick::VKFW_ENUMERATOR2(8, _8): return VKFW_CHAR_LITERAL"8";
			case Joystick::VKFW_ENUMERATOR2(9, _9): return VKFW_CHAR_LITERAL"9";
			case Joystick::VKFW_ENUMERATOR2(10, _10): return VKFW_CHAR_LITERAL"10";
			case Joystick::VKFW_ENUMERATOR2(11, _11): return VKFW_CHAR_LITERAL"11";
			case Joystick::VKFW_ENUMERATOR2(12, _12): return VKFW_CHAR_LITERAL"12";
			case Joystick::VKFW_ENUMERATOR2(13, _13): return VKFW_CHAR_LITERAL"13";
			case Joystick::VKFW_ENUMERATOR2(14, _14): return VKFW_CHAR_LITERAL"14";
			case Joystick::VKFW_ENUMERATOR2(15, _15): return VKFW_CHAR_LITERAL"15";
			case Joystick::VKFW_ENUMERATOR2(16, _16): return VKFW_CHAR_LITERAL"16";
			default: return VKFW_CHAR_LITERAL"invalid";
		}
	}
	VKFW_INLINE VKFW_STRING_T to_string(GamepadButton value) {
		switch (value) {
			case GamepadButton::VKFW_ENUMERATOR(A): return VKFW_CHAR_LITERAL"A (Cross)";
			case GamepadButton::VKFW_ENUMERATOR(B): return VKFW_CHAR_LITERAL"B (Circle)";
			case GamepadButton::VKFW_ENUMERATOR(X): return VKFW_CHAR_LITERAL"X (Square)";
			case GamepadButton::VKFW_ENUMERATOR(Y): return VKFW_CHAR_LITERAL"Y (Triangle)";
			case GamepadButton::VKFW_ENUMERATOR(LeftBumper): return VKFW_CHAR_LITERAL"Left Bumper";
			case GamepadButton::VKFW_ENUMERATOR(RightBumper): return VKFW_CHAR_LITERAL"Right Bumper";
			case GamepadButton::VKFW_ENUMERATOR(Back): return VKFW_CHAR_LITERAL"Back";
			case GamepadButton::VKFW_ENUMERATOR(Start): return VKFW_CHAR_LITERAL"Start";
			case GamepadButton::VKFW_ENUMERATOR(Guide): return VKFW_CHAR_LITERAL"Guide";
			case GamepadButton::VKFW_ENUMERATOR(LeftThumb): return VKFW_CHAR_LITERAL"Left Thumb";
			case GamepadButton::VKFW_ENUMERATOR(RightThumb): return VKFW_CHAR_LITERAL"Right Thumb";
			case GamepadButton::VKFW_ENUMERATOR(DpadUp): return VKFW_CHAR_LITERAL"Dpad Up";
			case GamepadButton::VKFW_ENUMERATOR(DpadRight): return VKFW_CHAR_LITERAL"Dpad Right";
			case GamepadButton::VKFW_ENUMERATOR(DpadDown): return VKFW_CHAR_LITERAL"Dpad Down";
			case GamepadButton::VKFW_ENUMERATOR(DpadLeft): return VKFW_CHAR_LITERAL"Dpad Left";
			default: return VKFW_CHAR_LITERAL"invalid";
		}
	}
	VKFW_INLINE VKFW_STRING_T to_string(GamepadAxis value) {
		switch (value) {
			case GamepadAxis::VKFW_ENUMERATOR(LeftX): return VKFW_CHAR_LITERAL"Left X";
			case GamepadAxis::VKFW_ENUMERATOR(LeftY): return VKFW_CHAR_LITERAL"Left Y";
			case GamepadAxis::VKFW_ENUMERATOR(RightX): return VKFW_CHAR_LITERAL"Right X";
			case GamepadAxis::VKFW_ENUMERATOR(RightY): return VKFW_CHAR_LITERAL"Right Y";
			case GamepadAxis::VKFW_ENUMERATOR(LeftTrigger): return VKFW_CHAR_LITERAL"Left Trigger";
			case GamepadAxis::VKFW_ENUMERATOR(RightTrigger): return VKFW_CHAR_LITERAL"Right Trigger";
			default: return VKFW_CHAR_LITERAL"invalid";
		}
	}
	VKFW_INLINE VKFW_STRING_T to_string(Error value) {
		switch (value) {
			case Error::VKFW_ENUMERATOR(None): return VKFW_CHAR_LITERAL"No error has occurred";
			case Error::VKFW_ENUMERATOR(NotInitialized): return VKFW_CHAR_LITERAL"GLFW has not been initialized";
			case Error::VKFW_ENUMERATOR(NoCurrentContext): return VKFW_CHAR_LITERAL"No context is current for this thread";
			case Error::VKFW_ENUMERATOR(InvalidEnum): return VKFW_CHAR_LITERAL"One of the arguments to the function was an invalid enum value";
			case Error::VKFW_ENUMERATOR(InvalidValue): return VKFW_CHAR_LITERAL"One of the arguments to the function was an invalid value";
			case Error::VKFW_ENUMERATOR(OutOfMemory): return VKFW_CHAR_LITERAL"A memory allocation failed";
			case Error::VKFW_ENUMERATOR(ApiUnavailable): return VKFW_CHAR_LITERAL"GLFW could not find support for the requested API on the system";
			case Error::VKFW_ENUMERATOR(VersionUnavailable): return VKFW_CHAR_LITERAL"The requested OpenGL or OpenGL ES version is not available";
			case Error::VKFW_ENUMERATOR(PlatformError): return VKFW_CHAR_LITERAL"A platform-specific error occurred that does not match any of the more specific categories";
			case Error::VKFW_ENUMERATOR(FormatUnavailable): return VKFW_CHAR_LITERAL"The requested format is not supported or available";
			case Error::VKFW_ENUMERATOR(NoWindowContext): return VKFW_CHAR_LITERAL"The specified window does not have an OpenGL or OpenGL ES context";
			default: return VKFW_CHAR_LITERAL"invalid";
		}
	}

	VKFW_INLINE VKFW_STRING_T to_string(ModifierKeyFlags value) {
		if (!value) return VKFW_CHAR_LITERAL"{}";
		VKFW_STRING_T result;

		if (value & ModifierKeyBits::VKFW_ENUMERATOR(CapsLock)) result += VKFW_CHAR_LITERAL"CapsLock | ";
		if (value & ModifierKeyBits::VKFW_ENUMERATOR(NumLock)) result += VKFW_CHAR_LITERAL"NumLock | ";

		if (value & ModifierKeyBits::VKFW_ENUMERATOR(Control)) result += VKFW_CHAR_LITERAL"Control + ";
		if (value & ModifierKeyBits::VKFW_ENUMERATOR(Alt)) result += VKFW_CHAR_LITERAL"Alt + ";
		if (value & ModifierKeyBits::VKFW_ENUMERATOR(Super)) result += VKFW_CHAR_LITERAL"Super + ";

		return VKFW_CHAR_LITERAL"{ " + result.substr(0, result.size() - 3) + VKFW_CHAR_LITERAL" }";
	}

	template <typename Type>
	struct isHandleType {
		static VKFW_CONST_OR_CONSTEXPR bool value = false;
	};
}

template <> struct VULKAN_HPP_NAMESPACE::FlagTraits<vkfw::ModifierKeyBits> {
	enum : VkFlags {
		allFlags = VkFlags(vkfw::ModifierKeyBits::VKFW_ENUMERATOR(Shift))
		| VkFlags(vkfw::ModifierKeyBits::VKFW_ENUMERATOR(Control))
		| VkFlags(vkfw::ModifierKeyBits::VKFW_ENUMERATOR(Alt))
		| VkFlags(vkfw::ModifierKeyBits::VKFW_ENUMERATOR(Super))
		| VkFlags(vkfw::ModifierKeyBits::VKFW_ENUMERATOR(CapsLock))
		| VkFlags(vkfw::ModifierKeyBits::VKFW_ENUMERATOR(NumLock))
	};
};
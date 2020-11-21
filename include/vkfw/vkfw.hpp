#pragma once
// Copyright (c) 2020 Cvelth.
//
// SPDX-License-Identifier: Apache-2.0
//

#if defined(_MSVC_LANG)
#  define VKFW_HPP_CPLUSPLUS _MSVC_LANG
#else
#  define VKFW_HPP_CPLUSPLUS __cplusplus
#endif

#if 201703L < VKFW_HPP_CPLUSPLUS
#  define VKFW_HPP_CPP_VERSION 20
#elif 201402L < VKFW_HPP_CPLUSPLUS
#  define VKFW_HPP_CPP_VERSION 17
#elif 201103L < VKFW_HPP_CPLUSPLUS
#  define VKFW_HPP_CPP_VERSION 14
#elif 199711L < VKFW_HPP_CPLUSPLUS
#  define VKFW_HPP_CPP_VERSION 11
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

#include <GLFW/glfw3.h>
#if !defined(VKFW_HPP_NO_INCLUDE_VULKAN_HPP)
#  include <vulkan/vulkan.hpp>
#endif

#if defined(VKFW_HPP_DISABLE_ENHANCED_MODE)
#  if !defined(VKFW_HPP_NO_SMART_HANDLE)
#    define VKFW_HPP_NO_SMART_HANDLE
#  endif
#else
#  include <memory>
#  include <vector>
#endif

#if !defined(VKFW_HPP_ASSERT)
#  include <cassert>
#  define VKFW_HPP_ASSERT assert
#endif

#if !defined(VKFW_HPP_ASSERT_ON_RESULT)
# define VKFW_HPP_ASSERT_ON_RESULT VKFW_HPP_ASSERT
#endif

#define VKFW_VERSION_MAJOR 0
#define VKFW_VERSION_MINOR 3
#define VKFW_VERSION_PATCH 0
static_assert(GLFW_VERSION_MAJOR == 3
			  && GLFW_VERSION_MINOR == 3
			  && GLFW_VERSION_REVISION == 2
			  , "\"glfw3.h\" version is not compatible with the \"vkfw.hpp\" version!");

#if !defined(VKFW_HPP_INLINE)
#  if defined(__clang__)
#    if __has_attribute(always_inline)
#      define VKFW_HPP_INLINE __attribute__((always_inline)) __inline__
#    else
#      define VKFW_HPP_INLINE inline
#    endif
#  elif defined(__GNUC__)
#    define VKFW_HPP_INLINE __attribute__((always_inline)) __inline__
#  elif defined(_MSC_VER)
#    define VKFW_HPP_INLINE inline
#  else
#    define VKFW_HPP_INLINE inline
#  endif
#endif

#if defined(VKFW_HPP_TYPESAFE_CONVERSION)
#  define VKFW_HPP_TYPESAFE_EXPLICIT
#else
#  define VKFW_HPP_TYPESAFE_EXPLICIT explicit
#endif

#if defined(__cpp_constexpr)
#  define VKFW_HPP_CONSTEXPR constexpr
#  if __cpp_constexpr >= 201304
#    define VKFW_HPP_CONSTEXPR_14  constexpr
#  else
#    define VKFW_HPP_CONSTEXPR_14
#  endif
#  define VKFW_HPP_CONST_OR_CONSTEXPR  constexpr
#else
#  define VKFW_HPP_CONSTEXPR
#  define VKFW_HPP_CONSTEXPR_14
#  define VKFW_HPP_CONST_OR_CONSTEXPR  const
#endif

#if !defined(VKFW_HPP_NOEXCEPT)
#  if defined(_MSC_VER) && (_MSC_VER <= 1800)
#    define VKFW_HPP_NOEXCEPT
#  else
#    define VKFW_HPP_NOEXCEPT noexcept
#    define VKFW_HPP_HAS_NOEXCEPT 1
#  endif
#endif

#if 14 <= VKFW_HPP_CPP_VERSION
#  define VKFW_HPP_DEPRECATED( msg ) [[deprecated( msg )]]
#else
#  define VKFW_HPP_DEPRECATED( msg )
#endif

#if ( 17 <= VKFW_HPP_CPP_VERSION ) && !defined( VKFW_HPP_NO_NODISCARD_WARNINGS )
#  define VKFW_HPP_NODISCARD [[nodiscard]]
#  if defined(VKFW_HPP_NO_EXCEPTIONS)
#    define VKFW_HPP_NODISCARD_WHEN_NO_EXCEPTIONS [[nodiscard]]
#  else
#    define VKFW_HPP_NODISCARD_WHEN_NO_EXCEPTIONS
#  endif
#else
#  define VKFW_HPP_NODISCARD
#  define VKFW_HPP_NODISCARD_WHEN_NO_EXCEPTIONS
#endif

#if !defined(VKFW_HPP_NAMESPACE)
#define VKFW_HPP_NAMESPACE vkfw
#endif

#define VKFW_HPP_STRINGIFY2(text) #text
#define VKFW_HPP_STRINGIFY(text) VKFW_HPP_STRINGIFY2(text)
#define VKFW_HPP_NAMESPACE_STRING VKFW_HPP_STRINGIFY(VKFW_HPP_NAMESPACE)

#if !(defined(VKFW_HPP_CHAR_T) && defined(VKFW_HPP_CHAR_LITERAL))
#  if defined(VKFW_HPP_USE_CHAR8_T) && defined(__cpp_char8_t) && defined(__cpp_lib_char8_t)
#    define VKFW_HPP_CHAR_T char8_t
#    define VKFW_HPP_CHAR_LITERAL u8""
#  elif defined(VKFW_HPP_USE_CHAR16_T)
#    define VKFW_HPP_CHAR_T char16_t
#    define VKFW_HPP_CHAR_LITERAL u""
#  elif defined(VKFW_HPP_USE_CHAR32_T)
#    define VKFW_HPP_CHAR_T char32_t
#    define VKFW_HPP_CHAR_LITERAL U""
#  elif defined(VKFW_HPP_USE_WCHAR_T)
#    define VKFW_HPP_CHAR_T wchar_t
#    define VKFW_HPP_CHAR_LITERAL L""
#  else
#    define VKFW_HPP_CHAR_T char
#    define VKFW_HPP_CHAR_LITERAL
#  endif
#endif

#define VKFW_HPP_STRING_T std::basic_string<VKFW_HPP_CHAR_T>
#if 17 <= VKFW_HPP_CPP_VERSION
#  define VKFW_HPP_STRING_VIEW_T std::basic_string_view<VKFW_HPP_CHAR_T>
#endif

namespace VKFW_HPP_NAMESPACE {
	enum class Boolean {
		eTrue = GLFW_TRUE,
		eFalse = GLFW_FALSE
	};
	enum class KeyAction {
		eRelease = GLFW_RELEASE,
		ePress = GLFW_PRESS,
		eRepeat = GLFW_REPEAT
	};
	enum class MouseButtonAction {
		eRelease = GLFW_RELEASE,
		ePress = GLFW_PRESS
	};
	enum class JoystickHatState {
		eCentered = GLFW_HAT_CENTERED,
		eUp = GLFW_HAT_UP,
		eRight = GLFW_HAT_RIGHT,
		eDown = GLFW_HAT_DOWN,
		eLeft = GLFW_HAT_LEFT,
		eRight_Up = GLFW_HAT_RIGHT_UP,
		eRight_Down = GLFW_HAT_RIGHT_DOWN,
		eLeft_Up = GLFW_HAT_LEFT_UP,
		eLeft_Down = GLFW_HAT_LEFT_DOWN
	};

	enum class Key {
		/* The unknown Key */
		eUnknown = GLFW_KEY_UNKNOWN,

		/* Printable Keys */
		eSpace = GLFW_KEY_SPACE,
		eApostrophe = GLFW_KEY_APOSTROPHE,		/* ' */
		eComma = GLFW_KEY_COMMA,				/* , */
		eMinus = GLFW_KEY_MINUS,				/* - */
		ePeriod = GLFW_KEY_PERIOD,				/* . */
		eSlash = GLFW_KEY_SLASH,				/* / */
		e0 = GLFW_KEY_0,
		e1 = GLFW_KEY_1,
		e2 = GLFW_KEY_2,
		e3 = GLFW_KEY_3,
		e4 = GLFW_KEY_4,
		e5 = GLFW_KEY_5,
		e6 = GLFW_KEY_6,
		e7 = GLFW_KEY_7,
		e8 = GLFW_KEY_8,
		e9 = GLFW_KEY_9,
		eSemicolon = GLFW_KEY_SEMICOLON,		/* ; */
		eEqual = GLFW_KEY_EQUAL,				/* = */
		eA = GLFW_KEY_A,
		eB = GLFW_KEY_B,
		eC = GLFW_KEY_C,
		eD = GLFW_KEY_D,
		eE = GLFW_KEY_E,
		eF = GLFW_KEY_F,
		eG = GLFW_KEY_G,
		eH = GLFW_KEY_H,
		eI = GLFW_KEY_I,
		eJ = GLFW_KEY_J,
		eK = GLFW_KEY_K,
		eL = GLFW_KEY_L,
		eM = GLFW_KEY_M,
		eN = GLFW_KEY_N,
		eO = GLFW_KEY_O,
		eP = GLFW_KEY_P,
		eQ = GLFW_KEY_Q,
		eR = GLFW_KEY_R,
		eS = GLFW_KEY_S,
		eT = GLFW_KEY_T,
		eU = GLFW_KEY_U,
		eV = GLFW_KEY_V,
		eW = GLFW_KEY_W,
		eX = GLFW_KEY_X,
		eY = GLFW_KEY_Y,
		eZ = GLFW_KEY_Z,
		eLeftBracket = GLFW_KEY_LEFT_BRACKET,	/* [ */
		eBackslash = GLFW_KEY_BACKSLASH,		/* \ */
		eRightBracket = GLFW_KEY_RIGHT_BRACKET,	/* ] */
		eGraveAccent = GLFW_KEY_GRAVE_ACCENT,	/* ` */
		eWorld1 = GLFW_KEY_WORLD_1,				/* non-US #1 */
		eWorld2 = GLFW_KEY_WORLD_2,				/* non-US #2 */

		/* Function Keys */
		eEscape = GLFW_KEY_ESCAPE,
		eEnter = GLFW_KEY_ENTER,
		eTab = GLFW_KEY_TAB,
		eBackspace = GLFW_KEY_BACKSPACE,
		eInsert = GLFW_KEY_INSERT,
		eDelete = GLFW_KEY_DELETE,
		eRight = GLFW_KEY_RIGHT,
		eLeft = GLFW_KEY_LEFT,
		eDown = GLFW_KEY_DOWN,
		eUp = GLFW_KEY_UP,
		ePageUp = GLFW_KEY_PAGE_UP,
		ePageDown = GLFW_KEY_PAGE_DOWN,
		eHome = GLFW_KEY_HOME,
		eEnd = GLFW_KEY_END,
		eCapsLock = GLFW_KEY_CAPS_LOCK,
		eScrollLock = GLFW_KEY_SCROLL_LOCK,
		eNumLock = GLFW_KEY_NUM_LOCK,
		ePrintScreen = GLFW_KEY_PRINT_SCREEN,
		ePause = GLFW_KEY_PAUSE,
		eF1 = GLFW_KEY_F1,
		eF2 = GLFW_KEY_F2,
		eF3 = GLFW_KEY_F3,
		eF4 = GLFW_KEY_F4,
		eF5 = GLFW_KEY_F5,
		eF6 = GLFW_KEY_F6,
		eF7 = GLFW_KEY_F7,
		eF8 = GLFW_KEY_F8,
		eF9 = GLFW_KEY_F9,
		eF10 = GLFW_KEY_F10,
		eF11 = GLFW_KEY_F11,
		eF12 = GLFW_KEY_F12,
		eF13 = GLFW_KEY_F13,
		eF14 = GLFW_KEY_F14,
		eF15 = GLFW_KEY_F15,
		eF16 = GLFW_KEY_F16,
		eF17 = GLFW_KEY_F17,
		eF18 = GLFW_KEY_F18,
		eF19 = GLFW_KEY_F19,
		eF20 = GLFW_KEY_F20,
		eF21 = GLFW_KEY_F21,
		eF22 = GLFW_KEY_F22,
		eF23 = GLFW_KEY_F23,
		eF24 = GLFW_KEY_F24,
		eF25 = GLFW_KEY_F25,
		eKeyPad0 = GLFW_KEY_KP_0,
		eKeyPad1 = GLFW_KEY_KP_1,
		eKeyPad2 = GLFW_KEY_KP_2,
		eKeyPad3 = GLFW_KEY_KP_3,
		eKeyPad4 = GLFW_KEY_KP_4,
		eKeyPad5 = GLFW_KEY_KP_5,
		eKeyPad6 = GLFW_KEY_KP_6,
		eKeyPad7 = GLFW_KEY_KP_7,
		eKeyPad8 = GLFW_KEY_KP_8,
		eKeyPad9 = GLFW_KEY_KP_9,
		eDecimal = GLFW_KEY_KP_DECIMAL,
		eDivide = GLFW_KEY_KP_DIVIDE,
		eMultiply = GLFW_KEY_KP_MULTIPLY,
		eSubtract = GLFW_KEY_KP_SUBTRACT,
		eAdd = GLFW_KEY_KP_ADD,
		eEnter = GLFW_KEY_KP_ENTER,
		eEqual = GLFW_KEY_KP_EQUAL,
		eLeftShift = GLFW_KEY_LEFT_SHIFT,
		eLeftControl = GLFW_KEY_LEFT_CONTROL,
		eLeftAlt = GLFW_KEY_LEFT_ALT,
		eLeftSuper = GLFW_KEY_LEFT_SUPER,
		eRightShift = GLFW_KEY_RIGHT_SHIFT,
		eRightControl = GLFW_KEY_RIGHT_CONTROL,
		eRightAlt = GLFW_KEY_RIGHT_ALT,
		eRightSuper = GLFW_KEY_RIGHT_SUPER,
		eMenu = GLFW_KEY_MENU,

		eLAST = GLFW_KEY_LAST
	};

	VKFW_HPP_INLINE VKFW_HPP_STRING_T to_string(Boolean value) {
		switch (value) {
			case Boolean::eTrue: return VKFW_HPP_CHAR_LITERAL"True";
			case Boolean::eFalse: return VKFW_HPP_CHAR_LITERAL"False";
			default: return VKFW_HPP_CHAR_LITERAL"invalid";
		}
	}
	VKFW_HPP_INLINE VKFW_HPP_STRING_T to_string(KeyAction value) {
		switch (value) {
			case KeyAction::eRelease: return VKFW_HPP_CHAR_LITERAL"Release";
			case KeyAction::ePress: return VKFW_HPP_CHAR_LITERAL"Press";
			case KeyAction::eRepeat: return VKFW_HPP_CHAR_LITERAL"Repeat";
			default: return VKFW_HPP_CHAR_LITERAL"invalid";
		}
	}
	VKFW_HPP_INLINE VKFW_HPP_STRING_T to_string(MouseButtonAction value) {
		switch (value) {
			case MouseButtonAction::eRelease: return VKFW_HPP_CHAR_LITERAL"Release";
			case MouseButtonAction::ePress: return VKFW_HPP_CHAR_LITERAL"Press";
			default: return VKFW_HPP_CHAR_LITERAL"invalid";
		}
	}
	VKFW_HPP_INLINE VKFW_HPP_STRING_T to_string(JoystickHatState value) {
		switch (value) {
			case JoystickHatState::eCentered: return VKFW_HPP_CHAR_LITERAL"Centered";
			case JoystickHatState::eUp: return VKFW_HPP_CHAR_LITERAL"Up";
			case JoystickHatState::eRight: return VKFW_HPP_CHAR_LITERAL"Right";
			case JoystickHatState::eDown: return VKFW_HPP_CHAR_LITERAL"Down";
			case JoystickHatState::eLeft: return VKFW_HPP_CHAR_LITERAL"Left";
			case JoystickHatState::eRight_Up: return VKFW_HPP_CHAR_LITERAL"Right Up";
			case JoystickHatState::eRight_Down: return VKFW_HPP_CHAR_LITERAL"Right Down";
			case JoystickHatState::eLeft_Up: return VKFW_HPP_CHAR_LITERAL"Left Up";
			case JoystickHatState::eLeft_Down: return VKFW_HPP_CHAR_LITERAL"Left Down";
			default: return VKFW_HPP_CHAR_LITERAL"invalid";
		}
	}
	VKFW_HPP_INLINE VKFW_HPP_STRING_T to_string(Key value) {
		switch (value) {
			case Key::eUnknown: return VKFW_HPP_CHAR_LITERAL"Unknown";

			/* Printable Keys */
			case Key::eSpace: return VKFW_HPP_CHAR_LITERAL"Space";
			case Key::eApostrophe: return VKFW_HPP_CHAR_LITERAL"Apostrophe";	
			case Key::eComma: return VKFW_HPP_CHAR_LITERAL"Comma";			
			case Key::eMinus: return VKFW_HPP_CHAR_LITERAL"Minus";			
			case Key::ePeriod: return VKFW_HPP_CHAR_LITERAL"Period";			
			case Key::eSlash: return VKFW_HPP_CHAR_LITERAL"Slash";			
			case Key::e0: return VKFW_HPP_CHAR_LITERAL"0";
			case Key::e1: return VKFW_HPP_CHAR_LITERAL"1";
			case Key::e2: return VKFW_HPP_CHAR_LITERAL"2";
			case Key::e3: return VKFW_HPP_CHAR_LITERAL"3";
			case Key::e4: return VKFW_HPP_CHAR_LITERAL"4";
			case Key::e5: return VKFW_HPP_CHAR_LITERAL"5";
			case Key::e6: return VKFW_HPP_CHAR_LITERAL"6";
			case Key::e7: return VKFW_HPP_CHAR_LITERAL"7";
			case Key::e8: return VKFW_HPP_CHAR_LITERAL"8";
			case Key::e9: return VKFW_HPP_CHAR_LITERAL"9";
			case Key::eSemicolon: return VKFW_HPP_CHAR_LITERAL"Semicolon";	
			case Key::eEqual: return VKFW_HPP_CHAR_LITERAL"Equal";			
			case Key::eA: return VKFW_HPP_CHAR_LITERAL"A";
			case Key::eB: return VKFW_HPP_CHAR_LITERAL"B";
			case Key::eC: return VKFW_HPP_CHAR_LITERAL"C";
			case Key::eD: return VKFW_HPP_CHAR_LITERAL"D";
			case Key::eE: return VKFW_HPP_CHAR_LITERAL"E";
			case Key::eF: return VKFW_HPP_CHAR_LITERAL"F";
			case Key::eG: return VKFW_HPP_CHAR_LITERAL"G";
			case Key::eH: return VKFW_HPP_CHAR_LITERAL"H";
			case Key::eI: return VKFW_HPP_CHAR_LITERAL"I";
			case Key::eJ: return VKFW_HPP_CHAR_LITERAL"J";
			case Key::eK: return VKFW_HPP_CHAR_LITERAL"K";
			case Key::eL: return VKFW_HPP_CHAR_LITERAL"L";
			case Key::eM: return VKFW_HPP_CHAR_LITERAL"M";
			case Key::eN: return VKFW_HPP_CHAR_LITERAL"N";
			case Key::eO: return VKFW_HPP_CHAR_LITERAL"O";
			case Key::eP: return VKFW_HPP_CHAR_LITERAL"P";
			case Key::eQ: return VKFW_HPP_CHAR_LITERAL"Q";
			case Key::eR: return VKFW_HPP_CHAR_LITERAL"R";
			case Key::eS: return VKFW_HPP_CHAR_LITERAL"S";
			case Key::eT: return VKFW_HPP_CHAR_LITERAL"T";
			case Key::eU: return VKFW_HPP_CHAR_LITERAL"U";
			case Key::eV: return VKFW_HPP_CHAR_LITERAL"V";
			case Key::eW: return VKFW_HPP_CHAR_LITERAL"W";
			case Key::eX: return VKFW_HPP_CHAR_LITERAL"X";
			case Key::eY: return VKFW_HPP_CHAR_LITERAL"Y";
			case Key::eZ: return VKFW_HPP_CHAR_LITERAL"Z";
			case Key::eLeftBracket: return VKFW_HPP_CHAR_LITERAL"LeftBracket";	
			case Key::eBackslash: return VKFW_HPP_CHAR_LITERAL"Backslash";		
			case Key::eRightBracket: return VKFW_HPP_CHAR_LITERAL"RightBracket";
			case Key::eGraveAccent: return VKFW_HPP_CHAR_LITERAL"GraveAccent";	
			case Key::eWorld1: return VKFW_HPP_CHAR_LITERAL"World1";			
			case Key::eWorld2: return VKFW_HPP_CHAR_LITERAL"World2";

			/* Function Keys */
			case Key::eEscape: return VKFW_HPP_CHAR_LITERAL"Escape";
			case Key::eEnter: return VKFW_HPP_CHAR_LITERAL"Enter";
			case Key::eTab: return VKFW_HPP_CHAR_LITERAL"Tab";
			case Key::eBackspace: return VKFW_HPP_CHAR_LITERAL"Backspace";
			case Key::eInsert: return VKFW_HPP_CHAR_LITERAL"Insert";
			case Key::eDelete: return VKFW_HPP_CHAR_LITERAL"Delete";
			case Key::eRight: return VKFW_HPP_CHAR_LITERAL"Right";
			case Key::eLeft: return VKFW_HPP_CHAR_LITERAL"Left";
			case Key::eDown: return VKFW_HPP_CHAR_LITERAL"Down";
			case Key::eUp: return VKFW_HPP_CHAR_LITERAL"Up";
			case Key::ePageUp: return VKFW_HPP_CHAR_LITERAL"PageUp";
			case Key::ePageDown: return VKFW_HPP_CHAR_LITERAL"PageDown";
			case Key::eHome: return VKFW_HPP_CHAR_LITERAL"Home";
			case Key::eEnd: return VKFW_HPP_CHAR_LITERAL"End";
			case Key::eCapsLock: return VKFW_HPP_CHAR_LITERAL"CapsLock";
			case Key::eScrollLock: return VKFW_HPP_CHAR_LITERAL"ScrollLock";
			case Key::eNumLock: return VKFW_HPP_CHAR_LITERAL"NumLock";
			case Key::ePrintScreen: return VKFW_HPP_CHAR_LITERAL"PrintScreen";
			case Key::ePause: return VKFW_HPP_CHAR_LITERAL"Pause";
			case Key::eF1: return VKFW_HPP_CHAR_LITERAL"F1";
			case Key::eF2: return VKFW_HPP_CHAR_LITERAL"F2";
			case Key::eF3: return VKFW_HPP_CHAR_LITERAL"F3";
			case Key::eF4: return VKFW_HPP_CHAR_LITERAL"F4";
			case Key::eF5: return VKFW_HPP_CHAR_LITERAL"F5";
			case Key::eF6: return VKFW_HPP_CHAR_LITERAL"F6";
			case Key::eF7: return VKFW_HPP_CHAR_LITERAL"F7";
			case Key::eF8: return VKFW_HPP_CHAR_LITERAL"F8";
			case Key::eF9: return VKFW_HPP_CHAR_LITERAL"F9";
			case Key::eF10: return VKFW_HPP_CHAR_LITERAL"F10";
			case Key::eF11: return VKFW_HPP_CHAR_LITERAL"F11";
			case Key::eF12: return VKFW_HPP_CHAR_LITERAL"F12";
			case Key::eF13: return VKFW_HPP_CHAR_LITERAL"F13";
			case Key::eF14: return VKFW_HPP_CHAR_LITERAL"F14";
			case Key::eF15: return VKFW_HPP_CHAR_LITERAL"F15";
			case Key::eF16: return VKFW_HPP_CHAR_LITERAL"F16";
			case Key::eF17: return VKFW_HPP_CHAR_LITERAL"F17";
			case Key::eF18: return VKFW_HPP_CHAR_LITERAL"F18";
			case Key::eF19: return VKFW_HPP_CHAR_LITERAL"F19";
			case Key::eF20: return VKFW_HPP_CHAR_LITERAL"F20";
			case Key::eF21: return VKFW_HPP_CHAR_LITERAL"F21";
			case Key::eF22: return VKFW_HPP_CHAR_LITERAL"F22";
			case Key::eF23: return VKFW_HPP_CHAR_LITERAL"F23";
			case Key::eF24: return VKFW_HPP_CHAR_LITERAL"F24";
			case Key::eF25: return VKFW_HPP_CHAR_LITERAL"F25";
			case Key::eKeyPad0: return VKFW_HPP_CHAR_LITERAL"KeyPad0";
			case Key::eKeyPad1: return VKFW_HPP_CHAR_LITERAL"KeyPad1";
			case Key::eKeyPad2: return VKFW_HPP_CHAR_LITERAL"KeyPad2";
			case Key::eKeyPad3: return VKFW_HPP_CHAR_LITERAL"KeyPad3";
			case Key::eKeyPad4: return VKFW_HPP_CHAR_LITERAL"KeyPad4";
			case Key::eKeyPad5: return VKFW_HPP_CHAR_LITERAL"KeyPad5";
			case Key::eKeyPad6: return VKFW_HPP_CHAR_LITERAL"KeyPad6";
			case Key::eKeyPad7: return VKFW_HPP_CHAR_LITERAL"KeyPad7";
			case Key::eKeyPad8: return VKFW_HPP_CHAR_LITERAL"KeyPad8";
			case Key::eKeyPad9: return VKFW_HPP_CHAR_LITERAL"KeyPad9";
			case Key::eDecimal: return VKFW_HPP_CHAR_LITERAL"Decimal";
			case Key::eDivide: return VKFW_HPP_CHAR_LITERAL"Divide";
			case Key::eMultiply: return VKFW_HPP_CHAR_LITERAL"Multiply";
			case Key::eSubtract: return VKFW_HPP_CHAR_LITERAL"Subtract";
			case Key::eAdd: return VKFW_HPP_CHAR_LITERAL"Add";
			case Key::eEnter: return VKFW_HPP_CHAR_LITERAL"Enter";
			case Key::eEqual: return VKFW_HPP_CHAR_LITERAL"Equal";
			case Key::eLeftShift: return VKFW_HPP_CHAR_LITERAL"LeftShift";
			case Key::eLeftControl: return VKFW_HPP_CHAR_LITERAL"LeftControl";
			case Key::eLeftAlt: return VKFW_HPP_CHAR_LITERAL"LeftAlt";
			case Key::eLeftSuper: return VKFW_HPP_CHAR_LITERAL"LeftSuper";
			case Key::eRightShift: return VKFW_HPP_CHAR_LITERAL"RightShift";
			case Key::eRightControl: return VKFW_HPP_CHAR_LITERAL"RightControl";
			case Key::eRightAlt: return VKFW_HPP_CHAR_LITERAL"RightAlt";
			case Key::eRightSuper: return VKFW_HPP_CHAR_LITERAL"RightSuper";
			case Key::eMenu: return VKFW_HPP_CHAR_LITERAL"Menu";
			default: return VKFW_HPP_CHAR_LITERAL"invalid";
		}
	}

	template <typename RefType>
	using Optional = VULKAN_HPP_NAMESPACE::Optional<RefType>;

#if !defined(VKFW_HPP_NO_SMART_HANDLE)
	template <typename Type> using UniqueHandleTraits
		= VULKAN_HPP_NAMESPACE::UniqueHandleTraits<Type, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE>;

	template <typename Type> using UniqueHandle
		= VULKAN_HPP_NAMESPACE::UniqueHandle<Type, VULKAN_HPP_DEFAULT_DISPATCHER_TYPE>;
#endif

	template <typename Type>
	struct isHandleType {
		static VKFW_HPP_CONST_OR_CONSTEXPR bool value = false;
	};
}
module;

#import <version>
#if defined(__cpp_lib_modules)
  #define VKFW_ENABLE_STD_MODULE
#endif

#include <vkfw/vkfw.hpp>

export module vkfw;

export namespace VKFW_NAMESPACE {
  using VKFW_NAMESPACE::AnglePlatformType;
  using VKFW_NAMESPACE::Attribute;
  using VKFW_NAMESPACE::Boolean;
  using VKFW_NAMESPACE::ClientAPI;
  using VKFW_NAMESPACE::ContextCreationAPI;
  using VKFW_NAMESPACE::ContextReleaseBehavior;
  using VKFW_NAMESPACE::ContextRobustness;
  using VKFW_NAMESPACE::CursorMode;
  using VKFW_NAMESPACE::CursorShape;
  using VKFW_NAMESPACE::DontCare;
  using VKFW_NAMESPACE::GamepadAxis;
  using VKFW_NAMESPACE::GamepadButton;
  using VKFW_NAMESPACE::InitializationHint;
  using VKFW_NAMESPACE::InputMode;
  using VKFW_NAMESPACE::Joystick;
  using VKFW_NAMESPACE::JoystickHatState;
  using VKFW_NAMESPACE::Key;
  using VKFW_NAMESPACE::KeyAction;
  using VKFW_NAMESPACE::ModifierKeyBits;
  using VKFW_NAMESPACE::ModifierKeyFlags;
  using VKFW_NAMESPACE::MouseButton;
  using VKFW_NAMESPACE::MouseButtonAction;
  using VKFW_NAMESPACE::OpenGLProfile;
  using VKFW_NAMESPACE::Platform;
  using VKFW_NAMESPACE::Result;
  using VKFW_NAMESPACE::Status;
  using VKFW_NAMESPACE::WaylandLibDecor;
  using VKFW_NAMESPACE::WindowAttribute;
  using VKFW_NAMESPACE::WindowHint;

  using VKFW_NAMESPACE::check;
  using VKFW_NAMESPACE::to_string;

  using VKFW_NAMESPACE::operator|;
  using VKFW_NAMESPACE::operator&;
  using VKFW_NAMESPACE::operator^;
  using VKFW_NAMESPACE::operator~;

#ifndef VKFW_HAS_SPACESHIP_OPERATOR
  using VKFW_NAMESPACE::operator<;
  using VKFW_NAMESPACE::operator<=;
  using VKFW_NAMESPACE::operator>;
  using VKFW_NAMESPACE::operator>=;
  using VKFW_NAMESPACE::operator==;
  using VKFW_NAMESPACE::operator!=;
#endif

#ifndef VKFW_NO_SMART_HANDLE

#endif

#ifndef VKFW_NO_EXCEPTIONS
  using VKFW_NAMESPACE::Error;
  using VKFW_NAMESPACE::SystemError;

  using VKFW_NAMESPACE::ApiUnavailableError;
  using VKFW_NAMESPACE::CursorUnavailableError;
  using VKFW_NAMESPACE::FeatureUnavailableError;
  using VKFW_NAMESPACE::FeatureUnimplementedError;
  using VKFW_NAMESPACE::FormatUnavailableError;
  using VKFW_NAMESPACE::InvalidEnumError;
  using VKFW_NAMESPACE::InvalidValueError;
  using VKFW_NAMESPACE::NoCurrentContextError;
  using VKFW_NAMESPACE::NotInitializedError;
  using VKFW_NAMESPACE::NoWindowContextError;
  using VKFW_NAMESPACE::OutOfMemoryError;
  using VKFW_NAMESPACE::PlatformError;
  using VKFW_NAMESPACE::PlatformUnavailableError;
  using VKFW_NAMESPACE::VersionUnavailableError;

  using VKFW_NAMESPACE::errorCategory;

  using VKFW_NAMESPACE::make_error_code;
  using VKFW_NAMESPACE::make_error_condition;
#endif

  using VKFW_NAMESPACE::ResultValue;
  using VKFW_NAMESPACE::ResultValueType;

  using VKFW_NAMESPACE::createResultValue;

#ifndef VKFW_NO_STD_FUNCTION_CALLBACKS
  using VKFW_NAMESPACE::DynamicCallbackStorage;
#endif

  using VKFW_NAMESPACE::Nullopt;
  using VKFW_NAMESPACE::Optional;

#ifndef VKFW_DISABLE_ENHANCED_MODE
  using VKFW_NAMESPACE::Cursor;
  using VKFW_NAMESPACE::Image;
  using VKFW_NAMESPACE::Instance;
  using VKFW_NAMESPACE::Monitor;
  using VKFW_NAMESPACE::Window;

  using VKFW_NAMESPACE::InitHints;
  using VKFW_NAMESPACE::InitializationHint;
  using VKFW_NAMESPACE::OptionalInitializationHint;

  using VKFW_NAMESPACE::OptionalWindowHint;
  using VKFW_NAMESPACE::WindowHint;
  using VKFW_NAMESPACE::WindowHints;

  using VKFW_NAMESPACE::setInitHint;
  using VKFW_NAMESPACE::setInitHints;

  using VKFW_NAMESPACE::setWindowHint;
  using VKFW_NAMESPACE::setWindowHints;
#endif

  using VKFW_NAMESPACE::defaultWindowHints;
  using VKFW_NAMESPACE::getError;
  using VKFW_NAMESPACE::getPlatform;
  using VKFW_NAMESPACE::initHint;
  using VKFW_NAMESPACE::platformSupported;
  using VKFW_NAMESPACE::set;
  using VKFW_NAMESPACE::setErrorCallback;
  using VKFW_NAMESPACE::windowHint;

  using VKFW_NAMESPACE::init;
  using VKFW_NAMESPACE::terminate;

  using VKFW_NAMESPACE::getVersion;
  using VKFW_NAMESPACE::getVersionString;
  using VKFW_NAMESPACE::Version;

  using VKFW_NAMESPACE::getMonitors;
  using VKFW_NAMESPACE::getPrimaryMonitor;

#ifdef VKFW_DISABLE_ENHANCED_MODE
  using VKFW_NAMESPACE::getMonitorContentScale;
  using VKFW_NAMESPACE::getMonitorName;
  using VKFW_NAMESPACE::getMonitorPhysicalSize;
  using VKFW_NAMESPACE::getMonitorPos;
  using VKFW_NAMESPACE::getMonitorWorkarea;
  using VKFW_NAMESPACE::setMonitorUserPointer;

  using VKFW_NAMESPACE::getVideoMode;
  using VKFW_NAMESPACE::getVideoModes;

  using VKFW_NAMESPACE::getGammaRamp;
  using VKFW_NAMESPACE::setGamma;
  using VKFW_NAMESPACE::setGammaRamp;

  // keeping track of these functions when clang-format reorders it around is
  // annoying
  // clang-format off
  using VKFW_NAMESPACE::destroyWindow;
  using VKFW_NAMESPACE::windowShouldClose;
  using VKFW_NAMESPACE::setWindowTitle;
  using VKFW_NAMESPACE::getWindowPos;
  using VKFW_NAMESPACE::setWindowPos;
  using VKFW_NAMESPACE::getWindowSize;
  using VKFW_NAMESPACE::setWindowSizeLimits;
  using VKFW_NAMESPACE::setWindowAspectRatio;
  using VKFW_NAMESPACE::setWindowASize;
  using VKFW_NAMESPACE::getFramebufferSize;
  using VKFW_NAMESPACE::getWindowFrameSize;
  using VKFW_NAMESPACE::getWindowContentScale;
  using VKFW_NAMESPACE::getWindowOpacity;
  using VKFW_NAMESPACE::setWindowOpacity;
  using VKFW_NAMESPACE::iconifyWindow;
  using VKFW_NAMESPACE::restoreWindow;
  using VKFW_NAMESPACE::maximizeWindow;
  using VKFW_NAMESPACE::showWindow;
  using VKFW_NAMESPACE::hideWindow;
  using VKFW_NAMESPACE::focusWindow;
  using VKFW_NAMESPACE::requestWindowAttention;
  using VKFW_NAMESPACE::getWindowMonitor;
  using VKFW_NAMESPACE::setWindowMonitor;
  using VKFW_NAMESPACE::setWindowIcon;
  using VKFW_NAMESPACE::getWindowAttribute;
  using VKFW_NAMESPACE::setWindowAttribute;

  using VKFW_NAMESPACE::get;
  // using VKFW_NAMESPACE::set; // already using-ed above

  using VKFW_NAMESPACE::getInputMode;
  using VKFW_NAMESPACE::setInputMode;

#ifdef VKFW_NO_STD_FUNCTION_CALLBACKS
  using VKFW_NAMESPACE::setWindowPosCallback;
  using VKFW_NAMESPACE::setWindowSizeCallback;
  using VKFW_NAMESPACE::setWindowCloseCallback;
  using VKFW_NAMESPACE::setWindowRefreshCallback;
  using VKFW_NAMESPACE::setWindowFocusCallback;
  using VKFW_NAMESPACE::setWindowIconifyCallback;
  using VKFW_NAMESPACE::setWindowMaximizeCallback;
  using VKFW_NAMESPACE::setFramebufferSizeCallback;
  using VKFW_NAMESPACE::setWindowContentScaleCallback;
  using VKFW_NAMESPACE::setKeyCallback;
  using VKFW_NAMESPACE::setCharCallback;
  using VKFW_NAMESPACE::setCharModsCallback;
  using VKFW_NAMESPACE::setMouseButtonCallback;
  using VKFW_NAMESPACE::setCursorPosCallback;
  using VKFW_NAMESPACE::setCursorEnterCallback;
  using VKFW_NAMESPACE::setScrollCallback;
  using VKFW_NAMESPACE::setDropCallback;
#else
  using VKFW_NAMESPACE::accessWindowCallbacks;
#endif

  using VKFW_NAMESPACE::getWindowUserPointer;
  using VKFW_NAMESPACE::setWindowUserPointer;
  using VKFW_NAMESPACE::getKey;
  using VKFW_NAMESPACE::getMouseButton;
  using VKFW_NAMESPACE::getCursorPos;
  using VKFW_NAMESPACE::setCursorPos;
  using VKFW_NAMESPACE::setCursor;
  // clang-format on

  using VKFW_NAMESPACE::makeContextCurrent;
  using VKFW_NAMESPACE::swapBuffers;
#endif

  using VKFW_NAMESPACE::createWindow;

  using VKFW_NAMESPACE::pollEvents;
  using VKFW_NAMESPACE::postEmptyEvent;
  using VKFW_NAMESPACE::waitEvents;
  using VKFW_NAMESPACE::waitEventsTimeout;

  using VKFW_NAMESPACE::getCurrentContext;
  using VKFW_NAMESPACE::swapInterval;

  using VKFW_NAMESPACE::rawMouseMotionSupported;

  using VKFW_NAMESPACE::getKeyName;
  using VKFW_NAMESPACE::getKeyScancode;

  using VKFW_NAMESPACE::createCursor;
  using VKFW_NAMESPACE::createStandardCursor;

#if !defined(VKFW_DISABLE_ENHANCED_MODE) && !defined(VKFW_NO_SMART_HANDLE)
  using VKFW_NAMESPACE::UniqueCursor;
  using VKFW_NAMESPACE::UniqueInstance;
  using VKFW_NAMESPACE::UniqueWindow;

  using VKFW_NAMESPACE::createCursorUnique;
  using VKFW_NAMESPACE::createResultValueUnique;
  using VKFW_NAMESPACE::createStandardCursorUnique;
  using VKFW_NAMESPACE::createWindowSurfaceUnique;
  using VKFW_NAMESPACE::createWindowUnique;
  using VKFW_NAMESPACE::initUnique;
#endif

  using VKFW_NAMESPACE::getClipboardString;
  using VKFW_NAMESPACE::setClipboardString;

  using VKFW_NAMESPACE::getTime;
  using VKFW_NAMESPACE::getTimerFrequency;
  using VKFW_NAMESPACE::getTimerValue;
  using VKFW_NAMESPACE::setTime;

  using VKFW_NAMESPACE::getJoystickAxes;
  using VKFW_NAMESPACE::getJoystickButtons;
  using VKFW_NAMESPACE::getJoystickGUID;
  using VKFW_NAMESPACE::getJoystickHats;
  using VKFW_NAMESPACE::getJoystickName;
  using VKFW_NAMESPACE::getJoystickUserPointer;
  using VKFW_NAMESPACE::joystickIsGamepad;
  using VKFW_NAMESPACE::joystickPresent;
  using VKFW_NAMESPACE::setJoystickCallback;
  using VKFW_NAMESPACE::setJoystickUserPointer;

  using VKFW_NAMESPACE::getGamepadName;
  using VKFW_NAMESPACE::getGamepadState;
  using VKFW_NAMESPACE::updateGamepadMappings;

  using VKFW_NAMESPACE::extensionSupported;
  using VKFW_NAMESPACE::getInstanceProcAddress;
  using VKFW_NAMESPACE::getPhysicalDevicePresentationSupport;
  using VKFW_NAMESPACE::getProcAddress;
  using VKFW_NAMESPACE::getRequiredInstanceExtensions;
  using VKFW_NAMESPACE::initVulkanLoader;
  using VKFW_NAMESPACE::vulkanSupported;

  using VKFW_NAMESPACE::createWindowSurface;
} // namespace VKFW_NAMESPACE

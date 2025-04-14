cmake_minimum_required(VERSION 3.20)
project(vkfw LANGUAGES CXX)

# Build options.
option(VKFW_FETCH_DEPENDENCIES "Fetch build dependencies" OFF)
option(VKFW_INSTALL "Create install target" OFF)
option(VKFW_BUILD_EXAMPLES "Build examples" OFF)

# Configuration options
option(VKFW_DISABLE_ENHANCED_MODE "Disable enhanced functionality" OFF)
option(VKFW_NO_EXCEPTIONS "Disable exceptions" OFF)
option(VKFW_NO_SMART_HANDLE "Disable UniqueHandles" OFF)
option(VKFW_NO_STD_FUNCTION_CALLBACKS "Disable std::function callbacks" OFF)
option(VKFW_NO_NODISCARD_WARNINGS "Disable [[nodiscard]] warnings" OFF)
option(VKFW_NO_INCLUDE_VULKAN "Disable includsion of vulkan.h" OFF)
option(VKFW_INCLUDE_GL "Include OpenGL headers" OFF)
option(VKFW_NO_INCLUDE_VULKAN_HPP "Disable inclusion of vulkan.hpp" OFF)
option(VKFW_NO_LEADING_E_IN_ENUMS "Disable leading e prefix in enums" OFF)
option(VKFW_NO_STRUCT_CONSTRUCTORS "Disable constructors for structs" OFF)
option(VKFW_NO_SPACESHIP_OPERATOR "Disable spaceship comparison" OFF)
option(VKFW_NO_STRING_VIEW "Disable usage of std::string_view" OFF)
option(VKFW_NO_SPAN "Disable usage of std::span" OFF)

set(VKFW_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(VKFW_SOURCE_ROOT ${VKFW_SOURCE_DIR}/include)
set(VKFW_EXAMPLE_ROOT ${VKFW_SOURCE_DIR}/example)
set(VKFW_DEPS_ROOT ${VKFW_SOURCE_DIR}/deps)

# This the version of GLFW that will be fetched either through VKFW_FETCH_DEPENDENCIES or
# by the examples (if VKFW_BUILD_EXAMPLES is set). See ./example/CMakeLists.txt for
# details.
set(VKFW_GLFW_FETCH_VERSION 3.4)

find_package(glfw3 QUIET)
if (NOT glfw3_FOUND AND VKFW_FETCH_DEPENDENCIES)
    include(FetchContent)
    FetchContent_Declare(
        glfw3
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG ${VKFW_GLFW_FETCH_VERSION}
    )
    FetchContent_MakeAvailable(glfw3)
elseif(NOT glfw3_FOUND)
    message(ERROR " Unable to find GLFW")
endif()

add_library(vkfw INTERFACE)
target_include_directories(vkfw INTERFACE
    $<BUILD_INTERFACE:${VKFW_SOURCE_ROOT}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(vkfw INTERFACE glfw)

function(add_definitions OPTION_NAME)
    if ("${${OPTION_NAME}}")
        target_compile_definitions(vkfw INTERFACE "${OPTION_NAME}")
    endif()
endfunction()

# Set options. See README.md for the full list.
add_definitions(VKFW_DISABLE_ENHANCED_MODE)
add_definitions(VKFW_NO_EXCEPTIONS)
add_definitions(VKFW_NO_SMART_HANDLE)
add_definitions(VKFW_NO_STD_FUNCTION_CALLBACKS)
add_definitions(VKFW_NO_NODISCARD_WARNINGS)
add_definitions(VKFW_NO_INCLUDE_VULKAN)
add_definitions(VKFW_INCLUDE_GL)
add_definitions(VKFW_NO_INCLUDE_VULKAN_HPP)
add_definitions(VKFW_NO_LEADING_E_IN_ENUMS)
add_definitions(VKFW_NO_STRUCT_CONSTRUCTORS)
add_definitions(VKFW_NO_SPACESHIP_OPERATOR)
add_definitions(VKFW_NO_STRING_VIEW)
add_definitions(VKFW_NO_SPAN)

if (VKFW_INSTALL)
    include(CMakePackageConfigHelpers)
    include(GNUInstallDirs)

    install(TARGETS vkfw
        EXPORT vkfw
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
    )

    install(EXPORT vkfw
        FILE vkfwTargets.cmake
        NAMESPACE vkfw::
        DESTINATION lib/cmake/vkfw
    )

    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/vkfwConfig.cmake"
        DESTINATION lib/cmake/vkfw
    )

    set(VKFW_INSTALL_HEADERS
        ${VKFW_SOURCE_ROOT}/vkfw/vkfw.hpp
    )

    install(FILES
        ${VKFW_INSTALL_HEADERS}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/vkfw"
    )
endif()

if (VKFW_BUILD_EXAMPLES)
    add_subdirectory(${VKFW_EXAMPLE_ROOT})
endif()

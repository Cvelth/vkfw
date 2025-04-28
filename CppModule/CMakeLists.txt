cmake_minimum_required(VERSION 3.29)

project(CppModules LANGUAGES CXX)

find_package(Vulkan QUIET)

option(
    VKFW_BUILD_WITH_VULKAN_MODULE
    "Build VKFW with VulkanHpp module instead of header"
    ON
)
option(
    VKFW_BUILD_MODULE_VULKAN_DYNAMIC
    "Build VKFW with dynamically loaded Vulkan"
    OFF
)
option(VKFW_BUILD_WITH_STD_MODULE "Build VKFW with std module" ON)

if(NOT ${VKFW_NO_INCLUDE_VULKAN_HPP})
    if(${VULKAN_FOUND})
        if(${VKFW_BUILD_WITH_VULKAN_MODULE})
            message(
                STATUS
                "Building with Vulkan module at ${Vulkan_INCLUDE_DIRS}"
            )
            add_library(Vulkan-Hpp-Module)

            target_sources(
                Vulkan-Hpp-Module
                PUBLIC
                    FILE_SET CXX_MODULES
                    BASE_DIRS ${Vulkan_INCLUDE_DIRS}/vulkan
                    FILES ${Vulkan_INCLUDE_DIRS}/vulkan/vulkan.cppm
            )

            if(${VKFW_BUILD_MODULE_VULKAN_DYNAMIC})
                target_compile_definitions(
                    Vulkan-Hpp-Module
                    PUBLIC VK_NO_PROTOTYPES=1
                )
                target_link_libraries(Vulkan-Hpp-Module PUBLIC Vulkan::Headers)
            else()
                target_link_libraries(Vulkan-Hpp-Module PUBLIC Vulkan::Vulkan)
            endif()

            if(${VKFW_BUILD_WITH_STD_MODULE})
                target_compile_features(Vulkan-Hpp-Module PUBLIC cxx_std_23)
                set_target_properties(
                    Vulkan-Hpp-Module
                    PROPERTIES CXX_MODULE_STD ON
                )
            else()
                target_compile_features(Vulkan-Hpp-Module PUBLIC cxx_std_20)
            endif()
        else()
            message(
                STATUS
                "Building with Vulkan headers at ${Vulkan_INCLUDE_DIRS}"
            )
            add_library(Vulkan-Hpp-Module INTERFACE)
            target_compile_features(Vulkan-Hpp-Module INTERFACE cxx_std_20)

            if(${VKFW_BUILD_MODULE_VULKAN_DYNAMIC})
                target_compile_definitions(
                    Vulkan-Hpp-Module
                    INTERFACE VK_NO_PROTOTYPES=1
                )
                target_link_libraries(
                    Vulkan-Hpp-Module
                    INTERFACE Vulkan::Headers
                )
            else()
                target_link_libraries(
                    Vulkan-Hpp-Module
                    INTERFACE Vulkan::Vulkan
                )
            endif()
        endif()
    else()
        message(
            WARNING
            "Vulkan-Hpp header not found, building without Vulkan support."
        )
    endif()
endif()

add_library(vkfw-module)
target_sources(
    vkfw-module
    PUBLIC FILE_SET CXX_MODULES BASE_DIRS ../src FILES ../src/vkfw.cppm
)

if(${VKFW_BUILD_WITH_STD_MODULE})
    target_compile_features(vkfw-module PUBLIC cxx_std_23)
    set_target_properties(vkfw-module PROPERTIES CXX_MODULE_STD ON)
else()
    target_compile_features(vkfw-module PUBLIC cxx_std_20)
endif()

target_link_libraries(vkfw-module PRIVATE vkfw)
if(NOT ${VKFW_NO_INCLUDE_VULKAN_HPP})
    target_link_libraries(vkfw-module PRIVATE Vulkan-Hpp-Module)
endif()

if(${VKFW_BUILD_WITH_VULKAN_MODULE})
    target_compile_definitions(
        vkfw-module
        PRIVATE VKFW_ENABLE_VULKAN_HPP_MODULE
    )
endif()

if(${VKFW_BUILD_WITH_VULKAN_MODULE})
    if(VKFW_BUILD_EXAMPLES)
        add_executable(Modules-Example modules-example.cpp)
        target_compile_features(Modules-Example PRIVATE cxx_std_20)
        target_link_libraries(
            Modules-Example
            PRIVATE vkfw-module Vulkan-Hpp-Module
        )

        # Additional glfw3 example dependencies.
        #
        # See example/CMakeLists.txt for more details.
        if(glfw3_FOUND)
            include(FetchContent)
            FetchContent_Populate(
                glfw3
                GIT_REPOSITORY https://github.com/glfw/glfw
                GIT_TAG ${VKFW_GLFW_FETCH_VERSION}
                QUIET
            )
        endif()
        target_include_directories(
            Modules-Example
            PRIVATE "${glfw3_SOURCE_DIR}/deps"
        )

        if(${VKFW_BUILD_WITH_STD_MODULE})
            target_compile_features(Modules-Example PUBLIC cxx_std_23)
            set_target_properties(Modules-Example PROPERTIES CXX_MODULE_STD ON)
        else()
            target_compile_features(Modules-Example PUBLIC cxx_std_20)
        endif()
    endif()
endif()

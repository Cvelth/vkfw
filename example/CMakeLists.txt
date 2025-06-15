find_package(OpenGL REQUIRED)
find_package(Vulkan REQUIRED)

# Under normal circumstances, FetchContent_MakeAvailable will create the GLFW target that
# other targets can link against. This creates a problem if find_package succeeds, as the
# target has already been defined, which will cause FetchContent_MakeAvailable to fail.
# Since it's impossible to get in here without either having found GLFW through
# find_package or having already fetched it through FetchContent, then all that we need to
# do is handle the case where FetchContent wasn't used because find_package succeeded.
# Since all that we want is for GLFW to be cloned so we can access the deps folder, we're
# going to use FetchContent_Populate instead.
if(NOT glfw3_FOUND)
    include(FetchContent)
    FetchContent_Populate(
        glfw3
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG ${VKFW_GLFW_FETCH_VERSION}
        QUIET
    )
endif()

function(add_example NAME)
    cmake_parse_arguments(ARG "MODULE" "" "" ${ARGN})

    add_executable(
        "${NAME}"
        WIN32
        MACOSX_BUNDLE
        "${VKFW_EXAMPLE_ROOT}/${NAME}.cpp"
    )

    if(${ARG_MODULE})
        target_compile_features("${NAME}" PRIVATE cxx_std_23)
        set_target_properties("${NAME}" PROPERTIES CXX_MODULE_STD ON)
        target_link_libraries("${NAME}" PUBLIC vkfw-module)
    else()
        target_compile_features("${NAME}" PRIVATE cxx_std_20)
        target_link_libraries("${NAME}" PRIVATE vkfw)
    endif()

    target_link_libraries("${NAME}" PRIVATE glfw Vulkan::Vulkan)
    target_include_directories("${NAME}" PRIVATE "${glfw3_SOURCE_DIR}/deps")

    if(MSVC OR CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
        target_compile_definitions("${NAME}" PRIVATE _CRT_SECURE_NO_WARNINGS)
    endif()

    if(MSVC)
        set_target_properties(
            "${NAME}"
            PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup"
        )
    elseif(CMAKE_CXX_SIMULATE_ID STREQUAL "MSVC")
        set_target_properties(
            "${NAME}"
            PROPERTIES LINK_FLAGS "-Wl,/entry:mainCRTStartup"
        )
    endif()

    if(APPLE)
        set_target_properties(
            "${NAME}"
            PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "${NAME}"
        )
    endif()
endfunction()

add_example(boing)
add_example(clipboard)
add_example(cursor)
add_example(empty)
add_example(empty_raii)
add_example(events)
add_example(gears)
add_example(heightmap)
add_example(icon)
add_example(iconify)
add_example(offscreen)
add_example(sharing)
add_example(windows)

# C++ module example, require C++23 (for import std;) and CMake 3.30+
if(VKFW_BUILD_CXX_MODULE AND VKFW_BUILD_WITH_STD_MODULE)
    add_example(empty-module MODULE)
endif()

include(CMakeFindDependencyMacro)
find_dependency(glfw3 REQUIRED)

include(${CMAKE_CURRENT_LIST_DIR}/vkfwTargets.cmake)

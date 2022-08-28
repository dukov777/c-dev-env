cmake_minimum_required(VERSION 3.22.0)
project(app VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(app main.c)
add_subdirectory(slcan)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

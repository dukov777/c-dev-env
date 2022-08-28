cmake_minimum_required(VERSION 3.22.0)
project(app VERSION 0.1.0)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
  app
  hello_test.cpp
)

add_subdirectory(../project/slcan build)

target_link_libraries(
  app
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(app)

# include(CTest)
enable_testing()

# add_executable(app main.c)
# add_subdirectory(slcan)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

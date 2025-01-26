cmake_minimum_required (VERSION 3.28)

project (leetcode LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

set(SOURCES 
  src/leetcode_test.cpp
  src/144_binary_tree_preorder_traversal.cpp
  src/92_binary_tree_inorder_traversal.cpp
  src/100_same_tree.cpp
  src/101_symmetric_tree.cpp
  src/104_maximum_depth_of_binary_tree.cpp
  src/108_convert_sorted_array_to_binary_search_tree.cpp
  src/110_balanced_binary_tree.cpp
  src/111_minimum_depth_of_binary_tree.cpp
  src/112_path_sum.cpp
  src/145_binary_tree_postorder_traversal.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)

gtest_discover_tests(${PROJECT_NAME})

# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.5)

# Name of the project
project(Nonograms)

set(CMAKE_BUILD_TYPE Debug)

# Create a few variables for the folder names, so they are easier to rename in
# the future
set(SRC_DIR src)

# Add all the source files needed to build the executable
add_executable(
  tomo_test
  test/test_tomo_io.cpp
  ${SRC_DIR}/TomographySet.cpp
)

add_executable(
  print_buff_test
  test/test_print_buff.cpp
  ${SRC_DIR}/TomographySet.cpp
  ${SRC_DIR}/NonogramGrid.cpp
  ${SRC_DIR}/CharBuffer.cpp
)

add_executable(
  brute_force_test
  test/test_brute_force.cpp
  ${SRC_DIR}/TomographySet.cpp
  ${SRC_DIR}/NonogramGrid.cpp
  ${SRC_DIR}/CharBuffer.cpp
  ${SRC_DIR}/BruteSolver.cpp
)

add_executable(
  dfs_test
  test/test_dfs.cpp
  ${SRC_DIR}/TomographySet.cpp
  ${SRC_DIR}/NonogramGrid.cpp
  ${SRC_DIR}/CharBuffer.cpp
  ${SRC_DIR}/DFSSolver.cpp
)


#set(CMAKE_C_COMPILER   aarch64-linux-gnu-gcc-11)
#set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++-10.2.0)
set(CMAKE_C_COMPILER   aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

cmake_minimum_required(VERSION 3.12.4)

if(NOT ESP_PLATFORM)
  project(lvgl HOMEPAGE_URL https://github.com/lvgl/lvgl)
endif()

set(LVGL_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

include(${CMAKE_CURRENT_LIST_DIR}/env_support/cmake/custom.cmake)

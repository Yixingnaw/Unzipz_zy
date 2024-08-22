cmake_minimum_required(VERSION 3.5)
set(CMAKE_PREFIX_PATH "C:/Users/22413/Downloads/vcpkg-master/installed/x64-mingw-dynamic")

project(zip_recover LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)




include_directories(C:/Users/22413/Downloads/vcpkg-master/installed/x64-mingw-dynamic/include)
link_directories(C:/Users/22413/Downloads/vcpkg-master/installed/x64-mingw-dynamic/lib)

find_package(minizip CONFIG REQUIRED)


find_package(Qt5 COMPONENTS Widgets REQUIRED)

  # 自动获取当前目录下的所有 .cpp 和 .h 文件
  file(GLOB_RECURSE SOURCES
    "*.cpp"
    "*.h"
    "*.ui"

  )
  add_executable(zip_recover ${SOURCES})

target_link_libraries(zip_recover PRIVATE minizip)
target_link_libraries(zip_recover PRIVATE Qt5::Widgets )



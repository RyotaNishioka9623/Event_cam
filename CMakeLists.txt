cmake_minimum_required(VERSION 3.22)
project(Event_cam)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCV を探す
find_package(OpenCV REQUIRED)

# Metavision SDK のパス
set(METAVISION_SDK_DIR "/usr/local")

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${METAVISION_SDK_DIR}/include
)

link_directories(
    ${METAVISION_SDK_DIR}/lib
)

add_executable(Event_cam test_src/main.cpp)

# OpenCV と Metavision SDK ライブラリをリンク（小文字）
target_link_libraries(Event_cam 
    ${OpenCV_LIBS}
    metavision_sdk_driver
    metavision_sdk_base
    metavision_sdk_core
)

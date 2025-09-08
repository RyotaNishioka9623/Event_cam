cmake_minimum_required(VERSION 3.22)
project(Event_cam)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OpenCVを探す
find_package(OpenCV REQUIRED)

# Metavision SDKのパス（必要に応じて変更）
set(METAVISION_SDK_DIR "/usr/local")  # SDKのインストールディレクトリに合わせて変更

include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${METAVISION_SDK_DIR}/include
)

link_directories(
    ${METAVISION_SDK_DIR}/lib
)

add_executable(Event_cam test_src/main.cpp)

target_link_libraries(Event_cam ${OpenCV_LIBS})
cmake_minimum_required(VERSION 3.10)
project(Event_cam)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Metavision SDK のパスを /usr/local に変更
set(METAVISION_SDK_PATH "/usr/local")

include_directories(
    ${METAVISION_SDK_PATH}/include
)

# ライブラリパス（必要に応じて）
link_directories(
    ${METAVISION_SDK_PATH}/lib
)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 実行ファイル
add_executable(Event_cam test_src/main.cpp)

# ライブラリリンク
target_link_libraries(Event_cam ${OpenCV_LIBS})
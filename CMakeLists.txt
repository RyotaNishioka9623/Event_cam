cmake_minimum_required(VERSION 3.10)
project(Event_cam)

# C++20 を使用
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Metavision SDK のパスを指定（必要に応じて変更）
# 例: /opt/Prophesee/Metavision_SDK
set(METAVISION_SDK_PATH "/opt/Prophesee/Metavision_SDK")

# include ディレクトリ
include_directories(
    ${METAVISION_SDK_PATH}/include
)

# ライブラリパス
link_directories(
    ${METAVISION_SDK_PATH}/lib
)

# OpenCV を探す
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# 実行ファイル
add_executable(Event_cam src/main.cpp)

# ライブラリをリンク
target_link_libraries(Event_cam
    MetavisionSDK::Driver          # カメラドライバ
    MetavisionSDK::Core            # 基本API
    MetavisionSDK::HAL             # ハードウェア抽象層
    ${OpenCV_LIBS}                 # OpenCV
)
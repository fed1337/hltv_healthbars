cmake_minimum_required(VERSION 3.20)
project(hltv_healthbars LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(HLSDK_DIR ${CMAKE_SOURCE_DIR}/external/hlsdk)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC_FILES
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/external/lodepng/*.cpp
)

add_library(hltv_healthbars SHARED ${SRC_FILES})

target_compile_definitions(hltv_healthbars PRIVATE
        WIN32_LEAN_AND_MEAN
        NOMINMAX
        WINVER=0x0601
        _WIN32_WINNT=0x0601
)

target_include_directories(hltv_healthbars PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/external/lodepng
        ${HLSDK_DIR}
        ${HLSDK_DIR}/cl_dll
        ${HLSDK_DIR}/common
        ${HLSDK_DIR}/devtools
        ${HLSDK_DIR}/dlls
        ${HLSDK_DIR}/dmc
        ${HLSDK_DIR}/engine
        ${HLSDK_DIR}/external
        ${HLSDK_DIR}/game
        ${HLSDK_DIR}/game_shared
        ${HLSDK_DIR}/lib
        ${HLSDK_DIR}/pm_shared
        ${HLSDK_DIR}/utils
        ${HLSDK_DIR}/public
)

target_link_libraries(hltv_healthbars
        user32
        gdi32
        winmm
)

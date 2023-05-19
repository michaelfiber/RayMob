cmake_minimum_required(VERSION 3.18.1)
project("${APP_LIB_NAME}")

set(GAME_SOURCES_DIR "${CMAKE_SOURCE_DIR}/game")
file(GLOB_RECURSE SOURCES "${GAME_SOURCES_DIR}/*.c")
list(APPEND SOURCES ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)

add_library(${APP_LIB_NAME} SHARED ${SOURCES})
target_compile_definitions(${APP_LIB_NAME} PRIVATE PLATFORM_ANDROID)

# Determines the build architecture target of the APK
if(${ANDROID_ABI} STREQUAL "armeabi-v7a")
    set(RAYLIB_ARCH_DIR "${CMAKE_SOURCE_DIR}/../../../libs/armv7a")
elseif(${ANDROID_ABI} STREQUAL "arm64-v8a")
    set(RAYLIB_ARCH_DIR "${CMAKE_SOURCE_DIR}/../../../libs/aarch64")
elseif(${ANDROID_ABI} STREQUAL "x86")
    set(RAYLIB_ARCH_DIR "${CMAKE_SOURCE_DIR}/../../../libs/i686")
elseif(${ANDROID_ABI} STREQUAL "x86_64")
    set(RAYLIB_ARCH_DIR "${CMAKE_SOURCE_DIR}/../../../libs/x86_64")
endif()

# Adds the corresponding Raylib static library to the architecture target
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "${RAYLIB_ARCH_DIR}/libraylib.a")

# Includes Raylib header files
target_include_directories(${APP_LIB_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/raylib")

# Tell CMake to link all necessary libraries to the native application
target_link_libraries(${APP_LIB_NAME}
        raylib
        log
        android
        EGL
        GLESv2
        OpenSLES
        dl
        m
        c)

target_link_options(${APP_LIB_NAME} PRIVATE "-u ANativeActivity_onCreate")

find_library(log-lib log)
target_link_libraries(${APP_LIB_NAME} ${log-lib})
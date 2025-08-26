#
# Copyright (C) 2020-2024 QuasarApp.
# Distributed under the lGPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.19)
project(QtSDL LANGUAGES CXX)
if(TARGET ${PROJECT_NAME})
  message("The ${PROJECT_NAME} arledy included in main Project")
  return()
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Test QUIET)

include(submodules/CMake/QuasarApp.cmake)

updateGitVars()
set(QTSDL_VERSION "0.${GIT_COMMIT_COUNT}.${GIT_COMMIT_HASH}")

option(QTSDL_TESTS "This option disables or enables tests of the ${PROJECT_NAME} project"  ON)
option(QTSDL_EXAMPLE "This option disables or enables example app of the ${PROJECT_NAME} project" ON)

if (ANDROID OR IOS OR QA_WASM32)
    set(QTSDL_TESTS OFF CACHE BOOL "This option force disbled for ANDROID IOS QA_WASM32 and Not Qt projects" FORCE)
endif()

make_directory(Distro)

initAll()

if (QTSDL_TESTS)
    add_subdirectory(src/testcore)
endif()

add_subdirectory(src/QtSDL)

if (QTSDL_TESTS)
    add_subdirectory(tests)
else()
    message("The ${PROJECT_NAME} tests is disabled.")
endif()

configure_file_in(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)
addDoc(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/doxygen.conf)

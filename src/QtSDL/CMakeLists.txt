#
# Copyright (C) 2020-2024 QuasarApp.
# Distributed under the lGPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.19)

set(CURRENT_PROJECT "${PROJECT_NAME}")
add_definitions(-DQTSDL_LIBRARY)


file(GLOB_RECURSE SOURCE_CPP
    "src/*.cpp"
    "src/*.h"
)

file(GLOB_RECURSE SOURCE_QRC
    "*.qrc"
)

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/public")
set(PRIVATE_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/private")

add_library(${CURRENT_PROJECT} ${SOURCE_CPP} ${SOURCE_QRC})
find_package(SDL3 REQUIRED)

if (QTSDL_TESTS)
    target_link_libraries(${CURRENT_PROJECT} PUBLIC ${PROJECT_NAME}testcore SDL3)
else()
    target_link_libraries(${CURRENT_PROJECT} PUBLIC Qt${QT_VERSION_MAJOR}::Core SDL3)
endif()

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCUDE_DIR})

configure_file_in(${CURRENT_PROJECT} "${CMAKE_CURRENT_SOURCE_DIR}/src/public/QtSDL/global.h")

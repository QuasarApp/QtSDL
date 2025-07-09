#
# Copyright (C) 2020-2024 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.19)

set(CURRENT_PROJECT "${PROJECT_NAME}testcore")
add_definitions(-DTEST_CORE_LIBRARY)


file(GLOB_RECURSE SOURCE_CPP
    "*.cpp"
    "*.h"
)

file(GLOB_RECURSE SOURCE_QRC
    "*.qrc"
)

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_library(${CURRENT_PROJECT} ${SOURCE_CPP} ${SOURCE_QRC})

target_link_libraries(${CURRENT_PROJECT} PUBLIC Qt${QT_VERSION_MAJOR}::Core )

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCUDE_DIR})

configure_file_in(${CURRENT_PROJECT} "${CMAKE_CURRENT_SOURCE_DIR}/testcore/global.h")

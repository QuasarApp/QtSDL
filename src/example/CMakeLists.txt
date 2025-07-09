#
# Copyright (C) 2021-2024 QuasarApp.
# Distributed under the GPLv3 software license, see the accompanying
# Everyone is permitted to copy and distribute verbatim copies
# of this license document, but changing it is not allowed.
#

cmake_minimum_required(VERSION 3.19)

get_filename_component(CURRENT_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CURRENT_PROJECT "${PROJECT_NAME}_${CURRENT_PROJECT_DIR}")
option(SIGN_APP "This option enable od disabled sign apk and aab files" ON)

file(GLOB_RECURSE SOURCE_CPP
    "*.cpp" "*.h"
)

file(GLOB_RECURSE SOURCE_QRC
    "*.qrc"
)

set(ALL_SOURCES ${SOURCE_CPP} ${SOURCE_QRC})

set(PUBLIC_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

set(PRIVATE_INCUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

updateGitVars()

qt_add_executable(${CURRENT_PROJECT} ${ALL_SOURCES})

target_link_libraries(${CURRENT_PROJECT} PUBLIC ${PROJECT_NAME})

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCUDE_DIR})

SET(TARGET_DIR "${CMAKE_SOURCE_DIR}/Distro")
file(MAKE_DIRECTORY ${TARGET_DIR})

if (ANDROID)

    set(ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android CACHE INTERNAL "")
    set(ENV{ANDROID_API_VERSION} 31)
    set(ANDROID_API_VERSION $ENV{ANDROID_API_VERSION})
    set(OPENSSL_ROOT_PATH "$ENV{OPENSSL_ROOT_DIR}")

    set(QtSDL_EXTRA_LIBS
        ${PROJECT_NAME}Library
#        libName
        )

    if (SIGN_APP)
        message("SIGN_APP")
        addDeploySignedAPK(${CURRENT_PROJECT}
            "${CMAKE_CURRENT_LIST_DIR}/android"
            "QuasarAppProject"
            "${SIGPATH}/quasarapp.keystore"
            "${SIGPASS_QUASARAPP}"
            "${TARGET_DIR}"
            "${QtSDL_EXTRA_LIBS}")

    else()
        message("NO_SIGN_APP")

        addDeployAPK(${CURRENT_PROJECT}
            "${CMAKE_CURRENT_LIST_DIR}/android"
            "${TARGET_DIR}"
            "${QtSDL_EXTRA_LIBS}")

    endif()
    set(manifest_file "${CMAKE_CURRENT_SOURCE_DIR}/android/AndroidManifest.xml")
    configure_file("${manifest_file}.in" ${manifest_file} @ONLY)

    set(gradle_file "${CMAKE_CURRENT_SOURCE_DIR}/android/build.gradle")
    configure_file("${gradle_file}.in" ${gradle_file} @ONLY)

    file(GLOB java_files
       "android/src/com/quasarapp/androidtools/*.java"
       "android/*.xml"
       "android/*.gradle"
       "android/gradlew"
       "android/gradle.*"

    )

    add_custom_target(${name}Android
        SOURCES ${java_files}
    )

elseif(IOS)
#    set_xcode_property(${CURRENT_PROJECT} PRODUCT_BUNDLE_IDENTIFIER ${CHEATCARD_PACKAGE_ID} All)

    set_target_properties(${CURRENT_PROJECT} PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER ${QTSDL_PACKAGE_ID}
        MACOSX_BUNDLE_BUNDLE_VERSION ${QTSDL_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${QTSDL_VERSION}
    )
else()
    # Desctop deploying

    message(GIT_COMMIT_COUNT = ${GIT_COMMIT_COUNT})
    configure_file_in(${CURRENT_PROJECT} "${CMAKE_CURRENT_SOURCE_DIR}/deploy/QtSDL.json")

    addDeployFromCustomFile(${CURRENT_PROJECT} "${CMAKE_CURRENT_SOURCE_DIR}/deploy/QtSDL.json")

endif()

set(LANGS ${CMAKE_CURRENT_SOURCE_DIR}/languages/en.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ru.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/uk.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/ja.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/tr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/zh.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/de.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/fr.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/es.ts
          ${CMAKE_CURRENT_SOURCE_DIR}/languages/pl.ts)

prepareQM(${CURRENT_PROJECT} ${CMAKE_CURRENT_SOURCE_DIR}/../ "${LANGS}")



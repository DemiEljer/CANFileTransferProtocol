# Copyright (c) 2025 Ilya Kobrunov <ilya.kobrunov@gmail.com>
# SPDX-License-Identifier: Apache-2.0

message("=== CANFileTransferProtocol library has been included ===")

set(LIBRARY_NAME CANFileTransferProtocol)

add_library(${LIBRARY_NAME} STATIC)

file(GLOB_RECURSE SOURCES ./sources/*.c)
file(GLOB_RECURSE HEADERS ./sources/*.h)
file(GLOB_RECURSE SUBDIRECTORIES LIST_DIRECTORIES TRUE ./sources/*)

FOREACH(SUBDIRECTORY ${SUBDIRECTORIES})
    IF(IS_DIRECTORY ${SUBDIRECTORY})
        target_include_directories(${LIBRARY_NAME}
            PUBLIC
                ${SUBDIRECTORY}
        )
    ENDIF()
ENDFOREACH()

target_sources(${LIBRARY_NAME}
    PRIVATE
        ${SOURCES}
    PUBLIC
        ${HEADERS}
)
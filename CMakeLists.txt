cmake_minimum_required(VERSION 3.2)
project(captive-portal)

include(CMakeListsPrivate.txt)
add_custom_command(
        OUTPUT
            src/portalResources.h
        COMMAND
            ${CMAKE_CURRENT_BINARY_DIR}/resourcesToHeader.exe ${CMAKE_CURRENT_SOURCE_DIR}/data/www/. ${CMAKE_CURRENT_SOURCE_DIR}/src/portalResources.h
        COMMENT
            ">>>>>>>>>> Generating portalResources header."
        DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/utils/resourcesToHeader.cpp
        VERBATIM
)

add_custom_target(
    PLATFORMIO_BUILD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_BUILD_VERBOSE ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --verbose
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOAD ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target upload
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_CLEAN ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target clean
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_MONITOR ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion device monitor
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_TEST ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion test
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_PROGRAM ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target program
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPLOADFS ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion run --target uploadfs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_UPDATE_ALL ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion update
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    PLATFORMIO_REBUILD_PROJECT_INDEX ALL
    COMMAND ${PLATFORMIO_CMD} -f -c clion init --ide clion
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

set(SOURCE_FILES utils/resourcesToHeader.cpp)
set (CMAKE_C_COMPILER "$ENV{HOMEDRIVE}/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin/gcc.exe" CACHE PATH "" FORCE)
set (CMAKE_CXX_COMPILER "$ENV{HOMEDRIVE}/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/bin/g++.exe" CACHE PATH "" FORCE)
add_executable(resourcesToHeader ${SOURCE_FILES})
add_custom_target(resourcesToHeader-target DEPENDS src/portalResources.h)
message(${CMAKE_CXX_COMPILER})
target_link_libraries(resourcesToHeader -static-libgcc -static-libstdc++ -lz)
set_target_properties(resourcesToHeader PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS OFF
        INCLUDE_DIRECTORIES "$ENV{HOMEDRIVE}/Program Files (x86)/mingw-w64/i686-8.1.0-posix-dwarf-rt_v6-rev0/mingw32/i686-w64-mingw32/include"
        )
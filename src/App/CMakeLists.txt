set(APP_BUILD_VERSION "0" CACHE STRING "Build version")
set(APP_SHOULD_BE_NICE "OFF" CACHE BOOL "We are nice")

project(ModbusTcpViewerApp LANGUAGES CXX VERSION 1.0.$CACHE{APP_BUILD_VERSION})

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(APP_NAME FTXModbusTcpViewer)

aux_source_directory(. SRC_FILES)

add_executable(${APP_NAME} MACOSX_BUNDLE ${SRC_FILES})

target_compile_definitions(${APP_NAME} PRIVATE APP_VERSION="${PROJECT_VERSION}")
target_compile_definitions(${APP_NAME} PRIVATE APP_BUILD_TYPE="$<CONFIG>")

target_compile_definitions(${APP_NAME} PRIVATE APP_IS_NICE=$<BOOL:$CACHE{APP_SHOULD_BE_NICE}>)

target_compile_options(${APP_NAME} PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:-Wall -O3 -Wno-unused-parameter>
        PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wall -O3 -Wno-unused-parameter>
        PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>: /O2>
        )
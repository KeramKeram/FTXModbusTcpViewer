set(APP_BUILD_VERSION "0" CACHE STRING "Build version")
set(APP_SHOULD_BE_NICE "OFF" CACHE BOOL "We are nice")

project(ModbusTcpViewerApp LANGUAGES CXX VERSION 1.0.$CACHE{APP_BUILD_VERSION})

set(APP_NAME FTXModbusTcpViewer)

aux_source_directory(. SRC_FILES)

add_executable(${APP_NAME} MACOSX_BUNDLE ${SRC_FILES})

target_compile_definitions(${APP_NAME} PRIVATE APP_VERSION="${PROJECT_VERSION}")
target_compile_definitions(${APP_NAME} PRIVATE APP_BUILD_TYPE="$<CONFIG>")

target_compile_definitions(${APP_NAME} PRIVATE APP_IS_NICE=$<BOOL:$CACHE{APP_SHOULD_BE_NICE}>)

target_link_libraries(${APP_NAME} PRIVATE screen)
target_link_libraries(${APP_NAME} PRIVATE component)
target_link_libraries(${APP_NAME} PRIVATE Views)
target_link_libraries(${APP_NAME} PRIVATE Controllers)
target_link_libraries(${APP_NAME} PRIVATE Model)
target_link_libraries(${APP_NAME} PRIVATE ModbusThread)
target_link_libraries(${APP_NAME} PRIVATE ModbusCommon)
target_link_libraries(${APP_NAME} PRIVATE IO)
target_link_libraries(${APP_NAME} PRIVATE Configuration)

target_compile_options(${APP_NAME} PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:-Wall -O3 -Wno-unused-parameter>
        PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wall -O3 -Wno-unused-parameter>
        PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>: /O2>
        )
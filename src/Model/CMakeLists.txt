
set(LIB_NAME Model)

aux_source_directory(. SRC_FILES)

add_library(${LIB_NAME} SHARED ${SRC_FILES})

if (MSVC)
    target_compile_definitions(${LIB_NAME} INTERFACE "APP_WIDGET_API=__declspec(dllimport)")
    target_compile_definitions(${LIB_NAME} PRIVATE "APP_WIDGET_API=__declspec(dllexport)")
else ()
    target_compile_definitions(${LIB_NAME} PUBLIC "APP_WIDGET_API=")
endif ()

target_include_directories(${LIB_NAME} INTERFACE .)

target_link_libraries(${LIB_NAME} PRIVATE Containers)

target_compile_options(
        ${LIB_NAME} PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,Clang,AppleClang>:-Wall -O3 -Wno-unused-parameter>
        PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,GNU>:-Wall -O3 -Wno-unused-parameter>
        PRIVATE $<$<COMPILE_LANG_AND_ID:CXX,MSVC>: /O2>
)
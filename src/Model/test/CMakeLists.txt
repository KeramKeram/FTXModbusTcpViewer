set(TEST_NAME ModelTests)

find_package(Catch2 REQUIRED)

aux_source_directory(. TEST_FILES)

add_executable(${TEST_NAME} ${TEST_FILES})

target_link_libraries(${TEST_NAME} PRIVATE Catch2::Catch2)
target_link_libraries(${TEST_NAME} PRIVATE Model)

add_test(NAME ${TEST_NAME}
        COMMAND ${TEST_NAME})
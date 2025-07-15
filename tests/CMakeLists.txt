find_package(boost_unit_test_framework CONFIG REQUIRED)

add_executable(${PROJECT_NAME}-tests    
    "src/tsx.test.cpp"
    "src/tmx.test.cpp"
    "src/main.cpp")

target_link_libraries(${PROJECT_NAME}-tests
    PRIVATE
       ${PROJECT_NAME}
        Boost::unit_test_framework
)

add_custom_command(
    TARGET ${PROJECT_NAME}-tests PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/tests/res
        ${CMAKE_BINARY_DIR}/tests/res
)

add_test(NAME ${PROJECT_NAME}.Tests COMMAND ${PROJECT_NAME}-tests)
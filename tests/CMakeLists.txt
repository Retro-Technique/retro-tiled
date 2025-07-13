find_package(boost_unit_test_framework CONFIG REQUIRED)

add_executable(${PROJECT_NAME}-tests
    
    "src/example.test.cpp"
    "src/example2.test.cpp"
    "src/main.cpp")

target_link_libraries(${PROJECT_NAME}-tests
    PRIVATE 
        # libraries to test
        Boost::unit_test_framework
)

add_test(NAME ${PROJECT_NAME}Tests COMMAND ${PROJECT_NAME}-tests)
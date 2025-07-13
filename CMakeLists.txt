cmake_minimum_required(VERSION 3.21)

# -> TODO: Update the project name and description
set(PROJECT_NAME template)
set(PROJECT_DESCRIPTION "A template project for CMake-based C++ applications")
# <- TODO

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(${PROJECT_NAME} 
	LANGUAGES CXX
	DESCRIPTION ${PROJECT_DESCRIPTION}
	VERSION 1.0
)

option(${PROJECT_NAME}_BUILD_TESTS "Build the test suite" ON)

if(${PROJECT_NAME}_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

add_subdirectory(app/project-app)
add_subdirectory(libs/project-business)
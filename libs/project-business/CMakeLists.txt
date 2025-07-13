add_library(${PROJECT_NAME}-business
	STATIC 
		"src/pch.cpp"
)

target_include_directories(${PROJECT_NAME}-business
	PUBLIC 
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_precompile_headers(${PROJECT_NAME}-business
	PRIVATE 
		"include/pch.h"
)
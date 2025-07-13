add_executable(${PROJECT_NAME}-app
	"src/main.cpp"
    "src/pch.cpp"
)

target_precompile_headers(${PROJECT_NAME}-app
	PRIVATE 
		"src/pch.h"
)
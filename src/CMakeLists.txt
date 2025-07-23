find_package(Boost REQUIRED COMPONENTS property_tree)
find_package(Boost REQUIRED COMPONENTS beast)
find_package(Boost REQUIRED COMPONENTS iostreams)
find_package(boost_algorithm CONFIG REQUIRED)

add_library(${PROJECT_NAME} 
	SHARED 
		"tiled/pch.cpp"
		"tiled/pch.h"
		"tiled/parser.h"
		"tiled/file.cpp"
		"tiled/data_parser.h" 
		"tiled/data_parser.cpp"
)

target_include_directories(${PROJECT_NAME}  
	PUBLIC 
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}  
	PRIVATE 
		Boost::property_tree
		Boost::beast
		Boost::iostreams
		Boost::algorithm
)

target_precompile_headers(${PROJECT_NAME}
	PRIVATE
		"tiled/pch.h"
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		RETRO_TILED_EXPORTS
)
cmake_minimum_required (VERSION 3.8)
project(Chess_engine)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(HEADER
	"include/BitBoard.h"
	"include/MoveGenerator.h"
	"include/Utility.h"
	"include/ChessEngine.h"
)

set(SOURCE
	"src/BitBoard.cpp"
	"src/MoveGenerator.cpp"
	"src/Utility.cpp"
	"src/ChessEngine.cpp"
)

set(TEST_FILES
	"include/Unittest/catch_amalgamated.hpp"
	"src/Unittest/catch_amalgamated.cpp"
	"src/Unittest/AI_Test.cpp"
	"src/Unittest/MoveGeneration_Test.cpp"
	"src/Unittest/Utility_Test.cpp"
)

source_group("\\Source Files\\Unit Tests" FILES ${TEST_FILES})

add_library(Chess_engine STATIC ${HEADER} ${SOURCE})
target_include_directories(Chess_engine PUBLIC include)





add_executable(Unittest ${TEST_FILES} ${HEADER} ${SOURCE})
target_include_directories(Unittest PUBLIC include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries(Unittest ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})

#[[
if (MSVC)
	add_custom_command(TARGET Unittest
						POST_BUILD
						COMMAND ${CMAKE_COMMAND} -E copy_directory
						"${CMAKE_SOURCE_DIR}/Images"
						"$<TARGET_FILE_DIR:Unittest>/Images")

    add_custom_command(TARGET Unittest
                        POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "$ENV{SDL2_BIN}/SDL2.dll"
                        $<TARGET_FILE_DIR:Unittest>)

    file(GLOB SDL2_IMAGE_DLLS "$ENV{SDL2IMAGE_BIN}/*.dll")
    add_custom_command(TARGET Unittest
                        POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        ${SDL2_IMAGE_DLLS}
                        $<TARGET_FILE_DIR:Unittest>)
endif (MSVC)
]]
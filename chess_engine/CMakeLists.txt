cmake_minimum_required (VERSION 3.8)
project(Chess_engine)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(HEADER
	"include/BitBoard.h"
	"include/MoveGenerator.h"
	"include/Utility.h"
	"include/ChessEngine.h"
	"include/NegamaxAI.h"
	"include/RNG.h"
	"include/ValueTables.h"
)

set(SOURCE
	"src/BitBoard.cpp"
	"src/MoveGenerator.cpp"
	"src/Utility.cpp"
	"src/ChessEngine.cpp"
	"src/NegamaxAI.cpp"
	"src/RNG.cpp"
)

source_group("\\Source Files\\Unit Tests" FILES ${TEST_FILES})

#Library project
add_library(Chess_engine STATIC ${HEADER} ${SOURCE})
target_include_directories(Chess_engine PUBLIC include)




set(TEST_FILES
	"include/Unittest/catch_amalgamated.hpp"
	"src/Unittest/catch_amalgamated.cpp"
	"src/Unittest/AI_Test.cpp"
	"src/Unittest/MoveGeneration_Test.cpp"
	"src/Unittest/Utility_Test.cpp"
	"src/Unittest/BitBoard_Test.cpp"
	"src/Unittest/Current_Test.cpp"
)

#Unittest project
add_executable(Unittest ${TEST_FILES} ${HEADER} ${SOURCE})
target_include_directories(Unittest PUBLIC include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries(Unittest ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
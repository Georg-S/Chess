cmake_minimum_required (VERSION 3.8)
project(Chess_4.0)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CHESS_HEADER
	"include/Chess/Chess.h"
	"include/Chess/Renderer.h"
	"include/Chess/RenderInformation.h"
	"include/Chess/PlayerCountSelection.h"
	"include/Chess/PlayerColorSelection.h"
	"include/Chess/Constant.h"
)

set(SDL_HEADER
	"include/SDL/Mouse.h"
	"include/SDL/MouseInformation.h"
	"include/SDL/SDLHandler.h"
	"include/SDL/SDLButton.h"
)

set(CHESS_SOURCE
	"src/Chess/Chess.cpp"
	"src/Chess/Renderer.cpp"
	"src/Chess/PlayerCountSelection.cpp"
	"src/Chess/PlayerColorSelection.cpp"
)

set(SDL_SOURCE
	"src/SDL/Mouse.cpp"
	"src/SDL/SDLHandler.cpp"
	"src/SDL/SDLButton.cpp"
)

set(TEST_FILES
	"include/Unittest/catch_amalgamated.hpp"
	"src/Unittest/catch_amalgamated.cpp"
	"src/Unittest/AITest.cpp"
)

source_group("\\Header Files\\Chess" FILES ${CHESS_HEADER})
source_group("\\Header Files\\SDL" FILES ${SDL_HEADER})

source_group("\\Source Files\\Chess" FILES ${CHESS_SOURCE})
source_group("\\Source Files\\SDL" FILES ${SDL_SOURCE})


add_executable(Chess_4.0 WIN32 "src/main.cpp"
						${SDL_HEADER}
						${CHESS_HEADER}
						${SDL_SOURCE}
						${CHESS_SOURCE}
						)

if	(WIN32)
	set(SDL2_INCLUDE_DIRS $ENV{SDL2_INCLUDE})
	set(SDL2_LIBRARIES "$ENV{SDL2_BIN}/SDL2.lib")
	set(SDL2IMAGE_INCLUDE_DIRS $ENV{SDL2IMAGE_INCLUDE})
	set(SDL2IMAGE_LIBRARIES "$ENV{SDL2IMAGE_BIN}/SDL2_image.lib")
endif(WIN32)


target_include_directories(Chess_4.0 PUBLIC include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries(Chess_4.0 Chess_engine ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Chess_4.0)

if (MSVC)
	add_custom_command(TARGET Chess_4.0
						POST_BUILD
						COMMAND ${CMAKE_COMMAND} -E copy_directory
						"${CMAKE_SOURCE_DIR}/Images"
						"$<TARGET_FILE_DIR:Chess_4.0>/Images")

    add_custom_command(TARGET Chess_4.0
                        POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        "$ENV{SDL2_BIN}/SDL2.dll"
                        $<TARGET_FILE_DIR:Chess_4.0>)

    file(GLOB SDL2_IMAGE_DLLS "$ENV{SDL2IMAGE_BIN}/*.dll")
    add_custom_command(TARGET Chess_4.0
                        POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                        ${SDL2_IMAGE_DLLS}
                        $<TARGET_FILE_DIR:Chess_4.0>)
endif (MSVC)
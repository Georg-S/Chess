cmake_minimum_required (VERSION 3.8)
project(Chess_4.0)
set(CMAKE_CXX_STANDARD 17)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CHESS_HEADER

)

set(SDL_HEADER
)

set(CHESS_SOURCE
)

set(SDL_SOURCE
)

set(SOURCES 
	"src/main.cpp")

#source_group("" FILES ${miscFiles})

add_executable(Chess_4.0 ${SOURCES})
if	(WIN32)
	set(SDL2_INCLUDE_DIRS $ENV{SDL2_INCLUDE})
	set(SDL2_LIBRARIES "$ENV{SDL2_BIN}/SDL2.lib")
	set(SDL2IMAGE_INCLUDE_DIRS $ENV{SDL2IMAGE_INCLUDE})
	set(SDL2IMAGE_LIBRARIES "$ENV{SDL2IMAGE_BIN}/SDL2_image.lib")
endif(WIN32)


target_include_directories(Chess_4.0 PUBLIC include ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
target_link_libraries(Chess_4.0 ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Chess_4.0)
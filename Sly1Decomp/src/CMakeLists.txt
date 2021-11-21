

set (FILES
	Util/util.cpp

	Cheats/cheats.cpp

	Savegame/savegame.cpp

	Difficulty/difficulty.cpp

	# ...
)

add_library(DECOMP ${FILES})
target_include_directories(DECOMP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test main.cpp)

target_link_libraries(test PUBLIC DECOMP)

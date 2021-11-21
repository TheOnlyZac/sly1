

set (FILES
	Cheats/cheats.cpp

	Savegame/savegame.cpp

	# ...
)

add_library(DECOMP ${FILES} "Difficulty/difficulty.cpp" "Difficulty/difficulty.h" "Util/util.cpp" "Util/util.h")
target_include_directories(DECOMP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test main.cpp "Difficulty/difficulty.cpp" "Difficulty/difficulty.h" "Util/util.cpp" "Util/util.h")

target_link_libraries(test PUBLIC DECOMP)

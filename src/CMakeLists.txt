

set (FILES
	util.cpp
	cheats.cpp
	savegame.cpp
	difficulty.cpp
	# ...
)

add_library(DECOMP ${FILES})
target_include_directories(DECOMP PUBLIC ${SLY1_INCLUDE_DIR})

add_executable(test main.cpp)

target_link_libraries(test PUBLIC DECOMP)

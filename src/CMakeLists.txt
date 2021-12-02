

set (FILES
	cheats.cpp
	difficulty.cpp
	font.cpp
	savegame.cpp
	screen.cpp
	util.cpp
	# ...
)

add_library(DECOMP SHARED ${FILES})
target_include_directories(DECOMP PUBLIC ${SLY1_INCLUDE_DIR})

add_executable(main main.cpp)

target_link_libraries(main PUBLIC DECOMP)

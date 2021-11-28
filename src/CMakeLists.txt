

set (FILES
	util.cpp
	joy.cpp
	savegame.cpp
	difficulty.cpp
	coin.cpp
	game.cpp
	xform.cpp
	# ...
)

add_library(DECOMP SHARED ${FILES})
target_include_directories(DECOMP PUBLIC ${SLY1_INCLUDE_DIR})

add_executable(main main.cpp)

target_link_libraries(main PUBLIC DECOMP)

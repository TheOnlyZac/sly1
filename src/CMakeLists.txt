

set (FILES
	clock.cpp
	coin.cpp
	difficulty.cpp
	font.cpp
	game.cpp
	gs.cpp
	joy.cpp
	screen.cpp
	ui.cpp
	util.cpp
	wipe.cpp
	xform.cpp
	# ...
)

add_library(DECOMP STATIC ${FILES}) # todo: use shared
target_include_directories(DECOMP PUBLIC ${SLY1_INCLUDE_DIR})

add_executable(main main.cpp)

target_link_libraries(main PUBLIC DECOMP)

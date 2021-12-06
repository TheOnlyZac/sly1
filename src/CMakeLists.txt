

set (FILES
	difficulty.cpp
	font.cpp
	screen.cpp
	util.cpp
	joy.cpp
	gs.cpp
	coin.cpp
	game.cpp
	ui.cpp
	wipe.cpp
	xform.cpp
	# ...
)

add_library(DECOMP STATIC ${FILES}) # todo: use shared
target_include_directories(DECOMP PUBLIC ${SLY1_INCLUDE_DIR})

add_executable(main main.cpp)

target_link_libraries(main PUBLIC DECOMP)

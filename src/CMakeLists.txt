

set (FILES
	Transition.cpp
	util.cpp
	joy.cpp
	gs.cpp
	difficulty.cpp
	coin.cpp
	game.cpp
	xform.cpp
	# ...
)

add_library(DECOMP STATIC ${FILES} "CTextBox.cpp") # todo: use shared

target_include_directories(DECOMP PUBLIC ${SLY1_INCLUDE_DIR})

add_executable(main main.cpp "CTextBox.cpp")

target_link_libraries(main PUBLIC DECOMP)
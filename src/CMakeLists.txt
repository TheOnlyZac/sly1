

set (FILES
	bis.cpp
	cat.cpp
	coin.cpp
	difficulty.cpp
	game.cpp
	gs.cpp
	joy.cpp
	mpeg.cpp
	transition.cpp
	util.cpp
	xform.cpp

	# ...
)

add_library(DECOMP STATIC ${FILES}) # todo: use shared

target_include_directories(DECOMP PUBLIC ${SLY1_INCLUDE_DIR})

add_executable(main main.cpp)

target_link_libraries(main PUBLIC DECOMP)
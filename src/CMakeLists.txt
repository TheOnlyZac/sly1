
set (FILES
	bas.cpp
	bis.cpp
	cat.cpp
	clock.cpp
	coin.cpp
	difficulty.cpp
	game.cpp
	gs.cpp
	joy.cpp
	mpeg.cpp
	prog.cpp
	sw.cpp
	transition.cpp
	util.cpp
	wipe.cpp
	wm.cpp
	xform.cpp
	zap.cpp
	# ...
 "keyhole.cpp")

add_library(DECOMP STATIC ${FILES} "keyhole.cpp" "vec.cpp" "so.cpp" "dialog.cpp" "speaker.cpp" "mat.cpp") # todo: use shared

target_include_directories(DECOMP PUBLIC ${SLY1_INCLUDE_DIR})

add_executable(main main.cpp "keyhole.cpp" "vec.cpp" "so.cpp" "dialog.cpp" "speaker.cpp" "mat.cpp")

target_link_libraries(main PUBLIC DECOMP)
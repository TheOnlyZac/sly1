

set (FILES
	chkpnt.cpp
	clock.cpp
	cm.cpp
	coin.cpp
	difficulty.cpp
	font.cpp
	frm.cpp
	game.cpp
	gs.cpp
	joy.cpp
	phasemem.cpp
	render.cpp
	screen.cpp
	sw.cpp
	ui.cpp
	update.cpp
	util.cpp
	wipe.cpp
	xform.cpp
	# ...

	splice/spliceutils.cpp
	# ...
)

add_library(DECOMP STATIC ${FILES})
target_include_directories(DECOMP PUBLIC
	${SLY1_INCLUDE_DIR}
	${SLY1_SOURCE_DIR}
)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC DECOMP)

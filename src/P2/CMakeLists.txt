# /src/P2

add_subdirectory(splice)

set (P2_SOURCE_FILES
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
)

add_library(P2 STATIC ${P2_SOURCE_FILES})
target_include_directories(P2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(P2 PUBLIC SPLICE)

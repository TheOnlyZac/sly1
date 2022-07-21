
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
	# ...

	splice/spliceutils.cpp
	# ...
)

add_library(${P2_LIB_TARGET} STATIC ${P2_SOURCE_FILES})
target_include_directories(P2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${P2_ELF_TARGET} main.cpp)
target_link_libraries(${P2_ELF_TARGET} PUBLIC P2)

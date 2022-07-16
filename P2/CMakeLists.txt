

set (FILES
	clock.cpp
	coin.cpp
	difficulty.cpp
	game.cpp
	gs.cpp
	joy.cpp
	util.cpp
	xform.cpp
	# ...
)

add_library(P2 STATIC ${FILES})
target_include_directories(P2 PUBLIC ${P2_SOURCE_DIR})

add_executable(${ELF_TARGET} main.cpp)

target_link_libraries(${ELF_TARGET} PUBLIC P2)

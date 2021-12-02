

set (FILES
	util.cpp
	cheats.cpp
	savegame.cpp
	difficulty.cpp
	# ...
)

add_library(DECOMP SHARED ${FILES} "CTransition.cpp")
target_include_directories(DECOMP PUBLIC ${SLY1_INCLUDE_DIR})

add_executable(main main.cpp "CTransition.cpp")

target_link_libraries(main PUBLIC DECOMP)

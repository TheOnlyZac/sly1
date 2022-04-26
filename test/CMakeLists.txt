
include (${CMAKE_CURRENT_SOURCE_DIR}/AddUnitTest.cmake)

set (TESTNAMES "")

add_subdirectory(clock)
add_subdirectory(coin)
add_subdirectory(difficulty)
add_subdirectory(game)
add_subdirectory(gs)
add_subdirectory(joy)
add_subdirectory(util)
add_subdirectory(xform)

#...

get_property(tests GLOBAL PROPERTY TESTNAMES)

add_custom_target(check COMMAND ctest -C Debug
	DEPENDS ${tests})

# now make check should work for unix systems

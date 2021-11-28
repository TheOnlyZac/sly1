
include (${CMAKE_CURRENT_SOURCE_DIR}/AddUnitTest.cmake)

add_subdirectory(joy)
add_subdirectory(coin)
add_subdirectory(difficulty)
add_subdirectory(game)
add_subdirectory(xform)
add_subdirectory(gs)

#...

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                        DEPENDS ${TESTNAMES})
		
# now make check should work for unix systems

# /test

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(TESTNAMES "")

include(${CMAKE_CURRENT_SOURCE_DIR}/AddUnitTest.cmake)

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
set_target_properties(${tests} PROPERTIES FOLDER tests)

add_custom_target(check DEPENDS ${tests})

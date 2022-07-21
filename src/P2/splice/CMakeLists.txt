# /src/P2/splice

set (SPLICE_SOURCE_FILES
	spliceutils.cpp
	# ...
)

add_library(SPLICE STATIC ${SPLICE_SOURCE_FILES})
target_include_directories(SPLICE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

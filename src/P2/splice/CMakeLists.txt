# /src/P2/splice

file(GLOB SPLICE_SOURCE_FILES *.cpp)

add_library(SPLICE STATIC ${SPLICE_SOURCE_FILES})
target_include_directories(SPLICE PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

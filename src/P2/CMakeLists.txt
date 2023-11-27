# /src/P2

add_subdirectory(splice)

file(GLOB P2_SOURCE_FILES *.cpp)
add_library(P2 STATIC ${P2_SOURCE_FILES})
target_include_directories(P2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(P2 PUBLIC SPLICE)

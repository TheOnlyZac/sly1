# /src/P2

add_subdirectory(splice)

file(GLOB P2_SOURCE_FILES *.cpp)
add_library(P2 STATIC ${P2_SOURCE_FILES} "brx.h" "brx.cpp" "alo.h" "alo.cpp" "lo.h" "lo.cpp" "dl.cpp" "slotheap.h" "slotheap.cpp" "Basic.h" "Basic.cpp" "light.h" "light.cpp" "sidebag.h" "sidebag.cpp" "gc.h" "gc.cpp" "ref.h" "ref.cpp")
target_include_directories(P2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(P2 PUBLIC SPLICE)

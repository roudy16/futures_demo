cmake_minimum_required ( VERSION 2.8.11 )

include_directories(${PROJECT_SOURCE_DIR}/src)

message("PROJECT_SOURCE_DIR is " ${PROJECT_SOURCE_DIR})


SET(SRC_FILES
    "${SRC_DIR}/prime_factorization.cpp"
    "${SRC_DIR}/prime_table.cpp"
    "${SRC_DIR}/futures.cpp"
    )

add_executable(futures_demo ${SRC_FILES})
set_target_properties(futures_demo PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(futures_demo PUBLIC ${FuturesDemo_SOURCE_DIR}/src)

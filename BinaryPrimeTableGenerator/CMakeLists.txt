cmake_minimum_required ( VERSION 2.8.11 )

include_directories("${PROJECT_SOURCE_DIR}/src")


SET(SRC_FILES
    "${SRC_DIR}/prime_table.cpp"
    "${SRC_DIR}/binary_prime_gen.cpp"
    )

add_executable(bin_prime_gen ${SRC_FILES})
set_target_properties(bin_prime_gen PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(bin_prime_gen PUBLIC ${FuturesDemo_SOURCE_DIR}/src)


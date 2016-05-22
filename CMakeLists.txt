cmake_minimum_required ( VERSION 2.8.11 )
project (FuturesDemo)

file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/data")

SET (SRC_DIR "${PROJECT_SOURCE_DIR}/src")
SET (DATA_DIR "${PROJECT_SOURCE_DIR}/data")
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

add_definitions(-DDATA_DIR=${DATA_DIR})

add_subdirectory (BinaryPrimeTableGenerator)
add_subdirectory (FuturesDemo)

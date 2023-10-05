# Create a library from utils.c
add_library(utils utils.c)

# Include the directory containing utils.h
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
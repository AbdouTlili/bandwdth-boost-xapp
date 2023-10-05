cmake_minimum_required(VERSION 3.12)
project(MyProject)

# Add the 'utils' directory to the project
add_subdirectory(ran_utils)

# Add your main executable and link it with the 'utils' library
add_executable(main main.c)
target_link_libraries(main PRIVATE utils)
target_link_libraries(main PRIVATE m)
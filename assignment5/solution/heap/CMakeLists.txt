cmake_minimum_required(VERSION 3.10) # Set the minimum required CMake version.
project(generic_BST C)

# Add the source files and create an executable.
add_executable(gen_heap heap.c  q4_q5_q6.c)

# Link the 'm' library to your executable (for math)
target_link_libraries(gen_heap PRIVATE m)

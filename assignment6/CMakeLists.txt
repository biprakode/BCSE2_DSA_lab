cmake_minimum_required(VERSION 3.10)

project(SortingEfficiency C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)


set(SOURCE_FILES
    main.c
    bubble_sort.c
    insertion_sort.c
    selection_sort.c
    heap_sort.c
    merge_sort.c
    quick_sort.c
    sort_engine.c
)

add_executable(sorter ${SOURCE_FILES})
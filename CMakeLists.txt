cmake_minimum_required(VERSION 3.10)
project(parallel-bfs)

set(CMAKE_CXX_STANDARD 17)

include_directories(lib/pctl/include)
include_directories(lib/cmdline/include)
include_directories(lib/chunkedseq/include)

add_compile_options(-fcilkplus -DUSE_CILK_PLUS_RUNTIME)

add_executable(parallel-bfs src/main.cpp)
target_link_libraries(parallel-bfs pthread cilkrts)

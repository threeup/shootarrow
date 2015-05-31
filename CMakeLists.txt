cmake_minimum_required(VERSION 1.0.1)
project(shootarrow)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

file(GLOB HDRS "shootarrow/*.h")
file(GLOB SRCS "shootarrow/*.cpp")


link_libraries(
    SDL2
    SDL2_image
)

add_executable(shootarrow ${SRCS} ${HDRS})

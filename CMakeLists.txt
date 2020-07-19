CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
PROJECT(algorithm_example)
set(CMAKE_CXX_FLAGS "-std=c++11")
INCLUDE_DIRECTORIES(
    include
    ${OpenCV_INCLUEDE_DIRS}
)
ADD_EXECUTABLE(rabin_karp src/rabin_karp.cpp)

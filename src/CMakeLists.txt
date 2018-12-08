set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED_ON)

add_subdirectory( components )

file( GLOB SRCS *.cpp *.h components/*.cpp)

add_executable ( hlsyn ${SRCS} )

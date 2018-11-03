set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED_ON)

add_subdirectory( components )

file( GLOB SRCS *.cpp *.h )

add_executable ( dpgen ${SRCS} )

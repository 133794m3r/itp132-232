cmake_minimum_required(VERSION 3.16)
project(itp232)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
	# Default debug flags are OK
	set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wextra -Wpedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 ")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g2")

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	else()
		# nothing special for gcc at the moment
	endif()
endif()
set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(array_sort_search
        array_sort_search.cpp)

add_executable(ceaser_cipher
		ceaser_cipher.cpp)

add_executable(enums
		enums.cpp)

add_executable(io_shifter
		io_shifter.cpp)

add_executable(matrix_functions
		matrix_functions.cpp
		matrix_functions.hxx)
		
add_executable(vector_ops
		vector_ops.cpp)


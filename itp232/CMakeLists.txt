cmake_minimum_required(VERSION 2.16)
project(itp232)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++11 /W4")
	set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O2 -g3 ")
	#since CLion decides that you debug from the damn release buildl always instead of from debug and won't let you change that.
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif()
endif()
#set(CMAKE_CXX_STANDARD 11)

include_directories(.)

#add_library(matrix INTERFACE)

add_library(matrix SHARED
		matrix.hxx
		vectors.hxx
		math.hxx)
#target_sources(matrix INTERFACE
#		matrix.hxx
#		math.hxx
#		vectors.hxx
#)
#target_include_directories(project INTERFACE .)

set_target_properties(matrix PROPERTIES LINKER_LANGUAGE CXX)
add_executable(matrix_test
		math.hxx
		vectors.hxx
		matrix.hxx
		matrix_test.hxx
		matrix_test.cpp)

#target_link_libraries(matrix_test
#		INTERFACE
#		matrix)
#add_executable(matrix
#		mat.cpp
#		math.hxx
#		matrix.hxx
#		vectors.hxx)

add_executable(hill_cipher
		hill_cipher.cpp
		matrix.hxx
		hill_cipher.hxx
		math.hxx
		vectors.hxx)

add_executable(hill_test
		hill_test.cpp)

add_executable(stock_trader
	stock_trader.cpp
	math.hxx
	random.h
	stock_trader.h
	terminal.h)

add_executable(movie_theater
		challenges/oop/movie_theater/terminal.h
		challenges/oop/movie_theater/movies.hxx
		challenges/oop/movie_theater/movie_theater.hxx
		challenges/oop/movie_theater/movie_theater.cpp)
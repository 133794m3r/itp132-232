cmake_minimum_required(VERSION 2.16)
project(itp232)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++11 /W4")
	set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -Wextra -Wpedantic")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 ")
	#since CLion decides that you debug from the damn release buildl always instead of from debug and won't let you change that.
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g3")

	if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endif()
endif()
#set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(matrix_test
		matrix_test.cpp
		math.hxx
        matrix.hxx
		vectors.hxx)

add_executable(matrix
		mat.cpp
		math.hxx
		matrix.hxx
		vectors.hxx)

add_executable(hill_cipher
		hill_cipher.cpp
		matrix.hxx
		hill_cipher.hxx
		math.hxx
		vectors.hxx)

add_executable(stock_trader
	stock_trader.cpp
		math.hxx
	random.h
	stock_trader.h
	terminal.h)

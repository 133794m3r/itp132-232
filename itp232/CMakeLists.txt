cmake_minimum_required(VERSION 3.16)
project(itp232)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest /W4")
	# Default debug flags are OK
	set(CMAKE_CXX_FLAGS_RELEASE "{CMAKE_CXX_FLAGS_RELEASE} /O2")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
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

add_executable(matrix_test
        mat.cpp
		math.hxx
        matrix.hxx vectors.hxx)

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


#include <vector>
#include <iostream>
#include "movies.hxx"
#include "movie_theater.hxx"
#include <string>
#include "terminal.h"

int main(){
	//It's uninitialized here. Make sure if you want to pass the list of movies.
	// and not declare another vector do it in a form like the line below. You'd have to make sure
	// that Movie takes the arguments of Name, Rating, Cost in that order. You can order it however you want though.
	//MovieTheater movie_theater({Movie("A Movie","G",10), Movie("B Movie","G",20)});
	MovieTheater movie_theater;
	std::cout << "test " << std::endl;
	pause();
	clear_and_move_top();
	return 0;
}


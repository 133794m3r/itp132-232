
#ifndef MOVIES_HXX
#define MOVIES_HXX
/**
 * Movie Class models a movie in the theater.
 * Properties
 * All are private.
 * name: a std::string
 * rating: one of [G, PG, PG-13, R]. Should be a std::string.
 * cost to see: double type.
 * desc: A std::string describing the movie.
 * The last property is optional and should default to an empty string.
 *
 *
 * Methods should all be in the public section.
 * Should just have an constructor
 * deconstruct(optional)
 *
 * and a print info method.
 *
 * You have a skeleton of the class given to you below.
 */

class MovieTheater;

class Movie{
  private:
	std::string name;
	std::string rating;
	double cost;
	std::string description;
  public:
	Movie(){

	}
	// We make the whole of the MovieTheater class
	friend MovieTheater;
};
#endif //MOVIES_HXX
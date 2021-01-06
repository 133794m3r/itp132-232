
#ifndef MOVIE_THEATER_HXX
#define MOVIE_THEATER_HXX
class Movie;
/**
 **MovieTheater Class holds all of the movies.
 *
 * Properties
 * movies is std::vector that contains Movie objects.
 * Example of a single movie is something like
 * Movie("test","G",10.00)
 *
 * tickets_sold
 * type: std::vector<unsigned int> This holds all of the tickets sold inside
 * of a parallel array instead of making this any more complex for you. So entry 0 matches Movie at index 0.
 *
 * methods
 * add_movie
 * this method should let the person add a movie to be shown. it should set the tickets value to 0. if  t he movie already exists return false, and print the error "Movie already exists".
 * It should only take a Movie object as it's only parameter.
 *
 *
 * purchase_ticket
 * This method should take a parameter of the movie name. If the movie exists it should increment the number of movies sold by 1. Get the index of this item by using the movie title and figuring out which movie has that title.
 *
 *
 * print_sales
 * This method should print all of the movies, and how many tickets were sold.
 * Finally it should print "The theater made $XX today". Where XX is the amount of money it made.
 *
 * This value is simply calculated by multiplying the number of tickets sold for each movie by the cost of that movie. Then adding that to the total. Finally that value is our total.
 *
 *
 * OPTIONAL METHODS
 * movie_info
 * This method should return the following information in a string.
 *
 * movie_name Rating:movie_rating Cost:movie_cost\r\n(new line)
 * movie_description
 *
 *
 * list_movies
 * This method should return the title and rating of each movie that we currently have.
 */


class MovieTheater {
  private:
	std::vector<Movie> movies;
	std::vector<unsigned int> movie_tickets;

  public:
	//constructors
	explicit MovieTheater(){

	}


	bool add_movie(Movie movie_to_add){

		return true;
	}

	bool purchase_ticket(std::string movie_title){

		return true;
	}

	void print_sales(){

	}

	// methods below here are entirely optional.
	std::string movie_info(std::string movie_title){

		return "";
	}

	std::string list_movies(){

	}


};
#endif //MOVIE_THEATER_HXX

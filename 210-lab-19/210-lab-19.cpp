#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

// Define the Movie class
class Movie {
private:
    string title;

    // Linked list for ratings
    struct RatingNode {
        double rating;
        RatingNode* next;
    } *ratingHead;

    // Linked list for comments
    struct CommentNode {
        string comment;
        CommentNode* next;
    } *commentHead;

public:
    // Constructor to initialize movie title and linked list heads
    Movie(string movieTitle) {
        title = movieTitle;
        ratingHead = nullptr;
        commentHead = nullptr;
    }

    // Add a review to both rating and comment lists
    void addReview(double rating, string comment) {
        // Add rating to the front of the rating list
        RatingNode* newRating = new RatingNode{ rating, ratingHead };
        ratingHead = newRating;

        // Add comment to the front of the comment list
        CommentNode* newComment = new CommentNode{ comment, commentHead };
        commentHead = newComment;
    }

    // Calculate and return the average rating
    double calculateAverageRating() {
        int count = 0;
        double sum = 0.0;
        RatingNode* current = ratingHead;

        while (current) {
            sum += current->rating;
            count++;
            current = current->next;
        }

        return count == 0 ? 0 : sum / count;
    }

    // Display all reviews (ratings and comments)
    void displayReviews() {
        cout << "Movie: " << title << endl;
        int reviewCount = 1;

        RatingNode* currentRating = ratingHead;
        CommentNode* currentComment = commentHead;

        while (currentRating && currentComment) {
            cout << "Review #" << reviewCount++ << " - Rating: " 
                 << fixed << setprecision(1) << currentRating->rating 
                 << ", Comment: " << currentComment->comment << endl;
            currentRating = currentRating->next;
            currentComment = currentComment->next;
        }

        cout << "Average Rating: " << fixed << setprecision(1) 
             << calculateAverageRating() << endl << endl;
    }
};

// Function to generate random ratings between 1.0 and 5.0
double generateRandomRating() {
    return (rand() % 41 + 10) / 10.0; // Random rating from 1.0 to 5.0
}

int main() {
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Open file for review comments
    ifstream commentFile("comments.txt");
    if (!commentFile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    // Create a vector of Movie objects
    vector<Movie> movies;
    movies.push_back(Movie("Inception"));
    movies.push_back(Movie("The Matrix"));
    movies.push_back(Movie("Harry Potter"));
     movies.push_back(Movie("The Avengers"));
    string comment;
    int movieIndex = 0;

    // Read comments from file and add reviews with random ratings
    while (getline(commentFile, comment)) {
        if (movieIndex >= movies.size()) {
            movieIndex = 0;  // Reset movie index if we exceed the number of movies
        }
        double randomRating = generateRandomRating();
        movies[movieIndex].addReview(randomRating, comment);
        movieIndex++;
    }

    commentFile.close();

    // Display reviews and average ratings for each movie
    for (Movie& movie : movies) {
        movie.displayReviews();
    }

    return 0;
}

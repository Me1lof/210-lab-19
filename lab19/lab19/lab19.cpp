//Melissa Ochoa Flores
//Assignment: Abstract & Automate 
//COMSC 210

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>

using namespace std;

struct RatingNode {
    double rating;
    RatingNode* next;
};

struct CommentNode {
    string comment;
    CommentNode* next;
};

class Movie {
private:
    string title;
    RatingNode* ratingsHead;
    CommentNode* commentsHead;

public:
    Movie(const string& movieTitle) : title(movieTitle), ratingsHead(nullptr), commentsHead(nullptr) {}

    void addRating(double rating) {
        RatingNode* newNode = new RatingNode{ rating, ratingsHead };
        ratingsHead = newNode;
    }

    void addComment(const string& comment) {
        CommentNode* newNode = new CommentNode{ comment, commentsHead };
        commentsHead = newNode;
    }

    void displayReviews() {
        cout << "Reviews for " << title << ":" << endl;
        RatingNode* rCurrent = ratingsHead;
        CommentNode* cCurrent = commentsHead;
        int reviewNumber = 1;

        while (rCurrent && cCurrent) {
            cout << "Review #" << reviewNumber++ << ": " << fixed << setprecision(1) << rCurrent->rating << ": " << cCurrent->comment << endl;
            rCurrent = rCurrent->next;
            cCurrent = cCurrent->next;
        }
        cout << endl;
    }
};

vector<string> readCommentsFromFile(const string& filename) {
    vector<string> comments;
    ifstream inputFile(filename);
    string line;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            comments.push_back(line);
        }
        inputFile.close();
    }
    else {
        cerr << "Unable to open file." << endl;
    }

    return comments;
}

double generateRandomRating() {
    return (rand() % 41 + 10) / 10.0;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    vector<string> comments = readCommentsFromFile("comments.txt");

    Movie movie1("Inception");
    Movie movie2("The Shawshank Redemption");

    for (const auto& comment : comments) {
        movie1.addRating(generateRandomRating());
        movie1.addComment(comment);
    }

    for (const auto& comment : comments) {
        movie2.addRating(generateRandomRating());
        movie2.addComment(comment);
    }

    movie1.displayReviews();
    movie2.displayReviews();

    return 0;
}

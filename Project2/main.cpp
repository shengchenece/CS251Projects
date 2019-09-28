//
// <<YOUR NAME>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
//
// Project #02: inputs movies and reviews, allowing the user to search
// by movie ID, movie Name, or review ID.  Uses binary search trees for 
// fast search; no other data structures are allowed.
//

#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"

using namespace std;

// BSTs now declared in main() as:
// binarysearchtree<int,MovieData> bstMoviesByID;
struct MovieData
{
int PubYear;
int Num5Stars = 0;
int Num4Stars = 0;
int Num3Stars = 0;
int Num2Stars = 0;
int Num1Stars = 0;
string NameOfMovie;
int IDOfMovie;
};

//
// trim
//
// trims whitespace from beginning and end of string.
//
// Ref: https://stackoverflow.com/questions/25829143/trim-whitespace-from-a-string
// Modified: to handle empty strings, and strings of all blanks.
//
string trim(const string& str)
{
  size_t first = str.find_first_not_of(" \t\n\r");
  size_t last = str.find_last_not_of(" \t\n\r");

  if (first == string::npos && last == string::npos)  // empty, or all blanks:
    return "";
  else if (first == string::npos)  // no blanks at the start:
    first = 0;                     // 0-based
  else if (last == string::npos)   // no blanks trailing at end:
    last = str.length() - 1;       // 0-based

  return str.substr(first, (last - first + 1));
}


//
// InputMovies
//
// Inputs the data from the "movies" file, which contains N>0 lines, where
// each line contains:
//     id pubYear name
//
void InputMovies(string moviesFilename, binarysearchtree<int,MovieData> byID, binarysearchtree<string,MovieData> byName)
{
  ifstream moviesFile(moviesFilename);
  int      id;
  string   name;
  MovieData data;
  
  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> data.PubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    name = trim(name);
    // add name and ID of movie to MoviesData struct as well
    data.NameOfMovie = name;
    data.IDOfMovie = id;

    byID.insert(id, data);
    byName.insert(name, data);

    // debugging:
    cout << id << "," << data.PubYear << "," << name << endl;

    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
  }
}

void InputReviews(string reviewsFilename, binarysearchtree<int,MovieData> byID, binarysearchtree<string,MovieData> byName)
{
  ifstream    reviewsFile(reviewsFilename);
  int         reviewNumber;
  int         movieID;
  int         reviewStars;
  MovieData   data;
  MovieData*  pointer;
  string      movieName;
  
  if (!reviewsFile.good())
  {
    cout << "**Error: unable to open reviews file '" << reviewsFilename << "', exiting" << endl;
    return;
  }

  reviewsFile >> reviewNumber;  // get first review ID, or set EOF flag if file empty:

  while (!reviewsFile.eof())
  {
    // we have more data, so input movie ID and number of stars in review:
    reviewsFile >> movieID;
    reviewsFile >> reviewStars;

    // search movies-by-ID BST for inserting review and filling additional data in struct
    pointer = byID.search(movieID);
    movieName = pointer->NameOfMovie;

    switch(reviewStars)
    {
      case 1: pointer->Num1Stars++;
      case 2: pointer->Num2Stars++;
      case 3: pointer->Num3Stars++;
      case 4: pointer->Num4Stars++;
      case 5: pointer->Num5Stars++;
    }

    // search movies-by-Name BST for inserting review
    pointer = byName.search(movieName);

    switch(reviewStars)
    {
      case 1: pointer->Num1Stars++;
      case 2: pointer->Num2Stars++;
      case 3: pointer->Num3Stars++;
      case 4: pointer->Num4Stars++;
      case 5: pointer->Num5Stars++;
    }

    reviewsFile >> reviewNumber;  // get next ID, or set EOF flag if no more data:
  }
}

//
// main
//
int main()
{
  string moviesFilename; // = "movies1.txt";
  string reviewsFilename; // = "reviews1.txt";

  binarysearchtree<int,MovieData> bstMoviesByID;
  binarysearchtree<string,MovieData> bstMoviesByName;

  cout << "movies file?> ";
  cin >> moviesFilename;

  cout << "reviews file?> ";
  cin >> reviewsFilename;

  string junk;
  getline(cin, junk);  // discard EOL following last input:

  InputMovies(moviesFilename, bstMoviesByID, bstMoviesByName);
  InputReviews(reviewsFilename, bstMoviesByID, bstMoviesByName);

  // output number of entries for each file
  cout << "Num movies: " << bstMoviesByID.size() << endl;
  cout << "Num reviews: " << bstMoviesByID.size() << endl << endl;
  
  cout << "Tree by movie id: size=" << bstMoviesByID.size() << ", height=" << bstMoviesByID.height() << endl;
  cout << "Tree by movie name: size=" << bstMoviesByName.size() << ", height=" << bstMoviesByName.height() << endl;

  // done:
  return 0;
}

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
int Num5Stars;
int Num4Stars;
int Num3Stars;
int Num2Stars;
int Num1Stars;
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
void InputMovies(string moviesFilename)
{
  ifstream moviesFile(moviesFilename);
  int      id, pubYear;
  string   name;

  if (!moviesFile.good())
  {
    cout << "**Error: unable to open movies file '" << moviesFilename << "', exiting" << endl;
    return;
  }

  moviesFile >> id;  // get first ID, or set EOF flag if file empty:

  while (!moviesFile.eof())
  {
    // we have more data, so input publication year and movie name:
    moviesFile >> pubYear;
    getline(moviesFile, name);  // movie name fills rest of input line:

    // trim potential whitespace from both ends of movie name:
    name = trim(name);  

    // debugging:
    cout << id << "," << pubYear << "," << name << endl;

    moviesFile >> id;  // get next ID, or set EOF flag if no more data:
  }
}


//
// main
//
int main()
{
  // binarysearchtree<int,MovieData> bstMoviesByID;
  // test code for individual project parts
  binarysearchtree<int,int> bst1;
  bst1.insert(123, 456);
  bst1.insert(789, 223);
  bst1.insert(264, 308);
  bst1.insert(450, 458);
  bst1.insert(500, 950);

  binarysearchtree<int, int> bst2 = bst1; // copy construct:
  
  cout << bst1.size() << " vs. " << bst2.size() << endl;
  cout << bst1.height() << " vs. " << bst2.height() << endl;

  int* value1 = bst1.search(123);
  int* value2 = bst2.search(123);

  cout << *value1 << " vs. " << *value2 << endl; // both 456
  *value2 = 789; // this should only change bst2:
  cout << *value1 << " vs. " << *value2 << endl; // 456 vs. 789

/*
  string moviesFilename; // = "movies1.txt";
  string reviewsFilename; // = "reviews1.txt";

  cout << "movies file?> ";
  cin >> moviesFilename;

  cout << "reviews file?> ";
  cin >> reviewsFilename;

  string junk;
  getline(cin, junk);  // discard EOL following last input:

  InputMovies(moviesFilename);
*/

  // done:
  return 0;
}

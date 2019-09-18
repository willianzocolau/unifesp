#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
  int numrows = 0, numcols = 0;
  stringstream ss;
  ifstream infile("text.txt");
  string inputLine = "";
  getline(infile, inputLine);
  getline(infile, inputLine);
  ss << infile.rdbuf();
  ss >> numcols >> numrows;

  int array[numrows][numcols];

  for (int row = 0; row < numrows; ++row) {
    for (int col = 0; col < numcols; ++col) {
      ss >> array[row][col];
    }
  }

//  for (int row = 0; row < numrows; ++row) {
//    for (int col = 0; col < numcols; ++col) {
//      cout << array[row][col];
//      cout << " ";
//    }
//    cout << endl;
//  }


}

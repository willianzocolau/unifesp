#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
  int row = 0, col = 0, numrows = 0, numcols = 0;
  ifstream infile("file.pgm");
  stringstream ss;
  string inputLine = "";

  getline(infile,inputLine);
  if(inputLine.compare("P2") != 0) cerr << "Version error" << endl;
  else cout << "Version : " << inputLine << endl;

  getline(infile,inputLine);
  cout << "Comment : " << inputLine << endl;

  ss << infile.rdbuf();
  ss >> numcols >> numrows;
  cout << numcols << " columns and " << numrows << " rows" << endl;

  int array[numrows][numcols];

  for(row = 0; row < numrows; ++row)
    for (col = 0; col < numcols; ++col) ss >> array[row][col];

  for(row = 0; row < numrows; ++row) {
    for(col = 0; col < numcols; ++col) {
      cout << array[row][col] << " ";
    }
    cout << endl;
  }
  infile.close();
}

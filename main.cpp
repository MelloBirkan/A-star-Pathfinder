#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::istringstream;
using std::ifstream;
using std::string;
using std::vector;

auto printBoard(const vector<vector<int>> &board) -> void {
  for (const auto &row: board) {
    for (const auto &cell: row) {
      std::cout << cell << " ";
    }
    std::cout << "\n";
  }
}

auto parseLine(string line) -> vector<int> {
  istringstream lineStream(line);
  int n;
  char c;
  vector<int> row;

  while (lineStream >> n >> c && c == ',') {
    row.push_back(n);
  }

  return row;
}

auto readBoardFile(const string &filename) -> vector<vector<int>> {
  ifstream boardFile(filename);
  vector<vector<int>> board;

  if (!boardFile) {
    std::cout << "Could not open board file" << std::endl;
    return vector<vector<int>>();
  }

  string line;
  while (getline(boardFile, line)) {
    board.push_back(parseLine(line));
  }
  return board;
}



auto main() -> int {
  printBoard(readBoardFile("../board1.txt"));
  return 0;
}

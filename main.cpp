#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State { kEmpty, kObstacle };

auto cellString(State cell) -> string {
  switch (cell) {
    case State::kEmpty:
      return "0 ";
    default:
      return "⛰ ";
  }
}

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
  auto board = readBoardFile("../board1.txt");
  printBoard(board);

  return 0;
}

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

auto printBoard(const vector<vector<State>> &board) -> void {
  for (const auto &row: board) {
    for (const auto &cell: row) {
      std::cout << cellString(cell) << " ";
    }
    std::cout << "\n";
  }
}

auto parseLine(string line) -> vector<State> {
  istringstream lineStream(line);
  int n;
  char c;
  vector<State> row;

  while (lineStream >> n >> c && c == ',') {
    if (n == 1) {
      row.push_back(State::kObstacle);
    } else {
      row.push_back(State::kEmpty);
    }
  }

  return row;
}

auto readBoardFile(const string &filename) -> vector<vector<State>> {
  ifstream boardFile(filename);
  vector<vector<State>> board;

  if (!boardFile) {
    std::cout << "Could not open board file" << std::endl;
    return vector<vector<State>>();
  }

  string line;
  while (getline(boardFile, line)) {
    board.push_back(parseLine(line));
  }
  return board;
}


auto main() -> int {
  auto board = readBoardFile("../1.board");
  printBoard(board);

  return 0;
}

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State { kEmpty, kObstacle, kClosed };

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

auto parseLine(const string &line) -> vector<State> {
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
    return {};
  }

  string line;
  while (getline(boardFile, line)) {
    board.push_back(parseLine(line));
  }
  return board;
}

// MARK: a*

auto addToOpen(int x, int y, int g, int h, vector<vector<int>> &openNodes, vector<vector<State>> &grid) -> void {
  vector<int> node = {x, y, g, h};
  openNodes.push_back(node);

  grid[x][y] = State::kClosed;

}

auto search(const vector<vector<State>> &board, std::array<int, 2> startPosition, std::array<int, 2> endPosition)
    -> vector<vector<State>> {
  std::cerr << "No Path found\n";
  return {};
}

auto heuristic(const int x1, const int y1, const int x2, const int y2) -> int {
  return abs(x1 - x2) + abs(y1 - y2);
}


auto main() -> int {
  std::array<int, 2> init = {0, 0};
  std::array<int, 2> goal = {5, 4};
  vector<vector<State>> board = readBoardFile("../1.board");
  vector<vector<State>> solution = search(board, init, goal);

  printBoard(board);

  return 0;
}

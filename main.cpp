#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

enum class State { kEmpty, kObstacle, kClosed, kPath };

auto compare(const vector<int> &nodeLhs, const vector<int> &nodeRhs) -> bool {
  const int fLhs = nodeLhs[2] + nodeLhs[3];
  const int fRhs = nodeRhs[2] + nodeRhs[3];

  return fLhs > fRhs;
}


auto cellString(const State cell) -> string {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    default: return "0   ";
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

auto checkValidCell(const int x, const int y, const vector<vector<State>> &grid) -> bool {
  if (x >= 0 && x <= grid.size() && y >= 0 && y <= grid[0].size()) {
    if (grid[x][y] == State::kEmpty) {
      return true;
    }
  }

  return false;
}

auto ceilSort(vector<vector<int>> &v) -> void {
std:
  std::sort(v.begin(), v.end(), compare);
}

auto addToOpen(int x, int y, int g, int h, vector<vector<int>> &openNodes, vector<vector<State>> &grid) -> void {
  vector<int> node = {x, y, g, h};
  openNodes.push_back(node);

  grid[x][y] = State::kClosed;
}

auto heuristic(const int x1, const int y1, const int x2, const int y2) -> int { return abs(x1 - x2) + abs(y1 - y2); }

auto search(vector<vector<State>> grid, std::array<int, 2> startPosition, std::array<int, 2> endPosition)
    -> vector<vector<State>> {
  vector<vector<int>> openNodes;
  int x = startPosition[0];
  int y = startPosition[1];
  int h = heuristic(x, y, endPosition[0], endPosition[1]);

  addToOpen(x, y, 0, h, openNodes, grid);

  while (!openNodes.empty()) {
    ceilSort(openNodes);
    vector<int> node = openNodes.back();
    openNodes.pop_back();

    x = node[0];
    y = node[1];

    grid[x][y] = State::kPath;

    if (x == endPosition[0] && y == endPosition[1]) {
      return grid;
    }
  }

  std::cerr << "No Path found\n";
  return {};
}

auto main() -> int {
  std::array<int, 2> init = {0, 0};
  std::array<int, 2> goal = {5, 4};
  vector<vector<State>> board = readBoardFile("../1.board");
  vector<vector<State>> solution = search(board, init, goal);

  printBoard(board);

  return 0;
}

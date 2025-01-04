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

constexpr std::array<std::array<int, 2>, 4> delta = {{{-1, 0}, {0, -1}, {1, 0}, {0, 1}}};

auto compare(const vector<int> &nodeLhs, const vector<int> &nodeRhs) -> bool {
  const int fLhs = nodeLhs[2] + nodeLhs[3];
  const int fRhs = nodeRhs[2] + nodeRhs[3];

  return fLhs > fRhs;
}

auto cellString(const State cell) -> string {
  switch (cell) {
    case State::kObstacle:
      return "⛰️   ";
    case State::kPath:
      return "🚗   ";
    default:
      return "0   ";
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
    if (n == 0) {
      row.push_back(State::kEmpty);
    } else {
      row.push_back(State::kObstacle);
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
  if (x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size()) {
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

auto expandNeighbors(vector<int> &node, std::array<int, 2> &goal, vector<vector<int>> &openNodes,
                     vector<vector<State>> &grid) -> void {
  int x = node[0];
  int y = node[1];
  int g = node[2];

  for (int i = 0; i < 4; ++i) {
    int x2 = x + delta[i][0];
    int y2 = y + delta[i][1];

    if (checkValidCell(x2, y2, grid)) {
      // Increment g value and add neighbor to open list.
      int g2 = g + 1;
      int h2 = heuristic(x2, y2, goal[0], goal[1]);
      addToOpen(x2, y2, g2, h2, openNodes, grid);
    }
  }
}

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

    // Adicione esta linha:
    expandNeighbors(node, endPosition, openNodes, grid);
  }

  std::cerr << "No Path found\n";
  return {};
}

auto main() -> int {
  std::array<int, 2> init = {0, 0};
  std::array<int, 2> goal = {4, 5};
  vector<vector<State>> board = readBoardFile("../1.board");
  vector<vector<State>> solution = search(board, init, goal);

  printBoard(solution);
  return 0;
}

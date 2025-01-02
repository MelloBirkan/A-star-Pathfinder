#include <iostream>
#include <vector>

using std::vector;

auto printBoard(const vector<vector<int>>& board) -> void {
  for (const auto& row: board) {
    for (const auto& cell: row) {
      std::cout << cell << " ";
    }
    std::cout << "\n";
  }
}

auto main() -> int {
  vector<vector<int>> board = {
    {0, 1, 0, 0, 0, 0},
 {0, 1, 0, 0, 0, 0},
 {0, 1, 0, 0, 0, 0},
 {0, 1, 0, 0, 0, 0},
 {0, 0, 0, 0, 1, 0}
  };


  printBoard(board);
  return 0;
}
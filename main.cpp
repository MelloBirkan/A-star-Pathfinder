#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using std::vector;
using std::string;
using std::ifstream;

auto printBoard(const vector<vector<int>>& board) -> void {
  for (const auto& row: board) {
    for (const auto& cell: row) {
      std::cout << cell << " ";
    }
    std::cout << "\n";
  }
}

auto readBoardFile(const string& filename) -> vector<vector<int>> {
  ifstream boardFile(filename);
  vector<vector<int>> board;

  if (!boardFile) {
    std::cout << "Could not open board file" << std::endl;
    return vector<vector<int>>();
  }

  string line;
  while (getline(boardFile, line)) {
    std::cout << line << "\n";
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
  readBoardFile("../board1.txt");
  return 0;
}
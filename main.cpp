
#include "a_star.h"
#include "utils.h"
#include "state.h"
#include <vector>

using std::vector;


auto main() -> int {
  std::array<int, 2> init = {0, 0};
  std::array<int, 2> goal = {4, 5};
  vector<vector<State>> board = readBoardFile("../1.board");
  vector<vector<State>> solution = search(board, init, goal);

  printBoard(solution);
  return 0;
}

//
// Created by Marcello Gonzatto Birkan on 05/01/25.
//

#include "utils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "state.h"
#include <string>

using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;

auto cellString(const State cell) -> string {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    case State::kStart: return "🚦   ";
    case State::kFinish: return "🏁   ";
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
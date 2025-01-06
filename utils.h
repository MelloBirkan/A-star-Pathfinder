//
// Created by Marcello Gonzatto Birkan on 05/01/25.
//

#ifndef UTILS_H
#define UTILS_H

#include "state.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

auto cellString(State cell) -> string;
auto printBoard(const vector<vector<State>> &board) -> void;
auto parseLine(const string &line) -> vector<State>;
auto readBoardFile(const string &filename) -> vector<vector<State>>;

#endif //UTILS_H

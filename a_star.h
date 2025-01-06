//
// Created by Marcello Gonzatto Birkan on 05/01/25.
//

#ifndef A_STAR_H
#define A_STAR_H

#include <vector>
#include "state.h"

using std::vector;

auto compare(const vector<int> &nodeLhs, const vector<int> &nodeRhs) -> bool;
auto checkValidCell(const int x, const int y, const vector<vector<State>> &grid) -> bool;
auto ceilSort(vector<vector<int>> &v) -> void;
auto addToOpen(int x, int y, int g, int h, vector<vector<int>> &openNodes, vector<vector<State>> &grid) -> void;
auto heuristic(const int x1, const int y1, const int x2, const int y2) -> int;
auto expandNeighbors(vector<int> &node, std::array<int, 2> &goal, vector<vector<int>> &openNodes,
                     vector<vector<State>> &grid) -> void;
auto search(vector<vector<State>> grid, std::array<int, 2> startPosition, std::array<int, 2> endPosition)
    -> vector<vector<State>>;

#endif //A_STAR_H

//
// Created by Marcello Gonzatto Birkan on 05/01/25.
//

#ifndef STATE_H
#define STATE_H

#include <array>

enum class State { kEmpty, kObstacle, kClosed, kPath, kStart, kFinish };
constexpr std::array<std::array<int, 2>, 4> delta = {{{-1, 0}, {0, -1}, {1, 0}, {0, 1}}};

#endif //STATE_H

#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include "util.cpp"
#include "Board.h"


bool Board::is_inside(const Point& location) {
    if ((location.x >= 0) && (location.y >= 0) \
       && (location.x < this->width) && (location.y < this->height))
        return true;
     return false;
}

float Board::move(const Point& current_loc, const Point& direction, const std::vector<std::vector<float>>& value, int timestep) {
    return Board::move(current_loc, direction, value, timestep, this->probs[0]);
}

float Board::move(const Point& current_loc, const Point& direction, const std::vector<std::vector<float>>& value, int timestep, float prob) {
    float total_reward = 0;
    if (std::abs(prob - this->probs[0]) < 0.0001) {  // 1st move
        total_reward = this->reward;
        if (this->is_in_vector(current_loc, this->obstacles)) {
            return 0;
        }
        if (this->is_in_vector(current_loc, this->end_states)) {
            return this->end_reward[current_loc];
        }
        if (direction.x == 0) {
            total_reward += move(current_loc, Point(-1, 0), value, timestep, this->probs[1]);
            total_reward += move(current_loc, Point(1, 0), value, timestep, this->probs[2]);
        }
        if (direction.y == 0) {
            total_reward += move(current_loc, Point(0, -1), value, timestep, this->probs[1]);
            total_reward += move(current_loc, Point(0, 1), value, timestep, this->probs[2]);
        }
    }
    Point new_loc = current_loc + direction;
    if (this->is_in_vector(new_loc, this->obstacles)) {
        return total_reward + prob * std::pow(this->gamma, timestep) * value[current_loc.x][current_loc.y];
    }
    if (this->is_in_vector(new_loc, this->end_states)) {
        return total_reward + prob * this->end_reward[new_loc];
    }
    if (this->is_inside(new_loc)) {
        return total_reward + prob * std::pow(this->gamma, timestep) * value[new_loc.x][new_loc.y];
    } else {
        return total_reward + prob * std::pow(this->gamma, timestep) * value[current_loc.x][current_loc.y];
    }
}


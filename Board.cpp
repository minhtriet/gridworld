#include <vector>
#include "Board.h"


bool Board::is_inside(Point& location) {
    if ((location.x > 0) && (location.y > 0) \
       && (location.x < this->width) && (location.y < this->height))
        return true;
     return false;
}

int Board::is_in_vector(const Point& location, const std::vector<Point>& to_check) {
    auto it = std::find(to_check.begin(), to_check.end(), location);
    if (it != std::end(to_check)) {
        return -1;
    }
    return std::distance(to_check.begin(), it);
}

float Board::move(const Point& current_loc, const Point& direction, const float prob=Board::probs[0]) {
    float total_reward = 0;
    if (prob == probs[0]) {
        if (direction.x == 0) {
            // move to direction x with 0.1 probs
            total_reward += move(current_loc, Point(-1, direction.y), this->probs[1]);
            total_reward += move(current_loc, Point(1, direction.y), this->probs[2]);
        }
        if (direction.y == 0) {
            // move to direction x with 0.1 probs
            total_reward += move(current_loc, Point(direction.x, -1), this->probs[1]);
            total_reward += move(current_loc, Point(direction.x, 1), this->probs[2]);
        }
    }
    Point new_loc = current_loc + direction;
    if (!this->is_inside(new_loc)) {
        return 0;
    }
    if (this->is_in_vector(new_loc, this->obstacles)) {
        return 0;
    }
    if (this->is_in_vector(new_loc, this->end_states)) {
        return this->end_reward[new_loc];
    }
    return prob*reward;
}

Board::probs{1,2,3}
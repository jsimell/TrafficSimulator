#include "road.hpp"

Road::Road(std::pair<int, int> start, std::pair<int, int> end, int speedLimit)
    : start_(start), end_(end), speedLimit_(speedLimit) {}

std::pair<int, int> Road::GetEnd() const { return end_; }

std::pair<int, int> Road::GetStart() const { return start_; }

int Road::GetSpeedLimit() const { return speedLimit_; }

bool Road::IsVertical() const { return (GetStart().first == GetEnd().first); }

bool Road::IsHorizontal() const {
  return (GetStart().second == GetEnd().second);
}

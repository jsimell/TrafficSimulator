#ifndef ROAD_H
#define ROAD_H

#include "grid.hpp"

/**
 * @brief A class for representing a road in the simulated city.
 *
 */
class Road {
 public:
  /**
   * @brief Construct a new Road object.
   *
   * @param start The starting coordinates of the road
   * @param end The ending coordinates of the road
   * @param speedLimit The speed limit on the road
   */
  Road(std::pair<int, int> start, std::pair<int, int> end, int speedLimit);

  /**
   * @brief Get the coordinates of the end of the road.
   *
   * @return std::pair<int, int>
   */
  std::pair<int, int> GetEnd() const;

  /**
   * @brief Get the coordinates of the start of the road.
   *
   * @return std::pair<int, int>
   */
  std::pair<int, int> GetStart() const;

  /**
   * @brief Get the speed limit of the road.
   *
   * @return The speed limit as an integer
   */
  int GetSpeedLimit() const;

  /**
   * @brief Returns a boolean value indicating if the road os vertical or not.
   *
   * @return True if the road is vertical, false otherwise
   */
  bool IsVertical() const;

  /**
   * @brief Returns a boolean value indicating if the road os horizontal or not.
   *
   * @return True if the road is horizontal, false otherwise
   */
  bool IsHorizontal() const;

 private:
  const std::pair<int, int> start_;
  const std::pair<int, int> end_;
  int speedLimit_;
};

#endif
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "grid.hpp"
#include "trafficlight.hpp"

/**
 * @brief A class used for representing an intersection in the simulated city.
 *
 */
class Intersection {
 public:
  /**
   * @brief Construct a new Intersection object.
   *
   * @param location the coordinates of the intersection as std::pair<int, int>
   */
  Intersection(std::pair<int, int> location);

  /**
   * @brief Get the location of the intersection.
   *
   * @return The coordinates of the intersection as std::pair<int, int>
   */
  std::pair<int, int> GetLocation() const;

  /**
   * @brief Attempts to update the status of the traffic lights in the
   * intersection, if there are any.
   *
   * @param deltaTime
   */
  void Update(float deltaTime);

  /**
   * @brief Adds a traffic light to the intersection.
   *
   * @param t A pointer to a TrafficLight object
   */
  void AddTrafficLight(TrafficLight* t);

  /**
   * @brief Check if the intersection has a traffic light
   *
   */
  bool HasTrafficLight() const;

  /**
   * @brief Returns a boolean value indicating if cars are currently allowed to
   * move vertically through the intersection.
   *
   * @return bool
   */
  bool AllowVertical();

  /**
   * @brief Returns a boolean value indicating if cars are currently allowed to
   * move horizontally through the intersection.
   *
   * @return bool
   */
  bool AllowHorizontal();

  /**
   * @brief Draws the intersection into the SFML window given as parameter.
   *
   * @param window The SFML window to draw the intersection to
   * @param cellSize The size of a single cell in the window
   */
  void Draw(sf::RenderWindow& window, int cellSize, Grid* grid);

 private:
  std::pair<int, int> location_;
  TrafficLight* trafficLight_;
  bool allowVertical_;
  bool allowHorizontal_;
  float timePassed_ = 0.0;
  bool yellow_ = false;
};

#endif

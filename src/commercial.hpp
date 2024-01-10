#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include <algorithm>

#include "building.hpp"

/**
 * @brief One of the concretizing classes for the abstract class Building.
 *
 */
class Commercial : public Building {
 public:
  /**
   * @brief Construct a new Commercial object
   *
   * @param buildingName The name of the commercial building
   * @param location The coordinates of the commercial building
   * @param commercialType The type of the commercial building ("gym",
   * "restaurant", or "shop")
   */
  Commercial(const std::string& buildingName,
             const std::pair<int, int>& location,
             const std::string& commercialType);

  /**
   * @brief Draws the building to the SFML window given as a parameter. Each
   * subclass defines the draw function themselves.
   *
   * @param window A reference to the SFML window where the building should be
   * drawn
   * @param cellSize The size of the cell to be drawn
   */

  virtual void Draw(sf::RenderWindow& window, int cellSize) override;

  /**
   * @brief Prints information about the commercial building to the standard
   * output
   *
   */
  std::string GetType() const override;

 private:
  const std::string type_;
};

#endif

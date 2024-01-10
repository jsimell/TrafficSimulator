#ifndef BUILDING_H
#define BUILDING_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief An abstract class for representing the buildings in the simulated
 * city. Each building is either a commercial, a residential, or an industrial
 * building.
 *
 */
class Building {
 public:
  /**
   * @brief Construct a new Building object.
   *
   * @param buildingName The name of the building
   * @param location The coordinates of the building
   * @param type The type of the building ("industrial",
   * "residential", "shop", "gym", or "restaurant")
   */
  Building(const std::string& buildingName, const std::pair<int, int>& location,
           const std::string& type);

  /**
   * @brief Destroy the Building object.
   *
   */
  virtual ~Building();

  /**
   * @brief Get the name of the building.
   *
   * @return The name of the building as std::string&
   */
  const std::string& GetName() const;

  /**
   * @brief Draws the building to the SFML window given as a parameter. Each
   * subclass defines the draw function themselves.
   *
   * @param window A reference to the SFML window where the building should be
   * drawn
   * @param cellSize The size of the cell to be drawn
   */
  virtual void Draw(sf::RenderWindow& window, int cellSize) = 0;

  /**
   * @brief Get the location of the building.
   *
   * @return The coordinates of the building as std::pair<int, int>&
   */
  const std::pair<int, int>& GetLocation() const;

  /**
   * @brief Get type of building.
   *
   * @return The type as a string.
   */
  virtual std::string GetType() const = 0;

 protected:
  std::string buildingName_;
  std::pair<int, int> location_;
  int personAmount_;
  int carAmount_;
  int maxPersonCapacity_;
  int maxCarCapacity_;
  std::string type_;
};

#endif

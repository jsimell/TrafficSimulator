#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "building.hpp"

/**
 * @brief One of the concretizing classes for the abstract class Building.
 *
 */
class Residential : public Building {
 public:
  /**
   * @brief Construct a new Residential object
   *
   * @param buildingName The name of the residential building
   * @param location The coordinates of the residential building
   */
  Residential(const std::string& buildingName,
              const std::pair<int, int>& location)
      : Building(buildingName, location, "Residential") {}

  /**
   * @brief Draws the building to the SFML window given as a parameter. Each
   * subclass defines the draw function themselves.
   *
   * @param window A reference to the SFML window where the building should be
   * drawn
   * @param cellSize The size of the cell to be drawn
   */
  virtual void Draw(sf::RenderWindow& window, int cellSize) override {
    sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
    int x = location_.first;
    int y = location_.second;
    cellShape.setFillColor(sf::Color(150, 75, 75));
    cellShape.setPosition(x * cellSize, y * cellSize);
    cellShape.setSize(sf::Vector2f(cellSize, cellSize));

    window.draw(cellShape);

    sf::RectangleShape door(sf::Vector2f(cellSize * 0.2f, cellSize * 0.4f));
    door.setFillColor(sf::Color(100, 50, 50));
    door.setPosition((x + 0.4f) * cellSize, (y + 0.6f) * cellSize);
    window.draw(door);

    sf::RectangleShape windowRect(
        sf::Vector2f(cellSize * 0.2f, cellSize * 0.2f));
    windowRect.setFillColor(sf::Color(200, 200, 255));
    windowRect.setPosition((x + 0.7f) * cellSize, (y + 0.2f) * cellSize);
    window.draw(windowRect);

    sf::ConvexShape roof(3);
    roof.setPoint(0, sf::Vector2f(x * cellSize, y * cellSize));
    roof.setPoint(1,
                  sf::Vector2f((x + 0.5f) * cellSize, (y - 0.5f) * cellSize));
    roof.setPoint(2, sf::Vector2f((x + 1.0f) * cellSize, y * cellSize));
    roof.setFillColor(sf::Color(100, 50, 50));
    window.draw(roof);
  }

  /**
   * @brief Prints information about the residential building to the standard
   * output
   *
   */
  std::string GetType() const override { return type_; }
};

#endif

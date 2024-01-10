#ifndef INDUSTRIAL_H
#define INDUSTRIAL_H

#include "building.hpp"

/**
 * @brief One of the concretizing classes for the abstract class Building.
 *
 */
class Industrial : public Building {
 public:
  /**
   * @brief Construct a new Industrial object
   *
   * @param buildingName The name of the industrial building
   * @param location The coordinates of the idnustrial building
   */
  Industrial(const std::string& buildingName,
             const std::pair<int, int>& location)
      : Building(buildingName, location, "Industrial") {}

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

    cellShape.setFillColor(sf::Color(180, 180, 180)); 
    cellShape.setPosition(x * cellSize, y * cellSize);
    cellShape.setSize(sf::Vector2f(cellSize, cellSize)); 

    window.draw(cellShape);

    sf::RectangleShape door(sf::Vector2f(cellSize * 0.4f, cellSize));
    door.setFillColor(sf::Color(120, 120, 120)); 
    door.setPosition((x + 0.6f) * cellSize, y * cellSize);
    window.draw(door);

    for (int i = 0; i < 2; ++i) {
        sf::RectangleShape windowRect(sf::Vector2f(cellSize * 0.2f, cellSize * 0.2f));
        windowRect.setFillColor(sf::Color(200, 200, 200)); 
        windowRect.setPosition((x + 0.2f + i * 0.4f) * cellSize, (y + 0.2f) * cellSize);
        window.draw(windowRect);
    }
    sf::RectangleShape streamlinedFeature(sf::Vector2f(cellSize, cellSize * 0.1f));
    streamlinedFeature.setFillColor(sf::Color(150, 150, 150));
    streamlinedFeature.setPosition(x * cellSize, (y + 0.9f) * cellSize);
    window.draw(streamlinedFeature);

  }

  /**
   * @brief Prints information about the industrial building to the standard
   * output
   *
   */
  std::string GetType() const override {
    return type_;
  }
};

#endif


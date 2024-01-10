#include "commercial.hpp"

Commercial::Commercial(const std::string& buildingName,
                       const std::pair<int, int>& location,
                       const std::string& type)
    : Building(buildingName, location, type), type_(type) {}

void Commercial::Draw(sf::RenderWindow& window, int cellSize) {
  sf::RectangleShape cellShape(sf::Vector2f(cellSize, cellSize));
  int x = location_.first;
  int y = location_.second;

  if (type_ == "Shop") {
    cellShape.setFillColor(sf::Color(255, 200, 100));
    cellShape.setOutlineColor(sf::Color::Black);
    cellShape.setOutlineThickness(2.0f);
    cellShape.setPosition(x * cellSize, y * cellSize);

    window.draw(cellShape);

    sf::RectangleShape door(sf::Vector2f(cellSize * 0.2f, cellSize * 0.4f));
    door.setFillColor(sf::Color(100, 50, 50));
    door.setPosition((x + 0.4f) * cellSize, (y + 0.6f) * cellSize);
    window.draw(door);

  } else if (type_ == "Gym") {
    cellShape.setFillColor(sf::Color(0, 255, 255));
    cellShape.setPosition(x * cellSize, y * cellSize);

    window.draw(cellShape);

    sf::RectangleShape door(sf::Vector2f(cellSize * 0.2f, cellSize * 0.4f));
    door.setFillColor(sf::Color(100, 50, 50));
    door.setPosition((x + 0.4f) * cellSize, (y + 0.6f) * cellSize);
    window.draw(door);

  } else if (type_ == "Restaurant") {
    cellShape.setFillColor(sf::Color(200, 100, 100));
    cellShape.setOutlineColor(sf::Color::Black);
    cellShape.setOutlineThickness(2.0f);
    cellShape.setPosition(x * cellSize, y * cellSize);

    window.draw(cellShape);

    sf::RectangleShape door(sf::Vector2f(cellSize * 0.2f, cellSize * 0.4f));
    door.setFillColor(sf::Color(100, 50, 50));
    door.setPosition((x + 0.4f) * cellSize, (y + 0.6f) * cellSize);
    window.draw(door);
  }
}

std::string Commercial::GetType() const {
  std::string lowertype = type_;
  // Compare two strings in a case-insensitive manner again
  std::transform(lowertype.begin(), lowertype.end(), lowertype.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  if (lowertype == "gym") {
    return "Gym";
  } else if (lowertype == "restaurant") {
    return "Restaurant";
  } else {
    return "Shop";
  }
}

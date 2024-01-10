#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief A class for representing a single cell in the graphical simulation.
 *
 */
class Cell {
 public:
  /**
   * @brief Construct a new Cell object.
   *
   * @param location the coordinates of the cell
   */
  Cell(std::pair<int, int> location);

  /**
   * @brief Returns a boolean value indicating if the cell is occupied or not.
   *
   * @return True if the cell is occupied, false otherwise
   */
  bool IsOccupied() const;

  /**
   * @brief Occupies the cell with an object of the type which is given as a
   * parameter.
   *
   * @param type The type of the object being placed in the cell ("Horizontal
   * road", "Vertical road", "Intersection", "industrial", "residential",
   * "shop", "gym", or "restaurant")
   */
  void Occupy(std::string type);

  /**
   * @brief Empties the cell (i.e. sets the value of the type_ variable to
   * "Empty").
   *
   */
  void Clear();

  /**
   * @brief Get the type of the cell.
   *
   * @return The type of the cell as std::string
   */
  std::string GetType() const;

  /**
   * @brief Get the x-coordinate of the cell.
   *
   * @return The x-coordinate as an integer
   */
  int GetX() const;

  /**
   * @brief Get the y-coordinate of the cell.
   *
   * @return The y-coordinate as an integer
   */
  int GetY() const;

  /**
   * @brief Draws the cell to the SFML window given as a parameter.
   *
   * @param window A reference to the SFML window where the cell should be drawn
   * @param cellSize The size of the cell to be drawn
   * @param x The x-coordinate of the cell to be drawn
   * @param y The y-coordinate of the cell to be drawn
   */
  void Draw(sf::RenderWindow& window, int cellSize, int x, int y);

 private:
  std::string type_;
  std::pair<int, int> location_;
};

#endif
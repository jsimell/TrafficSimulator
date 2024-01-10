#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

#include "car.hpp"
#include "grid.hpp"

/**
 * @brief Class used for visualizing the traffic simulator in a separate GUI
 *
 */
class Visualization {
 public:
  /**
   * @brief Construct a new Visualization object
   *
   * @param cellSize cell size in the GUI
   * @param g pointer to a grid
   */
  Visualization(int cellSize, Grid* g);

  /**
   * @brief Used for returning the Window object
   *
   * @return sf::RenderWindow&
   */
  sf::RenderWindow& GetWindow();

  /**
   * @brief Prints out the current grid
   *
   * @param grid
   */
  void PrintGrid(Grid* grid);

  /**
   * @brief Prints out the current cars
   *
   * @param cars
   */
  void PrintCars(std::vector<Car*> cars);

 private:
  sf::RenderWindow window_;
  int cellSize_;
};

#endif
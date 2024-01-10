#ifndef GRID_H
#define GRID_H

#include <vector>

#include "cell.hpp"

/**
 * @brief A class for storing all the cells of the graphical simulation
 *
 */
class Grid {
 public:
  /**
   * @brief Construct a new Grid object.
   *
   * @param xSize The vertical size of the grid
   * @param ySize The horizontal size of the grid
   */
  Grid(int xSize, int ySize);

  /**
   * @brief Destroy the Grid object.
   *
   */
  ~Grid();

  /**
   * @brief Get a pointer to the cell at the given location.
   *
   * @param x The x-coordinate of the cell
   * @param y The y-coordinate of the cell
   * @return A pointer to a Cell object if there is one in the given location, a
   * nullptr otherwise
   */
  Cell* GetCell(int x, int y);

  /**
   * @brief Get the neighbouring cells of the cell in the given location.
   *
   * @param x The x-coordinate of the cell
   * @param y The y-coordinate of the cell
   * @return A vector containing pointers to all the neighbouring cells
   */
  std::vector<Cell*> GetNeighborCells(int x, int y);

  /**
   * @brief Get the vertical size of the grid.
   *
   * @return The vertical size of the grid as an integer
   */
  int GetSizeX() const;

  /**
   * @brief Get the horizontal size of the grid.
   *
   * @return The horizontal size of the grid as an integer
   */
  int GetSizeY() const;

 private:
  int xSize_;
  int ySize_;
  std::vector<std::vector<Cell*>> cells_;
};

#endif

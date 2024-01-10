#include "grid.hpp"

Grid::Grid(int xSize, int ySize) {
  xSize_ = xSize;
  ySize_ = ySize;

  for (int i = 0; i < xSize; i++) {
    std::vector<Cell*> column;
    for (int j = 0; j < ySize; j++) {
      column.push_back(new Cell({i, j}));
    }
    cells_.push_back(column);
  }
}

Grid::~Grid() {
  for (int i = 0; i < xSize_; i++) {
    for (int j = 0; j < ySize_; j++) {
      delete (cells_[i][j]);
    }
  }
}

int Grid::GetSizeX() const { return xSize_; }

int Grid::GetSizeY() const { return ySize_; }

Cell* Grid::GetCell(int x, int y) {
  if (x < xSize_ && y < ySize_) {
    return cells_[x][y];
  }
  return nullptr;
}

std::vector<Cell*> Grid::GetNeighborCells(int x, int y) {
  std::vector<Cell*> result;

  if (y - 1 >= 0) {
    result.push_back(GetCell(x, y - 1));
  }

  if (y + 1 < GetSizeY()) {
    result.push_back(GetCell(x, y + 1));
  }

  if (x - 1 >= 0) {
    result.push_back(GetCell(x - 1, y));
  }

  if (x + 1 < GetSizeX()) {
    result.push_back(GetCell(x + 1, y));
  }

  return result;
}

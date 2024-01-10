#include "visualization.hpp"

Visualization::Visualization(int cellSize, Grid* g)
    : window_(
          sf::VideoMode(g->GetSizeX() / 2.0 * 100, g->GetSizeY() / 2.0 * 100),
          "Traffic Simulation"),
      cellSize_(cellSize) {
  // Set up the view to match the logical size of the content
  sf::View view(sf::FloatRect(0, 0, g->GetSizeX() / 2.0 * 100,
                              g->GetSizeY() / 2.0 * 100));
  window_.setView(view);
}

sf::RenderWindow& Visualization::GetWindow() { return window_; }

void Visualization::PrintGrid(Grid* grid) {
  for (int i = 0; i < grid->GetSizeX(); i++) {
    for (int j = 0; j < grid->GetSizeY(); j++) {
      grid->GetCell(i, j)->Draw(window_, cellSize_, i, j);
    }
  }
}

void Visualization::PrintCars(std::vector<Car*> cars) {
  for (auto car : cars) {
    car->Draw(window_, cellSize_);
  }
}
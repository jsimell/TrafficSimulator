#include "analysis.hpp"

Analysis::Analysis(City* city, SimulationClock* clock)
    : currentRoad_(nullptr), city_(city), clock_(clock) {}

void Analysis::Init() {
  auto cars = city_->GetCars();

  for (size_t i = 0; i < cars.size(); ++i) {
    previousCars_.insert({i, false});
  }
}

void Analysis::Analyze() {
  if (currentRoad_ != nullptr) {
    // Acquire the cars in the city
    auto cars = city_->GetCars();

    // Acquire the start/end coordinates of the road
    auto roadStart = currentRoad_->GetStart();
    auto roadEnd = currentRoad_->GetEnd();

    // Acquire the current hour for hourly statistics
    int currentHour = static_cast<int>(clock_->GetElapsedTime()) / 60 - (24 * clock_->GetDayNumber());

    // Initialization of roadHourlyCounts_: this should be ran only once at
    // start
    if (roadHourlyCounts_.empty()) {
      roadHourlyCounts_.resize(30, std::vector<int>(24));
    }

    // Initialization of a specific hour: if it doesn't exist, make it equal 0
    if (!roadHourlyCounts_[clock_->GetDayNumber()][currentHour]) {
      roadHourlyCounts_[clock_->GetDayNumber()][currentHour] = 0;
    }

    for (size_t i = 0; i < cars.size(); ++i) {
      auto car = cars[i];
      auto location = car->GetLocation();

      // checks if the car is on this horizontal road
      if (currentRoad_->IsHorizontal() &&
          (car->GetDirection() == "Right" || car->GetDirection() == "Left")) {
        if (location.first >= roadStart.first &&
            location.first <= roadEnd.first &&
            location.second == roadStart.second) {
          if (!previousCars_[i]) {
            roadHourlyCounts_[clock_->GetDayNumber()][currentHour]++;
            previousCars_[i] = true;
          }
        }
        // checks if the car is on this vertical road
      } else if (currentRoad_->IsVertical() &&
                 (car->GetDirection() == "Up" ||
                  car->GetDirection() == "Down")) {
        if (location.second >= roadStart.second &&
            location.second <= roadEnd.second &&
            location.first == roadStart.first) {
          if (!previousCars_[i]) {
            roadHourlyCounts_[clock_->GetDayNumber()][currentHour]++;
            previousCars_[i] = true;
          }
        }
      }

      if (currentRoad_->IsHorizontal() && (previousCars_[i])) {
        if (location.second != roadStart.second ||
            location.first < roadStart.first ||
            location.first > roadEnd.first) {
          previousCars_[i] = false;
        }
      } else if (currentRoad_->IsVertical() && (previousCars_[i])) {
        if (location.first != roadStart.first ||
            location.second < roadStart.second ||
            location.second > roadEnd.second) {
          previousCars_[i] = false;
        }
      }
    }
  }
}

void Analysis::SpecifyRoad(int roadIndex) {
  currentRoad_ = city_->GetRoads()[roadIndex];
}

void Analysis::GenerateHourlyHistogram(std::vector<std::vector<int>> data) {
  int max_value = *max_element(data[clock_->GetDayNumber()].begin(),
                               data[clock_->GetDayNumber()].end());

  for (int i = max_value; i >= 0; --i) {
    std::cout.width(2);
    std::cout << i << " | ";

    for (unsigned int j = 0; j < data[clock_->GetDayNumber()].size(); ++j) {
      if (data[clock_->GetDayNumber()][j] >= i) {
        std::cout << "x  ";
      } else {
        std::cout << "   ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << "----------------------------------------------------------------------------" << std::endl;
  std::cout << "    ";

  for (unsigned int i = 0; i < data[clock_->GetDayNumber()].size(); ++i) {
    if (i < 10) {
      std::cout << "0" << i << " ";
    } else {
      std::cout << i << " ";
    }
  }

  std::cout << std::endl;
}

std::vector<std::vector<int>> Analysis::GetData() { return roadHourlyCounts_; }

void Analysis::ExportToCSV(const std::string& filename) {
  std::ofstream csvFile(filename);

  if (!csvFile.is_open()) {
    std::cerr << "Error: Unable to open file " << filename << std::endl;
    return;
  }

  // Write header
  csvFile << "Day,Hour,CarCount" << std::endl;

  // Write data
  for (int day = 0; day < clock_->GetDayNumber() + 1; ++day) {
    for (unsigned int hour = 0; hour < roadHourlyCounts_[day].size(); ++hour) {
      csvFile << day << "," << hour << "," << roadHourlyCounts_[day][hour] << std::endl;
    }
  }

  std::cout << "Exported to root folder!" << std::endl;

  csvFile.close();
}
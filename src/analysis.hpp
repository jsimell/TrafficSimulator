#ifndef ANALYSIS_HPP
#define ANALYSIS_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "city.hpp"
#include "simulationClock.hpp"

/**
 * @brief Class used for analyzing the traffic data
 * provided by the simulator.
 */
class Analysis {
 public:
  /**
   * @brief Construct a new Analysis object
   *
   * @param city Pointer to the main city object
   * @param clock Pointer to the main clock object
   */
  Analysis(City* city, SimulationClock* clock);

  /**
   * @brief The main function of this class, which is used to obtain the
   * analysis data
   */
  void Analyze();

  /**
   * @brief Specifies the road that is going to be analyzed
   *
   * @param roadIndex Index of the road that is going to be analyzed
   */
  void SpecifyRoad(int roadIndex);

  /**
   * @brief Prints out a histogram of the current day with hourly statistics of
   * road usage
   *
   * @param data Road usage data that is provided by the GetData function in
   * this class
   */
  void GenerateHourlyHistogram(std::vector<std::vector<int>> data);

  /**
   * @brief Exports the analysis data into a CSV file in the root folder of the
   * project
   *
   * @param data Road usage data that is provided by the GetData function in
   * this class
   */
  void ExportToCSV(const std::string& filename);

  /**
   * @brief Returns the hourly road data
   *
   * @return The hourly road data
   */
  std::vector<std::vector<int>> GetData();

  /**
   * @brief Initializes the previousCars_ private variable
   */
  void Init();

 private:
  // Current road that is being analyzed
  Road* currentRoad_;

  // first element tells the day, second element tells the hour
  std::vector<std::vector<int>> roadHourlyCounts_;

  City* city_;
  SimulationClock* clock_;
  std::map<int, bool> previousCars_;
};

#endif  // ANALYSIS_HPP
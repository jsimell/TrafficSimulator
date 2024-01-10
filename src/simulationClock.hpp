#ifndef CLOCK_HPP
#define CLOCK_HPP

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

/**
 * @brief Class used for time management in the simulation.
 * Includes a clock that runs with regard to system time.
 * One second in real life equals one minute in simulation time.
 */
class SimulationClock {
 public:
  /**
   * @brief Construct a new Simulation Clock object
   */
  SimulationClock();

  /**
   * @brief Function that starts the clock
   */
  void Start();

  /**
   * @brief Returns the elapsed time in simulation
   *
   * @return A double value that represents the elapsed time in seconds
   */
  double GetElapsedTime();

  /**
   * @brief Returns the day number of the simulation
   *
   * @return An integer value that represents the day number
   */
  int GetDayNumber();

  /**
   * @brief Returns the simulation's time (1 second in real life = 1 minute in
   * simulation time)
   *
   * @return A string value that contains the time in "xx:xx" form
   */
  std::string GetSimulationTime();

  /**
   * @brief Set the Simulation Speed object
   *
   * @param simulationSpeed
   */
  void SetSimulationSpeed(int simulationSpeed) {
    simulationSpeed_ = simulationSpeed;
  }

 private:
  std::chrono::time_point<std::chrono::high_resolution_clock> startTime_;
  int dayNumber_;
  int simulationSpeed_;
};

#endif  // CLOCK_HPP
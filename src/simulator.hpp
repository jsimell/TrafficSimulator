#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <iterator>
#include <thread>
#include <vector>

#include "../libs/cpp-json/json.h"
#include "analysis.hpp"
#include "car.hpp"
#include "city.hpp"
#include "simulationClock.hpp"
#include "visualization.hpp"

/**
 * @brief Class that handles the crucial parts of simulation.
 * This class includes the main threads that the user uses to control
 * the simulation. The simulation is initialized/finished in this class.
 *
 */
class Simulator {
 public:
  /**
   * @brief Construct a new Simulator object
   *
   */
  Simulator();

  /**
   * @brief Destroy the Simulator object
   *
   */
  ~Simulator();

  /**
   * @brief Starts and initializes the simulation
   *
   */
  void StartSimulation();

  /**
   * @brief The simulator's main thread that is used to run the simulation
   *
   */
  void SimulatorThread();

  /**
   * @brief Updates the simulation with regard to time changes
   *
   * @param deltaTime tells how much time has passed in the main loop
   * @param currentTime tells what is the current system time
   */
  void UpdateSimulation(float deltaTime, float currentTime);

  /**
   * @brief Draws the simulation if the GUI is enabled
   *
   * @param gui graphical user interface used in visualization
   */
  void DrawSimulation(Visualization* gui);

  /**
   * @brief Loads the city from a .json file
   *
   * @return City*
   */
  City* LoadCity();

  /**
   * @brief Thread that is used for user input via terminal
   *
   * @param exitFuture information about the thread status (exit or not)
   */
  void InputThread(std::shared_future<void> exitFuture);

  /**
   * @brief Set the City object
   *
   * @param c city that is set
   */
  void SetCity(City* c) { c_ = c; }

 private:
  bool guiEnabled_;
  bool endSimulation_;
  int simulationSpeed_;  // 1x, 2x, 4x, etc.

  City* c_;
  SimulationClock* clock_;
  Analysis* analysis_;

  std::promise<void> exitSignal;  // Declare exitSignal as a member variable
};

#endif
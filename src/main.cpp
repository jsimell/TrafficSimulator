/**
 * @mainpage
 *
 * @section Introduction
 * This program can be used to simulate and analyze the traffic of a city model
 * inputted as a JSON file. The JSON file should be placed in the src/ folder of
 * the program. The JSON format and more instructions on how this program should
 * be used can be found in the README file located in the root folder of the
 * project.
 *
 */

#include <iostream>

#include "city.hpp"
#include "simulator.hpp"

int main() {
  Simulator simulator;
  simulator.StartSimulation();
  simulator.SimulatorThread();
  return 0;
}

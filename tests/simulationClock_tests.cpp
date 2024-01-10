#include "../src/simulationClock.hpp"
#include <chrono>
#include <cassert>
#include <thread>
#include "test_functions.hpp"

void TestSimulationClockInitialization() {
    SimulationClock clock;

    // Default Constructor
    assert(clock.GetDayNumber() == 0);
    assert(clock.GetSimulationTime() == "00:00");

    // Start and Elapsed Time
    clock.Start();
    // Sleep for a short time to simulate elapsed time
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    double elapsedTime = clock.GetElapsedTime();
    assert(elapsedTime > 0.0);

    std::cout << "All simulation clock initalization tests passed!" << std::endl;
}

void TestSimulationClockTimeConversion() {
    SimulationClock clock;

    // Get Simulation Time
    clock.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::string simulationTime = clock.GetSimulationTime();
    assert(simulationTime.size() == 5);
    // Check if the time is in the correct format (e.g., "00:00")
    assert(simulationTime[2] == ':');
    assert(std::isdigit(simulationTime[0]));
    assert(std::isdigit(simulationTime[1]));
    assert(std::isdigit(simulationTime[3]));
    assert(std::isdigit(simulationTime[4]));

    std::cout << "All simulation clock conversion tests passed!" << std::endl;
}
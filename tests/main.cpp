#include <iostream>
#include <SFML/Graphics.hpp>

#include "test_functions.hpp"

int main() {
    TestBuilding();
    TestIntersection();
    TestCar();
    TestSimulationClockInitialization();
    TestSimulationClockTimeConversion();
    TestTrafficLight();

    std::cout << "All tests finished." << std::endl;
    return 0;
}

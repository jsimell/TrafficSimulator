#include <cassert>
#include <iostream>

#include "test_functions.hpp"

void TestTrafficLight() {
    // Test case 1: Verify the initial state of the traffic light
    TrafficLight trafficLight({1, 2}, 10, 5);
    assert(trafficLight.GetLocation() == std::make_pair(1, 2));
    assert(trafficLight.GetGreenDuration() != 15);
    assert(trafficLight.GetRedDuration() == 10);
    assert(trafficLight.GetYellowDuration() == 5);
    assert(trafficLight.GetStatus() == "green");

    // Test case 2: Switch the traffic light to red and verify its state
    trafficLight.TurnRed();
    assert(trafficLight.GetStatus() == "red");

    // Test case 3: Switch the traffic light to yellow and verify its state
    trafficLight.TurnYellow();
    assert(trafficLight.GetStatus() == "yellow");

    // Test case 4: Switch the traffic light to green and verify its state
    trafficLight.TurnGreen();
    assert(trafficLight.GetStatus() == "green");

    std::cout << "All TrafficLight tests passed!" << std::endl;

    return;
}
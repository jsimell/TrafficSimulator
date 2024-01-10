#include <cassert>
#include <iostream>

#include "test_functions.hpp"

void TestIntersection() {
  // Test 1: Constructor and GetLocation method
  {
    Intersection intersection({1, 2});
    auto location = intersection.GetLocation();
    assert(location.first == 1);
    assert(location.second == 2);
  }

  // Test 2: AddTrafficLight and HasTrafficLight methods
  {
    Intersection intersection({1, 2});
    assert(!intersection.HasTrafficLight());  // No traffic light initially

    TrafficLight trafficlight({1, 2}, 10, 2);
    intersection.AddTrafficLight(&trafficlight);

    assert(intersection.HasTrafficLight());  // Traffic light added
  }

  // Test 3: AllowVertical and AllowHorizontal methods
  {
    Intersection intersection({1, 2});
    // Initially allows vertical movement
    assert(intersection.AllowVertical());
    // Initially allows horizontal movement
    assert(intersection.AllowHorizontal());

    intersection.AddTrafficLight(nullptr);  // No traffic light

    // Should still allow vertical movement
    assert(intersection.AllowVertical());
    // Should still allow horizontal movement
    assert(intersection.AllowHorizontal());
  }

  // Test 4: Update method (No traffic light)
  {
    Intersection intersection({1, 2});
    intersection.Update(5.0);  // Simulate 5 seconds elapsed time

    // No traffic light, movement permissions should not change
    assert(intersection.AllowVertical());
    assert(intersection.AllowHorizontal());
  }

  // Test 5: Update method (With traffic light)
  {
    Intersection intersection({1, 2});
    TrafficLight trafficlight({1, 2}, 10, 2);
    intersection.AddTrafficLight(&trafficlight);

    // Initially AllowVertical should return false and AllowHorizontal true.
    // After 12 or more seconds, the opposite.
    assert(!intersection.AllowVertical());
    assert(intersection.AllowHorizontal());
  }

  std::cout << "All intersection tests passed!" << std::endl;

  return;
}
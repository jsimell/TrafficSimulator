#include <cassert>
#include <iostream>

#include "test_functions.hpp"

void TestBuilding() { // for industrial, residential and commercial

    // Test 1: Create a building and check its basic properties:
    const std::string buildingName = "TestBuilding";
    const std::pair<int, int> location = {0, 0};
    const std::string type1 = "Shop";
    const std::string type2 = "Restaurant";
    const std::string type3 = "Gym";
    Residential* building1 = new Residential(buildingName, location);
    Industrial* building2 = new Industrial(buildingName, location);
    Commercial* building3 = new Commercial(buildingName, location, type1);
    Commercial* building4 = new Commercial(buildingName, location, type2);
    Commercial* building5 = new Commercial(buildingName, location, type3);

    assert(building1->GetName() == buildingName);
    assert(building1->GetLocation() == location);
    assert(building1->GetType() == "Residential");

    assert(building2->GetName() == buildingName);
    assert(building2->GetLocation() == location);
    assert(building2->GetType() == "Industrial");

    assert(building3->GetName() == buildingName);
    assert(building3->GetLocation() == location);
    assert(building3->GetType() == type1);

    assert(building4->GetName() == buildingName);
    assert(building4->GetLocation() == location);
    assert(building4->GetType() == type2);

    assert(building5->GetName() == buildingName);
    assert(building5->GetLocation() == location);
    assert(building5->GetType() == type3);


    delete(building1);
    delete(building2);
    delete(building3);
    delete(building4);
    delete(building5);

    std::cout << "All building tests passed!" << std::endl;
}

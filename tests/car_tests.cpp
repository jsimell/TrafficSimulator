#include <cassert>
#include <iostream>


#include "test_functions.hpp"


void TestCar() {

    //Add two nodes and one road
    Node* n1 = new Node(NodeType::Building, {0, 0});
    Node* n2 = new Node(NodeType::Building, {0, 4});
    Road* r1 = new Road({0, 0}, {0, 4}, 1);
    
    //Initialize variables
    std::vector<Node*> allNodes;
    allNodes.push_back(n1);
    allNodes.push_back(n2);
    n1->AddConnection(n2, 4);
    n2->AddConnection(n1, 4);
    std::vector<Intersection*> intersections;
    std::vector<Road*> roads;
    roads.push_back(r1);
    std::vector<Car*> cars;
    
    //Create car
    Car* c = new Car(n1);

    c->AddEvent(1, n2);

    c->Update(0.0001, 1.0, allNodes, intersections, cars, roads);

    //See if the car has correct direction
    assert(c->GetDirection() == "Down");

   //Update the car a few times
   for(int i = 0;i < 1000; i++){
    c->Update(0.1, 2.0, allNodes, intersections, cars, roads);
   }
    
    //Destination coordinates
    float i = 0;
    float j = 4;
    
    //Check if car has reached its destination
    assert(c->GetLocation() == std::make_pair(i, j));

    std::cout << "All car tests passed!" << std::endl;

    delete(n1);
    delete(n2);
    delete(c);
    delete(r1);

    return;
}
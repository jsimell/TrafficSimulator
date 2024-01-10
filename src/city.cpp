#include "city.hpp"

#include <iostream>

City::City(int sizeX, int sizeY) { grid_ = new Grid(sizeX, sizeY); }

City::~City() {
  for (auto it : roads_) {
    delete (it);
  }

  for (auto it : buildings_) {
    delete (it);
  }

  for (auto it : trafficLights_) {
    delete (it);
  }

  for (auto it : intersections_) {
    delete (it);
  }

  for (auto it : nodes_) {
    delete (it);
  }

  for (auto it : personCarMap_) {
    delete (it.first);
    delete (it.second);
  }

  delete(clock_);

  delete (grid_);
}

bool City::IsValidRoad(std::pair<int, int> start,
                       std::pair<int, int> end) const {
  // Check that the length of the road is not zero
  if (start == end) {
    return false;
  }

  // Check that road is not diagonal (only vertical or horizontal roads allowed)
  if ((start.first != end.first) && (start.second != end.second)) {
    return false;
  }

  // Check that road is inside the grid coordinates
  if ((start.first < 0) || (start.second < 0) || (end.first < 0) ||
      (end.second < 0)) {
    return false;
  }

  int xMax = grid_->GetSizeX();
  int yMax = grid_->GetSizeY();

  if ((start.first >= xMax) || (end.second >= yMax) || (end.first >= xMax) ||
      (end.second >= yMax)) {
    return false;
  }

  if (start.first == end.first) {  // vertical

    // Check that there are no buildings or other roads between the start and
    // end coordinates

    if (end.second > start.second) {
      for (int j = start.second + 1; j <= end.second - 1; j++) {
        if (grid_->GetCell(start.first, j)->IsOccupied()) {
          return false;
        }
      }
    } else {
      for (int j = end.second + 1; j <= start.second - 1; j++) {
        if (grid_->GetCell(end.first, j)->IsOccupied()) {
          return false;
        }
      }
    }

  } else {  // Horizontal

    // Check that there are no buildings or other roads between the start and
    // end coordinates
    if (start.first > end.first) {
      for (int i = end.first + 1; i <= start.first - 1; i++) {
        if (grid_->GetCell(i, start.second)->IsOccupied()) {
          return false;
        }
      }
    } else {
      for (int i = end.first + 1; i <= start.first - 1; i++) {
        if (grid_->GetCell(start.second, i)->IsOccupied()) {
          return false;
        }
      }
    }
  }

  return true;
}

void City::AddRoad(std::pair<int, int> start, std::pair<int, int> end) {
  // Check that the road is valid and that it connects two nodes.
  // If not, thwrow an InvalidCityException
  if (IsValidRoad(start, end) && GetNode(start) != nullptr &&
      GetNode(end) != nullptr) {
    auto node1 = GetNode(start);
    auto node2 = GetNode(end);
    roads_.push_back(new Road(start, end, 1));

    // Occupy the cells with the new road
    if (start.first == end.first) {  // vertical

      node1->AddConnection(node2, abs(start.second - end.second));
      node2->AddConnection(node1, abs(start.second - end.second));

      if (start.second < end.second) {
        for (int j = start.second + 1; j <= end.second - 1; j++) {
          grid_->GetCell(start.first, j)->Occupy("Vertical Road");
        }
      } else {
        for (int j = end.second + 1; j <= start.second - 1; j++) {
          grid_->GetCell(start.first, j)->Occupy("Vertical Road");
        }
      }

    } else {  // Horizontal

      node1->AddConnection(node2, abs(start.first - end.first));
      node2->AddConnection(node1, abs(start.first - end.first));

      if (start.first < end.first) {
        for (int i = start.first + 1; i <= end.first - 1; i++) {
          grid_->GetCell(i, start.second)->Occupy("Horizontal Road");
        }
      } else {
        for (int i = end.first + 1; i <= start.first - 1; i++) {
          grid_->GetCell(i, start.second)->Occupy("Horizontal Road");
        }
      }
    }
  } else {
    std::string startX = std::to_string(start.first);
    std::string startY = std::to_string(start.second);
    std::string endX = std::to_string(end.first);
    std::string endY = std::to_string(end.second);
    throw InvalidCityException(("road starting from {" + startX + ", " +
                                startY + "} and ending to {" + endX + ", " +
                                endY + "} is invalid"));
  }
}

bool City::IsValidBuilding(Building* b) const {
  if (b->GetLocation().first < 0 || b->GetLocation().second < 0) {
    return false;
  }

  if (b->GetLocation().first >= grid_->GetSizeX() ||
      b->GetLocation().second >= grid_->GetSizeY()) {
    return false;
  }

  if (grid_->GetCell(b->GetLocation().first, b->GetLocation().second)
          ->IsOccupied()) {
    return false;
  }
  auto it = std::find_if(buildings_.begin(), buildings_.end(),
                         [b](const Building* building) {
                           return building->GetName() == b->GetName();
                         });
  return it == buildings_.end();  // returns true if there's no building with
                                  // name b->GetName()
}

void City::AddBuilding(std::string name, std::pair<int, int> location,
                       const std::string& buildingType) {
  Building* b = nullptr;
  std::string lowertype = buildingType;
  // Compare two strings in a case-insensitive manner
  std::transform(lowertype.begin(), lowertype.end(), lowertype.begin(),
                 [](unsigned char c) { return std::tolower(c); });

  // Check the building type and create the corresponding building
  if (lowertype == "industrial") {
    b = new Industrial(name, location);
  } else if (lowertype == "residential") {
    b = new Residential(name, location);
  } else if (lowertype == "shop" || lowertype == "gym" ||
             lowertype == "restaurant") {
    b = new Commercial(name, location, buildingType);
  } else {
    throw InvalidCityException("building type " + lowertype + " is unknown");
  }

  // Check that the cell is not occupied or out of bounds
  if (!IsValidBuilding(b)) {
    delete (b);
    throw InvalidCityException("invalid building location at: {" +
                               std::to_string(location.first) + ", " +
                               std::to_string(location.second) + "}");
  } else {
    buildings_.push_back(b);
    nodes_.push_back(new Node(NodeType::Building, location));
    grid_->GetCell(b->GetLocation().first, b->GetLocation().second)
        ->Occupy(lowertype);
  }
}

Node* City::GetNode(std::pair<int, int> location) const {
  for (auto node : nodes_) {
    if (node->GetLocation() == location) {
      return node;
    }
  }
  return nullptr;
}

std::vector<Node*> City::GetBuildingNodes() const {
  std::vector<Node*> buildingNodes;
  for (auto node : nodes_) {
    if (node->GetType() == NodeType::Building) {
      buildingNodes.push_back(node);
    }
  }
  return buildingNodes;
}

void City::AddPersonAndCar(std::string& name, PersonType personType,
                           std::string& workplacename, std::string& homename) {
  Building* workplace = nullptr;
  Building* home = nullptr;
  auto it1 = std::find_if(buildings_.begin(), buildings_.end(),
          [&workplacename](const Building* building) {
          return building->GetName() == workplacename;});
  if (it1 != buildings_.end()) {
    workplace = *it1;
  }
  auto it2 = std::find_if(buildings_.begin(), buildings_.end(),
              [&homename](const Building* building) {
            return building->GetName() == homename;});
  if (it2 != buildings_.end()) {
    home = *it2;
  }

  std::unique_ptr<Industrial> ind;
  std::unique_ptr<Residential> res;

  if (workplace != nullptr && home != nullptr) {
    ind = std::make_unique<Industrial>(workplace->GetName(), workplace->GetLocation());
    res = std::make_unique<Residential>(home->GetName(), home->GetLocation());
  } else {
    throw InvalidCityException(
        "Invalid person: " + name +
        "! Check that the person's home and working place exist.");
  }

  Person* p = new Person(name, personType, ind.get(), res.get());

  if (!IsValidPerson(p)) {
    delete p;
    throw InvalidCityException(
        "Invalid person: " + name +
        "! Check that the person's home and working place exist.");
  } else {
    Event schedule(p, this->GetBuildingNodes());
    auto i = schedule.CreateSchedule();
    Car* car_ = new Car(GetNode(
        p->GetLocation()));  // creates a car for a person starting from home.
    car_->SetColor(p->GetPersonType());
    p->BuyCar(car_);
    p->InitializeSchedule(i);
    personCarMap_[p] = p->GetCar();
  }
}

bool City::IsValidPerson(Person* p) {
  // Goes through buildings and checks that these buildings exist before
  // creating person with these. Also checks that they are correct type. Person
  // cannot live in industrial building. Also for simulation purpose, cannot
  // work in home.
  auto i = p->GetResidence()->GetLocation();
  auto it = std::find_if(buildings_.begin(), buildings_.end(),
                         [i](Building* building) {
                           return ((building->GetLocation() == i) &&
                                   (building->GetType() == "Residential"));
                         });

  auto j = p->GetWorkplace()->GetLocation();
  auto jt = std::find_if(buildings_.begin(), buildings_.end(),
                         [j](Building* building) {
                           return ((building->GetLocation() == j) &&
                                   (building->GetType() == "Industrial"));
                         });
  if (it != buildings_.end() && jt != buildings_.end()) {
    return true;
  } else {
    return false;
  }
}

bool City::IsValidIntersection(Intersection* i) const {
  if (i->GetLocation().first < 0 || i->GetLocation().second < 0) {
    return false;
  }

  if (i->GetLocation().first >= grid_->GetSizeX() ||
      i->GetLocation().second >= grid_->GetSizeY()) {
    return false;
  }

  if (grid_->GetCell(i->GetLocation().first, i->GetLocation().second)
          ->IsOccupied()) {
    return false;
  }

  return true;
}

void City::AddIntersection(std::pair<int, int> location) {
  Intersection* i = new Intersection(location);
  if (IsValidIntersection(i)) {
    intersections_.push_back(i);
    nodes_.push_back(new Node(NodeType::Intersection, location));
    grid_->GetCell(location.first, location.second)->Occupy("Intersection");
  } else {
    delete (i);
    throw InvalidCityException("invalid intersection location at: {" +
                               std::to_string(location.first) + ", " +
                               std::to_string(location.second) + "}");
  }
}

Intersection* City::GetIntersection(std::pair<int, int> location) const {
  for (auto it : intersections_) {
    if (it->GetLocation() == location) {
      return it;
    }
  }
  return nullptr;
}

void City::UpdateIntersections(float deltaTime) const {
  for (auto it : intersections_) {
    it->Update(deltaTime);
  }
}

void City::DrawIntersections(sf::RenderWindow& window) const {
  for (auto it : intersections_) {
    it->Draw(window, 50, grid_);
  }
}

void City::AddTrafficLight(std::pair<int, int> location,
                           int redAndGreenDuration, int yellowDuration) {
  TrafficLight* t =
      new TrafficLight(location, redAndGreenDuration, yellowDuration);
  auto intersection = GetIntersection(t->GetLocation());
  if (intersection != nullptr) {
    trafficLights_.push_back(t);
    intersection->AddTrafficLight(t);
  } else {
    delete t;
    throw InvalidCityException("invalid traffic light location at: {" +
                               std::to_string(location.first) + ", " +
                               std::to_string(location.second) +
                               "}, no intersection in the given location");
  }
}

// Update location of person and its car.
void City::UpdateCars(float deltaTime, float currentTime) {
  // Extract cars from personCarMap_
  std::vector<Car*> allCars;
  for (const auto& personCar : personCarMap_) {
    allCars.push_back(personCar.second);
  }

  // Update each car
  for (const auto& personCar : personCarMap_) {
    AddEvent(personCar.first);
    personCar.second->Update(deltaTime, currentTime, nodes_, intersections_,
                             allCars, roads_);
    personCar.first->UpdateLocationFromCar(personCar.second->GetLocation());
  }
}

void City::DrawCars(sf::RenderWindow& window) const {
  for (const auto& personCar : personCarMap_) {
    personCar.second->Draw(window, 50);
  }
}

void City::ChooseRoad(int roadIndex){
  Road* road = roads_[roadIndex];

  auto s = road->GetStart();
  auto e = road->GetEnd();

  if(road->IsHorizontal()){
    if(e.first > s.first){
      for(int i = s.first; i < e.first; i++){
        grid_->GetCell(i , s.second)->Occupy("Horizontal Road Selected");
      }
    }else{
      for(int i = e.first; i < s.first; i++){
        grid_->GetCell(i , s.second)->Occupy("Horizontal Road Selected");
      }
    }
  }else{
    if(e.second > s.second){
      for(int j = s.second; j < e.second; j++){
        grid_->GetCell(s.first , j)->Occupy("Vertical Road Selected");
      }
    }else{
      for(int j = e.second; j < s.second; j++){
        grid_->GetCell(s.first , j)->Occupy("Vertical Road Selected");
      }
    }
  }
}

void City::DrawBuildings(sf::RenderWindow& window) const {
  for (const auto building : buildings_) {
    building->Draw(window, 50);
  }
}

void City::PrintCity(sf::RenderWindow& window) const {
  const int cellSize = 50;
  for (int i = 0; i < grid_->GetSizeX(); i++) {
    for (int j = 0; j < grid_->GetSizeY(); j++) {
      grid_->GetCell(i, j)->Draw(window, cellSize, i, j);
    }
  }
}

Grid* City::GetGrid() const { return grid_; }

std::vector<Road*> City::GetRoads() const { return roads_; }

std::vector<Car*> City::GetCars() const {
  std::vector<Car*> cars;
  for (const auto& personCar : personCarMap_) {
    cars.push_back(personCar.second);
  }
  return cars;
}

int City::TimeUntilNextEvent(Person* p) const {  // uusi
  int currentTime = round(clock_->GetElapsedTime());
  auto schedule = p->GetSchedule();
  auto it = schedule.upper_bound(currentTime);

  if (it != schedule.end()) {
    // Next key that is greater than the current time
    int nextEventTime = it->first;
    return nextEventTime - currentTime;
  } else {
    return -1;  // If no future events
  }
}

// If there's enough time, person will return home to take a rest.
bool City::IsBusy(Person* p) const {
  return (this->TimeUntilNextEvent(p) < 40 ||
          this->TimeUntilNextEvent(p) == -1);
}

// Add clock from simulator.cpp
void City::AddClock(SimulationClock* clock) { clock_ = clock; }

// Add event to schedule
void City::AddEvent(Person* p) {
  if (!IsBusy(p) && !(p->isAtHome()) &&
      (p->GetWorkplace()->GetLocation() != p->GetLocation())) {
    p->AddEvent(clock_->GetElapsedTime(),
                GetNode(p->GetResidence()->GetLocation()));
  }
}

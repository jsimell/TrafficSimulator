#ifndef CITY_H
#define CITY_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

#include "building.hpp"
#include "car.hpp"
#include "cell.hpp"
#include "commercial.hpp"
#include "event.hpp"
#include "grid.hpp"
#include "industrial.hpp"
#include "intersection.hpp"
#include "invalidcityexception.hpp"
#include "node.hpp"
#include "person.hpp"
#include "residential.hpp"
#include "road.hpp"
#include "trafficlight.hpp"

/**
 * @brief A class used for keeping track of the different elements (e.g
 * buildings, roads, intersectons, etc.) in the simulated city.
 */
class City {
 public:
  /**
   * @brief Construct a new City object
   *
   * @param sizeX The vertical size of the city
   * @param sizeY The horizontal size of the city
   */
  City(int sizeX, int sizeY);

  /**
   * @brief Destroy the City object
   *
   */
  ~City();

  /**
   * @brief
   * Checks if the road with the given start and end coordinates is a valid
   * road. Requirements:
   * - the road must be inside the boundaries of the city
   * - the length of the road must be more than zero
   * - the road can only be horizontal or vertical (not diagonal)
   * - there cannot be any other roads or buildings between the start and end
   *   coordinates of the road
   *
   * @param start The start coordinates of the road
   * @param end The end coordinates of the road
   * @return true if the road is valid, false otherwise
   */
  bool IsValidRoad(std::pair<int, int> start, std::pair<int, int> end) const;

  /**
   * @brief
   * Adds a road to the city.
   * Throws an InvalidCityException if the road is invalid.
   *
   * @param start The start coordinates of the road
   * @param end The end coordinates of the road
   */
  void AddRoad(std::pair<int, int> start, std::pair<int, int> end);

  /**
   * @brief
   * Checks if the building that the pointer given as parameter is pointing to
   * is valid. The building must be inside city boundaries and the
   * location of the building must be unoccupied.
   *
   * @param b A pointer to a building object
   * @return true if the building is valid, false otherwise
   */
  bool IsValidBuilding(Building* b) const;

  /**
   * @brief Adds a building to the city if it is valid. Otherwise throws an
   * InvalidCityException.
   *
   * @param name The name of the building
   * @param location The coordinates of the building
   * @param buildingType The type of the building (should be: industrial,
   * residential, shop, gym, or restaurant)
   */
  void AddBuilding(std::string name, std::pair<int, int> location,
                   const std::string& buildingType);

  /**
   * @brief Get a pointer to the Node object in the given location.
   *
   * @param location The location of the node
   * @return A pointer to a Node object if there is a Node in the given location
   * or a nullptr otherwise
   */
  Node* GetNode(std::pair<int, int> location) const;

  /**
   * @brief Get a list of the Node pointers that have type "Building".
   *
   * @return A list of pointers to Nodes with type "Building".
   */
  std::vector<Node*> GetBuildingNodes() const;

  /**
   * @brief Adds a person and its car to the city.
   *
   * @param name Name of the person.
   * @param personType Type of the person.
   * @param workplacename Name of working place.
   * @param homename Name of home.
   */
  void AddPersonAndCar(std::string& name, PersonType personType,
                       std::string& workplacename, std::string& homename);

  /**
   * @brief Checks if the person that is trying to be added is valid.
   *
   * @param p A pointer to the Person object
   */
  bool IsValidPerson(Person* p);

  /**
   * @brief
   * Checks if the intersection that the pointer given as parameter is pointing
   * to is valid. The intersection must be inside city boundaries and the
   * location of the intersection must be unoccupied.
   *
   * @param i A pointer to a intersection object
   * @return true if the intersection is valid, false otherwise
   */
  bool IsValidIntersection(Intersection* i) const;

  /**
   * @brief Attempts to create an intersection to the given location.
   * Returns an InvalidCityException if the location is occupied already.
   *
   * @param location The coordinates of the intersection
   */
  void AddIntersection(std::pair<int, int> location);

  /**
   * @brief Get the a pointer to the Intersection object in the given location.
   *
   * @param location The location of the intersection
   * @return A pointer to an Intersection object if there is an Intersection in
   * the given location, or a nullptr if there is no Intersection in the given
   * location.
   */
  Intersection* GetIntersection(std::pair<int, int> location) const;

  /**
   * @brief Updates the status of all the traffic lights in the city.
   *
   * @param deltaTime
   */
  void UpdateIntersections(float deltaTime) const;

  /**
   * @brief Draws the intersections in the city to the SFML window given as
   * parameter.
   *
   * @param window A reference to a SFML window
   */
  void DrawIntersections(sf::RenderWindow& window) const;

 /**
   * @brief Chooses the road that the user wants to analyze and highlights it
   *
   * @param roadIndex The index of the chosen road
   */
  void ChooseRoad(int roadIndex);

  /**
   * @brief Adds a traffic light to the city.
   *
   * @param t A pointer to the traffic light object to be added
   */
  void AddTrafficLight(std::pair<int, int> location, int redAndGreenDuration,
                       int yellowDuration);

  /**
   * @brief Updates the locations and destinations of all the cars in the city.
   *
   * @param deltaTime
   * @param currentTime
   */
  void UpdateCars(float deltaTime, float currentTime);

  /**
   * @brief Draws the cars in the city to the SFML window given as parameter.
   *
   * @param window A reference to an SFML window
   */
  void DrawCars(sf::RenderWindow& window) const;

  /**
   * @brief Draws the buildings in the city to the SFML window given as
   * parameter.
   *
   * @param window A reference to an SFML window
   */
  void DrawBuildings(sf::RenderWindow& window) const;

  /**
   * @brief Draws the city to the SFML window given as parameter.
   *
   * @param window A reference to an SFML window
   */
  void PrintCity(sf::RenderWindow& window) const;

  /**
   * @brief Get a pointer to the Grid object of the city.
   *
   * @return Grid*
   */
  Grid* GetGrid() const;

  /**
   * @brief Get a vector containing pointers to all the roads in the city.
   *
   * @return std::vector<Road*>
   */
  std::vector<Road*> GetRoads() const;

  /**
   * @brief Get a vector containing pointers to all the cars in the city.
   *
   * @return std::vector<Car*>
   */
  std::vector<Car*> GetCars() const;

  /**
   * @brief Get time until next event.
   *
   * @param p Next event from a specified person.
   */
  int TimeUntilNextEvent(Person* p) const;

  /**
   * @brief Add the simulation clock to city.
   *
   * @param clock Clock implemented in SimulationClock, used in simulator.cpp.
   */
  void AddClock(SimulationClock* clock);

  /**
   * @brief Check if person has an event going on.
   *
   * @param p Check if this exact person is busy.
   *
   * @return Boolean value if a person is busy at the moment.
   */
  bool IsBusy(Person* p) const;

  /**
   * @brief Add event to schedule.
   *
   * @param p This is the person that is going to have new event.
   */
  void AddEvent(Person* p);

 private:
  Grid* grid_;
  std::vector<Road*> roads_;
  std::vector<Building*> buildings_;
  std::vector<Intersection*> intersections_;
  std::vector<TrafficLight*> trafficLights_;
  std::map<Person*, Car*> personCarMap_;
  std::vector<Node*> nodes_;
  SimulationClock* clock_;
};

#endif

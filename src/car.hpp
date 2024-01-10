#ifndef CAR_H
#define CAR_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <limits>
#include <map>
#include <queue>

#include "grid.hpp"
#include "intersection.hpp"
#include "node.hpp"
#include "road.hpp"

/**
 * @brief The PersonType defines the car color of a person and
 * affects the schedule of the person.
 *
 */
enum class PersonType {  //
  Lazy,
  Active,
  Neutral,
  Gentleman,
  Angry,
  Nocturnal
};

/**
 * @brief A class used for representing a car in the simulated city.
 * The cars move around the city to varius destinations during the day.
 *
 */
class Car {
 public:
  /**
   * @brief Constructor. Constructs a new car object.
   * @param startingNode The Node where the car starts at is the home of its
   * owner by default.
   */
  Car(Node* startingNode);

  /**
   * @brief Updates the cars location and state. Checks the cars schedule to
   * find the next destination.
   * @param deltaTime How much time has passed since the car was last updated.
   * @param currentTime How much time has passed in the simulation in total.
   * Used to check the schedule.
   * @param allNodes All the nodes currently in the city.
   * @param intersections All the intersections currently in the city.
   * @param cars All the cars currently in the city.
   * @param roads All the roads currently in the city.
   */
  void Update(float deltaTime, float currentTime, std::vector<Node*> allNodes,
              std::vector<Intersection*> intersections, std::vector<Car*> cars,
              std::vector<Road*> roads);

  /**
   * @brief Used to return the intersection at the vicinity of the car
   * @param intersections All the intersections in the city.
   * @return Intersection near the cars location
   */
  Intersection* GetIntersection(std::vector<Intersection*> intersections);

  /**
   * @brief Set a new destination for the car.
   * @param destination New destination Node.
   */
  void SetDestination(Node* destination);

  /**
   * @brief Set the direction for the car.
   * @param current Current location of the car.
   * @param destination The location of the destination.
   */
  void SetDirection(std::pair<int, int> current,
                    std::pair<int, int> destination);

  /**
   * @brief Set the speedlimit for the car according to the current road
   * @param roads All the roads in the city
   */
  void SetSpeedLimit(std::vector<Road*> roads);

  /**
   * @brief Check if the car is at destination
   * @param destinationX The x-coordinate of the destination
   * @param destinationY The y-coordinate of the destination
   * @return True if the car is at destination, false otherwise
   */
  bool AtDestination(float destinationX, float destinationY);

  /**
   * @brief Check that the intersection is ok and car can proceed
   * @param intersection The intersection in front of the car
   * @param cars All the cars in the city
   * @return True if the car can proceed
   */
  bool CheckIntersection(Intersection* intersection, std::vector<Car*> cars);

  /**
   * @brief Check that the lane that the car will go to after the intersection
   * in free
   * @param intersection The intersection in front of the car
   * @param cars The cars in the city
   * @param nextDirection The direction that the car will go to after the
   * intersection
   * @return True if the lane is free and false otherwise
   */
  bool LaneIsFree(Intersection* intersection, std::vector<Car*> cars,
                  std::string nextDirection);

  /**
   * @brief If intersection does not have traffic lights cars should yield to
   * other cars coming from right
   * @param intersection The intersection in front of the car
   * @param cars All the cars in the city
   * @return True if the car should yield
   */
  bool YieldRight(Intersection* intersection, std::vector<Car*> cars);

  /**
   * @brief Get the direction of the car
   *@return The direction that the car is going to
   */
  std::string& GetDirection();

  /**
   * @brief Draw the car into the SFML-window
   * @param window The SFML-window
   * @param cellSize The size of the cell in the GUI
   */
  void Draw(sf::RenderWindow& window, int cellSize);

  /**
   * @brief Add an event to the cars schedule
   * @param time What time should the car move to the destination
   * @param node The node that the car should move to
   */
  void AddEvent(int time, Node* node);

  /**
   * @brief Initialize the cars schedule
   * @param schedule The schedule for the car
   */
  void InitializeSchedule(std::map<int, Node*> schedule);

  /**
   * @brief Check if there is a car in front of this car
   * @param cars The cars in the city
   */
  bool CarInFront(std::vector<Car*> cars);

  /**
   * @brief Set the color for the car according to the PersonType
   * @param pType the PersonType of the car's owner
   */
  void SetColor(PersonType pType);

  /**
   * @brief Get the location of the car
   *
   */
  std::pair<float, float> GetLocation();

  /**
   * @brief An algorithm to calculate the shortest route from source node to
   * destination node
   * @param source The node where the car starts
   * @param destination The node where the car should move next
   * @param allNodes All the nodes in the city
   */
  std::vector<Node*> Dijkstra(Node* source, Node* destination,
                              std::vector<Node*> allNodes);

 private:
  sf::RectangleShape carShape;
  sf::RectangleShape leftRearTireShape;
  sf::RectangleShape rightRearTireShape;
  sf::RectangleShape leftFrontTireShape;
  sf::RectangleShape rightFrontTireShape;
  sf::RectangleShape leftFrontLight;
  sf::RectangleShape rightFrontLight;
  sf::RectangleShape frontWindow;

  float maxSpeed_;
  float acceleration_;
  float currentSpeed_;
  bool idle_;
  float currentSpeedLimit;
  std::string direction_;
  std::pair<float, float> location_;
  Node* destination_;
  std::vector<Node*> path_;
  std::map<int, Node*> schedule_;
  Node* previous_;
  sf::Color color_;
  float waitingTime_;
};

#endif

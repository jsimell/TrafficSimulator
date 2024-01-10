#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "building.hpp"
#include "car.hpp"
#include "industrial.hpp"
#include "node.hpp"
#include "residential.hpp"
#include "simulationClock.hpp"

/**
 * @brief A class for persons in the city. Each person has a name, type, working
 * place and home. In addition they will have a car and a schedule, once they
 * are added into the city. Starting location for person and its car is at home.
 */

class Person {
 public:
  /**
   * @brief Construct a new Person object.
   *
   * @param name The name of the person
   * @param personType The type of person (Neutral, Angry, Lazy, Gentleman,
   * Active and Nocturnal)
   * @param workplace Pointer to a Industrial object. Persons workplace
   * @param home Pointer to a Residential object. Persons home.
   */
  Person(const std::string& name, PersonType personType, Industrial* workplace,
         Residential* home);

  /**
   * @brief Get the person's working place.
   *
   * @return Pointer to an Industrial object.
   */
  Industrial* GetWorkplace() const;

  /**
   * @brief Get the person's home.
   *
   * @return Pointer to a Residential object.
   */
  Residential* GetResidence() const;

  /**
   * @brief Get the person's car.
   *
   * @return Pointer to a Car object.
   */
  Car* GetCar();

  /**
   * @brief Get the person's name.
   *
   * @return Name as string.
   */
  std::string GetName() const;

  /**
   * @brief Buy a car for person. This is done
   * when the person is added to city, so the person can travel.
   *
   * @param car Pointer to a Car object.
   */
  void BuyCar(Car* car);

  /**
   * @brief Initialize the schedule for the person and its car.
   * This is done after person is added to a city and it has "bought"
   * a car.
   * @param schedule The random schedule that is given for a person.
   */
  void InitializeSchedule(std::map<int, Node*> schedule);

  /**
   * @brief Gives boolean value that tells, is the person at home (true),
   * or not (false).
   * @return Boolean value, false or true.
   */
  bool isAtHome() const;

  /**
   * @brief Gives the location of the person.
   *
   * @return Coordinates of the location as a pair of ints.
   */
  std::pair<int, int> GetLocation() const;

  /**
   * @brief Gives type of the person.
   *
   * @return The type of the person as PersonType, that is
   * implemented in car.hpp
   */
  PersonType GetPersonType() const;

  /**
   * @brief Gives the schedule for the person.
   *
   * @return Schedule which is a map that contains minutes as keys,
   * and pointers to Node objects as events.
   */
  std::map<int, Node*> GetSchedule() const;

  /**
   * @brief Adds a new event to the schedule.
   *
   * @param time Time in minutes when this event occurs.
   * @param node Pointer to the destination Node object.
   */
  void AddEvent(int time, Node* node);

  /**
   * @brief When car travels, person travels in the car.
   * This makes it possible.
   * @param location The location of the car.
   */
  void UpdateLocationFromCar(std::pair<float, float> location);

 private:
  std::string name_;
  PersonType personType_;
  std::map<int, Node*> schedule_;
  Industrial* workplace_;
  std::pair<float, float> location_;
  Residential* home_;
  Car* car_;
};

#endif

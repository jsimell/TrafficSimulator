#ifndef EVENT_H
#define EVENT_H
#include <random>

#include "node.hpp"
#include "person.hpp"

/**
 * @brief The Event class is responsible for creating random schedules
 * that determine the events a person will have over a period of time.
 * It considers the person's type and adjusts the schedule accordingly.
 */

class Event {
 public:
  /**
   * @brief Construct a new Event object.
   *
   * @param person The person whose schedule is created.
   * @param buildingNodes The nodes that contain a building.
   */
  Event(Person* person, std::vector<Node*> buildingNodes);

  /**
   * @brief Create a new random schedule for a person.
   *
   * @return Returns the schedule in map format, where a time value is
   * mapped to a corresponding event node.
   */
  std::map<int, Node*> CreateSchedule();

 private:
  std::map<int, Node*> schedule_;
  Person* person_;
  std::vector<Node*> buildingNodes_;
  std::default_random_engine generator_;  // for randomizing
};

#endif

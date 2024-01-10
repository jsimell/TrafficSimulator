#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <iostream>
#include <utility>

/**
 * @brief A class for representing the traffic lights in the simulated city.
 *
 */
class TrafficLight {
 public:
  /**
   * @brief Construct a new Traffic Light object.
   *
   * @param location The coordinates of the traffic light
   * @param redDuration The duration of the red light
   * @param yellowDuration The duration of the yellow light
   * @param greenDuration The duration of the green light
   */
  TrafficLight(std::pair<int, int> location, int redAndGreenDuration,
               int yellowDuration)
      : location_(location),
        redDuration_(redAndGreenDuration),
        yellowDuration_(yellowDuration),
        greenDuration_(redAndGreenDuration){};

  /**
   * @brief Get the coordinates of the traffic light's location.
   *
   * @return The coordinates of the traffic light as std::pair<int, int>
   */
  std::pair<int, int> GetLocation() const { return location_; }

  /**
   * @brief Get the red light duration of the traffic light.
   *
   * @return Red light duration
   */
  int GetRedDuration() const { return redDuration_; }

  /**
   * @brief Get the yellow light duration of the traffic light.
   *
   * @return Yellow light duration
   */
  int GetYellowDuration() const { return yellowDuration_; }

  /**
   * @brief Get the green light duration of the traffic light.
   *
   * @return Green light duration
   */
  int GetGreenDuration() const { return greenDuration_; }

  /**
   * @brief Switches the state of the traffic light to red.
   *
   */
  void TurnRed() {
    isRed_ = true;
    isYellow_ = false;
    isGreen_ = false;
  }

  /**
   * @brief Switches the state of the traffic light to yellow.
   *
   */
  void TurnYellow() {
    isRed_ = false;
    isYellow_ = true;
    isGreen_ = false;
  }

  /**
   * @brief Switches the state of the traffic light to green.
   *
   */
  void TurnGreen() {
    isRed_ = false;
    isYellow_ = false;
    isGreen_ = true;
  }

  /**
   * @brief Get the current color of the traffic light.
   *
   * @return A string representing the current state of the traffic light
   * ("red", "yellow", or "green")
   */
  std::string GetStatus() const {
    if (isRed_) {
      return "red";
    } else if (isYellow_) {
      return "yellow";
    } else {
      return "green";
    }
  }

 private:
  std::pair<int, int> location_;
  int redDuration_;
  int yellowDuration_;
  int greenDuration_;
  bool isRed_ = false;
  bool isYellow_ = false;
  bool isGreen_ = true;  // In the beginning, the light is green by default
};

#endif
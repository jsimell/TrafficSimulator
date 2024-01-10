#ifndef INVALID_CITY_EXCEPTION_H
#define INVALID_CITY_EXCEPTION_H

#include <exception>
#include <string>

/**
 * @brief An exception class extending the std::exception class. Used in
 * situations where the JSON file provided by the user is invalid.
 *
 */
class InvalidCityException : public std::exception {
 public:
  /**
   * @brief Construct a new InvalidCityException object.
   *
   * @param errorMessage
   */
  InvalidCityException(std::string errorMessage)
      : errorMessage_(errorMessage) {}

  /**
   * @brief Return the error message describing what went wrong.
   *
   * @return std::string
   */
  std::string GetError() const {
    return "InvalidCityException: " + errorMessage_;
  }

 private:
  std::string errorMessage_;
};

#endif
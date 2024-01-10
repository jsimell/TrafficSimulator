#include "person.hpp"

#include <chrono>  // Include for std::chrono
#include <cmath>
#include <ctime>  // Include for std::time

Person::Person(const std::string& name, PersonType personType,
               Industrial* workplace, Residential* home)
    : name_(name), personType_(personType), workplace_(workplace), home_(home) {
  location_ = home_->GetLocation();  // initial location is at home.
}

Industrial* Person::GetWorkplace() const { return workplace_; }

Residential* Person::GetResidence() const { return home_; }

Car* Person::GetCar() { return car_; }

void Person::BuyCar(Car* car) { car_ = car; }

void Person::InitializeSchedule(std::map<int, Node*> schedule) {
  schedule_ = schedule;
  car_->InitializeSchedule(schedule_);
}

bool Person::isAtHome() const {
  return (this->GetLocation() == home_->GetLocation());
}

std::pair<int, int> Person::GetLocation() const {
  return {round(location_.first), round(location_.second)};
}

PersonType Person::GetPersonType() const { return personType_; }

std::map<int, Node*> Person::GetSchedule() const { return schedule_; }

void Person::AddEvent(int time, Node* node) {
  schedule_.insert({time, node});
  car_->AddEvent(time, node);  // Adds the same event to the corresponding car
  for (auto it = schedule_.begin(); it != schedule_.end() && it->first < time; ) {
                it = schedule_.erase(it);
    }
}

void Person::UpdateLocationFromCar(std::pair<float, float> location) {
  // Update person's location based on car's location, in car.cpp update
  // function, which is called in city.cpp updatecars, so they work in sync.
  location_ = location;
}

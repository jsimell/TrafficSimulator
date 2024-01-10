#include "event.hpp"

#include <algorithm>
#include <random>

Event::Event(Person* person, std::vector<Node*> buildingNodes) {
  person_ = person;
  buildingNodes_ = buildingNodes;
  std::random_device rd;
  generator_.seed(rd());

  // Shuffle the buildingNodes
  std::shuffle(buildingNodes_.begin(), buildingNodes_.end(), generator_);
}

std::map<int, Node*> Event::CreateSchedule() {
  schedule_.clear();
  int lastSelectedIndex = -1;  // Initialize to an invalid index
  int timeDifferenceRange = 5;
  int days = 30;  // initialized to month

  // Different person types have different expected leaving and arrival times.
  switch (person_->GetPersonType()) {
    case PersonType::Lazy:
      timeDifferenceRange += 40;
      break;
    case PersonType::Active:

      break;
    case PersonType::Neutral:
      timeDifferenceRange += 60;
      break;
    case PersonType::Gentleman:
      timeDifferenceRange += 20;
      break;
    case PersonType::Angry:
      timeDifferenceRange += 30;
      break;
    case PersonType::Nocturnal:
      timeDifferenceRange += 10;
      break;
  }

  for (int day = 0; day < days; ++day) {
    // Events during (00:00 - 07:00)
    for (int time = (day * 1440); time <= 420 + (day * 1440); time += 50) {
      if ((rand() % 100 < 3) ||
          (person_->GetPersonType() ==
           PersonType::Nocturnal)) {  // 3% chance that will happen
        int index;
        do {
          index = rand() % (buildingNodes_.size() - 1);
        } while (
            index == lastSelectedIndex ||
            (buildingNodes_[index]->GetLocation() == person_->GetLocation()));

        lastSelectedIndex = index;

        int timeDifferenceSign = (rand() % 2 == 0) ? 1 : -1;
        int timeDifference =
            timeDifferenceSign * (rand() % timeDifferenceRange + 1);
        int newTime = time + timeDifference;

        // Check if the new time is within the desired range
        schedule_[newTime] = buildingNodes_[index];
      }
    }

    // Events during (07:00 - 09:30) with normal probability
    for (int time = 420 + (day * 1440); time <= 660 + (day * 1440);
         time += 60) {
      // 90% chance
      if (rand() % 100 < 90) {
        int index;

        do {
          index = rand() % (buildingNodes_.size() - 1);
        } while (
            index == lastSelectedIndex ||
            (buildingNodes_[index]->GetLocation() == person_->GetLocation()));

        lastSelectedIndex = index;

        int timeDifferenceSign = (rand() % 2 == 0) ? 1 : -1;
        int timeDifference =
            timeDifferenceSign * (rand() % timeDifferenceRange + 1);
        int newTime = time + timeDifference;

        // Check if the new time is within the desired range

        schedule_[newTime] = buildingNodes_[index];
      }
    }

    // Events during (09:30 - 16:00).
    for (int time = 660 + (day * 1440); time <= 960 + (day * 1440);
         time += 60) {
      //
      if (rand() % 100 < 30 &&
          person_->GetPersonType() !=
              PersonType::Nocturnal) {  // 50% chance that will happen
        int index;

        do {
          index = rand() % (buildingNodes_.size() - 1);
        } while (
            index == lastSelectedIndex ||
            (buildingNodes_[index]->GetLocation() == person_->GetLocation()));

        lastSelectedIndex = index;

        int timeDifferenceSign = (rand() % 2 == 0) ? 1 : -1;
        int timeDifference =
            timeDifferenceSign * (rand() % timeDifferenceRange + 1);
        int newTime = time + timeDifference;

        // Checking if time is correct

        schedule_[newTime] = buildingNodes_[index];
      }
    }
    // events during (16:00 - 21:00) with normal probability
    for (int time = 960 + (day * 1440); time <= 1260 + (day * 1440);
         time += 60) {
      if (rand() % 100 < 80) {  // 80% probability
        int index;

        do {
          index = rand() % (buildingNodes_.size() - 1);
        } while (
            index == lastSelectedIndex ||
            (buildingNodes_[index]->GetLocation() == person_->GetLocation()));

        lastSelectedIndex = index;

        int timeDifferenceSign = (rand() % 2 == 0) ? 1 : -1;
        int timeDifference =
            timeDifferenceSign * (rand() % timeDifferenceRange + 1);
        int newTime = time + timeDifference;

        schedule_[newTime] = buildingNodes_[index];
      }
    }

    for (int time = 1260 + (day * 1440); time <= 1440 + (day * 1440);
         time += 120) {         // from (21:00 to 00:00) there's less traffic
      if (rand() % 100 < 10) {  // 80% probability
        int index;

        do {
          index = rand() % (buildingNodes_.size() - 1);
        } while (
            index == lastSelectedIndex ||
            (buildingNodes_[index]->GetLocation() == person_->GetLocation()));

        lastSelectedIndex = index;

        int timeDifferenceSign = (rand() % 2 == 0) ? 1 : -1;
        int timeDifference =
            timeDifferenceSign * (rand() % timeDifferenceRange + 1);
        int newTime = time + timeDifference;

        schedule_[newTime] = buildingNodes_[index];
      }
    }
  }
  return schedule_;
}

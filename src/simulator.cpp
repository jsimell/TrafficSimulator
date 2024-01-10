#include "simulator.hpp"

#include <cmath>

Simulator::Simulator()
    : guiEnabled_(true),
      endSimulation_(false),
      simulationSpeed_(1),
      clock_(new SimulationClock()) {}

Simulator::~Simulator() {
  // Delete the Analysis object if it is created
  if (analysis_) {
    delete analysis_;
  }

  // Delete the City object if it is created
  if (c_) {
    delete c_;
  }
  // Delete clock
  delete clock_; 
}

void Simulator::UpdateSimulation(float deltaTime, float currentTime) {
  c_->UpdateCars(deltaTime, currentTime);
  c_->UpdateIntersections(deltaTime);
}

void Simulator::DrawSimulation(Visualization* gui) {
  sf::Event event;
  while (gui->GetWindow().pollEvent(event)) {
    if (event.type == sf::Event::Closed) gui->GetWindow().setVisible(false);
  }

  gui->GetWindow().clear();

  // Draw the city and the cars
  c_->PrintCity(gui->GetWindow());
  c_->DrawIntersections(gui->GetWindow());
  c_->DrawCars(gui->GetWindow());
  c_->DrawBuildings(gui->GetWindow());

  gui->GetWindow().display();
}

void Simulator::StartSimulation() {
  std::cout << "Starting simulation..." << std::endl;
  City* c = nullptr;

  // Continue asking for JSON file name until the user provides a valid file.
  while (c == nullptr) {
    c = LoadCity();
  }

  SetCity(c);
}

bool is_integer(const std::string& string) {
  return !string.empty() &&
         std::find_if(string.begin(), string.end(), [](unsigned char c) {
           return !std::isdigit(c);
         }) == string.end();
}

void Simulator::SimulatorThread() {
  analysis_ = new Analysis(c_, clock_);

  std::string roadIndex;

  while (true) {
    std::cout << "Please enter road index to be analyzed (the analyzed road "
                 "will be highlighted in the simulation):"
              << std::endl;
    std::cin >> roadIndex;

    if (!is_integer(roadIndex) || stoi(roadIndex) < 0 ||
        stoi(roadIndex) > int(c_->GetRoads().size()) - 1) {
      std::cout << "Invalid input." << std::endl;
    } else {
      break;
    }
  }

  analysis_->SpecifyRoad(stoi(roadIndex));
  analysis_->Init();

  std::string simulationSpeedStr;

  while (true) {
    std::cout << "Set simulation speed (1, 2, 4, 8, 16): ";
    std::cin >> simulationSpeedStr;

    if (simulationSpeedStr == "1" || simulationSpeedStr == "2" ||
        simulationSpeedStr == "4" || simulationSpeedStr == "8" ||
        simulationSpeedStr == "16") {
      // Valid input, convert to integer
      simulationSpeed_ = std::stoi(simulationSpeedStr);
      clock_->SetSimulationSpeed(simulationSpeed_);
      break;  // Exit the loop if a valid speed is entered
    } else {
      std::cout << "Invalid input. Please enter 1, 2, 4, 8, or 16."
                << std::endl;
    }
  }

  Visualization* gui;

  std::string guiEnabledStr;
  std::cout << "Enable GUI? (type yes or no):" << std::endl;
  std::cin >> guiEnabledStr;
  if (guiEnabledStr == "yes") {
    gui = new Visualization(50, c_->GetGrid());
    c_->ChooseRoad(stoi(roadIndex));
  } else {
    guiEnabled_ = false;
  }

  float previousTime = 0.0;

  // Use shared state for the promise/future
  std::shared_future<void> exitFuture = exitSignal.get_future();

  // Start input thread
  std::thread inputThread(&Simulator::InputThread, this, std::move(exitFuture));

  // Main loop
  clock_->Start();

  while (true) {
    if (endSimulation_ || clock_->GetDayNumber() > 29) {
      break;
    }

    float currentTime = clock_->GetElapsedTime();
    float deltaTime = (currentTime - previousTime);
    previousTime = currentTime;
    std::string simulationTime = clock_->GetSimulationTime();

    UpdateSimulation(deltaTime, currentTime);
    analysis_->Analyze();

    if (guiEnabled_) {
      DrawSimulation(gui);
    }
  }

  // Set the exit signal
  exitSignal.set_value();

  // Wait for the input thread to finish
  inputThread.join();

  if (guiEnabled_) {
    delete gui;  // Delete the Visualization object if it was created
  }

  // create a finish simulation function
  std::cout << "Simulation complete." << std::endl;
}

City* Simulator::LoadCity() {
  // logic here
  std::string filename;
  std::cout << "Please enter JSON file name:" << std::endl;
  std::cin >> filename;
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: The file " << filename
              << " does not exist or there was an issue when opening "
                 "the file."
              << std::endl;
    return nullptr;
  }

  City* c = nullptr;
  // Try to create a city
  try {
  // Load the file into a string
  std::string contents = std::string{std::istreambuf_iterator<char>(file),
                                     std::istreambuf_iterator<char>()};

  // Parse the JSON using cpp-json
  json::value jsonData = json::parse(contents);

  // Extract data from the JSON and use it to initialize the simulator
  int x = json::to_number<int>(jsonData["x"]);
  int y = json::to_number<int>(jsonData["y"]);

  // init to max 5 cars for now; using 1 car right now
  std::vector<Person*> persons;
  c = new City(x, y);

  // Extract buildings
  auto buildingsArray = json::as_array(jsonData["buildings"]);
  for (const auto& building : buildingsArray) {
    auto buildingObject = json::as_object(building);

    if (!buildingObject.empty()) {
      // Assuming there's only one key in the building object
      std::string name = buildingObject.begin()->first;
      auto buildingData = json::as_array(buildingObject.begin()->second);

      std::string buildingType = buildingData[0].as_string();
      auto positionArray = json::as_array(buildingData[1]);

      int buildingX = json::to_number<int>(positionArray[0]);
      int buildingY = json::to_number<int>(positionArray[1]);

      try {
        c->AddBuilding(name, {buildingX, buildingY}, buildingType);
      } catch (InvalidCityException& e) {
        std::cout << "Could not load the city from the JSON file." << std::endl;
        std::cout << e.GetError() << std::endl;
        delete c;
        file.close();
        return nullptr;
      }
    } else {
      std::cerr << "Invalid building object in the array." << std::endl;
      file.close();
      delete c;
      return nullptr;
    }
  }

  // Extract intersections
  auto intersectionsArray = json::as_array(jsonData["intersections"]);
  for (const auto& intersection : intersectionsArray) {
    int intersectionX = json::to_number<int>(intersection[0]);
    int intersectionY = json::to_number<int>(intersection[1]);
    try {
      c->AddIntersection({intersectionX, intersectionY});
    } catch (InvalidCityException& e) {
      std::cout << "Could not load the city from the JSON file." << std::endl;
      std::cout << e.GetError() << std::endl;
      file.close();
      delete c;
      return nullptr;
    }
  }

  // Extract roads
  auto roadsArray = json::as_array(jsonData["roads"]);
  for (const auto& road : roadsArray) {
    int start_x = json::to_number<int>(road[0]);
    int start_y = json::to_number<int>(road[1]);
    int end_x = json::to_number<int>(road[2]);
    int end_y = json::to_number<int>(road[3]);
    try {
      c->AddRoad({start_x, start_y}, {end_x, end_y});
    } catch (InvalidCityException& e) {
      std::cout << "Could not load the city from the JSON file." << std::endl;
      std::cout << e.GetError() << std::endl;
      file.close();
      delete c;
      return nullptr;
    }
  }

  // Extract persons
  auto personsArray = json::as_array(jsonData["persons"]);
  for (const auto& person : personsArray) {
    std::string name = json::as_string(person[0]);
    std::string pTypeString = json::as_string(person[1]);
    PersonType pType;
    if (pTypeString == "Lazy") {
      pType = PersonType::Lazy;
    } else if (pTypeString == "Active") {
      pType = PersonType::Active;
    } else if (pTypeString == "Neutral") {
      pType = PersonType::Neutral;
    } else if (pTypeString == "Angry") {
      pType = PersonType::Angry;
    } else if (pTypeString == "Gentleman") {
      pType = PersonType::Gentleman;
    } else if (pTypeString == "Nocturnal") {
      pType = PersonType::Nocturnal;
    } else {
      // Unknown string
      std::cerr << "Unknown PersonType " << pTypeString
                << " in the JSON file for person named " << name << std::endl;
      std::cout << "Person type of " << name
                << " will be set to the default value 'Neutral'." << std::endl;
      pType = PersonType::Neutral;  // Sets a default value when unknown
    }
    auto workplaceName = json::as_string(person[2]);
    auto homeName = json::as_string(person[3]);

    if (homeName.empty() || workplaceName.empty()) {
      std::cerr << "Something is missing from person parameters!" << std::endl;
      file.close();
      delete c;
      return nullptr;
    }

    try {
      c->AddPersonAndCar(name, pType, workplaceName, homeName);
    } catch (InvalidCityException& e) {
      std::cout << "Could not load the city from the JSON file." << std::endl;
      std::cout << e.GetError() << std::endl;
      file.close();
      return nullptr;
    }
  }

  c->AddClock(clock_);  // Add clock to city

  auto trafficLightsArray = json::as_array(jsonData["trafficLights"]);
  for (const auto& trafficLight : trafficLightsArray) {
    auto trafficLightPosArray = json::as_array(trafficLight[0]);
    int posX = json::to_number<int>(trafficLightPosArray[0]);
    int posY = json::to_number<int>(trafficLightPosArray[1]);
    int redAndGreenDuration = json::to_number<int>(trafficLight[1]);
    int yellowDuration = json::to_number<int>(trafficLight[2]);
    try {
      c->AddTrafficLight({posX, posY}, redAndGreenDuration, yellowDuration);
    } catch (InvalidCityException& e) {
      std::cout << "Could not load the city from the JSON file." << std::endl;
      std::cout << e.GetError() << std::endl;
      file.close();
      delete c;
      return nullptr;
    }
  }
  } catch (const std::exception& e) {
    std::cerr << "Error loading city: " << e.what() << std::endl;

    // Delete the City object to avoid memory leak
    delete c;

    // Close the file and return nullptr
    file.close();
    return nullptr;
  }

  // close file
  file.close();

  return c;
}

void Simulator::InputThread(std::shared_future<void> exitFuture) {
  std::string command;
  while (exitFuture.wait_for(std::chrono::milliseconds(50)) ==
         std::future_status::timeout) {
    std::cout << "Enter a command (e.g., status, exit, analyze, export): ";
    std::cin >> command;

    if (command == "exit") {
      endSimulation_ = true;
    } else if (command == "status") {
      std::cout << "Day: " << clock_->GetDayNumber()
                << " | Time is: " << clock_->GetSimulationTime() << std::endl;
    } else if (command == "analyze") {
      analysis_->GenerateHourlyHistogram(analysis_->GetData());
    } else if (command == "export") {
      std::string filename;
      std::cout << "Enter filename: ";
      std::cin >> filename;
      analysis_->ExportToCSV(filename);
    } else {
      std::cout << "Invalid command. Try again." << std::endl;
    }
  }
}


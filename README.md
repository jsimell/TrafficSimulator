# Introduction
The purpose of this program is to simulate and analyze the traffic of a city model inputted as a JSON file.

This document contains instructions on how to use the program.

# Credits
This project was developed as a group project in the Aalto University _ELEC-A7151 Object-oriented Programming with C++_ course in 2023. The responsible teacher for the course was Yusein Ali, and the project advisor was Henrik Toikka.

The project was developed by:
- Artur Brander
- Aape Hartikainen
- Jaakko Karhu
- Jiri Simell

# Instructions on how to use the program
**Dependencies:** 
The simulator requires some additional libraries to be installed, so run these commands in the terminal:
1. Linux: `sudo apt-get install libxrandr-dev libxcursor-dev libsfml-dev`
2. MacOS: `brew install sfml`

**Building and running the program**
  1. Clone `https://version.aalto.fi/gitlab/karhuj5/traffic-simulator-henrik-toikka-4.git`
  2. Navigate to the folder `cd build`
  3. Generate makefile with CMake: `cmake ..`
  4. Build the file in the same directory `make`
  5. Navigate to the root folder `cd ..`
  6. Run the file `build/./main`

**How to use the simulation:** 
In the beginning, the program asks for a JSON file name. If the file is not found in the root folder, or if it is invalid, the program will not proceed and it will ask for another file (see the JSON file template and requirements below).

After the JSON file has been successfully loaded, the program asks for a road index to analyze during the simulation. Index i chooses the i:th road listed in the JSON file to be analyzed.

After choosing the road to be analyzed, the program asks for simulation speed (1, 2, 4, 8, or 16).

After this the program asks if the gui should be enabled or not, and then it will start the simulation.

During the simulation you can use the commands:
- `status` Prints the current simulation time to the terminal
- `exit` Exits the program
- `analyze` Prints the usage data of the i:th road to the terminal
- `export` Exports the road analysis data to a CSV file

# Files
1. The .json-files should be placed in the project's root folder (this folder) and some examples are found in this folder as well. 
2. All of the source code is found in the src folder. 
3. The used libraries can be found in the libs folder.
4. Test files can be found in the tests folder.
5. The project plan can be found in the plan folder.
6. The final project documentation can be found in the doc folder.

# JSON file template for city loading
The city is loaded from a JSON file which should be located in the root folder of the project. A template for the JSON files is provided below. If the JSON file is invalid, the program will continue asking for a new file until the file is valid. The root folder of this project contains two example JSON files: city.json and smallcity.json.

Requirements:
- The order of the elements must be the same as in the template. 
- All the locations of the buildings, intersections, roads, and traffic lights must be inside city boundaries.
- The building type must be on of the following types: "Residential", "Industrial", "Gym", "Shop", or "Restaurant".
- The starting and ending points of roads must be either intersections or buildings.
- The PersonType parameter of person objects must be one of the following types: "Lazy", "Active", "Neutral", "Gentleman", or "Angry".
- The workplace of a person must be one of the Industrial buildings added to the city (i.e. the name of the workplace must be found in the added Industrial buildings' names)
- The home of a person must be one of the Residential buildings added to the city (i.e. the name of the home building must be found in the added Residential buildings' names)
- The traffic lights must have the same coordinates as one of the intersections.
- The objects must be placed in locations where there are no other objects (excluding traffic lights, which must be placed on top of intersections).

The template:
```json
{
  "x": vertical_city_size(int),
  "y": horizontal_city_size(int),
  "buildings": [
    {name(std::string): [building_type(std::string), [x-coordinate(int), y-coordinate(int)]]}
  ],
  "intersections": [
    [x-coordinate(int), y-coordinate(int)]
  ],
  "roads": [
    [starting_x-coordinate(int), starting_y-coordinate(int), ending_x-coordinate(int), ending_y-coordinate(int)]
    ],
  "persons": [
    [name(std::string), PersonType(std::string), name_of_workplace(std::string), name_of_home_building(std::string)]
  ],
  "trafficLights": [
    [[x-coordinate(int), y-coordinate(int)], red_and_green_light_duration(int), yellow_light_duration(int)]
  ]
}
```

# License
This project is licensed under the MIT License - see the LICENSE.md file for details.

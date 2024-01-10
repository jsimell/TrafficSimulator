# Introduction
The /tests folder contains tests for some of the classes of the program. However, tests have not been written for all of the classes.

# How to run the tests:
The tests can be run by entering the following commands to the terminal while in the tests folder. (NOTE: Running the tests requires SFML to be installed on your device!):
1. `g++ -o tests *.cpp ../src/!(main).cpp -lsfml-graphics -lsfml-window -lsfml-system`
2. `./tests`

If a test fails, there will be an assertion error and the execution of the tests will stop.


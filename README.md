# APR Project
This repository uses a linear controller to navigate a Turtlebot3 around a circular shape and back to its starting position. The odometry and the laser scan is provided by a server running on the Turtlebot3 and is obtained by establishing a TCP/IP connection. Also the linear and angular velocities can be sent to control the robot.

This project was done for the UAS Technikum Vienna

## Requirments
* Turtlebot3 with server client
* Connection to the Turtlebot3
* cmake
* make
* C++ compiler

## Usage

1. Download the repository
2. use `mkdir build` to create a build folder.
3. use `cd build` then `cmake ..` then `make` to build an executable
4. run the programm with `./main`
5. now the robot should start driving its predefined motion

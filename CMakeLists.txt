cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)
include_directories(lib)

# Add the executable
#add_executable(testPrint src/testPrint.cpp src/odomScaler.cpp)
add_executable(main src/main.cpp src/odomScaler.cpp)
target_link_libraries(main PRIVATE pthread)
add_executable(linearControl src/linearControl.cpp src/linearControl.cpp)

# If you have other source files in the 'src' directory and want to include them,
# list them in the add_executable call, like this:
# add_executable(MyExecutable src/main.cpp src/other_source_file.cpp)
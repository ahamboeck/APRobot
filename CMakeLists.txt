cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(MyProject VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable
add_executable(testPrint src/testPrint.cpp src/odomScaler.cpp)
add_executable(thread1 src/thread1.cpp src/thread1.cpp)
target_link_libraries(thread1 PRIVATE pthread)


# If you have other source files in the 'src' directory and want to include them,
# list them in the add_executable call, like this:
# add_executable(MyExecutable src/main.cpp src/other_source_file.cpp)
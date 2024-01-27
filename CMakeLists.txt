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
add_executable(main src/main.cpp src/odomScaler.cpp src/linearControl.cpp src/localization.cpp)
target_link_libraries(main PRIVATE pthread)

find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(PythonLibs 3.0 REQUIRED)
include_directories(${PYTHON3_INCLUDE_DIRS} ${NumPy_INCLUDE_DIRS})

# populate matplotlib repository
include(FetchContent)
FetchContent_Declare(
    matplotlib
    GIT_REPOSITORY https://github.com/lava/matplotlib-cpp.git
    GIT_TAG        f23347fca25219d1c42cbb91608b5556814bf572
)
FetchContent_GetProperties(matplotlib)
if(NOT matplotlib_POPULATED)
    FetchContent_Populate(matplotlib)
endif()
include_directories(SYSTEM ${matplotlib_SOURCE_DIR})

# link python and numpy
target_link_libraries(main PRIVATE ${PYTHON_LIBRARIES} Python3::NumPy)
# If you have other source files in the 'src' directory and want to include them,
# list them in the add_executable call, like this
# add_executable(MyExecutable src/main.cpp src/other_source_file.cpp)
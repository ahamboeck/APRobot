#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <tuple>

class localization
{
public:
    // Standard Constructer
    localization(){};
    // Standard Destructor
    ~localization(){};

    localization(const std::vector<float> &polarCoordinates);
    std::vector<std::tuple<float, float, int>> filterWall(std::vector<std::tuple<float, float, int>> scanData, double boundry, double tolerance);
    std::vector<std::tuple<float, float, int>> convertToCartesian();
    void pyPlot();
    void center();

protected:
private:
    // laserscan werte daweil hartgecoded Ersetzen mit LaserScaler Vektor
    std::vector<std::tuple<float, float, int>> cartesianCoordinates;
    std::vector<float> laserScanVec;

};

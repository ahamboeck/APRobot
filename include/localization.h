#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include <tuple>

class pol2Car
{
public:
    // Standard Constructer
    pol2Car(){};
    // Standard Destructor
    ~pol2Car(){};

    // Polare Lidarpunkte in Karthesische umwanden
    pol2Car(const std::vector<float> &polarCoordinates);
    // Vektor mit Tupel (X,Y,Messpunkt in °)
    std::vector<std::tuple<float, float, int>> convertToCartesian();

    // Suchfunktion nach winkel scanpunkt
    // std::tuple<float, float, int> findCoordinatesByAngle(int angle);
protected:
private:
    // Koordinaten mit Winkelangabe
    std::vector<std::tuple<float, float, int>> cartesianCoordinates;

    // laserscan werte daweil hartgecoded Ersetzen mit LaserScaler Vektor
    std::vector<float> laserScanVec;

};

class localization
{
public:
    // Standard Constructer
    localization(){};
    // Standard Destructor
    ~localization(){};

    localization(const std::vector<float> &polarCoordinates);
    std::vector<std::tuple<float, float, int>> filterWall(std::vector<std::tuple<float, float, int>> scanData, int boundry, double tolerance);
    void pyPlot();
    void center();

protected:
private:
    // laserscan werte daweil hartgecoded Ersetzen mit LaserScaler Vektor
    std::vector<float> laserScanVec;

};

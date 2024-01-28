#include <localization.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

double dist_a = 0.7;
double tol_a = 0.1;


localization::localization(const std::vector<float> &polarCoordinates) : laserScanVec(polarCoordinates) {}

localization localizer(laserScanVec);



auto cartesianCoordinates = localizer.convertToCartesian();
// auto coordAt20Degrees = converter.findCoordinatesByAngle(20);
auto upperWall = localizer.filterWall(cartesianCoordinates, dist_a, -tol_a);
auto lowerWall = localizer.filterWall(cartesianCoordinates, -dist_a, tol_a);

std::vector<std::tuple<float, float, int>> localization::convertToCartesian()
{
    cartesianCoordinates.clear();
    for (int i = 0; i < laserScanVec.size(); ++i)
    {
        float angleInRadians = i * M_PI / 180.0;
        float x = laserScanVec[i] * cos(angleInRadians);
        float y = laserScanVec[i] * sin(angleInRadians);
        cartesianCoordinates.push_back(std::make_tuple(x, y, i));
    }
    return cartesianCoordinates;
}

std::vector<std::tuple<float, float, int>> localization::filterWall(std::vector<std::tuple<float, float, int>> scanData, double boundary, double tolerance)
{
    // this function filters the upper or lower walls
    std::vector<std::tuple<float, float, int>> Wall;

    for (const auto &point : scanData)
    {
        float x, y;
        int angle;
        std::tie(x, y, angle) = point;

        if (y > (boundary - tolerance))
        {
            Wall.push_back(point);
            // Points where y is exactly boundary - tolerance are not included in either vector.
            // You can decide where to put such points based on your requirements.
        }
    }
    return Wall;
}

void localization::center()
{
    for (const auto &coord : cartesianCoordinates)
    {
        float x, y;
        int angle;
        std::tie(x, y, angle) = coord;
        std::cout << "(" << x << ", " << y << ", " << angle << ")" << std::endl;
    };
} 

void localization::pyPlot()
{
    std::vector<float> xValues;
    std::vector<float> yValues;

    for (const auto &coord : cartesianCoordinates)
    {
        float x, y;
        int angle;
        std::tie(x, y, angle) = coord;
        xValues.push_back(x);
        yValues.push_back(y);
    }

    // Plotting
    plt::plot(xValues, yValues, "bo"); // "bo" for blue dots
    plt::title("XY Coordinates");
    plt::xlabel("X-axis");
    plt::ylabel("Y-axis");
    plt::show();
}

// void angle_search()
// {
//     try
//     {

//         float x, y;
//         int angle;
//         std::tie(x, y, angle) = coordAt20Degrees;
//         std::cout << "Coordinates at 20 degrees: X=" << x << ", Y=" << y << std::endl;
//     }
//     catch (const std::runtime_error &e)
//     {
//         std::cerr << e.what() << std::endl;
//     }
// }
// std::tuple<float, float, int> pol2Car::findCoordinatesByAngle(int angle) {
//     for (const auto& coord : cartesianCoordinates) {
//         if (std::get<2>(coord) == angle) {
//             return coord;
//         }
//     }
//     throw std::runtime_error("Angle not found in the vector.");
// }
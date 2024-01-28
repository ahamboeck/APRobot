#include "recieve.h"
#include "localization.h"
#include "laserScaler.h"

int main()
{
    Recv laserRecv;
    LaserDataExtractor laserDataExtractor;

    std::string laserData = laserRecv.recvScan();
    std::vector<float> ranges = laserDataExtractor.extractRanges(laserData);
    localization localizer(ranges);
    std::vector<std::tuple<float, float, int>> cartesianTouple = localizer.convertToCartesian(ranges);
    localizer.pyPlot(cartesianTouple);
}
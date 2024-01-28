#include <laserScaler.h>
#include <recieve.h>
#include <iostream>
#include <vector>
#include <iomanip>

std::vector<float> extractRanges(const std::string &jsonString)
{
    std::vector<float> ranges;
    try
    {
        auto j = nlohmann::json::parse(jsonString);
        if (j.contains("ranges") && j["ranges"].is_array())
        {
            for (const auto &item : j["ranges"])
            {
                ranges.push_back(item.get<float>());
            }
        }
    }
    catch (nlohmann::json::exception &e)
    {
        std::cerr << "JSON error: " << e.what() << std::endl;
    }
    return ranges;
}

// EXAMPLE USAGE
/*
int main() {
    Recv laserReciever;
    LaserDataExtractor laserDataExtractor;

    std::string scanData = laserReciever.recvScan();
    std::vector<float> laserRanges = laserDataExtractor.extractRanges(scanData);

    // ONLY NEEDED FOR THE PRINT
    std::cout << std::fixed << std::setprecision(10);

    // Print vector elements
    std::cout << "Vector elements: ";
    for (const float &value : laserRanges) {
        std::cout << value << " ";
    }

    std::cout << std::endl;
}
*/
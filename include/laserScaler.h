#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "../lib/json/json.hpp"

class LaserDataExtractor
{
public:
    LaserDataExtractor() {}

    ~LaserDataExtractor() {}

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
};

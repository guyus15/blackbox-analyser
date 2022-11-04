#include "data_sources.h"

#include <fstream>

#include "spdlog/spdlog.h"

CommonData CsvSource::load(const std::string& filepath)
{
    SPDLOG_INFO("Loading CSV data source");

    // Handling loading of CSV file.
    std::ifstream csv_file{ filepath };

    std::string line;
    while (std::getline(csv_file, line))
    {
        SPDLOG_INFO("{0}", line.c_str());
    }

    CommonData common_data;
    return common_data;
}

CommonData ByteSource::load(const std::string& filepath)
{
    // Handle loading of CSV byte file.

    CommonData common_data;
    return common_data;
}

CommonData SerialisedSource::load(const std::string& filepath)
{
    // Handle loading of serialised data file.

    CommonData common_data;
    return common_data;
}

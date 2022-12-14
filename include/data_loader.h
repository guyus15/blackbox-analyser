#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "data_sources.h"
#include "common_data.h"

#include "spdlog/spdlog.h"

#include <string>
#include <type_traits>

template<typename T>
class DataLoader
{
    static_assert(std::is_base_of_v<DataSource, T> ||
                  std::is_same_v<DataSource, T>,
                  "T must inherit from type DataSource");

public:
    DataLoader() = default;
    ~DataLoader() = default;

    DataLoader(const DataLoader&) = default;
    DataLoader(DataLoader&&) noexcept = default;

    DataLoader& operator=(const DataLoader&) = default;
    DataLoader& operator=(DataLoader&&) = default;

    /**
     * @brief Loads a log file at the specified filepath based off the given DataSource type
     */
    [[nodiscard]] CommonData load(const std::string& filepath) const
    {
        SPDLOG_INFO("Loading data source");

        T source{};

        CommonData data = static_cast<DataSource*>(&source)->load(filepath);

        return data;
    }
};

#endif
#ifndef DATA_SOURCE_H
#define DATA_SOURCE_H

#include "common_data.h"

#include <string>

class DataSource
{
public:
    DataSource() = default;
    virtual ~DataSource() = default;

    DataSource(const DataSource&) = default;
    DataSource(DataSource&&) noexcept = default;

    DataSource& operator=(const DataSource&) = default;
    DataSource& operator=(DataSource&&) noexcept  = default;

    /**
     * @brief Provides a definition for how a data source will be loaded into CommonData.
     * @param filepath The filepath of the data source.
     * @return The data in the form of the CommonData structure.
     */
    virtual CommonData load(const std::string& filepath) = 0;
};

/**
 * @brief A data source in JSON format.
 */
class CsvSource final : public DataSource
{
public:
    CommonData load(const std::string& filepath) override;
};

/**
 * @brief A data source as a sequence bytes.
 */
class ByteSource final : public DataSource
{
    CommonData load(const std::string& filepath) override;
};

/**
 * @brief A data source as a stream of raw binary data.
 */
class SerialisedSource final : public DataSource
{
    CommonData load(const std::string& filepath) override;
};

#endif

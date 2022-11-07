#ifndef COMMON_DATA_H
#define COMMON_DATA_H

#include "log_record.h"

#include <vector>
#include <string>

using Headers = std::vector<std::string>;

class CommonData
{
public:
    CommonData() = default;
    CommonData(Headers headers, std::vector<LogRecord> data);

    /**
     * @brief Gets the headers of the data.
     * @return The data headers.
     */
    Headers get_headers();

    /**
     * @brief Gets the data as a vector of LogRecords.
     * @returns The LogRecords data/
     */
    std::vector<LogRecord> get_data();

    /**
     * @brief Gets the number of log records.
     * @returns The number of log records.
     */
    [[nodiscard]] size_t size() const;

    /**
     * @brief Determines if this instance contains any data.
     * @returns true If this instance does not contain any data.
     * @returns false If this instance does contain data.
     */
    [[nodiscard]] bool empty() const;

    LogRecord& operator[](const int& index);

private:
    Headers m_headers_;
    std::vector<LogRecord> m_data_;
};

#endif
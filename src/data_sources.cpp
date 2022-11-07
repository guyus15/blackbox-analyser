#include "data_sources.h"
#include "utils.h"

#include <fstream>

#include "spdlog/spdlog.h"

CommonData CsvSource::load(const std::string& filepath)
{
    // Handling loading of CSV file.

    SPDLOG_INFO("Loading CSV data source");

    Headers headers;
    std::vector<LogRecord> log_records;

    std::ifstream csv_file{ filepath };

    std::string line;
    int current_line = 0;
    while (std::getline(csv_file, line))
    {
        if (current_line == 0)
        {
	        // If this is the first line, then it should be the header.
            headers = Utilities::tokeniser(line, ',');
        }
        else
        {
            LogRecord log_record;

            std::vector<std::string> data = Utilities::tokeniser(line, ',');

            // Fill the log record fields with the tokenised data.
            for (size_t i = 0; i < data.size(); i++)
            {
                (&log_record.datetime)[i] = data[i];
            }

            log_records.push_back(log_record);
        }

        current_line++;
    }

    CommonData common_data{ headers, log_records };
    return common_data;
}

CommonData ByteSource::load(const std::string& filepath)
{
    // Handle loading of CSV byte file.

    SPDLOG_INFO("Handling loading CSV byte file.");

    // TODO: This data first needs to be converted into the verbose equivalent. This is done with packet decoding.
    // This will be implemented with the addition of packet decoding, or a common library system is achieved.

    CommonData common_data;
    return common_data;
}

CommonData SerialisedSource::load(const std::string& filepath)
{
    // Handle loading of serialised data file.

    SPDLOG_INFO("Handling loading serialised data file.");

    // TODO: This is present as an example for the future implementation of logging to a serialised format.
    // Currently this is not implemented.

    CommonData common_data;
    return common_data;
}

#ifndef LOG_RECORD_H
#define LOG_RECORD_H

#include <string>

/**
 * @brief Contains all relevant data from a point information reply log.
 * @details Does not contain useless information such as the reply status.
 */
struct LogRecord
{
    // NOTE: For now, everything will be represented in string format, to allow us to quickly
    // display the data. This will soon be converted into relevant data types, to allow us
    // to perform an analysis of the data.

    std::string datetime;
    std::string flags;
    std::string node;
    std::string channel;
    std::string channel_address;
    std::string point_category;
    std::string point_number;
    std::string logical_point_number;
    std::string logical_point_zone;
    std::string device_type;
    std::string auxiliary_point_attributes;
    std::string group;
    std::string area_type;
    std::string area_number;
    std::string sector_id;
    std::string loop_type;
    std::string raw_identity;
    std::string actual_device_type;
    std::string mode_and_sensitivity;
    std::string raw_analogue_values1, raw_analogue_values2, raw_analogue_values3;
    std::string lta_flags;
    std::string raw_lta;
    std::string dirtiness;
    std::string units_of_measure1, units_of_measure2, units_of_measure3;
    std::string converted_values1, converted_values2, converted_values3;
    std::string instantaneous_active_state;
    std::string instantaneous_fault_state;
    std::string confirmed_active_state;
    std::string confirmed_fault_state;
    std::string acknowledged_active_state;
    std::string acknowledged_fault_state;
    std::string output_force_mode;
    std::string output_unforced_state;
    std::string output_forced_state;
};

#endif
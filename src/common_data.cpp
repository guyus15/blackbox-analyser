#include "common_data.h"

CommonData::CommonData(Headers headers, std::vector<LogRecord> data)
	: m_headers_{std::move(headers)}, m_data_{std::move(data)} 
{
}

Headers CommonData::get_headers()
{
	return m_headers_;
}

std::vector<LogRecord> CommonData::get_data()
{
	return m_data_;
}

size_t CommonData::size() const
{
	return m_data_.size();
}

bool CommonData::empty() const
{
	return m_data_.empty();
}
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utilities
{
	/**
	 * @brief Splits a given string `s` by any character delimiter `del`.
	 * @returns A vector of strings separated by the delimiter.
	 */
	std::vector<std::string> tokeniser(const std::string& s, char del);
}

#endif
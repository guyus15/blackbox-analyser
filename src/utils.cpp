#include "utils.h"

#include <sstream>

std::vector<std::string> Utilities::tokeniser(const std::string& s, const char del)
{
	std::vector<std::string> elements{};

	std::stringstream ss{ s };
	std::string word;

	while (!ss.eof())
	{
		std::getline(ss, word, del);
		elements.push_back(word);
	}

	return elements;
}

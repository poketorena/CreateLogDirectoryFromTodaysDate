#include <iostream>
#include "CreateLogDirectoryFromTodaysDate.hpp"

int main()
{
	namespace util = MyUtility;

	auto logDirectoryPath = util::Log::CreateLogDirectoryFromTodaysDate();

	std::cout << logDirectoryPath << std::endl;
}

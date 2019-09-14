#include <iostream>
#include "expertSystem.h"
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		ExpertSystem newFile(argv[1]);
		// if open argv ok sinon Wrong input
		// if (newFile.m_listRules.size() > 0)
		// {
		// 	for (std::list<Rules>::iterator it = newFile.m_listRules.begin(); it != newFile.m_listRules.end(); it++)
		// 	{
		// 		it->printFacts();
		// 	}
		// }

		std::cout << "annalyser starting" << std::endl;
	}
	else
		std::cout << "Wrong input" << std::endl;
	return 0;
}

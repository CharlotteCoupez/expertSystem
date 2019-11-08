#include <iostream>
#include "../ExpertSystem.h"
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		ExpertSystem newFile(argv[1]);
		// if open argv ok sinon Wrong input
	//	if (newFile.m_listRules.size() > 0)
	//	{
	//		for (std::list<Rules>::iterator it = newFile.m_listRules.begin(); it != newFile.m_listRules.end(); it++)
	//		{
	//			it->printValues();
	//		}
	//	}

		std::cout << "annalyser starting" << std::endl;
	}
	else
		std::cout << "too much files or missing file :/" << std::endl;
	return 0;
}

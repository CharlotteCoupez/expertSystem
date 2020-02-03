#include <iostream>
#include "../ExpertSystem.h"
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		ExpertSystem newFile(argc, argv);
		// if (newFile.m_listRules.size() > 0)
		// {
		// 	for (std::list<Rules>::iterator it = newFile.m_listRules.begin(); it != newFile.m_listRules.end(); it++)
		// 	{
		// 		it->printValues();
		// 	}
		// }
	}
	else
		std::cout << "wrong argument :/" << std::endl;
	return 0;
}

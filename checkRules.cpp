#include "ExpertSystem.h"
#include <iostream>

using namespace std;

int ExpertSystem::coherentRule()
{
    std::set<int>::iterator	fact;
    std::vector<int>	    path;
    int                     ret;
    ret = 1;
    for (fact = m_allFacts.begin(); fact != m_allFacts.end(); fact++)
	{
		std::cout << "list facts : " << char(*fact) << std::endl;
	}
	for (fact = m_allFacts.begin(); fact != m_allFacts.end(); fact++)
	{
		std::cout << "facts : " << char(*fact) << std::endl;
	    path.erase( path.begin(), path.end() );
        if (checkCoherence(path, *fact) == 0)
            return 0;
		std::cout << "ret = checkCoherence : " << ret << std::endl;
	}
        return ret;
}

int ExpertSystem::checkCoherence(std::vector<int> path, int fact)
{
    std::list<Rules>::iterator	itL;
    std::vector<int>::iterator	factInConclusion;
    
    std::cout << "1fact " << char(fact) << std::endl;
    for (size_t m = 0; m < path.size(); m++)
    {
        if (path[m] == fact)
            return 0;
        std::cout << "first path[i] : " << char(path[m]) << std::endl;
    }
    path.push_back(fact);
    // for (size_t j = 0; j < path.size(); j++)
    // {
    //     std::cout << "path[i] : " << char(path[j]) << std::endl;
    // }
    for (itL = m_listRules.begin(); itL != m_listRules.end();)
    {
        factInConclusion = std::find(itL->m_conclusion.begin(), itL->m_conclusion.end(), fact);
        if (*factInConclusion == fact)
        {
            
            for (size_t i = 0; i < itL->m_condition.size(); )
            {
		        // std::cout << "in checkCoherence : " << char(itL->m_condition[i]) << std::endl;
		        // std::cout << "in checkCoherence id : " << itL->id << std::endl;
		        // std::cout << "i: " << i << std::endl;
                if (isupper(itL->m_condition[i]) && checkCoherence(path, itL->m_condition[i]) == 0)
                {
		            std::cout << "2 BOUCLAGE FOR RULE with id : " << itL->id << std::endl;
                    return 0;
                }
		        // std::cout << "in checkCoherence2 : " << char(itL->m_condition[i]) << std::endl;
		        // std::cout << "in checkCoherence2 id : " << itL->id << std::endl;
		        // std::cout << "i : " << i << std::endl;
                i++;
            }
        }
        itL++;
    }
    // for (size_t l = 0; l < path.size(); l++)
    // {
    //     std::cout << "last path[i] : " << char(path[l]) << std::endl;
    // }
	path.erase( path.end() - 1, path.end() );
    return 1; //tout est passé ok
}

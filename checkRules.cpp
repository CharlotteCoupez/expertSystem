#include "ExpertSystem.h"
#include <iostream>

using namespace std;

int ExpertSystem::coherentRule()
{
    std::set<int>::iterator	fact;
    std::vector<int>	    path;
    int                     ret;
	//
	//std::list<Rules>::iterator	itL2;
    //std::vector<int>::iterator	factInCondition;
    //int                         ret;
    //// std::set<int> m_allFacts;
    //ret = 1;
    //for (itL = m_listRules.begin(); itL != m_listRules.end();)
    //{
    //    //path.push_back(m_condition[i]);
    //    for (int i = 0; i < itL->m_conclusion.size(); i++)
    //    {
    //        for (int i = 0; i < itL->m_condition.size(); i++)
    //        {
//
    //        }
    //        // itL->m_condition[i]
    //    }
    //    
    //}
    //return ret;
    ret = 1;
    for (fact = m_allFacts.begin(); fact != m_allFacts.end(); fact++)
	{
		std::cout << "facts : " << char(*fact) << std::endl;
	}
	for (fact = m_allFacts.begin(); fact != m_allFacts.end(); fact++)
	{
		std::cout << "facts : " << char(*fact) << std::endl;
        if (checkCoherence(path, *fact) == 0)
        {
            ret = 0;
        }
		std::cout << "ret = checkCoherence : " << ret << std::endl;
	}
        return ret;
}

int ExpertSystem::checkCoherence(std::vector<int> path, int fact)
{
    std::list<Rules>::iterator	itL;
    std::vector<int>::iterator	factInConclusion;
    std::vector<int>::iterator	factInPath;

    if (path.size() > 0)
    {
        factInPath = find(path.begin(), path.end(), fact);
        std::cout << "fact " << char(fact) << std::endl;
        std::cout << "factInPath " << char(*factInPath) << std::endl;
        if (*factInPath == fact)
        {
            std::cout << "BOUCLAGE FOR RULE with id : " << std::endl;
            return 0;
        }
    }
    path.push_back(fact);
    for (size_t j = 0; j < path.size(); j++)
    {
        std::cout << "path[i] : " << char(path[j]) << std::endl;
    }
    for (itL = m_listRules.begin(); itL != m_listRules.end();)
    {
        factInConclusion = find(itL->m_conclusion.begin(), itL->m_conclusion.end(), fact);
        if (*factInConclusion == fact)
        {
            
            for (size_t i = 0; i < itL->m_condition.size(); )
            {
		        std::cout << "in checkCoherence : " << char(itL->m_condition[i]) << std::endl;
		        std::cout << "in checkCoherence id : " << itL->id << std::endl;
		        std::cout << "i: " << i << std::endl;

                if (isupper(itL->m_condition[i]) && checkCoherence(path, itL->m_condition[i]) == 0)
                {
		            std::cout << "2 BOUCLAGE FOR RULE with id : " << itL->id << std::endl;
                	//path.erase( path.end() - 1, path.end() );
                    return 0;
                }
		        std::cout << "in checkCoherence2 : " << char(itL->m_condition[i]) << std::endl;
		        std::cout << "in checkCoherence2 id : " << itL->id << std::endl;
		        std::cout << "i : " << i << std::endl;
                i++;

            }
        }
        itL++;
    }
	//path.erase( path.end() - 1, path.end() );
    return 1; //tout est passé ok
}

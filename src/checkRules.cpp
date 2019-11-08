/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkRules.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:28:43 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/07 16:58:29 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ExpertSystem.h"

using namespace std;

bool    ExpertSystem::coherentRule()
{
    std::set<int>::iterator	fact;
    std::vector<int>	    path;
 
	for (fact = m_allFacts.begin(); fact != m_allFacts.end(); fact++)
	{
	    path.erase( path.begin(), path.end() );
        if (checkCoherence(path, *fact) == false)
            return false;
	}
        return true;
}


bool    ExpertSystem::checkCoherence(std::vector<int> path, int fact)
{
    std::list<Rules>::iterator	itL;
    std::vector<int>::iterator	factInConclusion;
    
    for (size_t m = 0; m < path.size(); m++)
    {
        if (path[m] == fact)
            return false;
    }
    path.push_back(fact);
    for (itL = m_listRules.begin(); itL != m_listRules.end();)
    {
        factInConclusion = find(itL->m_conclusion.begin(), itL->m_conclusion.end(), fact);
        if (*factInConclusion == fact)
        {
            for (size_t j = 0; j < itL->m_condition.size();j++)
            {
                if (isupper(itL->m_condition[j]) && checkCoherence(path, itL->m_condition[j]) == false)
                {
		            std::cout << "Rule number: " << itL->id << " is not properly linked."  << std::endl;
                    return false;
                }
            }
        }
        itL++;
    }
    return true;
}

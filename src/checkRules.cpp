/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkRules.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:28:43 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/12 14:19:54 by ccoupez          ###   ########.fr       */
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
	int	tmp;
    std::list<Rules>::iterator	itL;
    std::vector<int>::iterator	factInCls;

    tmp = -1;
    for (size_t m = 0; m < path.size(); m++)
    {
        if (path[m] == fact)
            return false;
    }
    path.push_back(fact);
    for (itL = m_listRules.begin(); itL != m_listRules.end();)
    {
        for (factInCls = itL->m_conclusion.begin(); factInCls != itL->m_conclusion.end();factInCls++)
	    {
		    if (*factInCls == fact)
			    tmp = fact;
	    }
        if (tmp == fact)
        {
            for (size_t j = 0; j < itL->m_condition.size();j++)
            {
                if (isupper(itL->m_condition[j]) && checkCoherence(path, itL->m_condition[j]) == false)
                {
                    path.erase( path.begin(), path.end() );
                    return false;
                }
            }
            tmp = 0;    
        }
        itL++;
    }
    path.erase( path.begin(), path.end() );
    return true;
}


void    ExpertSystem::print()
{
	std::set<int>::iterator	truef;
	std::set<int>::iterator	falsef;

	std::cout << "trueFacts.sizeof() : " << m_trueFacts.size() << std::endl;
	std::cout << "falseFacts.sizeof() : " << m_falseFacts.size() << std::endl;

	for (truef = m_trueFacts.begin(); truef != m_trueFacts.end(); truef++)
	{
		std::cout << "trueFacts[i] : " << char(*truef) << std::endl;
	}
	for (falsef = m_falseFacts.begin(); falsef != m_falseFacts.end(); falsef++)
	{
		std::cout << "falseFacts[i] : " << char(*falsef) << std::endl;
	}
}
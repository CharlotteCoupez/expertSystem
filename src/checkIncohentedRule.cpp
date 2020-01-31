/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkIncohentedRule.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:01:37 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/14 13:35:13 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ExpertSystem.h"

using namespace std;

void	ExpertSystem::fillTrueFasleFacts(Rules rule)
{
    m_falseFacts.erase( m_falseFacts.begin(), m_falseFacts.end() );
    m_trueFacts.erase( m_trueFacts.begin(), m_trueFacts.end() );
	for (size_t i = 0; i < rule.m_condition.size();)
	{
		if (char(rule.m_condition[i]) == '!')
			m_falseFacts.insert(rule.m_condition[++i]);
		else if (isupper(char(rule.m_condition[i])))
			m_trueFacts.insert(rule.m_condition[i]);
		i++;
	}
}

bool	ExpertSystem::checkFacts()
{
	std::set<char>::iterator	trueFact;
	std::set<char>::iterator	falseFact;

	for (trueFact = m_trueFacts.begin(); trueFact != m_trueFacts.end();)
	{
		for (falseFact = m_falseFacts.begin(); falseFact != m_falseFacts.end();)
		{
			if (*trueFact == *falseFact)
				return false;
			falseFact++;
		}
		trueFact++;
	}
	return true;
}

bool	ExpertSystem::ruleNotIncoherented()
{
	int							ret;
	std::list<Rules>::iterator	itL;

	for (itL = m_listRules.begin(); itL != m_listRules.end();)
	{
		fillTrueFasleFacts(*itL);
		for (size_t i = 0; i < itL->m_conclusion.size();)
		{
			if (isupper(itL->m_conclusion[i]))
			{
				ret = backwardChaining(itL->m_conclusion[i]);
				if (ret == PROVEN)
					fillList(true, itL->m_conclusion);
				if (ret == NOT_PROVEN)
					fillList(false, itL->m_conclusion);
				if (!checkFacts())
					return false;
			}
			i++;
		}
		itL++;
	}
	m_falseFacts.erase( m_falseFacts.begin(), m_falseFacts.end() );
    m_trueFacts.erase( m_trueFacts.begin(), m_trueFacts.end() );
	return true;
}

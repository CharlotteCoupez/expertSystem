/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incoRule.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:01:37 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/12 18:13:55 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ExpertSystem.h"

using namespace std;


void	ExpertSystem::fillTrueFasleFacts(Rules rule)
{
    m_falseFacts.erase( m_falseFacts.begin(), m_falseFacts.end() );
    m_trueFacts.erase( m_trueFacts.begin(), m_trueFacts.end() );

	for (size_t i = 0; i < rule.m_condition.size();) {

		if (char(rule.m_condition[i]) == '!') {
			m_falseFacts.insert(m_initialFacts[i + 1]);
			i++;
		}
		else if (isupper(char(rule.m_condition[i])))
		{
			m_trueFacts.insert(m_initialFacts[i]);
		}
		i++;
	}
}

bool	ExpertSystem::incoRule()
{
	std::list<Rules>::iterator	itL;
	std::vector<int> trueF;
	std::vector<int> falseF;

	for (itL = m_listRules.begin(); itL != m_listRules.end();)
	{
		// putFact();
		cout << "1************************" << std::endl;
		cout << "*itL->id : " << itL->id << std::endl;
		cout << "*(itL->m_conclusion.begin()) : " << *(itL->m_conclusion.begin()) << std::endl;

		fillTrueFasleFacts(*itL);
		backwardChaining(*(itL->m_conclusion.begin()));
		printTrueFacts();
		cout << "2************************" << std::endl;

		itL++;
	}
	return true;
}

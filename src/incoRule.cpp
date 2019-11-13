/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incoRule.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:01:37 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/13 13:24:37 by ccoupez          ###   ########.fr       */
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
			cout << "----i" << i << std::endl;
			cout << "----m_initialFacts[i" << char(rule.m_condition[i]) << std::endl;
			cout << "----m_initialFacts[i + 1" << char(rule.m_condition[i + 1]) << std::endl;

			m_falseFacts.insert(rule.m_condition[i + 1]);
			i++;
		}
		else if (isupper(char(rule.m_condition[i])))
		{
			m_trueFacts.insert(rule.m_condition[i]);
		}
		i++;
	}
}

bool	ExpertSystem::incoRule() 
{
	std::list<Rules>::iterator	itL;
	std::vector<int> trueF;
	std::vector<int> falseF;
    std::set<int>::iterator	fact;
	int							ret;

 
	// for (fact = m_allFacts.begin(); fact != m_allFacts.end(); )
	// {
	// 		cout << "fact" << *fact << std::endl;

		for (itL = m_listRules.begin(); itL != m_listRules.end();)
		{
			// putFact();
			cout << "1************************" << std::endl;
			cout << "*itL->id : " << itL->id << std::endl;
			cout << "*(itL->m_conclusion.begin()) : " << *(itL->m_conclusion.begin()) << std::endl;

			fillTrueFasleFacts(*itL);
			ret = backwardChaining(*(itL->m_conclusion.begin()));
			if (ret == PROVEN)
			{
					fillList(true, itL->m_conclusion);
			}
			if (ret == NOT_PROVEN)
			{
					fillList(false, itL->m_conclusion);
			}

			//backwardChaining(*fact);
			printTrueFacts();
			cout << "2************************" << std::endl;

			itL++;
		}
		// fact++;
	// }
	m_falseFacts.erase( m_falseFacts.begin(), m_falseFacts.end() );
    m_trueFacts.erase( m_trueFacts.begin(), m_trueFacts.end() );
	return true;
}

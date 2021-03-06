/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expertSystem.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:19:56 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/13 11:19:56 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ExpertSystem.h"

using namespace std;

void	ExpertSystem::fillList(bool type, std::vector<char> conclusion)
{
	if (type == 1)
	{
		for (size_t i = 0;i < conclusion.size(); i++)
		{
			if (char(conclusion[i]) == '!')
				m_falseFacts.insert(conclusion[++i]);
			else if (isupper(char(conclusion[i])))
				m_trueFacts.insert(conclusion[i]);
		}
		return;
	}
	for (size_t i = 0;i < conclusion.size(); i++)
	{
		if (isupper(char(conclusion[i])))
			m_falseFacts.insert(conclusion[i]);
	}
}

int		ExpertSystem::matchQuery(std::list<Rules>::iterator itL, char querie)
{
	for (size_t i = 0; i < itL->m_conclusion.size();)
	{
		if (itL->m_conclusion[i] == querie)
			return querie;
		i++;
	}
	// if (itL->impORif == '<')
	// {
	// 	for (size_t i = 0; i < itL->m_condition.size();)
	// 	{
	// 		if (itL->m_condition[i] == querie)
	// 			return querie;
	// 		i++;
	// 	}
	// }
	return 0;
}

bool	ExpertSystem::lastChecking(char querie)
{
	std::vector<char>			vecTmp;
	std::set<char>::iterator	checkResult;

	checkResult = find(m_trueFacts.begin(), m_trueFacts.end(), querie);
	if (*checkResult == querie)
	{
		if (m_opt_visu && !m_checking)
			std::cout << "This fact is TRUE: " << querie << std::endl;
		return true;
	}
	vecTmp.push_back(querie);
	fillList(false, vecTmp);
	if (m_opt_visu && !m_checking)
		std::cout << "This fact is FALSE : " << querie << std::endl;
	return false;
}

bool	ExpertSystem::backwardChaining(char querie)
{
	int							result;
	int							factInConc;
	std::list<Rules>::iterator	itL;

	if (checkKnowFacts(querie))
		return true;
	for (itL = m_listRules.begin(); itL != m_listRules.end();)
	{
		factInConc = matchQuery(itL, querie);
		if (factInConc == querie)
		{
			result = ruleChecking(itL->m_condition);
			if (result == PROVEN)
			{
				if (m_opt_visu && !m_checking)
					std::cout << "This fact is TRUE: " << querie << std::endl;
				fillList(true, itL->m_conclusion);
				if (!m_checking)
					return true;
			}
			else if (result == PROVEN_FALSE)
			{
				if (m_opt_visu && !m_checking)
					std::cout << "This fact is FALSE: " << querie << std::endl;
				fillList(false, itL->m_conclusion);
				if (!m_checking)
					return false;
			}
		}
		itL++;
	}
	return lastChecking(querie);
}

bool ExpertSystem::checkKnowFacts(char querie)
{
	std::set<char>::iterator cmp;
	std::set<char>::iterator cmp2;

	cmp = find(m_trueFacts.begin(), m_trueFacts.end(), querie);
	if (*cmp == querie)
	{
		cout << "\n-- The querie " << querie << " is true --\n" << std::endl;
		return true;
	}
	else
	{
		cmp2 = find(m_falseFacts.begin(), m_falseFacts.end(), querie);
		if (*cmp2 == querie)
		{
			cout << "\n-- The querie " << querie << " is false --\n" << std::endl;
			return true;
		}
	}
	return false;
}

void ExpertSystem::analyseQuerie()
{
	std::set<char>::iterator checkResult;

	for (size_t i = 0; i< m_queries.size();i++)
	{
		if (m_checking)
			backwardChaining(m_queries[i]);
		else
		{
			backwardChaining(m_queries[i]);
			checkResult = find(m_trueFacts.begin(), m_trueFacts.end(), m_queries[i]);
			if (*checkResult == m_queries[i])
				cout << "\n-- The querie " << m_queries[i] << " is true --\n" << std::endl;
			else
				cout << "\n-- The querie " << m_queries[i] << " is false --\n" << std::endl;
		}
	}
	if (m_output && !m_checking)
		printTrueFacts();
}

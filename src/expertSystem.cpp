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

void	ExpertSystem::fillList(bool type, std::vector<int> conclusion)
{
	std::vector<int>::iterator	truef;

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

int		ExpertSystem::matchQuery(std::list<Rules>::iterator itL, int querie)
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

bool	ExpertSystem::backwardChaining(int querie)
{
	std::cout << "backwardChaining querie : " << char(querie) << std::endl;
	int							result;
	std::list<Rules>::iterator	itL;
	std::vector<int>::iterator	factInConclusion;
	int							factInConc;
	std::set<int>::iterator		checkResult;
	std::vector<int>			vecTmp;

	for (itL = m_listRules.begin(); itL != m_listRules.end();)
	{
		factInConc = 0;
		factInConc = matchQuery(itL, querie);
		if (factInConc == querie)
		{
			std::cout << "*factInConc: " << char(factInConc) << " in int: " << factInConc << std::endl;
			std::cout << "QUERIE IN CONCLUSON char: " << char(querie) << " in int: " << querie << std::endl;
			result = ruleChecking(itL->m_condition);
			std::cout << "ret result in backward: " << result << std::endl;
			std::cout << "querie in backward: " << querie << std::endl;
			if (result == PROVEN)
			{
				cout << "PROVEN query : " << char(querie) << std::endl;
				fillList(true, itL->m_conclusion);
				if (!m_checking)
					return true;
			}
			else if (result == PROVEN_FALSE)
			{
				cout << "PROVEN_FALSE query : " << char(querie) << std::endl;
				fillList(false, itL->m_conclusion);
				if (!m_checking)
					return false;
			}
		}
		itL++;
	}
	checkResult = find(m_trueFacts.begin(), m_trueFacts.end(), querie);
	if (*checkResult == querie)
	{
		std::cout << "QUERIE HAVE A Solution : " << char(querie) << std::endl;
		return true;
	}
	else
	{
		vecTmp.push_back(querie);
		fillList(false, vecTmp);
		std::cout << "QUERIE have NO Solution for : " << char(querie) << std::endl;
		return false;
	}
}

void ExpertSystem::analyseQuerie()
{
	int	querie;

	for (size_t i = 0; i< m_queries.size();i++)
	{
		querie = 0;
		if (m_checking)
			backwardChaining(m_queries[i]);
		else
		{
			querie = find_in_set(m_queries[i], m_trueFacts);
			if (querie == m_queries[i])
				cout << "querie True :) : " << char(querie) << std::endl;
			else {
				querie = find_in_set(m_queries[i], m_falseFacts);
				if (querie == m_queries[i])
					cout << "querie False :'( : " << char(querie) << std::endl;
				else
					backwardChaining(m_queries[i]);
			}
		}
	}
	printTrueFacts();
}


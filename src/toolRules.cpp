/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolRules.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:46:45 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/14 14:55:43 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Rules.h"

using namespace std;

bool	Rules::isOperator(char c)
{
	if (c == '+' || c == '^' || c == '|')
		return true;
	return false;
}

bool	Rules::isRelationOp(char c)
{
	if (c == '=' || c == '<')
		return true;
	return false;
}

bool	Rules::opPriorities(char c, char op)
{
	if (c == '+')
		return true;
	if (op == 1 && c == '|')
		return true;
	return false;
}

int		Rules::getImpORif(string rule, size_t i)
{
	impORif = rule[i];
	if (i < (rule.size() + 1) && rule[i] == '=' && rule[i + 1] == '>')
		return i + 2;
	else if (i < (rule.size() + 2) && rule[i] == '<' && rule[i + 1] == '=' && rule[i + 2] == '>')
		return i + 3;
	return -1;
}

void	Rules::putInCondition()
{
	for (size_t i = 0; i < m_polonaise.size(); i++)
	{
		m_condition.push_back(m_polonaise[i]);
		if (isupper(m_polonaise[i]))
			m_facts.push_back(m_polonaise[i]);
	}
	m_polonaise.erase(m_polonaise.begin(), m_polonaise.end());
}

void	Rules::putInConclusion()
{
	for (size_t i = 0; i < m_polonaise.size(); i++)
	{
		m_conclusion.push_back(m_polonaise[i]);
		if (isupper(m_polonaise[i]))
			m_facts.push_back(m_polonaise[i]);
		if (m_polonaise[i] == '|' || m_polonaise[i] == '^')
			return ;
	}
	m_polonaise.erase(m_polonaise.begin(), m_polonaise.end());
}

void Rules::printValues()
{
	std::cout << "ID : " << id << std::endl;
	for (size_t i = 0; i < m_condition.size(); i++)
	{
		std::cout << "condition " << i << " : " << m_condition[i] << std::endl;
	}
	for (size_t i = 0; i < m_conclusion.size(); i++)
	{
		std::cout << "conculsion " << i << " : " << char(m_conclusion[i]) << std::endl;
	}
	std::cout << "impORif : " << impORif << "\n" << std::endl;
}

void Rules::printFacts()
{
	for (size_t i = 0; i < m_facts.size(); i++)
	{
		std::cout << "m_fact[i] : " << m_facts[i] << std::endl;
	}
	std::cout << "" << std::endl;
}

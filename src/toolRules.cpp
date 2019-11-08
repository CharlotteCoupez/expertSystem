/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolRules.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:46:45 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/08 16:23:50 by ccoupez          ###   ########.fr       */
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
	}
	m_polonaise.erase(m_polonaise.begin(), m_polonaise.end());
}




void Rules::printValues()
{
	std::cout << "ID : " << id << std::endl;
	for (size_t i = 0; i < m_condition.size(); i++)
	{
		std::cout << "char(m_condition[i] : " << char(m_condition[i]) << std::endl;
		//std::cout << "m_condition[i] : " << m_condition[i] << std::endl;
	}
	for (size_t i = 0; i < m_conditionType.size(); i++)
	{
		std::cout << "char(m_conditionType[i] : " << char(m_conditionType[i]) << std::endl;
		//std::cout << "m_conditionType[i] : " << m_conditionType[i] << std::endl;
	}
	for (size_t i = 0; i < m_conclusion.size(); i++)
	{
		std::cout << "char(m_conculsion[i] : " << char(m_conclusion[i]) << std::endl;
		//std::cout << "m_conculsion[i] : " << m_conclusion[i] << std::endl;
	}
	for (size_t i = 0; i < m_conclusionType.size(); i++)
	{
		std::cout << "char(m_conclusionType[i] : " << char(m_conclusionType[i]) << std::endl;
		//std::cout << "m_conclusionType[i] : " << m_conclusionType[i] << std::endl;
	}
	std::cout << "impORif : " << impORif << std::endl;
}

void Rules::printFacts()
{
	for (size_t i = 0; i < m_facts.size(); i++)
	{
		std::cout << "m_fact[i] : " << m_facts[i] << std::endl;
	}
	std::cout << "    " << std::endl;
}

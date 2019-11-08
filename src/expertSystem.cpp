/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expertSystem.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:36:27 by ccoupez           #+#    #+#             */
/*   Updated: 2019/10/23 16:36:27 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ExpertSystem.h"

using namespace std;

void	ExpertSystem::fillList(bool type, std::vector<int> conclusion)
{
	if (type == 1)
	{
		for (int i = 0;i < conclusion.size(); i++)
		{
			if (isupper(conclusion[i]))
				m_trueFacts.insert(conclusion[i]);
		}
		return;
	}
	for (int i = 0;i < conclusion.size(); i++)
	{
		if (isupper(conclusion[i]))
			m_falseFacts.insert(conclusion[i]);
	}
}

bool	ExpertSystem::backwardChaining(int querie)
{
	std::cout << "backwardChaining querie : " << char(querie) << std::endl;
	int							result;
	std::list<Rules>::iterator	itL;
	std::vector<int>::iterator	factInConclusion;
	std::set<int>::iterator		checkResult;

	for (itL = m_listRules.begin(); itL != m_listRules.end();)
	{
		factInConclusion = find(itL->m_conclusion.begin(), itL->m_conclusion.end(), querie);

		if (*factInConclusion == querie)
		{
			std::cout << "QUERIE IN CONCLUSON char: " << char(querie) << " in int: " << querie << std::endl;
			result = ruleChecking(itL->m_condition);
			std::cout << "ret result in backward: " << result << std::endl;
			std::cout << "querie in backward: " << querie << std::endl;
			if (result == PROVEN)
			{
				cout << "QUERIE HAVE A SSolution : " << char(querie) << std::endl;
				fillList(true, itL->m_conclusion);
				return true;
			}
			else
				itL++;
		}
		else
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
		std::vector<int> test;
		test.push_back(querie);
		fillList(false, test);
		std::cout << "QUERIE have NO Solution for : " << char(querie) << std::endl;
		return false;
	}
}

void ExpertSystem::analyseQuerie()
{
	std::vector<int>::iterator	itrQ;
	std::set<int>::iterator		querie;

	for (itrQ = m_queries.begin(); itrQ != m_queries.end(); itrQ++)
	{
		querie = find(m_trueFacts.begin(), m_trueFacts.end(), *itrQ);
		if (*querie != *itrQ)
		{
			std::cout << "START QUERING"<< char(*itrQ) << std::endl;
			querie = find(m_falseFacts.begin(), m_falseFacts.end(), *itrQ);
			if (*querie == *itrQ)
				cout << "querie False :'( : " << char(*querie) << std::endl;
			else
				backwardChaining(*itrQ);
		}
		else
		{
			cout << "querie True :) : " << char(*querie) << std::endl;
		}

	}
	printTrueFacts();
}

void ExpertSystem::createBaseRules(string ligne, int ruleId)
{
	Rules	rule(ligne);

	if (rule.status == 1)
	{
		for (int i = 0; i < rule.m_facts.size(); i++)
		{
			cout << "rule.m_facts[i]: " << char(rule.m_facts[i]) << std::endl;
			m_allFacts.insert(rule.m_facts[i]);
		}
		rule.id = ruleId;
		m_listRules.push_back(rule);
		rule.printValues();
	}
	else
		cout << "Rule number: " << ruleId << " is not correct." << std::endl;
	
}

void ExpertSystem::getInitialeFacts(string ligne)
{
	int	i;

	i = 1;
	while (isupper(ligne[i]))
	{
		m_initialFacts.push_back(ligne[i]);
		m_trueFacts.insert(ligne[i]);
		i++;
	}
}

void ExpertSystem::getQueries(string ligne)
{
	int	i;

	i = 1;
	while (isupper(ligne[i]))
	{
		m_queries.push_back(ligne[i]);
		i++;
	}
}

ExpertSystem::ExpertSystem(string argv)
{
	int					idRule;
	string				ligne;

	idRule = 1;
	ifstream monFichier(argv.c_str());
	if (monFichier)
	{
		while (getline(monFichier,  ligne))
		{
			if (ligne[0] == '=')
				getInitialeFacts(ligne);
			else if (ligne[0] == '?')
				getQueries(ligne);
			else if (isupper(ligne[0]) || ligne[0] == '!' || ligne[0] == '(')
			{
				createBaseRules(ligne, idRule);
				idRule++;
			}
		}
	}
	else
		std::cout << "No such a file" << std::endl;
	if (coherentRule() == true && m_queries.size() > 0)
		analyseQuerie();
}

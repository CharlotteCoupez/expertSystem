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
	std::vector<int>::iterator	truef;

	for (truef = conclusion.begin(); truef != conclusion.end(); truef++)
	{
		std::cout << "-------------conclusion : " << char(*truef) << std::endl;
	}
	std::cout << "------------- " << std::endl;

	if (type == 1)
	{
		for (size_t i = 0;i < conclusion.size(); i++)
		{
			if (isupper(char(conclusion[i])))
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

bool	ExpertSystem::backwardChaining(int querie)
{
	std::cout << "backwardChaining querie : " << char(querie) << std::endl;
	int							result;
	std::list<Rules>::iterator	itL;
	std::vector<int>::iterator	factInConclusion;
	std::set<int>::iterator		checkResult;
	std::vector<int>			vecTmp;

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
				cout << "QUERIE SSolution 1 : " << char(querie) << std::endl;
				//cout << "char(*(factInConclusion--) : " << char(*(--factInConclusion)) << std::endl;
				if (factInConclusion == itL->m_conclusion.begin()
					|| (factInConclusion != itL->m_conclusion.begin() && *(--factInConclusion) != '!'))
					fillList(true, itL->m_conclusion);
				else
					fillList(false, itL->m_conclusion);
				if (!checking)
					return true;
			}
		}
		factInConclusion = itL->m_conclusion.end();
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
	std::vector<int>::iterator	itrQ;
	int							querie;

	for (itrQ = m_queries.begin(); itrQ != m_queries.end(); itrQ++)
	{
		querie = find_in_set(*itrQ, m_trueFacts);
		if (querie == *itrQ)
			cout << "querie True :) : " << char(querie) << std::endl;
		else {
			querie = find_in_set(*itrQ, m_falseFacts);
			if (querie == *itrQ)
				cout << "querie False :'( : " << char(querie) << std::endl;
			else {
				std::cout << "START SHEARCHING"<< char(*itrQ) << std::endl;
				backwardChaining(*itrQ);
			}
		}
		querie = 0;
	}
	printTrueFacts();
}

void ExpertSystem::createBaseRules(string ligne, int ruleId)
{
	Rules	rule(ligne);
	if (rule.status == 1)
	{
		for (size_t i = 0; i < rule.m_facts.size(); i++)
		{
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
		// m_trueFacts.insert(ligne[i]);
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
	int		idRule;
	string	ligne;
	// int		fact;
	// std::set<int>		tmpTrueFacts;
	// std::set<int>		tmpFalseFacts;

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
	// tmpTrueFacts = m_trueFacts;
	if (coherentRule() == true && m_queries.size() > 0)
	{
		checking = true;
		// if (incoRule())
		// {
			// checking = false;
		// 	std::cout << "analyse" << std::endl;
			for (size_t i = 0; i < m_initialFacts.size();) {
				m_trueFacts.insert(m_initialFacts[i]);
				i++;
			}
		// }
			analyseQuerie();
		// else
		// {
		// 	std::cout << "incoRULe FALSe" << std::endl;
		// }
		
	}
	else
	{
		std::cout << "No analyse" << std::endl;
	}
	
}

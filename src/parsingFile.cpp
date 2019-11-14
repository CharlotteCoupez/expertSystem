/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsingFile.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 13:23:09 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/14 16:17:29 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ExpertSystem.h"

using namespace std;

void ExpertSystem::createBaseRules(string ligne, int ruleId)
{
	Rules	rule(ligne);
	if (rule.status == 1)
	{
	std::cout << "IAAAAAAAAAy" << std::endl;

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
		m_initialFacts.push_back(ligne[i++]);
}

void ExpertSystem::getQueries(string ligne)
{
	int	i;

	i = 1;
	while (isupper(ligne[i]))
		m_queries.push_back(ligne[i++]);
}

ExpertSystem::ExpertSystem(string argv)
{
	int		idRule;
	string	ligne;
	idRule = 1;
	ifstream monFichier(argv.c_str());
	if (!monFichier)
	{
		std::cout << "No file" << std::endl;
		return ;
	}
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
	checkAllCoherence();
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
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

bool ExpertSystem::checkAllCoherence()
{
	m_checking = true;
	if (ruleNotLinked() && ruleNotIncoherented())
	{
		m_checking = false;
		m_trueFacts.erase(m_trueFacts.begin(), m_trueFacts.end());
		m_falseFacts.erase(m_falseFacts.begin(), m_falseFacts.end());
		for (size_t i = 0; i < m_initialFacts.size(); i++) {
			m_trueFacts.insert(m_initialFacts[i]);
		}
		return true;
	}
	std::cout << "Incoherent rules or no Query" << std::endl;
	return false;
}

ExpertSystem::ExpertSystem(string argv)
{
	int		idRule;
	string	ligne;

	ifstream monFichier(argv.c_str());
	if (!monFichier)
	{
		std::cout << "wrong name file" << std::endl;
		return ;
	}
	idRule = 1;
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
	if (m_queries.size() > 0 && checkAllCoherence())
	{
		std::cout << "\n--- Checking finish -> analysis begins ---\n" << std::endl;
		// printTrueFacts();
		analyseQuerie();
	}
}

#include <iostream>
#include "ExpertSystem.h"
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
using namespace std;

void ExpertSystem::createBaseRules(string ligne)
{
	std::cout << "parseRules --" << ligne << std::endl;
	Rules rule(ligne);
	// rule.printValues();
	m_listRules.push_back(rule);
}

void ExpertSystem::createBaseFacts(string ligne)
{
	std::cout << "parseInitialFacts " << ligne << std::endl;
	int i = 1;

	while (isupper(ligne[i]))
	{
		m_facts.push_back(ligne[i]);
		i++;
	}
	for (int i = 0; i < m_facts.size(); i++)
	{
		std::cout << "m_facts[i] : " << m_facts[i] << std::endl;
	}
}

void ExpertSystem::getQueries(string ligne)
{
	std::cout << "getQueries " << ligne << std::endl;
	int i = 1;

	while (isupper(ligne[i]))
	{
		m_queries.push_back(ligne[i]);
		i++;
	}
	for (int i = 0; i < m_queries.size(); i++)
	{
		std::cout << "m_queries[i] : " << m_queries[i] << std::endl;
	}
}

ExpertSystem::ExpertSystem(string argv)
{
	std::cout << "good file : " << argv << std::endl;
	ifstream monFichier(argv.c_str());

	if (monFichier)
	{
		string ligne;
		while (getline(monFichier,  ligne))
		{
			if (ligne[0] == '=')
				createBaseFacts(ligne);
			else if (ligne[0] == '?')
				getQueries(ligne);
			else if (isupper(ligne[0]) || ligne[0] == '!')
				createBaseRules(ligne);
		}
	}
	else
	{
		std::cout << "No such a file" << std::endl;
	}
	// auto it = m_listRules.begin();
	if (m_listRules.size() > 0)
	{
		for (Rules it = m_listRules.begin(); it != m_listRules.end(); it++)
		{
			it.print
		}
	}
}

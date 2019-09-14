#include <iostream>
#include "ExpertSystem.h"
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
using namespace std;

void ExpertSystem::createFacts()
{
	std::cout << "create facts " << std::endl;

	// if (m_listRules.size() > 0)
	// {
	// 	for (std::list<Rules>::iterator it = m_listRules.begin(); it != m_listRules.end(); it++)
	// 	{
	// 		for (int i = 0; i < it->m_facts.size(); i++)
	// 		{
	// 			m_allFacts.insert(it->m_facts[i]);
	// 		}
	// 	}
	// }
	cout << "m_allFacts size" << m_allFacts.size() << std::endl;
	std::set<int>::iterator itr;
	for (itr = m_allFacts.begin(); itr != m_allFacts.end(); itr++)
	{
		cout << char(*itr) << std::endl;
	}
}

void ExpertSystem::createBaseRules(string ligne)
{
	// std::cout << "parseRules --" << ligne << std::endl;
	Rules rule(ligne);
	for (int i = 0; i < rule.m_facts.size(); i++)
	{
		m_allFacts.insert(rule.m_facts[i]);
	}
	m_listRules.push_back(rule);
}

void ExpertSystem::getInitialeFacts(string ligne)
{
	// std::cout << "parseInitialFacts " << ligne << std::endl;
	int i = 1;

	while (isupper(ligne[i]))
	{
		m_initialFacts.push_back(ligne[i]);
		i++;
	}
}

void ExpertSystem::getQueries(string ligne)
{
	// std::cout << "getQueries " << ligne << std::endl;
	int i = 1;

	while (isupper(ligne[i]))
	{
		m_queries.push_back(ligne[i]);
		i++;
	}
}

ExpertSystem::ExpertSystem(string argv)
{
	// std::cout << "file : " << argv << std::endl;
	ifstream monFichier(argv.c_str());

	if (monFichier)
	{
		string ligne;
		while (getline(monFichier,  ligne))
		{
			if (ligne[0] == '=')
				getInitialeFacts(ligne);
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
	// for (int i = 0; i < m_queries.size(); i++)
	// {
	// 	std::cout << "m_queries[i] : " << m_queries[i] << std::endl;
	// }
	// for (int i = 0; i < m_facts.size(); i++)
	// {
	// 	std::cout << "m_facts[i] : " << m_facts[i] << std::endl;
	// }
	createFacts();
}

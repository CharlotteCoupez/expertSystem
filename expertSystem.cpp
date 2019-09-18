#include <iostream>
#include "ExpertSystem.h"
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <algorithm>

using namespace std;
/*
faire une fonction filtrage (premiere regle quon va parcourir)
on selectionne les regles qui aboutissent au but que lon recherche
si dans les regle selectionnnees on a des condition nonverifiee (a false)
celle ci deviennent aussi des conditions a rechercher 

on sarrete quand on a tout verifies

We basically go through the rules in the knowledge base looking for conclusions which match the query and if we find them, 
donc quand on trouve toute les regle avec nos queries en conclusion on y joute de nouvelles queries qui sont dans les conditions de nos regles (si elle ne sont pas set a true on cherche si elle peuvent etre set a true avec toute les autres regle)
*/

void ExpertSystem::analyseQuerie(char querie)
{
	std::cout << "in analyse queri querie" << querie << std::endl;
	std::list<Rules>::iterator itL;
	for (itL = m_listRules.begin(); itL != m_listRules.end(); itL++)
	{
		std::vector<char>::iterator itrQ;
		std::vector<char>::iterator test;
		test = find(itL->m_conculsion.begin(), itL->m_conculsion.end(), querie);
		// std::cout << "test querie" << char(*test) << std::endl;
		if (char(*test) == querie)
		{
			// garde cette regle et cherche si les fait sont true
			std::cout << "QUERIE IN CONCLUSON" << std::endl;
		}
	}
	// si cest jmais passe par une conclusion dire que ya rien qui permet de dire ce quest cette querie
}

void ExpertSystem::createFacts()
{
	std::cout << "create facts " << std::endl;
	cout << "m_allFacts size" << m_allFacts.size() << std::endl;
	std::set<int>::iterator itr;
	for (itr = m_allFacts.begin(); itr != m_allFacts.end(); itr++)
	{
		std::vector<char>::iterator toFind;
		toFind = find (m_initialFacts.begin(), m_initialFacts.end(), char(*itr));
		std::cout << "result find a: " << char(*toFind) << std::endl;
		if (char(*toFind) == char(*itr))
		{
			std::cout << "FIND THIS FACT in ININTIAL FACT" << std::endl;
		}
		cout << char(*itr) << std::endl;
	}
		std::vector<char>::iterator itrQ;
		for (itrQ = m_queries.begin(); itrQ != m_queries.end(); itrQ++)
		{
			analyseQuerie(char(*itrQ));
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

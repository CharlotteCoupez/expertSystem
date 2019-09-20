#include <iostream>
#include "ExpertSystem.h"
#include <stdlib.h>
#include <ctype.h>

#include <algorithm>

using namespace std;
#include <typeinfo>

/*
A FAIRE
If there is an error in the input, for example a contradiction in the facts, or a syntax
error, the program must inform the user of the problem.
*/

void ExpertSystem::backwardChaining(int querie)
{
	std::cout << "in analyse queri querie" << querie << std::endl;
	std::list<Rules>::iterator itL;
	int result;

	for (itL = m_listRules.begin(); itL != m_listRules.end();)
	{
		std::cout << "mliste id " << itL->id << std::endl;

		std::vector<int>::iterator fact1;
		fact1 = find(itL->m_conculsion.begin(), itL->m_conculsion.end(), querie);
		if (char(*fact1) == querie) // || char(*fact2) == querie)
		{
			// Si la conclusion de la regle et la query on regarde si les conditions sont remplis (si oui on donne la réponse si non on regarde pourquoi)
			std::cout << "QUERIE IN CONCLUSON : " << char(querie) << std::endl;
			result = checkConditions(*itL);
			if (result == 0)
			{
				printTrueFacts();
				std::cout << "11QUERIE HAVE A Solution : " << char(querie) << std::endl;
				return;
				//condition remplie on a l'état de notre querie
			}
			else
			{
				backwardChaining(result);
				std::cout << "sortir backward: " << char(querie) << std::endl;
				itL = m_listRules.begin();
			}
		}
		else
			itL++;
	}
	std::vector<int>::iterator checkResult;
	checkResult = find(m_trueFacts.begin(), m_trueFacts.end(), querie);
	printTrueFacts();
	if (*checkResult == querie)
		std::cout << "QUERIE HAVE A Solution : " << char(querie) << std::endl;
	else
		std::cout << "QUERIE have NO Solution it is false : " << char(querie) << std::endl;

	// querie fals or undeermineds
	// si cest jmais passe par une conclusion dire que ya rien qui permet de dire ce quest cette querie
}

void ExpertSystem::analyseQuerie()
{
	// analyse QUERIE BY QUERIE
	std::vector<int>::iterator itrQ;
	for (itrQ = m_queries.begin(); itrQ != m_queries.end(); itrQ++)
	{
		backwardChaining(*itrQ);
	}
}

void ExpertSystem::printTrueFacts()
{
	for (int i = 0; i < m_trueFacts.size(); i++)
	{
		std::cout << "m_trueFacts[i] : " << char(m_trueFacts[i]) << std::endl;
	}
}

void ExpertSystem::createBaseRules(string ligne, int ruleId)
{
	// std::cout << "parseRules --" << ligne << std::endl;
	Rules rule(ligne);
	for (int i = 0; i < rule.m_facts.size(); i++)
	{
		m_allFacts.insert(rule.m_facts[i]);
	}
	rule.id = ruleId;
	//std::cout << "typeid(rule).name()" << typeid(rule).name() << std::endl;

	m_listRules.push_back(rule);
}

void ExpertSystem::getInitialeFacts(string ligne)
{
	// std::cout << "parseInitialFacts " << ligne << std::endl;
	int i = 1;

	while (isupper(ligne[i]))
	{
		m_initialFacts.push_back(ligne[i]);
		m_trueFacts.push_back(ligne[i]);
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
	int idRule = 1;

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
			{
				createBaseRules(ligne, idRule);
				idRule++;
			}
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
	analyseQuerie();
}

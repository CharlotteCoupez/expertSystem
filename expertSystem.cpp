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

int ExpertSystem::backwardChaining(int querie)
{
	std::cout << "backwardChaining querie : " << char(querie) << std::endl;
	std::list<Rules>::iterator	itL;
	int							result;
	int							ret;
	std::vector<int>::iterator	factInConclusion;
	std::set<int>::iterator		checkResult;

	for (itL = m_listRules.begin(); itL != m_listRules.end();)
	{
		factInConclusion = find(itL->m_conclusion.begin(), itL->m_conclusion.end(), querie);

		if (*factInConclusion == querie)
		{
			// Si la conclusion de la regle et la query on regarde si les conditions sont remplis (si oui on donne la réponse si non on regarde pourquoi)
			std::cout << "QUERIE IN CONCLUSON char: " << char(querie) << " in int: " << querie << std::endl;
			result = ruleChecking(itL->m_condition, itL->m_conclusion);
			std::cout << "ret result in backward: " << result << std::endl;
			std::cout << "querie in backward: " << querie << std::endl;
			if (result == -1)
			{
				cout << "QUERIE HAVE A SSolution : " << char(querie) << std::endl;
				return 1; //condition remplie on a l'état de notre querie
			}
			// else if (result == -2)
			// {
			// 	//false no solution a cause de xor
			// 	cout << "querie imposible xor : " << char(querie) << std::endl;
			// 	return 0;
			// }
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
		return 1;
	}
	else
	{
		std::vector<int> test;
		test.push_back(querie);
		fillList(false, test);
		std::cout << "QUERIE have NO Solution for : " << char(querie) << std::endl;
		return 0;
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
			m_allFacts.insert(rule.m_facts[i]);
		}
		rule.id = ruleId;
		m_listRules.push_back(rule);
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
	// if (coherentRule() == 1)
	// {
	// 	if (m_queries.size() > 0)
	// 		analyseQuerie();
	// }
}

void ExpertSystem::printTrueFacts()
{
	std::set<int>::iterator	truef;
	std::set<int>::iterator	falsef;
		
	std::cout << "m_trueFacts.sizeof() : " << m_trueFacts.size() << std::endl;
	std::cout << "m_falseFacts.sizeof() : " << m_falseFacts.size() << std::endl;

	for (truef = m_trueFacts.begin(); truef != m_trueFacts.end(); truef++)
	{
		std::cout << "m_trueFacts[i] : " << char(*truef) << std::endl;
	}
	for (falsef = m_falseFacts.begin(); falsef != m_falseFacts.end(); falsef++)
	{
		std::cout << "m_falseFacts[i] : " << char(*falsef) << std::endl;
	}
}

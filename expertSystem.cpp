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

	for (itL = m_listRules.begin(); itL != m_listRules.end();)
	{
		std::cout << "mliste id " << itL->id << std::endl;
		std::vector<int>::iterator	factInConclusion;

		factInConclusion = find(itL->m_conclusion.begin(), itL->m_conclusion.end(), querie);
		if (*factInConclusion == querie)
		{
			// Si la conclusion de la regle et la query on regarde si les conditions sont remplis (si oui on donne la réponse si non on regarde pourquoi)
			std::cout << "QUERIE IN CONCLUSON c : " << char(querie) << std::endl;
			std::cout << "QUERIE IN CONCLUSON : " << querie << std::endl;
			//result = checkConditions(*itL);
			// if (in condition pour if and onlyif)
		
			result = ruleChecking(itL->m_condition, itL->m_conclusion);
			
			// else 
				// result = ruleChecking(itL->m_conclusion, itL->m_condition)
			if (result == -1)
			{
				cout << "QUERIE HAVE A SSolution : " << char(querie) << std::endl;
				return 1;
				//condition remplie on a l'état de notre querie
			}
			else if (result == -2)
			{
				//false no solution a cause de xor
				cout << "querie imposible xor : " << char(querie) << std::endl;
				return -1;
			}
			else if (result == -3)
			{
				// ca na pas abouti on continue
				itL++;
			}
			else // notre retour est une nouvelle querie on recursive:)
			{
				ret = backwardChaining(result);
				cout << "sortir backward: " << char(querie) << std::endl;
				if (ret == -2)
					return -1; // on sait que la solution est false on cherche pas plus
				else if (ret == 1)
					itL = m_listRules.begin(); // on a abouti a un true donc on retourne a notre queri precedente voir si ca la fait avancée
				else
					itL++; // ca na pas abouti on regarde si il ny a pas dautres regles qui peuvent nous aider a prouver cette querie
			}
		}
		else
		{
			std::cout << "on tourne " << char(querie) << std::endl;

			itL++;
		}
	}
	std::set<int>::iterator checkResult;
	checkResult = find(m_trueFacts.begin(), m_trueFacts.end(), querie);
	std::cout << "checkResult : " << char(*checkResult) << std::endl;
	std::cout << "querie : " << char(querie) << std::endl;

	if (*checkResult == querie)
	{
		std::cout << "QUERIE HAVE A Solution : " << char(querie) << std::endl;
		return 1;
	}
	else
	{
		std::cout << "QUERIE have NO Solution for : " << char(querie) << std::endl;
		return -1;
	}

	// querie fals or undeermineds
	// si cest jmais passe par une conclusion dire que ya rien qui permet de dire ce quest cette querie
}

void ExpertSystem::analyseQuerie()
{
	std::vector<int>::iterator	itrQ;

	for (itrQ = m_queries.begin(); itrQ != m_queries.end(); itrQ++)
	{
		backwardChaining(*itrQ);
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
	int		idRule;
	string	ligne;

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
	
	if (m_queries.size() > 0)
		analyseQuerie();
}

void ExpertSystem::printTrueFacts()
{
	std::set<int>::iterator	truef;

	for (truef = m_trueFacts.begin(); truef != m_trueFacts.end(); truef++)
	{
		std::cout << "m_trueFacts[i] : " << char(*truef) << std::endl;
	}
}

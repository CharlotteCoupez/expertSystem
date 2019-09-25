#include <iostream>
#include "Rules.h"
#include <stdlib.h>
#include <cctype>

using namespace std;

int parseRule(string rule, std::vector<int>	values, std::vector<int>	m_facts)
{
		std::cout << "parseRule " << std::endl;

}

int Rules::getImpORif(string rule, int i)
{
	if (i < (rule.size() + 1) && rule[i] == '=' && rule[i + 1] == '>')
	{
		i = i + 2;
	}
	else if (i < (rule.size() + 2) && rule[i] == '<' && rule[i + 1] == '=' && rule[i + 2] == '>')
		i = i + 3;
	else
		return -1; //systaxe error sur la rule 
}

int Rules::getNumber(string rule, int type, int i)
{
	while (i < rule.size() && rule[i] != '=' && rule[i] != '<' && rule[i] != '#')
	{
		if (isupper(rule[i])) // voir ici comment gerer les parentheses
		{
			if (type == 1)
				m_condition.push_back(rule[i]);
			else if (type == 2)
				m_conclusion.push_back(rule[i]);
			if (isupper(rule[i]))  // on recheck parce que on va vir comment gerer les parentheses
				m_facts.push_back(rule[i]);
		}
		i++;
	}
}

int Rules::getOperator(string rule, int type, int i)
{
	while (i < rule.size() && rule[i] != '=' && rule[i] != '<' && rule[i] != '#')
	{
		if (rule[i] == '+' || rule[i] == '|' || rule[i] == '^')
		{
			if (type == 1)
				m_conditionType.push_back(rule[i]);
			else if (type == 2 && rule[i] != '|' && rule[i] != '^')
				m_conclusionType.push_back(rule[i]);
			else
			{
				return -1;
			}
			
		}
	}

}

Rules::Rules(string rule)
{
	int i;

	i = 0;
	impORif = 0;
	status = 0;
	rule.erase(std::remove(rule.begin(), rule.end(), ' '), rule.end());
	if (getNumber(rule, 1, i) < 0) //type 1 pour les conditions
		return ;
	if ( (i = getOperator(rule, 2, i)) < 0);
		return;
	if ( (i = getImpORif(rule, i)) < 0);
		return;
	if (getNumber(rule, 2, i) < 0) //type 2 pour les conclusions
		return;
	if (getOperator(rule, 2, i) < 0) //type 2 pour les conclusions
		return ;
	status = 1;
	// while (i < rule.size() && rule[i] != '=' && rule[i] != '<' && rule[i] != '#')
	// {
	// 	if (i < (rule.size() + 1) && rule[i] == '!' && isupper(rule[i + 1]))
	// 	{
	// 		i++;
	// 		m_condition.push_back(rule[i] * -1);
// 
	// 	}
	// 	else if (isupper(rule[i]) || (rule[i] == '(' && isupper(rule[i + 1])) || (rule[i] == ')' && isupper(rule[i - 1])) )
	// 	{
	// 		m_condition.push_back(rule[i]);
	// 		if (isupper(rule[i]))
	// 			m_facts.push_back(rule[i]);
	// 	}
	// 	else if (rule[i] == '+' || rule[i] == '|' || rule[i] == '^')
	// 		m_conditionType.push_back(rule[i]);
	// 	else
	// 		return; // error dans la regle on laisse le status a 0
	// 	i++;
	// }
	// impORif = rule[i];
	// if (i < (rule.size() + 1) && rule[i] == '=' && rule[i + 1] == '>')
	// {
	// 	i = i + 2;
	// }
	// else if (i < (rule.size() + 2) && rule[i] == '<' && rule[i + 1] == '=' && rule[i + 2] == '>')
	// 	i = i + 3;
	// else
	// 	return; //systaxe error sur la rule 
	// while (i < rule.size() && rule[i] != '#')
	// {
	// 	if (i < (rule.size() + 1) && rule[i] == '!' && isupper(rule[i + 1]))
	// 	{
	// 		i++;
	// 		m_conculsion.push_back(rule[i] * -1);
// 
	// 	}
	// 	else if (isupper(rule[i]) || (rule[i] == '(' && isupper(rule[i + 1])) || (rule[i] == ')' && isupper(rule[i - 1])))
	// 	{
	// 		m_conculsion.push_back(rule[i]);
	// 		if (isupper(rule[i]))
	// 			m_facts.push_back(rule[i]);
	// 	}
	// 	else if (rule[i] == '+') // no or ou xor in rule cest bonus - || rule[i] == '|' || rule[i] == '^')
	// 		m_conclusionType.push_back(rule[i]);
	// 	else
	// 		return; // error dans la regle on laisse le status a 0
	// 	i++;
	// }
}



void Rules::printValues()
{
	std::cout << "ID : " << id << std::endl;
	for (int i = 0; i < m_condition.size(); i++)
	{
		std::cout << "char(m_condition[i] : " << char(m_condition[i]) << std::endl;
		std::cout << "m_condition[i] : " << m_condition[i] << std::endl;
	}
	for (int i = 0; i < m_conditionType.size(); i++)
	{
		std::cout << "char(m_conditionType[i] : " << char(m_conditionType[i]) << std::endl;
		std::cout << "m_conditionType[i] : " << m_conditionType[i] << std::endl;
	}
	for (int i = 0; i < m_conculsion.size(); i++)
	{
		std::cout << "char(m_conculsion[i] : " << char(m_conculsion[i]) << std::endl;
		std::cout << "m_conculsion[i] : " << m_conculsion[i] << std::endl;
	}
	for (int i = 0; i < m_conclusionType.size(); i++)
	{
		std::cout << "char(m_conclusionType[i] : " << char(m_conclusionType[i]) << std::endl;
		std::cout << "m_conclusionType[i] : " << m_conclusionType[i] << std::endl;
	}
	std::cout << "impORif : " << impORif << std::endl;
}

void Rules::printFacts()
{
	for (int i = 0; i < m_facts.size(); i++)
	{
		std::cout << "m_fact[i] : " << m_facts[i] << std::endl;
	}
	std::cout << "    " << std::endl;
}

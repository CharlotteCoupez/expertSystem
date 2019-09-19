#include <iostream>
#include "Rules.h"
#include <stdlib.h>
#include <cctype>

using namespace std;

Rules::Rules(string rule)
{
	//ruleing rule = deleteSpace(rule);
	// std::cout << "rule : " << rule << std::endl;
	rule.erase(std::remove(rule.begin(), rule.end(), ' '), rule.end());
	// std::cout << "rule : " << rule << std::endl;

	impORif = 0;
	int i = 0;
	while (i < rule.size() && rule[i] != '=' && rule[i] != '<' && rule[i] != '#')
	{
		if (rule[i] == '!')
		{
			i++;
			m_condition.push_back(rule[i] * -1);

		}
		else if (isupper(rule[i]))
		{
			m_condition.push_back(rule[i]);
			m_facts.push_back(rule[i]);
		}
		else if (rule[i] == '+' || rule[i] == '|' || rule[i] == '^' || rule[i] == '!')
		{
			m_conditionType.push_back(rule[i]);
		}
		i++;
	}
	impORif = rule[i];
	while (i < rule.size() && rule[i] != '#')
	{
		if (rule[i] == '!')
		{
			i++;
			m_conculsion.push_back(rule[i] * -1);

		}
		else if (isupper(rule[i]))
		{
			m_conculsion.push_back(rule[i]);
			m_facts.push_back(rule[i]);
		}
		else if (rule[i] == '+' || rule[i] == '|' || rule[i] == '^' || rule[i] == '!')
			m_conclusionType.push_back(rule[i]);
		i++;
	}
}

void Rules::parseRule(string rule, std::vector<char> values, std::vector<char> type)
{
		std::cout << "parseRule " << std::endl;

}

void Rules::printValues()
{
	std::cout << "ID : " << id << std::endl;
	for (int i = 0; i < m_condition.size(); i++)
	{
		std::cout << "m_condition[i] : " << m_condition[i] << std::endl;
	}
	for (int i = 0; i < m_conditionType.size(); i++)
	{
		std::cout << "m_conditionType[i] : " << m_conditionType[i] << std::endl;
	}
	for (int i = 0; i < m_conculsion.size(); i++)
	{
		std::cout << "m_conculsion[i] : " << m_conculsion[i] << std::endl;
	}
	for (int i = 0; i < m_conclusionType.size(); i++)
	{
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

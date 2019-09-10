#include <iostream>
#include "Rules.h"
#include <stdlib.h>

using namespace std;

Rules::Rules(string rule)
{
	std::cout << "rules 1: " << rule << std::endl;
	impORif = 0;
	int i = 0;
	while (i < rule.size() && rule[i] != '=' && rule[i] != '<')
	{
		if (isupper(rule[i]))
		{
			// std::cout << "dans is upper : " << rule[i] << "--i : " << i << std::endl;
			m_condition.push_back(rule[i]);
			// std::cout << "isupper: " << rule[i] << std::endl;
		}
		else if (rule[i] == '+' || rule[i] == '|' || rule[i] == '^' || rule[i] == '!')
		{
			m_conditionType.push_back(rule[i]);
			// std::cout << "dans if type : " << rule[i] << "--i : " << i << std::endl;
		}
		// else
			// std::cout << "Wrong input sortir et ne pas creer obj1: " << rule[i] << "--i : " << i << std::endl;
		i++;
	}
	std::cout << "rule[i]1b impORif : " << rule[i] << "--i : "<< i << std::endl;
	impORif = rule[i];
	while (i < rule.size() && rule[i] != '#')
	{
		if (isupper(rule[i]))
			m_conculsion.push_back(rule[i]);
		else if (rule[i] == '+' || rule[i] == '|' || rule[i] == '^' || rule[i] == '!')
			m_conclusionType.push_back(rule[i]);
		// else
		// 	std::cout << "Wrong input sortir et ne pas creer obj2: " << std::endl;
		i++;
	}
	std::cout << "rules 2: " << std::endl;
	printValues();
	std::cout << "rules 2: " << std::endl;
}

int Rules::parseRule(string rule, std::vector<char> values, std::vector<char> type)
{

}

void Rules::printValues()
{
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

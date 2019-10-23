#include <iostream>
#include "Rules.h"
#include <stdlib.h>
#include <cctype>

using namespace std;

int Rules::getImpORif(string rule, int i)
{
	std::cout << "get imporif: " << std::endl;
	impORif = rule[i];
	if (i < (rule.size() + 1) && rule[i] == '=' && rule[i + 1] == '>')
		return i + 2;
	else if (i < (rule.size() + 2) && rule[i] == '<' && rule[i + 1] == '=' && rule[i + 2] == '>')
		return i + 3;
	return -1; //systaxe error sur la rule
}

int Rules::notationPolonaise(string rule, int i)
{
	int		len;
	while (i < rule.size() && rule[i] !='<' && rule[i] != '=' && rule[i] != '#')
	{
		len = m_polonaiseTmp.size();
		if (rule[i] == '!')
			m_polonaise.push_back(rule[i]);
		else if (isupper(rule[i]))
		{
			m_polonaise.push_back(rule[i]);
			m_facts.push_back(rule[i]);
		}
		else if (rule[i] == '(')
			m_polonaiseTmp.push_back(rule[i]);
		else if (rule[i] == ')')
		{
			while (m_polonaiseTmp[len - 1] != '(')
			{
				m_polonaise.push_back(m_polonaiseTmp[len -1]);
				m_polonaiseTmp.erase(m_polonaiseTmp.begin()+ (len -1), m_polonaiseTmp.end());
				len = m_polonaiseTmp.size();
			}
			m_polonaiseTmp.erase(m_polonaiseTmp.begin() + (len - 1), m_polonaiseTmp.end());

		}
		else if(rule[i] == '+' || rule[i] == '|' || rule[i] == '^')
		{
			if (len == 0)
				m_polonaiseTmp.push_back(rule[i]);
			else
			{
				if (m_polonaiseTmp[len - 1] == '(')
					m_polonaiseTmp.push_back(rule[i]);
				else if (rule[i] =='+')
				{
					m_polonaiseTmp.push_back(rule[i]);
				}
				else if (rule[i] == '|')
				{
					while (m_polonaiseTmp[len -1] == '+')
					{
						m_polonaise.push_back(m_polonaiseTmp[len - 1]);
						m_polonaiseTmp.erase(m_polonaiseTmp.begin() + (len - 1), m_polonaiseTmp.end());
						len--;
					}
					m_polonaiseTmp.push_back(rule[i]);

				}
				else if (rule[i] == '^')
				{
					while (m_polonaiseTmp[len -1] == '|' || m_polonaiseTmp[len -1] == '+')
					{
						m_polonaise.push_back(m_polonaiseTmp[len - 1]);
						m_polonaiseTmp.erase(m_polonaiseTmp.begin()+ (len - 1), m_polonaiseTmp.end());
						len--;
					}
					m_polonaiseTmp.push_back(rule[i]);
				}
			}
		}
		i++;
	}
	while (m_polonaiseTmp.size() > 0)
	{
		if (m_polonaiseTmp[len -1] != '(')
		{
			m_polonaise.push_back(m_polonaiseTmp[len -1]);
		}
		m_polonaiseTmp.erase(m_polonaiseTmp.begin()+ (len -1), m_polonaiseTmp.end());
		len = m_polonaiseTmp.size();
	}
	return i;
}

int Rules::check_format(string rule, int i, int bracket)
{
	std::cout << "bracket " << bracket << std::endl;
	std::cout << "checkformat" << std::endl;
	while (i < rule.size())
	{
		std::cout << "i" << i << std::endl;
		std::cout << "rule[i]" << rule[i] << std::endl;
		if (rule[i] == ')')
		{
			std::cout << "bracket in if" << bracket << std::endl;
			if (bracket == 1)
			{
				std::cout << "rule[i + 1] " << rule[i + 1] << std::endl;
				if (i + 1 < rule.size() && (rule[i + 1] == '(' || isupper(rule[i + 1])))
					return RULE_ERROR;
				return i;
			}
			return RULE_ERROR; //error
		}
		else if (isupper(rule[i]))
		{
			std::cout << "rule[i + 1] " << rule[i + 1] << std::endl;

			if (i + 1 < rule.size() && (rule[i + 1] != '+' && rule[i + 1] != '|' && rule[i + 1] != '^' && rule[i + 1] != ')' && rule[i + 1] != '=' && rule[i + 1] != '<'))
				{
					std::cout << "error A" << std::endl;
					return RULE_ERROR; //error
				}
		}
		else if (rule[i] == '!' || rule[i] == '+' || rule[i] == '|' || rule[i] == '^')
		{
			if (i + 1 >= rule.size() && !isupper(rule[i + 1]) && rule[i] != '(')
			{
				std::cout << "error B" << std::endl;
				return RULE_ERROR; //error
			}
		}
		else if (rule[i] == '=' || rule[i] == '<')
		{
			i = rule[i] == '=' ? i + 2 : i + 3;
			if (check_format(rule, i, bracket) != -2)
			{
				std::cout << "error C" << std::endl;
				return RULE_ERROR; //error
			}
		}
		else if (rule[i] == '(')
		{
			i = check_format(rule, i + 1, 1);
			//std::cout << "ret" << ret << std::endl;
			if (i == RULE_ERROR)
			{
				std::cout << "error D" << std::endl;
				return RULE_ERROR; //error
			}
			std::cout << "--avw----------rule[i]" << rule[i] << std::endl;
			std::cout << "--avw----------i" << i << std::endl;
			std::cout << "------------rule[i]" << rule[i] << std::endl;
			std::cout << "------------i" << i << std::endl;
			std::cout << "-bracket" << bracket << std::endl;
		}
		i++;
		std::cout << "i" << i << std::endl;
	}
	if (bracket == 1)
		return RULE_ERROR;
	return RULE_OK;
}

Rules::Rules(string rule)
{
	int i;
	int ret;

	i = 0;
	impORif = 0;
	status = 0;
	rule.erase(std::remove(rule.begin(), rule.end(), ' '), rule.end());
	ret = check_format(rule, 0, 0);
	std::cout << "ret : " << ret << std::endl;
	if (ret != RULE_OK)
	{
		std::cout << "checkformat ret 0" << std::endl;
		status = 0;
		return;
	}
	std::cout << "checkformat ret 1" << std::endl;

	i = notationPolonaise(rule, i);
	putInCondition();
	if ( (i = getImpORif(rule, i)) < 0)
		return;
	notationPolonaise(rule, i);
	putInConclusion();
	status = 1;
}

void Rules::putInCondition()
{
	for (int i = 0; i < m_polonaise.size(); i++)
	{
		m_condition.push_back(m_polonaise[i]);
	}
	m_polonaise.erase(m_polonaise.begin(), m_polonaise.end());
}

void Rules::putInConclusion()
{
	for (int i = 0; i < m_polonaise.size(); i++)
	{
		m_conclusion.push_back(m_polonaise[i]);
	}
	m_polonaise.erase(m_polonaise.begin(), m_polonaise.end());
}

void Rules::printValues()
{
	std::cout << "ID : " << id << std::endl;
	for (int i = 0; i < m_condition.size(); i++)
	{
		std::cout << "char(m_condition[i] : " << char(m_condition[i]) << std::endl;
		//std::cout << "m_condition[i] : " << m_condition[i] << std::endl;
	}
	for (int i = 0; i < m_conditionType.size(); i++)
	{
		std::cout << "char(m_conditionType[i] : " << char(m_conditionType[i]) << std::endl;
		//std::cout << "m_conditionType[i] : " << m_conditionType[i] << std::endl;
	}
	for (int i = 0; i < m_conclusion.size(); i++)
	{
		std::cout << "char(m_conculsion[i] : " << char(m_conclusion[i]) << std::endl;
		//std::cout << "m_conculsion[i] : " << m_conclusion[i] << std::endl;
	}
	for (int i = 0; i < m_conclusionType.size(); i++)
	{
		std::cout << "char(m_conclusionType[i] : " << char(m_conclusionType[i]) << std::endl;
		//std::cout << "m_conclusionType[i] : " << m_conclusionType[i] << std::endl;
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

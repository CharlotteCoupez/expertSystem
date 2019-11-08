/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:29:11 by ccoupez           #+#    #+#             */
/*   Updated: 2019/10/23 16:29:11 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Rules.h"

using namespace std;

Rules::Rules(string rule)
{
	int i;

	impORif = 0;
	status = 0;
	rule.erase(std::remove(rule.begin(), rule.end(), ' '), rule.end());
	if (check_format(rule, 0, 0) != RULE_OK)
		return;
	i = notationPolonaise(rule, 0);
	putInCondition();
	if ( (i = getImpORif(rule, i)) < 0)
		return;
	notationPolonaise(rule, i);
	putInConclusion();
	status = 1;
}


int		Rules::check_format(string rule, int i, int bracket)
{
	while (i < rule.size())
	{
		if (rule[i] == ')')
		{
			if (bracket == 1)
			{
				if (i + 1 < rule.size() && !isOperator(rule[i + 1]) && !isRelationOp(rule[i + 1]))
					return RULE_ERROR;
				return i;
			}
			return RULE_ERROR;
		}
		else if (isupper(rule[i]))
		{
			if (i + 1 < rule.size() && !isOperator(rule[i + 1]) && !isRelationOp(rule[i + 1]) && rule[i + 1] != ')' )
				return RULE_ERROR;
		}
		else if (rule[i] == '!' || isOperator(rule[i]))
		{
			if (i + 1 < rule.size() && (isOperator(rule[i + 1]) || rule[i + 1] == ')'))
				return RULE_ERROR;
		}
		else if (isRelationOp(rule[i]))
		{
			i = rule[i] == '=' ? i + 2 : i + 3;
			if (check_format(rule, i, bracket) != RULE_OK)
				return RULE_ERROR;
		}
		else if (rule[i] == '(')
		{
			i = check_format(rule, i + 1, 1);
			if (i == RULE_ERROR)
				return RULE_ERROR;
		}
		i++;
	}
	if (bracket == 1)
		return RULE_ERROR;
	return RULE_OK;
}

int Rules::notationPolonaise(string rule, int i)
{
	int		len;
	char	op;

	while (i < rule.size() && !isRelationOp(rule[i]) && rule[i] != '#')
	{
		len = m_polonaiseTmp.size();
		if (rule[i] == '!' || isupper(rule[i]))
			m_polonaise.push_back(rule[i]);
		else if (rule[i] == '(')
			m_polonaiseTmp.push_back(rule[i]);
		else if (rule[i] == ')')
		{
			while (m_polonaiseTmp[len - 1] != '(')
			{
				m_polonaise.push_back(m_polonaiseTmp[len - 1]);
				m_polonaiseTmp.erase(m_polonaiseTmp.begin() + (len - 1), m_polonaiseTmp.end());
				len--;
			}
			m_polonaiseTmp.erase(m_polonaiseTmp.begin() + (len - 1), m_polonaiseTmp.end());

		}
		else if(isOperator(rule[i]))
		{
			if (len == 0 || m_polonaiseTmp[len - 1] == '(' || rule[i] =='+')
				m_polonaiseTmp.push_back(rule[i]);
			else
			{
				if (rule[i] == '|')
					op = 0;
				else if (rule[i] == '^')
					op = 1;
				while (opPriorities(m_polonaiseTmp[len -1], op))
				{
					m_polonaise.push_back(m_polonaiseTmp[len - 1]);
					m_polonaiseTmp.erase(m_polonaiseTmp.begin() + (len - 1), m_polonaiseTmp.end());
					len--;
				}
				m_polonaiseTmp.push_back(rule[i]);
			}
		}
		i++;
	}
	while (m_polonaiseTmp.size() > 0)
	{
		if (m_polonaiseTmp[len -1] != '(')
			m_polonaise.push_back(m_polonaiseTmp[len - 1]);
		m_polonaiseTmp.erase(m_polonaiseTmp.begin()+ (len - 1), m_polonaiseTmp.end());
		len--;
	}
	return i;
}

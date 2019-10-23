/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruleChecking.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:28:20 by ccoupez           #+#    #+#             */
/*   Updated: 2019/10/23 19:00:06 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ExpertSystem.h"

using namespace std;

int		ExpertSystem::ruleChecking(vector<int> condition)
{
	if (condition.size() == 1 || (condition[0] == '!' && condition.size() == 2))
		return oneCondition(condition);
	return severalConditions(condition);
}


int		ExpertSystem::severalConditions(vector<int> condition)
{
	int			nb;
	int		 	ret = 0;
	int			result;
	const char	*rstr;
	const char	str [] = "+|^";

	for (size_t i = 0; i < condition.size(); i++)
	{
		rstr = strchr(str, condition[i]);
		if (rstr != NULL && *rstr != 0)
		{
			ret = getResult(condition, i);
			if (ret == NOT_PROVEN)
			{
				if (checkNextOperator(condition, i + 1) != 1)
					return NOT_PROVEN;
				else
					result = 0;
			}
			else
				result = 1;
			condition.insert(condition.begin() + i + 1, result);
			nb = nbToErase(condition,i);
			condition.erase(condition.begin() + i - nb, condition.begin() + i + 1 );
			if (condition.size() > 1)
				i = 0;
		}
	}
	return ret;
}


int ExpertSystem::getResult(std::vector<int> condition, size_t i)
{
	bool					factA;
	bool					factB;
	vector<vector<int> >	array;

	getNegative(condition, &array, i);
	factA = getFact(array[1][0]);
	factB = getFact(array[0][0]);
	if (condition[i] == '+')
		return andCondition(factA, factB, array, i);
	else if (condition[i] == '|')
		return orCondition(factA, factB, array, i);
	else if (condition[i] == '^')
		return xorCondition(factA, factB, array, i);
	return 0;
}


int		ExpertSystem::orCondition(bool a, bool b, std::vector<std::vector<int> > array, int i)
{
	if (a == false && array[1][0] != 0)
	{
		// RECHERCHER DANS FALSE FACT AVANT BACKWARD
		a = backwardChaining(array[1][0]);
	}
	if (condition(a, array[1][1]))
		return PROVEN;
	if (b == false && array[0][0] != 0)
	{
		// RECHERCHER DANS FALSE FACT AVANT BACKWARD
		b = backwardChaining(array[0][0]);
	}
	if (condition(b, array[0][1]))
		return PROVEN;
	return NOT_PROVEN;
}


int		ExpertSystem::xorCondition(bool a, bool b, std::vector<std::vector<int> > array, int i)
{
	if (a == false && array[1][0] != 0)
	{
		// RECHERCHER DANS FALSE FACT AVANT BACKWARD
		a = backwardChaining(array[1][0]);
	}
	if (b == false && array[0][0] != 0)
	{
		// RECHERCHER DANS FALSE FACT AVANT BACKWARD
		b = backwardChaining(array[0][0]);
	}
	if (condition(a, array[1][1]) ^ condition(b, array[0][1]))
		return PROVEN;
	return NOT_PROVEN;
}


int		ExpertSystem::andCondition(bool a, bool b, std::vector<std::vector<int> > array, int i)
{
	if (a == false && array[1][0] != 0)
	{
		// RECHERCHER DANS FALSE FACT AVANT BACKWARD
		a = backwardChaining(array[1][0]);
	}
	if (b == false && array[0][0] != 0)
	{
		// RECHERCHER DANS FALSE FACT AVANT BACKWARD
		b = backwardChaining(array[0][0]);
	}
	if (condition(a, array[1][1]) && condition(b, array[0][1]))
		return PROVEN;
	return NOT_PROVEN;
}


int		ExpertSystem::oneCondition(vector<int> condition)
{
	size_t				 	i;
	bool					ret;
	std::set<int>::iterator	fact;

	i = 0;
	fact = find(m_trueFacts.begin(), m_trueFacts.end(), condition[condition.size() - 1]);
	if (*fact == condition[condition.size() - 1] || condition[condition.size() - 1] == 1)
	{
		if (condition[0] != '!')
			return PROVEN;
	}
	// RECHERCHER DANS FALSE FACT AVANT BACKWARD
	ret = backwardChaining(condition[condition.size() - 1]);
	if (ret == false && condition[0] != '!')
		return NOT_PROVEN;
	return PROVEN;
}

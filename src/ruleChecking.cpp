/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruleChecking.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:28:20 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/13 17:40:19 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ExpertSystem.h"

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

/*
** get fact return 0  1  2
** 0 it is proven that the condition is false
** 1 it is proven that the condition is true
** 2 we dont know, we maybe will need a backwardchaining
*/
int ExpertSystem::getResult(std::vector<int> condition, size_t i)
{
	int						factA;
	int						factB;
	vector<vector<int> >	array;

	getNegative(condition, &array, i);
	factA = getFact(array[1][0], array[1][1]);
	factB = getFact(array[0][0], array[0][1]);
	if (condition[i] == '+')
		return andCondition(factA, factB, array);
	else if (condition[i] == '|')
		return orCondition(factA, factB, array);
	else if (condition[i] == '^')
		return xorCondition(factA, factB, array);
	return 0;
}


int		ExpertSystem::orCondition(int a, int b, std::vector<std::vector<int> > array)
{
	if (a == 1 || b == 1)
		return PROVEN;
	else if (a == 0 && b == 0)
		return NOT_PROVEN;
	if (a == 2)
		a = backwardChaining(array[1][0]);
	if (condition(a, array[1][1]))
		return PROVEN;
	if (b == 2)
		b = backwardChaining(array[0][0]);
	if (condition(b, array[0][1]))
		return PROVEN;
	return NOT_PROVEN;
}


int		ExpertSystem::xorCondition(int a, int b, std::vector<std::vector<int> > array)
{
	if (a == 1 && b == 1)
		return NOT_PROVEN;
	else if (a == 0 && b == 0)
		return NOT_PROVEN;
	if (a == 2)
		a = backwardChaining(array[1][0]);
	if (b == 2)
		b = backwardChaining(array[0][0]);
	if (condition(a, array[1][1]) ^ condition(b, array[0][1]))
		return PROVEN;
	return NOT_PROVEN;
}

// int		ExpertSystem::andCondition(int a, int b, std::vector<std::vector<int> > array)
// {
// 	if (a == 1 && b == 1)
// 		return PROVEN;
// 	else if (a == 0 || b == 0)
// 		return NOT_PROVEN;
// 	if (a != 2 && b != 2)
// 	{
// 		a = backwardChaining(array[1][0]);
// 		if (a && b == 2)
// 			b = backwardChaining(array[0][0]);
// 	// if (b == 2)
// 		if (condition(a, array[1][1]) && condition(b, array[0][1]))
// 			return PROVEN;
// 	}
// 	return NOT_PROVEN;
// }
int		ExpertSystem::andCondition(int a, int b, std::vector<std::vector<int> > array)
{
	if (a == 1 && b == 1)
		return PROVEN;
	else if (a == 0 || b == 0)
		return NOT_PROVEN;
	if (a == 2)
		a = backwardChaining(array[1][0]);
	if (b == 2)
		b = backwardChaining(array[0][0]);
	if (condition(a, array[1][1]) && condition(b, array[0][1]))
		return PROVEN;
	if (!checking)
	{
		if (conditionProvenFalse(a, array[1][1]) && conditionProvenFalse(b, array[0][1]))
			return PROVEN_FALSE;
	}
	return NOT_PROVEN;
}


int		ExpertSystem::oneCondition(vector<int> condition)
{
	bool	ret;

	if (find_in_set(condition[condition.size() - 1], m_trueFacts) != -1)
	{
		if (condition[0] != '!')
		{
			return PROVEN;
		}
		else
		{
			return PROVEN_FALSE;
		}
	}
	if (find_in_set(condition[condition.size() - 1], m_falseFacts) != -1)
	{
		if (condition[0] == '!')
		{
			return PROVEN;
		}
		else
		{
			return PROVEN_FALSE;
		}
	}
	ret = backwardChaining(condition[condition.size() - 1]);
	if (ret == false && condition[0] != '!')
	{
		return PROVEN_FALSE;
	}
	return PROVEN;
}

#include "ExpertSystem.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;
/* règles des retours :
ret -1  OK fait validé on met dans true fact
ret -3  On continue de chercher

ret fact on renvoie une nouvelle querie pour le backwardChainning   */

int ExpertSystem::ruleChecking(vector<int> condition, vector<int> conclusion) // type cest pour if and only if donc est ce quon checher les conclu ou les conditions
{
	int i;
	int ret;

	if (condition.size() == 1 || (condition[0] == '!' && condition.size() == 2))
		return oneCondition(condition, conclusion);
	ret = severalConditions(condition);
	if (ret == -1)
	{
		std::cout << "conclusion[i] - 1: " << char(conclusion[i]) << std::endl;
		i  = 0;
		while (isupper(conclusion[i]))
		{
			m_trueFacts.insert(conclusion[i]);
			i++;
		}
	}
	if (ret == -2)
	{
		std::cout << "conclusion[i] - 2: " << char(conclusion[0]) << std::endl;
		i  = 0;
		while (isupper(conclusion[i]))
		{
			m_falseFacts.insert(conclusion[i]);
			i++;
		}
	}
	std::cout << "----------------------ret diff de - 1: " << ret << std::endl;

	return ret;
}

int		nbToErase(std::vector<int> condition, int i)
{
	if (isupper(condition[i - 2]) || condition[i - 2] == 0 || condition[i - 2] == 1)
		return 2;
	else if (condition[i - 2] == '!' && (i < 4 || condition[i - 4] != '!'))
		return 3; // A negatif
	else if (isupper(condition[i - 2]) && i >= 3 && condition[i - 3] == '!')
		return 3; // B negatif
	else if (condition[i - 2] == '!' && i >= 4 && condition[i - 4] == '!')
		return 4; // A et B negatif
	return 0;
}

int ExpertSystem::severalConditions(vector<int> condition)
{
	int			nb;
	int		 	ret = 0;
	int			result = 0;
	const char	*rstr;
	const char	str [] = "+|^";

	for (size_t i = 0; i < condition.size(); i++)
	{
		rstr = strchr(str, condition[i]);
		if (rstr != NULL && *rstr != 0)
		{
			ret = getResult(condition, i);
			if (ret == -3)
			{
				if (checkNextOperator(condition, i + 1) != 1)
					return -2;
				else
					result = 0;
			}
			else if (ret == -1)
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

int ExpertSystem::getNegative(std::vector<int> condition, std::vector<std::vector<int> > *array, int i)
{
	// for (int i = 0; i < condition.size(); i++)
	// {
	// 	if (condition[i] < 50)
	// 		std::cout << "condition1 : " << condition[i] << std::endl;
	// 	else
	// 		std::cout << "condition1 : " << char(condition[i]) << std::endl;
	// }
	// std::cout << "getNegative i avant : " << i << std::endl;
	i = getConditionValue(condition, array, i);
	getConditionValue(condition, array, i);
	return 0;
}

int ExpertSystem::getConditionValue(std::vector<int> condition, std::vector<std::vector<int> > *array, int i)
{
	vector<int> tmp;
	tmp.push_back(condition[i - 1]);
	if (i - 2 >= 0 && condition[i - 2] == '!') {
		tmp.push_back(-1);
	} else {
		tmp.push_back(1);
	}
	(*array).push_back(tmp);

	return (i - 2 >= 0 && condition[i - 2] == '!' ? i - 2 : i - 1);
}

bool	ExpertSystem::getFact(int array_value)
{
	std::set<int>::iterator ret;
	if (isupper(char(array_value)))
	{
        ret = find(m_trueFacts.begin(), m_trueFacts.end(), array_value);
		// if (*ret == array_value)
		// 	return 1;
		// return 0;
		return *ret == array_value;
	}
	else
		return array_value;

}

int ExpertSystem::getResult(std::vector<int> condition, size_t i)
{
	int						neg;
	std::set<int>::iterator retA;
	std::set<int>::iterator retB;
	bool					factA = false;
	bool					factB = false;
	vector<vector<int> >	array;

	getNegative(condition, &array, i);
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i][0] < 50)
			std::cout << "array[i][0]: " << array[i][0] << std::endl;
		else
			std::cout << "char(array[i][0]: " << char(array[i][0]) << std::endl;
		std::cout << "array[i][1]: " << array[i][1] << std::endl;
	}
	factA = getFact(array[1][0]);
	std::cout << "factA: " << factA << std::endl;
	factB = getFact(array[0][0]);
	std::cout << "factB: " << factB << std::endl;

	if (condition[i] == '+')
		return andCondition(factA, factB, array, i);
	else if (condition[i] == '|')
		return orCondition(factA, factB, array, i);
	else if (condition[i] == '^')
		return xorCondition(factA, factB, array, i);
	return 0;
}

bool	condition(bool a, int neg)
{
	if (a == 1 && neg == 1)
		return 1;
	if (a == 1 && neg == -1)
		return 0;
	if (a == 0 && neg == 1)
		return 0;
	if (a == 0 && neg == -1)
		return 1;
	return 0;
}

int	ExpertSystem::xorCondition(bool a, bool b, std::vector<std::vector<int> > array, int i)
{
	//std::cout << "XOR a " << a << std::endl;
	//std::cout << "XOR b " << b << std::endl;
	//std::cout << "condition[i - neg] " << char(condition[i - 2]) << std::endl;
	//std::cout << "condition[i -1] " << char(condition[i - 1]) << std::endl;
	if (a != 1 && array[1][0] != 0)
		a = backwardChaining(array[1][0]);
	if (b != 1 && array[0][0] != 0)
		b = backwardChaining(array[0][0]);

	if (condition(a, array[1][1]) ^ condition(b, array[0][1]))
		return -1;
	else
		return -3;
}

int ExpertSystem::orCondition(bool a, bool b, std::vector<std::vector<int> > array, int i)
{
	int ret;
	//std::cout << "OR a " << a << std::endl;
	//std::cout << "OR b " << b << std::endl;
	//std::cout << "condition[i -2] " << char(condition[i - neg]) << std::endl;
	//std::cout << "condition[i -1] " << char(condition[i - 1]) << std::endl;
	//std::cout << "condition[i -2] " << condition[i - neg] << std::endl;
	//std::cout << "condition[i -1] " << condition[i - 1] << std::endl;
	if (condition(a, array[1][1]) || condition(b, array[0][1]))
		return -1;
	if (array[1][0] == 0 && array[0][0] == 0)
		return -3;
	if (a == 0)
	{
		ret = backwardChaining(array[1][0]);
		if ((ret == 0 && array[1][1] == -1) || (ret == 1 && array[1][1] == 1 )) // faire une fonction pour ce 4 checking moche
			return -1;
	}
	if (b == 0)
	{
		ret = backwardChaining(array[0][0]);
		if ((ret == 0 && array[0][1] == -1) || (ret == 1 && array[0][1] == 1)) // faire une fonction pour ce 4 checking moche
			return -1;
	}
	return -3;
}

int ExpertSystem::andCondition(bool a, bool b, std::vector<std::vector<int> > array, int i)
{
	int ret;
	int	neg;

	neg = (array[1][0] == '!') ? 3 : 2;
	std::cout << "AND a " << a << std::endl;
	std::cout << "AND b " << b << std::endl;
	std::cout << "condition[i -2] " << char(array[1][0]) << std::endl;
	std::cout << "condition[i -1] " << char(array[0][0]) << std::endl;
	if (condition(a, array[1][1]) && condition(b, array[0][1]))
		return -1;
	
	if (array[1][0] == 0 || array[0][0] == 0)
		return -3;
	if (a == 0)
	{
		ret = backwardChaining(array[1][0]);
		if ((ret == 0 && array[1][1] == 1) || (ret == 1 && array[1][1] == -1 )) // faire une fonction pour ce 4 checking moche
			return -3;
	}
	if (b == 0)
	{
		ret = backwardChaining(array[0][0]);
		if ((ret == 0 && array[0][1] == 1) || (ret == 1 && array[0][1] == -1)) // faire une fonction pour ce 4 checking moche
			return -3;
	}
	return -1;
}


int ExpertSystem::oneCondition(vector<int> condition, vector<int> conclusion)
{
	size_t				 	i;
	int						ret;
	std::set<int>::iterator	fact;

	i = 0;
	fact = find(m_trueFacts.begin(), m_trueFacts.end(), condition[condition.size() - 1]);
	if (*fact == condition[condition.size() - 1] || condition[condition.size() - 1] == 1)
	{
		while (isupper(conclusion[i]))
		{
			m_trueFacts.insert(conclusion[i]);
			i++;
		}
		if (condition[0] == '!')
			return -3;
		return -1;
	}
	ret = backwardChaining(condition[condition.size() - 1]);
	if (ret == 0 && condition[0] != '!')
		return -3;
	m_trueFacts.insert(conclusion[i]);
	return -1;
}

int ExpertSystem::checkNextOperator(std::vector<int> condition, size_t i)
{
	int ret = 0;
	const char str[] = "+|^";
	const char *rstr;

	while (i < condition.size())
	{
		rstr = strchr(str, condition[i]);
		if (rstr != NULL)
		{
			if (*rstr != '+')
				ret = 1;
		}
		i++;
	}
	return ret;
}

/*
	for (int i = 0; i < condition.size(); i++)
	{
		std::cout << "condition1 : " << char(condition[i]) << std::endl;
	}

	std::cout << "condition.size() : " << condition.size() << std::endl;

	condition.insert(condition.begin() + 3, 1);
	std::cout << "apres insert : " << condition.size() << std::endl;
	for (int i = 0; i < condition.size(); i++)
	{
		//std::cout << "condition2 : " << condition[i] << std::endl;
		std::cout << "condition2 : " << char(condition[i]) << std::endl;
	}
	condition.erase(condition.begin() + (2 - 2), condition.begin() + 3); // (i - 2)  et (i + 1)

	std::cout << "condition.size() : " << condition.size() << std::endl;

	for (int i = 0; i < condition.size(); i++)
	{
		//std::cout << "condition2 : " << condition[i] << std::endl;
		std::cout << "condition3 : " << char(condition[i]) << std::endl;
	}


	return -2;
*/

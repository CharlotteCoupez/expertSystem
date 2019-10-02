#include "ExpertSystem.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;
/* règles des retours :
ret -1  OK fait validé on met dans true fact

ret -2  FALSE conclusion impossible (pour le moment cest seulement pour XOR quand les 2 facts existent)

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
		i  = 0;
		while (isupper(conclusion[i]))
		{
			m_trueFacts.insert(conclusion[i]);
			i++;
		}
		//std::cout << "ruleChecking ret : " << ret << std::endl;
	}
	return ret;
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
		if (rstr != NULL)
		{
			for (size_t j = 0; j < condition.size(); j++)
			{
				//std::cout << "condition1 : " << char(condition[j]) << std::endl;
				//std::cout << "condition1 : " << condition[j] << std::endl;
			}
			//std::cout << "fin " << std::endl;
			ret = getResult(condition, i);
			if (ret == -2)
				return -2; // IMPOSSIBLE XOR FALSE AVEC LES 2 CONDITIONS QUI EXISTE..
			else if (ret == -3)
			{
				//std::cout << "ret -3" << std::endl;
				if (checkNextOperator(condition, i + 1) != 1)
					return -2;
				else
					result = 0;
			}
			else if (ret == -1)
				result = 1;
			//std::cout << "result" << result << std::endl;
			condition.insert(condition.begin() + i + 1, result);
			nb = getNegative(condition,i);
			condition.erase(condition.begin() + i - nb, condition.begin() + i + 1 );
			if (condition.size() > 1)
				i = 0;
		}
	}
	//std::cout << "ret al fin de several condition : " << ret << std::endl;
	return ret;
}

int ExpertSystem::getNegative(std::vector<int> condition, int i)
{
	if (isupper(condition[i - 2]))
		return 2;
	else if (condition[i - 2] == '!' && (i < 4 || condition[i - 4] != '!'))
		return 3; // A negatif
	else if (isupper(condition[i - 2]) && i >= 3 && condition[i - 3] == '!')
		return 3; // B negatif
	else if (condition[i - 2] == '!' && i >= 4 && condition[i - 4] == '!')
		return 4; // A et B negatif
}

int ExpertSystem::getResult(std::vector<int> condition, size_t i)
{

	int						neg;
	std::set<int>::iterator retA;
	std::set<int>::iterator retB;
	bool					factA = false;
	bool					factB = false;

	getNegative(condition, i);
	neg = (condition[i - 2] == '!') ? 3 : 2;
	if (condition[i - neg] == 1 || condition[i - neg] == 0)
	{
		factA = condition[i - neg];
	}
	else if (condition[i - neg] != 1 || condition[i - neg] != 0)
	{
        retA = find(m_trueFacts.begin(), m_trueFacts.end(), condition[i - neg]);
		factA = *retA == condition[i - neg];
	}
	if (condition[i - 1] == 1 || condition[i - 1] == 0)
	{
		factB = condition[i - 1];
	}
	else if (condition[i - 1] != 1 || condition[i - 1] != 0)
	{
		retB = find(m_trueFacts.begin(), m_trueFacts.end(), condition[i - 1]);
		factB = *retB == condition[i - 1];
	}

	if (condition[i] == '+')
		return andCondition(factA, factB, condition, i);
	else if (condition[i] == '|')
		return orCondition(factA, factB, condition, i);
	else if (condition[i] == '^')
		return xorCondition(factA, factB, condition, i);
	return 0;
}

int	ExpertSystem::xorCondition(bool a, bool b, vector<int> condition, int i)
{
	int	neg;
	neg = (condition[i - 2] == '!') ? 3 : 2;
	//std::cout << "XOR a " << a << std::endl;
	//std::cout << "XOR b " << b << std::endl;
	//std::cout << "condition[i - neg] " << char(condition[i - 2]) << std::endl;
	//std::cout << "condition[i -1] " << char(condition[i - 1]) << std::endl;
	if (a != 1 && condition[i - neg] != 0)
		a = backwardChaining(condition[i - neg]);
	if (b != 1 && condition[i - 1] != 0)
		b = backwardChaining(condition[i - 1]);
	if (a ^ b)
		return -1;
	else if (a && b)
		return -2;
	else
		return -3;
}

int ExpertSystem::orCondition(bool a, bool b, vector<int> condition, int i)
{
	int ret;
	int	neg;
	neg = (condition[i - 2] == '!') ? 3 : 2;
	//std::cout << "OR a " << a << std::endl;
	//std::cout << "OR b " << b << std::endl;
	//std::cout << "condition[i -2] " << char(condition[i - neg]) << std::endl;
	//std::cout << "condition[i -1] " << char(condition[i - 1]) << std::endl;
	//std::cout << "condition[i -2] " << condition[i - neg] << std::endl;
	//std::cout << "condition[i -1] " << condition[i - 1] << std::endl;
	if (a || b)
		return -1;
	else if (condition[i - neg] != 0)
	{
		ret = backwardChaining(condition[i - neg]);  // NEGATIF A FAIRE
		//std::cout << "OR backwardChaining(v ret " << ret << std::endl;
		if (ret == 0)
		if (ret == 0 && condition[i - 1] != 0)
		{
			ret = backwardChaining(condition[i - 1]);  // NEGATIF A FAIRE
 
			//std::cout << "OR backwardChaining ret b " << ret << std::endl;
			if (ret == 0) //Querie false
				return -3;
			return -1; // ok on a trouvé
		}
		else if (ret == 1) // si a == 0 et b == 0 on renvoie -3 voir si il y a un autre ou apres sinn on renvera false apres
			return -1;
	}
	else if (condition[i - 1] != 0)
	{
		ret = backwardChaining(condition[i - 1]);
		if (ret == 1 && condition[i - 2] != '!')
			return -1;
	}
	return -3; // on renvoie -3 car on est dans ou
	// donc si il y a un ou apres on continue sinon en renvera false
}

int ExpertSystem::andCondition(bool a, bool b, vector<int> condition, int i)
{
	int ret;
	int	neg;

	neg = (condition[i - 2] == '!') ? 3 : 2;
	std::cout << "AND a " << a << std::endl;
	std::cout << "AND b " << b << std::endl;
	std::cout << "condition[i -2] " << char(condition[i - neg]) << std::endl;
	std::cout << "condition[i -1] " << char(condition[i - 1]) << std::endl;

	if (a && b)
		return -1;
	if (a != 1)
	{
		if (condition[i - neg] == 0)
			return -3;
		ret = backwardChaining(condition[i - neg]);
		//std::cout << "AND bc ret A " << ret << std::endl;
		if (ret == 0 && condition[i - neg - 1] != '!')
			return -3;
	}
	if (b != 1)
	{
		if (condition[i - 1] == 0)
			return -3;
		ret = backwardChaining(condition[i - 1]);
		//std::cout << "AND bc ret B " << ret << std::endl;
		if (ret == 0 && condition[i - 2] != '!')
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

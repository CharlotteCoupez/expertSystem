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
	int ret;
	if (condition.size() == 1)
		return oneCondition(condition, conclusion);
	else
	{
		ret = severalConditions(condition);
		if (ret == -1)
		{
			int i = 0;
			while (isupper(conclusion[i]))
			{
				m_trueFacts.insert(conclusion[i]);
				i++;
			}
			cout << "ruleChecking ret : " << ret << std::endl;
		}

		return ret;
	}

}

int ExpertSystem::severalConditions(vector<int> condition)
{
	int		 	ret = 0;
	const char	str [] = "+|^";
	const char	*rstr;

	for (int i = 0; i < condition.size(); i++)
	{
		rstr = strchr(str, condition[i]);
		if (rstr != NULL)
		{
			for (int j = 0; j < condition.size(); j++)
			{
				std::cout << "condition1 : " << char(condition[j]) << std::endl;
				std::cout << "condition1 : " << condition[j] << std::endl;
			}
			std::cout << "fin " << std::endl;

			ret = getResult(condition, i);
			if (isupper(char(ret)))
				return ret; // On relance la recherche avec une nouvelle querie
			else if (ret == -2)
				return -2; // IMPOSSIBLE XOR FALSE AVEC LES 2 CONDITIONS QUI EXISTE..
			else if (ret == -3)
			{
				cout << "ret -3" << std::endl;
				if (checkNextOperator(condition, i + 1) != 1)
					return -2;
				else
				{
					condition.insert(condition.begin() + (i + 1), 0);
					condition.erase(condition.begin() + (i - 2), condition.begin() + (i + 1));
					if (condition.size() > 1)
						i = 0;
				}
			}
			else if (ret == -1)
			{
				cout << "ret -1" << std::endl;
				condition.insert(condition.begin()+(i + 1), 1);
				condition.erase(condition.begin() + (i - 2), condition.begin()+ (i + 1) );
				if (condition.size() > 1)
					i = 0;
			}
		}
	}
	cout << "ret al fin de several condition : " << ret << std::endl;
	return ret; // Normalement soit -1 soit -3 ||  -1 TRUE -3 FALSE
}

int ExpertSystem::getResult(std::vector<int> condition, int i)
{
	int					 	ret = 0;
	std::set<int>::iterator retA;
	std::set<int>::iterator retB;
	bool					factA = false;
	bool					factB = false;

	if (condition[i - 2] == 1 || condition[i - 2] == 0)
	{
		factA = condition[i - 2];
	}
	else if (condition[i - 2] != 1 || condition[i - 2] != 0)
	{
        retA = find(m_trueFacts.begin(), m_trueFacts.end(), condition[i - 2]);
		factA = *retA == condition[i - 2];
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
	cout << "XOR a " << a << std::endl;
	cout << "XOR b " << b << std::endl;
	cout << "condition[i -2] " << char(condition[i - 2]) << std::endl;
	cout << "condition[i -1] " << char(condition[i - 1]) << std::endl;
	if (a != 1 && condition[i - 2] != 0)
		a = backwardChaining(condition[i - 2]);
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

	cout << "OR a " << a << std::endl;
	cout << "OR b " << b << std::endl;
	cout << "condition[i -2] " << char(condition[i - 2]) << std::endl;
	cout << "condition[i -1] " << char(condition[i - 1]) << std::endl;
	cout << "condition[i -2] " << condition[i - 2] << std::endl;
	cout << "condition[i -1] " << condition[i - 1] << std::endl;

	if (a || b)
		return -1;
	else if (condition[i - 2] != 0)
	{
		ret = backwardChaining(condition[i - 2]);
		cout << "OR backwardChaining(v ret " << ret << std::endl;

		if (ret == 0 && condition[i - 1] != 0)
		{
			ret = backwardChaining(condition[i - 1]);

			cout << "OR backwardChaining ret b " << ret << std::endl;
			if (ret == 0)
				return -3;
			else
				return -1; // ok on a trouvé
		}
		else if (ret != -1) // si a == 0 et b == 0 on renvoie -3 voir si il y a un autre ou apres sinn on renvera false apres
			return -1;
	}
	else if (condition[i - 1] != 0) // si a etait direct a 0 on cherche b de maniere normale
		return condition[i - 1];
	return -3; // on renvoie -3 car on est dans ou
	// donc si il y a un ou apres on continue sinon en renvera false
}

int ExpertSystem::andCondition(bool a, bool b, vector<int> condition, int i)
{
	int ret;
	cout << "AND a " << a << std::endl;
	cout << "AND b " << b << std::endl;
	cout << "condition[i -2] " << char(condition[i - 2]) << std::endl;
	cout << "condition[i -1] " << char(condition[i - 1]) << std::endl;
	if (a && b)
		return -1;
	if (a != 1)
	{
		if (condition[i -2] == 0)
			return -3;
		ret = backwardChaining(condition[i - 2]);
		cout << "AND bc ret A " << ret << std::endl;
		if (ret == 0)
			return -3;
	}
	if (b != 1)
	{
		if (condition[i - 1] == 0)
			return -3;
		ret = backwardChaining(condition[i - 1]);
		cout << "AND bc ret B " << ret << std::endl;
		if (ret == 0)
			return -3;
	}
	return -1;
}


int ExpertSystem::oneCondition(vector<int> condition, vector<int> conclusion)
{
	int					 	i;
	int						ret;
	std::set<int>::iterator	fact;

	i = 0;
	fact = find(m_trueFacts.begin(), m_trueFacts.end(), condition[0]);
	if (*fact == condition[0] || condition[0] == 1)
	{
		while (isupper(conclusion[i]))
		{
			m_trueFacts.insert(conclusion[i]);
			i++;
		}
		return -1;
	}
	ret = backwardChaining(condition[0]);
	if (ret == 0)
		return -3;
	return -1;
}

int ExpertSystem::checkNextOperator(std::vector<int> condition, int i)
{
	int ret = 0;
	const char str[] = "+|^";
	const char *rstr;

	for (i; i < condition.size(); i++)
	{
		rstr = strchr(str, condition[i]);
		if (rstr != NULL)
		{
			if (*rstr != '+')
				ret = 1;
		}
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

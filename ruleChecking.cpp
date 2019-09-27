#include "ExpertSystem.h"
#include <iostream>

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
		return oneCondition2(condition, conclusion);
	else
	{
		ret = severalConditions2(condition);
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

int ExpertSystem::severalConditions2(vector<int> condition)
{
	int		 ret = 0;
	vector<bool> tmpResult(false);
	cout << "severalConditions2  : " << condition.size() << std::endl;

	for (int i = 0; i < condition.size(); i++)
	{
		const char str [] = "+|^";
		const char *rstr;
		rstr = strchr(str, condition[i]);
		printf("rstr %s \n", rstr);
		cout << " condition[i]) : " << char(condition[i]) << std::endl;

		if (rstr != NULL)
		{
			cout << "INININNININstrchr(  : " << char(condition[i]) << std::endl;

			ret = getResult(condition, tmpResult, i);
			if (isupper(char(ret)))
				return ret; // On relance la recherche avec une nouvelle querie 
			else if (ret == -2)
				return -2; // IMPOSSIBLE XOR FALSE AVEC LES 2 CONDITIONS QUI EXISTE..
			else if (ret == -1)
			{
				condition.insert(condition.begin()+(i + 1), 1);
				condition.erase(condition.begin() + (i - 2), condition.begin()+ (i + 1) );
				cout << "INININNININstr   scondition.size()  : " << condition.size() << std::endl;
				if (condition.size() > 1)
					i = 0;
			}
			// else if (i < (condition.size() - 2) && ret == -3 && condition[i] == '|' && condition[i + 1] == '|')
			// 	tmpResult.push_back(false); //quand on trouve une condition ok il faut enlever les 0.. pienso
			// else if (i < (condition.size() - 2) && ret == -3 && condition[i] == '^' && condition[i + 1] == '^')
			// 	tmpResult.push_back(false);
			// else
			// 	tmpResult.push_back(true);
		}
	}
	cout << "ret al fin de several condition : " << ret << std::endl;
	return ret; // Normalement soit -1 soit -3 ||  -1 TRUE -3 FALSE
}

int ExpertSystem::getResult(std::vector<int> condition, std::vector<bool> tmpResult, int i)
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
	{
		return andCondition2(factA, factB, condition, i);
	}
	//else if (condition[i] == '|')
	//{
	//	ret = orCondition2(factA, factB, condition);
	//}
	//else if (condition[i] == '^')
	//{
	//	ret = xorCondition2(factA, factB, condition);
	//}
	return 0;
}

int ExpertSystem::andCondition2(bool a, bool b, vector<int> condition, int i)
{
		cout << "a " << a << std::endl;
		cout << "b " << b << std::endl;

	if (a && b)
	{
		cout << "AND OK" << std::endl;
		return -1;
	}
	else if (!a)
	{
		cout << "AND 1ere condition missing relance pour : " << char(a) << std::endl;
		//faire ici un if condition i-2 nest pas 0 alors cherche sinon -2 impossible
		return condition[i - 2];
	}
	else
	{
		cout << "AND 2ere condition missing relance pour : " << char(b) << std::endl;
		//faire ici un if condition i-2 nest pas 0 alors cherche sinon -2 impossible
		return condition[i - 1];
	}
}


int ExpertSystem::oneCondition2(vector<int> condition, vector<int> conclusion)
{
	int					 i;
	std::set<int>::iterator fact;

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
	return condition[0];
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
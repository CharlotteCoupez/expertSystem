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
			// if (ret == -2)
			// 	return -2; // IMPOSSIBLE XOR FALSE AVEC LES 2 CONDITIONS QUI EXISTE.. a enregistrer dans liste false
			if (ret == -3)
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
			// nb = getNegative(condition,i);  A RRFAIREEEE utilie en fait
			condition.erase(condition.begin() + i - nb, condition.begin() + i + 1 );
			if (condition.size() > 1)
				i = 0;
		}
	}
	//std::cout << "ret al fin de several condition : " << ret << std::endl;
	return ret;
}

int ExpertSystem::getValue(std::vector<int> condition, std::vector<std::vector<int> > *array, int i)
{
	vector<int> tmp;
	tmp.push_back(condition[i - 1]);
	for (int i = 0; i < condition.size(); i++)
	{
		std::cout << "condition1 : " << char(condition[i]) << std::endl;
	}
	if (i - 2 >= 0 && condition[i - 2] == '!') {
		tmp.push_back(-1);
	} else {
		tmp.push_back(1);
	}
	(*array).push_back(tmp);

	return (i - 2 >= 0 && condition[i - 2] == '!' ? i - 2 : i - 1);
}

int ExpertSystem::getNegative(std::vector<int> condition, std::vector<std::vector<int> > *array, int i)
{
	i = getValue(condition, array, i);
	getValue(condition, array, i);
	return 0;
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
	cout << "before segfault" << '\n';
	for (int i = 0; i < array.size(); i++)
	{
		if (array[i][0] < 50)
			std::cout << "array[i][0]: " << array[i][0] << std::endl;
		else
			std::cout << "array[i][0]: " << char(array[i][0]) << std::endl;
		std::cout << "array[i][1]: " << array[i][1] << std::endl;
	}
	if (isupper(array[1][0]))
	{
        retA = find(m_trueFacts.begin(), m_trueFacts.end(), array[1][0]);
		factA = *retA == array[1][0];
	}
	else
		factA = array[1][0];
	// mettre ca dans une fonction
	// retourner fact a ou fact b
	// if find dans true fact ret 1
	// if find dans false fact ret 0
	// else backward

	if (isupper(array[0][0]))
	{
        retB = find(m_trueFacts.begin(), m_trueFacts.end(), array[0][0]);
		factB = *retB == array[0][0];
	}
	else
		factB = array[0][0];
	// test en fonction de a ou b et du negatif

	if (condition[i] == '+')
		return andCondition(factA, factB, array, i);
	else if (condition[i] == '|')
		return orCondition(factA, factB, array, i);
	else if (condition[i] == '^')
		return xorCondition(factA, factB, array, i);
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

	if (a ^ b)
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
	if (a || b)
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
	// else if (array[1][0] != 0)
	// {
	// 	ret = backwardChaining(array[1][0]);  // NEGATIF A FAIRE
	// 	//std::cout << "OR backwardChaining(v ret " << ret << std::endl;
	// 	// if (ret == 0)
	// 	if (ret == 0 && array[0][0] != 0)
	// 	{
	// 		ret = backwardChaining(array[0][0]);  // NEGATIF A FAIRE
 
	// 		//std::cout << "OR backwardChaining ret b " << ret << std::endl;
	// 		if (ret == 0 && array[0][1] == 1) //Querie false
	// 			return -3;
	// 		return -1; // ok on a trouvé
	// 	}
	// 	else if (ret == 1) // si a == 0 et b == 0 on renvoie -3 voir si il y a un autre ou apres sinn on renvera false apres
	// 		return -1;
	// }
	// else if (array[0][0] != 0)
	// {
	// 	ret = backwardChaining(array[0][0]);
	// 	if (ret == 1 && array[0][0] != '!')
	// 		return -1;
	// }
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


	if (a && b)
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

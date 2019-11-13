/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolSystemExpert.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:57:26 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/13 17:06:51 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ExpertSystem.h"

using namespace std;

int		ExpertSystem::find_in_set(int to_compare, std::set<int> list)
{
	std::set<int>::iterator	ret;
	// std::cout << " to_compare : : " << char(to_compare) << std::endl;


	// for (ret = list.begin(); ret != list.end();ret++)
	// {
	// 		std::cout << " ret : : " << char(*ret) << std::endl;

	// }
	for (ret = list.begin(); ret != list.end();ret++)
	{
		if (*ret == to_compare)
			return to_compare;
	}
	// std::cout << " ret fin to_compare : : " << char(to_compare) << std::endl;
	return -1;
}

bool	ExpertSystem::condition(bool a, int neg)
{
	if (a == true && neg == 1)
		return true;
	if (a == true && neg == -1)
		return false;
	if (a == false && neg == 1)
		return false;
	if (a == false && neg == -1)
		return true;
	return false;
}

bool	ExpertSystem::conditionProvenFalse(bool a, int neg)
{
	if (a == true && neg == -1)
		return true;
	if (a == false && neg == 1)
		return true;
	return false;
}

int		ExpertSystem::getFact(int array_value, int neg)
{
	int	ret;
	// std::cout << " array_value : " << char(array_value) << std::endl;
	// std::cout << " array_value : " << array_value << std::endl;

	if (!checking && isupper(char(array_value)))
	{
        // ret = find(m_trueFacts.begin(), m_trueFacts.end(), array_value);
        ret = find_in_set(array_value, m_trueFacts);
		if (ret == array_value && neg == 1)
			return 1;
		else if (ret == array_value && neg == -1)
			return 0;
        ret = find_in_set(array_value, m_falseFacts);
		if (ret == array_value && neg == -1)
			return 1;
		else if (ret == array_value && neg == 1)
			return 0;
		return 2;
	}
	return array_value;
}

int		ExpertSystem::getConditionValue(std::vector<int> condition, std::vector<std::vector<int> > *array, int i)
{
	std::vector<int>	tmp;

	tmp.push_back(condition[i - 1]);
	if (i - 2 >= 0 && condition[i - 2] == '!')
		tmp.push_back(-1);
	else
		tmp.push_back(1);
	(*array).push_back(tmp);
	return (i - 2 >= 0 && condition[i - 2] == '!' ? i - 2 : i - 1);
}

int		ExpertSystem::getNegative(std::vector<int> condition, std::vector<std::vector<int> > *array, int i)
{
	i = getConditionValue(condition, array, i);
	getConditionValue(condition, array, i);
	return 0;
}

int ExpertSystem::checkNextOperator(std::vector<int> condition, size_t j)
{
	for (size_t i = j; i < condition.size(); i++)
	{
		if (condition[i] == '|' || condition[i] == '^')
			return 1;
	}
	return 0;
}


int		ExpertSystem::nbToErase(std::vector<int> condition, int i)
{
	if (condition[i - 2] == '!' && (i < 4 || condition[i - 4] != '!'))
		return 3;
	else if (isupper(condition[i - 2]) && i >= 3 && condition[i - 3] == '!')
		return 3;
	else if (condition[i - 2] == '!' && i >= 4 && condition[i - 4] == '!')
		return 4;
	return 2;
}


void ExpertSystem::printTrueFacts()
{
	std::set<int>::iterator	truef;
	std::set<int>::iterator	falsef;
		
	std::cout << "m_trueFacts.sizeof() : " << m_trueFacts.size() << std::endl;
	std::cout << "m_falseFacts.sizeof() : " << m_falseFacts.size() << std::endl;

	for (truef = m_trueFacts.begin(); truef != m_trueFacts.end(); truef++)
	{
		std::cout << "m_trueFacts[i] : " << char(*truef) << std::endl;
	}
	for (falsef = m_falseFacts.begin(); falsef != m_falseFacts.end(); falsef++)
	{
		std::cout << "m_falseFacts[i] : " << char(*falsef) << std::endl;
	}
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
*/

	// std::cout << "AND a " << a << std::endl;
	// std::cout << "AND b " << b << std::endl;
	//std::cout << "AND array[1][0] " << array[1][1] << std::endl;
	//std::cout << "AND array[1][1] " << array[1][1] << std::endl;
	//std::cout << "AND array[0][0] " << array[0][0] << std::endl;
	//std::cout << "AND array[0][1] " << array[0][1] << std::endl;

    	//std::cout << "XOR a " << a << std::endl;
	//std::cout << "XOR b " << b << std::endl;
	//std::cout << "XOR array[1][0] " << array[1][1] << std::endl;
	//std::cout << "XOR array[1][1] " << array[1][1] << std::endl;
	//std::cout << "XOR array[0][0] " << array[0][0] << std::endl;
	//std::cout << "XOR array[0][1] " << array[0][1] << std::endl;

    	//std::cout << "OR a " << a << std::endl;
	//std::cout << "OR b " << b << std::endl;
	//std::cout << "OR array[1][0] " << array[1][1] << std::endl;
	//std::cout << "OR array[1][1] " << array[1][1] << std::endl;
	//std::cout << "OR array[0][0] " << array[0][0] << std::endl;
	//std::cout << "OR array[0][1] " << array[0][1] << std::endl;
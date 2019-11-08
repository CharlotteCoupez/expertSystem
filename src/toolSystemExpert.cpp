/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolSystemExpert.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:57:26 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/07 16:58:51 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ExpertSystem.h"

using namespace std;


bool	ExpertSystem::condition(bool a, int neg)
{
	if (a == true && neg == 1)
		return 1;
	if (a == true && neg == -1)
		return 0;
	if (a == false && neg == 1)
		return 0;
	if (a == false && neg == -1)
		return 1;
	return false;
}

bool	ExpertSystem::getFact(int array_value)
{
	std::set<int>::iterator	ret;

	if (isupper(char(array_value)))
	{
        ret = find(m_trueFacts.begin(), m_trueFacts.end(), array_value);
		return *ret == array_value;
	}
	return array_value;
}

int		ExpertSystem::getNegative(std::vector<int> condition, std::vector<std::vector<int> > *array, int i)
{
	i = getConditionValue(condition, array, i);
	getConditionValue(condition, array, i);
	return 0;
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


int ExpertSystem::checkNextOperator(std::vector<int> condition, size_t i)
{
	for (int i = 0; i < condition.size(); i++)
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
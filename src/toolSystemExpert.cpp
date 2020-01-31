/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolSystemExpert.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccoupez <ccoupez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 18:57:26 by ccoupez           #+#    #+#             */
/*   Updated: 2019/11/14 12:01:08 by ccoupez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ExpertSystem.h"

using namespace std;

char	ExpertSystem::find_in_set(char to_compare, std::set<char> list)
{
	std::set<char>::iterator	ret;

	for (ret = list.begin(); ret != list.end();ret++)
	{
		if (*ret == to_compare)
			return to_compare;
	}
	return 0;
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

int		ExpertSystem::getFact(int array_value, int neg)
{
	int	ret;

	if (!m_checking && isupper(char(array_value)))
	{
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

int		ExpertSystem::getConditionValue(std::vector<char> condition, std::vector<std::vector<int> > *array, int i)
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

int		ExpertSystem::getNegative(std::vector<char> condition, std::vector<std::vector<int> > *array, int i)
{
	i = getConditionValue(condition, array, i);
	getConditionValue(condition, array, i);
	return 0;
}

int ExpertSystem::checkNextOperator(std::vector<char> condition, size_t j)
{
	for (size_t i = j; i < condition.size(); i++)
	{
		if (condition[i] == '|' || condition[i] == '^')
			return 1;
	}
	return 0;
}

int		ExpertSystem::nbToErase(std::vector<char> condition, int i)
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
	std::set<char>::iterator	truef;
	std::set<char>::iterator	falsef;

	std::cout << "\n\nlen tab TRUE : " << m_trueFacts.size() << std::endl;
	for (truef = m_trueFacts.begin(); truef != m_trueFacts.end(); truef++)
	{
		std::cout << "true Facts: " << *truef << std::endl;
	}
	std::cout << "\nlen tab FALSE: " << m_falseFacts.size() << std::endl;
	for (falsef = m_falseFacts.begin(); falsef != m_falseFacts.end(); falsef++)
	{
		std::cout << "false Facts: " << *falsef << std::endl;
	}
}

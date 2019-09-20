#include "ExpertSystem.h"
#include <iostream>

using namespace std;

int ExpertSystem::checkConditions(Rules rule)
{
    int result;

    if (rule.m_condition.size() == 1)
    {
        result = checkOneCondition(rule.m_condition[0], 0, 0);
        if (result == 0)
        {
            m_trueFacts.insert(rule.m_conculsion[0]);
        }
        else
        {
            return result;
        }

    }
    for (int i = 0; i < rule.m_condition.size() -1; i++)
    {
        cout << "checkConditions rule->m_condition[i]" << rule.m_condition[i] <<  std::endl;
        result = checkOneCondition(rule.m_condition[i], rule.m_condition[i + 1], rule.m_conditionType[i]);
        if (result != 0)
        {
            return result;
        }
    }
    m_trueFacts.insert(rule.m_conculsion[0]);
    return 0;
}

int ExpertSystem::checkOneCondition(char a, char b, char condition)
{
    std::set<int>::iterator retB;
    std::set<int>::iterator retA;

    retA = find(m_trueFacts.begin(), m_trueFacts.end(), a);
    if (condition == 0)
    {
        if (*retA == a)
        {
            cout << "retA == a" << std::endl;
            return 0;
        }
        else
        {
            return a;
        }

    }
    retB = find(m_trueFacts.begin(), m_trueFacts.end(), b);
    if (condition = '+')
    {
        if (*retA == a && *retB == b)
        {
            cout << "CONDITIONS REMPLIES retA == a && retB == b" << std::endl;
            return 0;
        }
        else if (*retA != a)
        {
           cout << "lancer une nouvelle querie pour A" << std::endl;
           return a;
        }
        else if (*retB != b)
        {
            return b;
            cout << "lancer une nouvelle querie pour B" << std::endl;
        }
    }
    else if (condition = '|')  // OR
    {
        if (*retA == a || *retB == b)
        {
            cout << "retA == a || retB == b" << std::endl;
            return true;
         }
    }
    else if (condition = '^') // XOR
    {
        if (*retA == a ^ *retB == b)
        {
         cout << "retA == a ^ retB == b" << std::endl;
         return true;
        }
    }
    return false;
}

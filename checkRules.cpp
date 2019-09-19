#include "ExpertSystem.h"
#include <iostream>

using namespace std;

void ExpertSystem::checkConditions(Rules::Rules rule)
{
    for (int i = 0; i < rule->m_condition.sizeof() -1; i++)
    {
        cout << "checkConditions rule->m_condition[i]" << rule.m_condition[0] <<  std::endl;
        checkOneCondition(rule->m_condition[i], rule->m_condition[i +1], rule->m_conditionType[i])
    }
}

bool ExpertSystem::checkOneCondition(char a, char b, char condition)
{
    // le int neg -> 0 pas de neg 1 le a est neg 2 le best neg 3 les deux sont neg
    std::vector<char>::iterator retA;
    std::vector<char>::iterator retB;
    // std::vector<char>::iterator retNegA;
    // std::vector<char>::iterator retNegB;

    retA = find(m_trueFacts.begin(), m_trueFacts.end(), a);
    retB = find(m_trueFacts.begin(), m_trueFacts.end(), b);
    // retNegA = find(m_trueFacts.begin(), m_trueFacts.end(), a * -1);
    // retNegB = find(m_trueFacts.begin(), m_trueFacts.end(), b * -1);
    if (condition = '+')
    {
        if (retA == a && retB == b)
        {
            cout << "retA == a && retB == b" << std::endl;
            return true;
        }
 
    }
    else if (condition = '|')  // OR
    {
        if (retA == a || retB == b)
        {
         cout << "retA == a || retB == b" << std::endl;
         return true;
         }
    }
    else if (condition = '^') // XOR
    {
        if (retA == a ^ retB == b)
        {
         cout << "retA == a ^ retB == b" << std::endl;
         return true;
        }
    }
    return false;
}
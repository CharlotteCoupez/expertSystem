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
    if (condition.size() == 1)
        return oneCondition2(condition, conclusion);
    else
        return severalConditions2(condition, conclusion)
    
}

int ExpertSystem::severalConditions2(vector<int> condition, vector<int> conclusion)
{
    int ret;

    for (int i = 0; i < condition.size() -1; i++)
    {
        if (strchr("+|^", condition[i]))
        {
            ret = getResult();
        }
    }
}

int ExpertSystem::oneCondition2(vector<int> condition, vector<int> conclusion)
{
    int                     i;
    std::set<int>::iterator fact;

    i = 0;
    fact = find(m_trueFacts.begin(), m_trueFacts.end(), condition[0]);
    if (*fact == condition[0])
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
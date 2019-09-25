#include "ExpertSystem.h"
#include <iostream>

using namespace std;

int ExpertSystem::checkConditions(Rules rule)
{
    int result;
    std::vector<int> allResult;

    if (rule.m_condition.size() == 1)
    {
        return oneCondition(rule.m_condition[0], rule);
    }
    for (int i = 0; i < rule.m_condition.size() -1; i++)
    {
        cout << "checkConditions rule->m_condition[i]" << char(rule.m_condition[i]) <<  std::endl;

        if (i == 0)
            result = checkOneCondition(rule.m_condition[i], rule.m_condition[i + 1], rule.m_conditionType[i]);
        else
            result = checkOneCondition(true, rule.m_condition[i + 1], rule.m_conditionType[i]);
        cout << "apres check one result " << result << std::endl;
        cout << "apres check one char(result) " << char(result) << std::endl;
        if (result == -2)
        {
            cout << "sortie -2 xor" << std::endl;
            return -2;
        }
        else if (result != -1 && result != -3)
        {
            return result;
        }
        cout << "result" << result << std::endl;
        cout << "rule.m_condition[i]" << char(rule.m_condition[i]) << std::endl;
        cout << "rule.m_condition[i + 1]" << char(rule.m_condition[i + 1]) << std::endl;
    }
    if (result == -1)
    {
        m_trueFacts.insert(rule.m_conculsion[0]);
        return -1;
    }
    else
    {
        // on avait des ou et on en a trouvé aucun
        // -3 on continue de chercher
        return -3;
    }

}

int ExpertSystem::checkOneCondition(int a, int b, char condition)
{
    int                     ret;
    std::set<int>::iterator retB;
    std::set<int>::iterator retA;
    bool                    boolA;
    bool                    boolB;
    cout << "condition in check ONE" << condition << std::endl;

    if (a != true)
    {
         retA = find(m_trueFacts.begin(), m_trueFacts.end(), a);
         boolA = a == *retA;
    }
    else
    {
        boolA == true;
    }
    retB = find(m_trueFacts.begin(), m_trueFacts.end(), b);
    boolB = b == *retB;
    cout << "boolA" << boolA << std::endl;
    cout << "boolB" << boolB << std::endl;

    if (condition == '+')
    {
        return andCondition(a, b, boolA, boolB);
    }
    else if (condition == '|')
    {
        return orCondition(a, b, boolA, boolB);
    }
    else if (condition == '^')
    {
        return xOrCondition(a, b, boolA, boolB);
    }
    return -1;
}

int ExpertSystem::xOrCondition(int a, int b, bool boolA, bool boolB)
{
    // cout <<"HELLLO XOR" << std::endl;
    // if (*retA == a ^ *retB == b)
    // {
    //     cout << "condition remplie retA == a ^ retB == b" << std::endl;
    //     return -1;
    // }
    // else if (*retA == a && *retB == b)
    // {
    //     cout << "XO R NO POSSIBLE LES DEUX EXISTE" << std::endl;
    //     // les deux existes donc cette solution ne pourra jamais etre true
    //     return -2;
    // }
    // else
    //     return -2;
    // pour ce else chercher a prouver les deux si au bout de la recherche
    // on en a 1 sur deux cest ok sinon cest mort
    return 1;
}

int ExpertSystem::orCondition(int a, int b, bool boolA, bool boolB)
{
    int ret;

    cout << "3OR A : " << char(a) << std::endl;
    cout << "3OR b : " << char(b) << std::endl;
    if (boolA || boolB)
    {
        cout << "retA == a || retB == b" << std::endl;
        return -1;
    }
    cout << "BACKCHAIN IN CHECK RULE" << std::endl;
    ret = backwardChaining(a);
    cout << "BACKCHAIN IN CHECK RULE A ret : " << ret << std::endl;
    if (ret == -1) // on sait que la solution est false on cherche pas plus
    {
        // on chercher si b existe
        cout << "IN CHECK RULE pour B" << std::endl;
        ret = backwardChaining(b);
        cout << "BACKCHAIN IN CHECK RULE B ret : " << ret << std::endl;
        if (ret == -1)
            return -3;
    }
    return -1;
}

int ExpertSystem::andCondition(int a, int b, bool boolA, bool boolB)
{
    int                     ret;

    if (boolA && boolB)
    {
        cout << "CONDITIONS REMPLIES retA == a && retB == b" << std::endl;
        return -1;
    }
    else if (!boolA)
    {
        cout << "lancer une nouvelle querie pour : " << char(a) << std::endl;
        return a;
    }
    else if (!boolB)
    {
        return b;
        cout << "lancer une nouvelle querie pour : " << char(b) << std::endl;
    }
}

int ExpertSystem::oneCondition(int a, Rules rule)
{
    std::set<int>::iterator retA;

    retA = find(m_trueFacts.begin(), m_trueFacts.end(), a);
    if (*retA == a)
    {
        m_trueFacts.insert(rule.m_conculsion[0]);
        return -1;
    }
    return a;
}

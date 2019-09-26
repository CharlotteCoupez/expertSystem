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
    result = severalConditions(rule.m_condition, rule.m_conditionType);
    if (result == -2)
    {
        cout << "sortie -2 xor" << std::endl;
        return -2;
    }
    else if (result != -1 && result != -3)
    {
        return result;
    }
    if (result == -1)
    {
        m_trueFacts.insert(rule.m_conclusion[0]);
        return -1;
    }
    else
    {
        // on avait des ou et on en a trouvé aucun
        // -3 on continue de chercher
        return -3;
    }

}

void test(std::vector<int> m_condition)
{
	std::cout << "--m_condition.size() : " << m_condition.size() << std::endl;

    for (int i = 0; i < m_condition.size(); i++)
	{
		cout << "-----char(m_conditionType[i] : " << char(m_condition[i]) << std::endl;
		std::cout << "---------m_conditionType[i] : " << m_condition[i] << std::endl;
	}

}
int ExpertSystem::severalConditions(std::vector<int> m_condition, std::vector<char> m_conditionType)
{
    int result;
    int firstArg;
    std::set<int>::iterator retB;
    std::set<int>::iterator retA;
    bool                    boolA;
    bool                    boolB;

    result = 0;
    for (int i = 0; i < m_condition.size() -1; i++)
    {
        //if (m_condition[i] == 40 || m_condition[i + 1] == 40) // si on a une parenthese ?
        //{
        //    cout << "P------ARENTHESE" <<  std::endl;
        //    std::vector<int> fooo = std::vector<int>(m_condition.begin() + i, m_condition.end());
        //    test(fooo);
        //    // while (m_condition[i] != 40 || m_condition[i] !=41)
        //    //     i++;
        //}
        retA = find(m_trueFacts.begin(), m_trueFacts.end(), m_condition[i]);
        retB = find(m_trueFacts.begin(), m_trueFacts.end(), m_condition[i + 1]);

        cout << "RESULT AVANT " << result << std::endl;
        cout << "RESULT AVANT CHAR " << char(result) << std::endl;
        cout << "m_conditionType[i]" << m_conditionType[i] << std::endl;
        cout << "iiiiii" << i << std::endl;
        
        if (result == -1 && m_conditionType[i - 1] == '|')
            boolA = true;
        else
            boolA = m_condition[i] == *retA;
        boolB = m_condition[i + 1] == *retB;

        cout << "checkConditions rule->m_condition[i]" << char(m_condition[i]) <<  std::endl;
        cout << "checkConditions rule->m_condition[i +1]" << char(m_condition[i +1]) <<  std::endl;
        cout << "boolA" << boolA <<  std::endl;
        cout << "boolB" << boolB <<  std::endl;
        cout << "P------m_conditionType[i]" << m_conditionType[i] << std::endl;

        result = checkTheCondition( m_condition[i], m_condition[i + 1], boolA, boolB, m_conditionType[i]);

        cout << "RESULT APRES " << result << std::endl;
        cout << "RESULT APRES CHAR " << char(result) << std::endl;

        if (result == -2)
        {
            cout << "AA sortie -2 xor" << std::endl;
            return -2;
        }
        else if (result != -1 && result != -3)
        {
            return result;
        }
    }
    cout << "SORTIE DE BOUCLE RESULT" << result << std::endl;
    if (result == -3)
        return -2;
    return -1;
}

int ExpertSystem::checkTheCondition(int a, int b, bool boolA, bool boolB, char condition)
{
    cout << "condition in check ONE" << condition << std::endl;
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

int ExpertSystem::oneCondition(int a, Rules rule)
{
    std::set<int>::iterator retA;

    retA = find(m_trueFacts.begin(), m_trueFacts.end(), a);
    if (*retA == a)
    {
        m_trueFacts.insert(rule.m_conclusion[0]);
        return -1;
    }
    return a;
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
    if (ret == -1) 
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
        cout << "AND lancer une nouvelle querie pour : " << char(a) << std::endl;
        return a;
    }
    else
    {
        return b;
        cout << "AND lancer une nouvelle querie pour : " << char(b) << std::endl;
    }
}


#ifndef RULES_H
#define RULES_H

#include <stdlib.h>
#include <cctype>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <list>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctype.h>
#include <typeinfo>


# define RULE_ERROR -1
# define RULE_OK -2
class Rules
{
	public:
		Rules();
		Rules(std::string rule);
		std::vector<int>	m_condition;
		std::vector<int>	m_conclusion;
		std::vector<int>	m_facts;
		int					id;
		int					status;
		void				parseRule(std::string rule, std::vector<char> values, std::vector<char> type);
		void				printValues();
		void				printFacts();
		int					getImpORif(std::string rule, int i);

	private:
		std::vector<char>	m_conditionType;
		std::vector<char>	m_conclusionType;
		std::vector<char>	m_polonaise;
		std::vector<char>	m_polonaiseTmp;
		char				impORif;
  		int					check_format(std::string rule, int i, int bracket);
		void				putInCondition();
		void				putInConclusion();
		int					notationPolonaise(std::string rule, int type);
		bool				isOperator(char c);
		bool				isRelationOp(char c);
		bool				opPriorities(char c, char op);
};

#endif

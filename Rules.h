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
		std::vector<char>	m_condition;
		std::vector<char>	m_conclusion;
		char				impORif;
		std::vector<char>	m_facts;
		int					id;
		int					status;
		void				parseRule(std::string rule, std::vector<char> values, std::vector<char> type);
		void				printValues();
		void				printFacts();

	private:
		std::vector<char>	m_polonaise;
		std::vector<char>	m_polonaiseTmp;
  		int					check_format(std::string rule, size_t i, int bracket);
		void				putInCondition();
		void				putInConclusion();
		int					notationPolonaise(std::string rule, size_t i);
		bool				isOperator(char c);
		bool				isRelationOp(char c);
		bool				opPriorities(char c, char op);
		int					getImpORif(std::string rule, size_t i);
};

#endif

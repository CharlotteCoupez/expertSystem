#ifndef DEF_EXPERTSYSTEM
#define DEF_EXPERTSYSTEM

#include <string>
#include <vector>
#include <fstream>
#include "Rules.h"
#include <list>
#include <set>

class ExpertSystem
{
  public:
	ExpertSystem();					//Constructeur
	ExpertSystem(std::string argv); // autre constructeur avec un parametre
	std::list<Rules> m_listRules;   //utiliser pushback pour add object a la liste
	std::set<int> m_allFacts;
	std::set<int> m_trueFacts;
	std::vector<int> m_queries;
	int backwardChaining(int querie);
	void analyseQuerie();

	int severalConditions(std::vector<int> m_condition, std::vector<char> m_conditionType);
	int checkTheCondition(int a, int b, bool boolA, bool boolB, char condition);
	int ruleChecking(std::vector<int> condition, std::vector<int> conclusion);

	int severalConditions(std::vector<int> condition);
	int getResult(std::vector<int> condition, int i);
	int andCondition(bool a, bool b, std::vector<int> condition, int i);
	int orCondition(bool a, bool b, std::vector<int> condition, int i);
	int xorCondition(bool a, bool b, std::vector<int> condition, int i);
	int oneCondition(std::vector<int> condition, std::vector<int> conclusion);
	int checkNextOperator(std::vector<int> condition, int i);

	int coherentRule();
	int checkCoherence(std::vector<int> path, int fact);
	void printTrueFacts();

  private:

	std::vector<int> m_initialFacts;
	void createFacts();
	void createBaseRules(std::string ligne, int ruleId);
	void getInitialeFacts(std::string ligne);
	void getQueries(std::string ligne);
	std::fstream fs;
};

#endif

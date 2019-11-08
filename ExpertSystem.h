#ifndef DEF_EXPERTSYSTEM
#define DEF_EXPERTSYSTEM

#include "Rules.h"

# define PROVEN -1
# define NOT_PROVEN -3
class ExpertSystem
{
  public:
	ExpertSystem();					//Constructeur
	ExpertSystem(std::string argv); // autre constructeur avec un parametre
	std::list<Rules> m_listRules;   //utiliser pushback pour add object a la liste
	std::set<int> m_allFacts;
	std::set<int> m_trueFacts;
	std::set<int> m_falseFacts;
	std::vector<int> m_queries;
	bool	backwardChaining(int querie);
	void	analyseQuerie();

	int		severalConditions(std::vector<int> m_condition, std::vector<char> m_conditionType);
	int		checkTheCondition(int a, int b, bool boolA, bool boolB, char condition);
	int		ruleChecking(std::vector<int> condition);

	int		severalConditions(std::vector<int> condition);
	int		getNegative(std::vector<int> condition, std::vector<std::vector<int> > *array, int i);
	int		getResult(std::vector<int> condition, size_t i);
	int		andCondition(bool a, bool b, std::vector<std::vector<int> > array);
	int		orCondition(bool a, bool b, std::vector<std::vector<int> > array);
	int		xorCondition(bool a, bool b, std::vector<std::vector<int> > array);
	int		oneCondition(std::vector<int> condition);
	int		checkNextOperator(std::vector<int> condition, size_t i);

	bool	coherentRule();
	bool	coherence();
	bool	checkCoherence(std::vector<int> path, int fact);
	void	printTrueFacts();
	void	print();

  private:

	std::vector<int> m_initialFacts;
	std::fstream fs;
	void	createFacts();
	void	createBaseRules(std::string ligne, int ruleId);
	void	getInitialeFacts(std::string ligne);
	void	getQueries(std::string ligne);
	int		getConditionValue(std::vector<int> condition, std::vector<std::vector<int> > *array, int i);
	bool	getFact(int array_value);
	void	fillList(bool type, std::vector<int> conclusion);
	bool	condition(bool a, int neg);
	int		nbToErase(std::vector<int> condition, int i);
};

#endif

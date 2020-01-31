#ifndef DEF_EXPERTSYSTEM
#define DEF_EXPERTSYSTEM

#include "Rules.h"

# define PROVEN -1
# define PROVEN_FALSE -2
# define NOT_PROVEN -3
# define UNDIFINED -4

class ExpertSystem
{
  public:
	ExpertSystem();
	ExpertSystem(std::string argv);

	void	printTrueFacts();

  private:

	std::list<Rules>	m_listRules;
	std::set<char>		m_allFacts;
	std::set<char>		m_trueFacts;
	std::set<char>		m_falseFacts;
	std::vector<char>	m_queries;
	bool				m_checking;
	std::vector<char>	m_initialFacts;
	std::fstream		fs;

	void	createFacts();
	void	createBaseRules(std::string ligne, int ruleId);
	void	getInitialeFacts(std::string ligne);
	void	getQueries(std::string ligne);
	int		getConditionValue(std::vector<char> condition, std::vector<std::vector<int> > *array, int i);
	int		getFact(int array_value, int neg);

	bool	ruleNotLinked();
	bool	checkCoherence(std::vector<char> path, char fact);
	bool	checkFacts();
	bool	ruleNotIncoherented();
	bool	checkAllCoherence();
	void	fillList(bool type, std::vector<char> conclusion);
	void	fillTrueFasleFacts(Rules rule);
	char	find_in_set(char to_compare, std::set<char> list);

	bool	checkKnowFacts(char querie);
	void	analyseQuerie();
	bool	backwardChaining(char querie);
	bool	lastChecking(char querie);
	int		matchQuery(std::list<Rules>::iterator itL, char querie);

	int		ruleChecking(std::vector<char> condition);
	int		oneCondition(std::vector<char> condition);
	int		severalConditions(std::vector<char> condition);
	int		getNegative(std::vector<char> condition, std::vector<std::vector<int> > *array, int i);
	int		getResult(std::vector<char> condition, size_t i);
	int		checkNextOperator(std::vector<char> condition, size_t i);
	int		nbToErase(std::vector<char> condition, int i);

	int		andCondition(int a, int b, std::vector<std::vector<int> > array);
	int		orCondition(int a, int b, std::vector<std::vector<int> > array);
	int		xorCondition(int a, int b, std::vector<std::vector<int> > array);
	bool	condition(bool a, int neg);

};

#endif

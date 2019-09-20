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
		ExpertSystem(std::string argv);	// autre constructeur avec un parametre
		std::list<Rules> m_listRules; //utiliser pushback pour add object a la liste
		std::set<int> m_allFacts;
		std::vector<int> m_trueFacts;
		void analyseQuerie(char querie);
		int checkConditions(Rules rule);
		int checkOneCondition(char a, char b, char condition);
		void backwardChaining(int querie);
		void analyseQuerie();
	  	std::vector<int> m_queries;
		void printTrueFacts();

	  private:
		// Create an empty list of ints
		// std::vector<Rules> m_listRules; ??
	  	std::vector<int> m_initialFacts;
	  	void createFacts();
	  	void createBaseRules(std::string ligne, int ruleId);
	  	void getInitialeFacts(std::string ligne);
	  	void getQueries(std::string ligne);
	  	std::fstream fs;
};

#endif

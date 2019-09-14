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
		std::vector<int> m_factsStatus;

	  private:
		// Create an empty list of ints
		// std::vector<Rules> m_listRules; ??
	  std::vector<char> m_initialFacts;
	  std::vector<char> m_queries;
	  void createFacts();
	  void createBaseRules(std::string ligne);
	  void getInitialeFacts(std::string ligne);
	  void getQueries(std::string ligne);
	  std::fstream fs;
};

#endif

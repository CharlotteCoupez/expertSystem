#ifndef DEF_EXPERTSYSTEM
#define DEF_EXPERTSYSTEM

#include <string>
#include <vector>
#include <fstream>
#include "Rules.h"
#include <list>

class ExpertSystem
{
  public:

		ExpertSystem();					//Constructeur
		ExpertSystem(std::string argv);	// autre constructeur avec un parametre

	private:
		// Create an empty list of ints
		std::list<Rules> m_listRules; //utiliser pushback pour add object a la liste
		// std::vector<Rules> m_listRules; ??
		std::vector<char> m_facts; // toute les variable a true (peut augmenter pendant l'analyse) donc si tu es dans listfacts tu es true else tu es false
		std::vector<char> m_queries;
		void createBaseRules(std::string ligne);
		void createBaseFacts(std::string ligne);
		void getQueries(std::string ligne);
		std::fstream fs;
};

#endif

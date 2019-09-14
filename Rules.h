#ifndef DEF_RULES

#define DEF_RULES

#include <string>
#include <vector>
#include <fstream>
// #include "expertSystem.h"

class Rules
{
  public:
	Rules();			   //Constructeur
	Rules(std::string rule); // autre constructeur avec un parametre
	int parseRule(std::string rule, std::vector<char> values, std::vector<char> type);
	void printValues();
	void printFacts();
	std::vector<char> m_facts;			// toute les variable a true (peut augmenter pendant l'analyse)
	std::vector<char> m_conditionType; // multiple choice : A N O X

  private:
	// condition : and, not, or, xor;
		std::vector<char> m_condition;			// toute les variable a true (peut augmenter pendant l'analyse)
		std::vector<char> m_conclusionType; // multiple choice : I O
		std::vector<char> m_conculsion;			// toute les variable a true (peut augmenter pendant l'analyse)
		char impORif;

		// resultats: implies, ifAndOnlyIf;

};

#endif

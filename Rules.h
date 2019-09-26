#ifndef DEF_RULES

#define DEF_RULES

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
// #include "expertSystem.h"

class Rules
{
  public:
		Rules();			   //Constructeur
		Rules(std::string rule); // autre constructeur avec un parametre
		void parseRule(std::string rule, std::vector<char> values, std::vector<char> type);
		void printValues();
		void printFacts();
		int getNumber(std::string rule, int type, int i);
		int getImpORif(std::string rule, int i);
		int getOperator(std::string rule, int type, int i);
		int notationPolonaise(std::string rule, int type);
		
		std::vector<int>	m_facts;			// toute les variable a true (peut augmenter pendant l'analyse)
		std::vector<char>	m_conditionType; // multiple choice : A N O X
		std::vector<int>	m_condition;			// toute les variable a true (peut augmenter pendant l'analyse)
		std::vector<char>	m_conclusionType; // multiple choice : I O
		std::vector<int>	m_conclusion;
		std::vector<char>	m_polonaise;			// toute les variable a true (peut augmenter pendant l'analyse)
		std::vector<char>	m_polonaiseTmp;			// toute les variable a true (peut augmenter pendant l'analyse)
		char				impORif;
		int					id;
		int					status; // pour savoir i la regle et au norme ou nn 

  private:
		// resultats: implies, ifAndOnlyIf;

};

#endif

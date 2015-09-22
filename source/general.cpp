#include <limits.h>
#include "Language.h"
#include <iostream>
#include <string>
void warn(const char * message, const char * fallback){
	std::cout << "Warning: " << std::endl;
	std::cout << message << std::endl << fallback << std::endl;
}

#define PO10_LIMIT (INT_MAX/10)

int nDigits(int i)
{
  int n,po10;

  if (i < 0) i = -i;
  n=1;
  po10=10;
  while(i>=po10)
  {
    n++;
    if (po10 > PO10_LIMIT) break;
    po10*=10;
  }
  return n;
}

void printNoun(std::string name, Noun* n)
{
#ifdef DEBUG
/*	std::cout << name << "->id = " << n->id << std::endl;
	std::cout << name << "->num = " << n->num << std::endl;
	std::cout << name << "->typ = " << n->typ << std::endl;
	std::cout << name << "->plural = " << n->plural << std::endl;
	std::cout << name << "->reflex = " << n->reflex << std::endl;
	std::cout << name << "->usegenitive = " << n->reflex << std::endl;
	std::string value = "NULL";
	if (n->genitivenoun!=NULL)
		value = "DATA";
	std::cout << name << "->genitivenoun = " << value << std::endl;
	std::cout << name << "->prepos = " << n->prepos << std::endl;
	for (int i = 0; i < 16; ++i)
		std::cout << name << "->adj[" << i << "] = " << n->adj[i] << std::endl;
	std::cout << name << "->useRClause = " << n->useRClause << std::endl;
	std::cout << name << "->rClauseObj = " << n->rClauseObj << std::endl;
	std::cout << name << "->rClauseEssential = " << n->rClauseEssential << std::endl;
	std::cout << name << "->data = " << n->data << std::endl;*/
#endif
}

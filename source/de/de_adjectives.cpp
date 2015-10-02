#include "../settings.h"
#include "de.h"
#include <string>
#include <iostream>
#include <fstream>

const std::string de::AdjectiveEndings[3][4][4] = 
{
	{ //Strong inflection (no article)
		{"er","e" ,"es","e" },
		{"en","e" ,"es","e" },
		{"em","er","em","en"},
		{"en","er","en","er"}
	},
	{ //Weak inflection (definite articles, "der" words)
		{"e" ,"e" ,"e" ,"en"},
		{"en","e" ,"e" ,"en"},
		{"en","en","en","en"},
		{"en","en","en","en"}
	},	
	{ //Mixed inflection other articles
		{"er","e" ,"es","en"},
		{"en","e" ,"es","en"},
		{"en","en","en","en"},
		{"en","en","en","en"}
	}
};

std::string de::GetAdjective(Noun& n, int AdjectiveNum)
{
	int NounType = 'z';
	if (n.ID > 0)
		NounType = GetNounType(n);
	
	int Gender = 0;
	if (NounType == 'f')
		Gender = 1;
	else if (NounType == 'n')
		Gender = 2;
	if (n.IsPlural)
		Gender = 3;
	
	//Default mixed inflection
	int InflectionType = 2;
	
	//If definite article or "der" word (who named them 'der' words...), use weak inflection
	if (n.ArticleType == -1 || n.ArticleType == 11)
		InflectionType = 1;
	//If no article, use strong inflection
	else if (n.ArticleType == 0)
		InflectionType = 0;
	//If no preceeding noun, use no inflection
	if (n.ID <= 0 || n.ID == 14)
		InflectionType = -1;
	
	std::ifstream is(DICTIONARY DE_FOLDER "adjectives.txt");
	if (GotoLine(is,AdjectiveNum))
	{
		is.close();
		return "";
	}
	int Data = is.get();
	if (GotoSegment(is,1))
	{
		is.close();
		return "";
	}
	std::string Adjective = GetSegment(is);
	is.close();
	
	//If a specific adjective does not require an ending, don't add one
	if (Data == '1')
		InflectionType = -1;
	
	if (InflectionType >= 0)
	{
		Adjective += AdjectiveEndings[InflectionType][n.Data][Gender];
	}
	
	return Adjective;
}
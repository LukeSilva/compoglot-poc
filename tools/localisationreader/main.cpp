#include <iostream>
#include <string>

#include "DE.h"
#include "EN.h"


const char** loadedLanguageTags;
const char** loadedLanguageValues;
int 	loadedLanguageNum;

std::string getLocalisedString(std::string tag)
{
	for (int i = 0; i <= loadedLanguageNum; ++i)
	{
		if (tag.compare(loadedLanguageTags[i])==0)
			return loadedLanguageValues[i];
	}
	return tag;
}

void printStuff()
{
	std::cout << "Selected Language " << getLocalisedString("locale") << std::endl;
	std::cout << "Apple = " << getLocalisedString("apple") << std::endl;
	std::cout << "Table = " << getLocalisedString("table") << std::endl;
	std::cout << "Unknown tag = " << getLocalisedString("unknown-tag") << std::endl;
}

int main()
{
	loadedLanguageTags = EN_tags;
	loadedLanguageValues = EN_values;
	loadedLanguageNum = EN_num;
	printStuff();
	loadedLanguageTags = DE_tags;
	loadedLanguageValues = DE_values;
	loadedLanguageNum = DE_num;
	printStuff();
}


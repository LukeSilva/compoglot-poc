#include "../settings.h"
#include "en.h"
#include <string>
#include <iostream>
#include <fstream>

std::string en_Articles[] = {"a", "the", "", "my", "your", "his", "her", "its", "our", "your", "their", "your", "a lot of ","this"};

std::string en::GetArticle(Noun* NounObj,bool NextLetterIsVowel)
{
#ifdef DEBUG
	std::cout << "[EN] GetArticle(Noun* NounObj,bool NextLetterIsVowel = " << NextLetterIsVowel << " )" << std::endl;
#endif
	if (NounObj->ArticleType < -2 || NounObj->ArticleType > 11) return "";
	std::string Article = en_Articles[NounObj->ArticleType+2];
	if (NextLetterIsVowel && NounObj->ArticleType == -2)
		Article+="n";
	return Article;
}
